#include <DHT.h>

/* ======== BLUETOOTH (external HC-05/HC-06 on UART2) ======== */
// SoftwareSerial is not needed on ESP32, it has hardware UARTs
#define BT_RX 16   // ESP32 RX2  <- HC-05 TX
#define BT_TX 17   // ESP32 TX2  -> HC-05 RX
HardwareSerial BT(2);

/* ======== ULTRASONIC ======== */
#define TRIG_PIN  5
#define ECHO_PIN  18   // use a voltage divider (HC-SR04 echo is 5V)

/* ======== MQ SENSOR ======== */
#define MQ2_PIN   34   // ADC1, input only (use a divider if module output is 5V)

/* ======== LIGHT SENSOR ======== */
#define LDR_PIN   35   // ADC1, input only

/* ======== DHT SENSOR ======== */
#define DHTPIN    4
#define DHTTYPE   DHT22

DHT dht(DHTPIN, DHTTYPE);

/* ======== MOTOR DRIVER ======== */
#define ENA  25
#define ENB  26

#define IN1  27
#define IN2  14
#define IN3  33
#define IN4  32

#define MOTOR_SPEED 170

/* ======== LED ======== */
#define LED_PIN 23

/* ======== THRESHOLDS ======== */
#define LIGHT_LOW_THRESHOLD   800
#define LIGHT_HIGH_THRESHOLD  100
#define GAS_THRESHOLD         400
#define TEMP_THRESHOLD        45

/* ======== PWM HELPER (works on ESP32 core 2.x and 3.x) ======== */
#define PWM_FREQ 5000
#define PWM_RES  8      // 8-bit, 0-255 like Arduino analogWrite
#define CH_A 0
#define CH_B 1

void pwmSetup() {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcAttach(ENA, PWM_FREQ, PWM_RES);
  ledcAttach(ENB, PWM_FREQ, PWM_RES);
#else
  ledcSetup(CH_A, PWM_FREQ, PWM_RES);
  ledcSetup(CH_B, PWM_FREQ, PWM_RES);
  ledcAttachPin(ENA, CH_A);
  ledcAttachPin(ENB, CH_B);
#endif
}

void pwmWriteMotors(int a, int b) {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcWrite(ENA, a);
  ledcWrite(ENB, b);
#else
  ledcWrite(CH_A, a);
  ledcWrite(CH_B, b);
#endif
}

/* ======== ADC HELPER ======== */
// ESP32 ADC is 12-bit (0-4095). Shift to 10-bit (0-1023)
// so the original thresholds still work unchanged.
int readADC10(int pin) {
  return analogRead(pin) >> 2;
}

void setup() {
  Serial.begin(9600);
  BT.begin(9600, SERIAL_8N1, BT_RX, BT_TX);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(MQ2_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pwmSetup();

  pinMode(LED_PIN, OUTPUT);   // LED setup

  dht.begin();

  BT.println("Smart AI Robot Ready 🚀");
}

void loop() {

  long distance = getDistance();
  int gasValue = readADC10(MQ2_PIN);
  int lightValue = readADC10(LDR_PIN);
  float temp = dht.readTemperature();

  if (isnan(temp)) temp = 0;

  /* ======== OBSTACLE AVOIDANCE ======== */
  if (distance > 20 || distance == -1) {
    moveForward();
  } else {
    stopMotors();
    delay(300);
    turnRight();
    delay(500);
  }

  /* ======== ANOMALY DETECTION ======== */
  String anomaly = "NORMAL";

  // Light anomaly + LED control
  if (lightValue > LIGHT_LOW_THRESHOLD) {
    anomaly = "LOW LIGHT ⚠️";
    digitalWrite(LED_PIN, HIGH);   // LED ON
  } 
  else if (lightValue < LIGHT_HIGH_THRESHOLD) {
    anomaly = "HIGH LIGHT ⚠️";
    digitalWrite(LED_PIN, LOW);    // LED OFF
  }
  else {
    digitalWrite(LED_PIN, LOW);    // Normal → LED OFF
  }

  // Gas anomaly (HIGH PRIORITY)
  if (gasValue > GAS_THRESHOLD) {
    anomaly = "GAS LEAK 🚨";
  }

  // Temperature anomaly
  if (temp > TEMP_THRESHOLD) {
    anomaly = "HIGH TEMP 🔥";
  }

  /* ======== SEND DATA ======== */
  BT.print("Dist: ");
  BT.print(distance);
  BT.print(" cm | Gas: ");
  BT.print(gasValue);
  BT.print(" | Light: ");
  BT.print(lightValue);
  BT.print(" | Temp: ");
  BT.print(temp);
  BT.print(" C | Status: ");
  BT.println(anomaly);

  delay(500);
}

/* ======== MOTOR FUNCTIONS ======== */

void moveForward() {
  pwmWriteMotors(MOTOR_SPEED, MOTOR_SPEED);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  pwmWriteMotors(0, 0);
}

void turnRight() {
  pwmWriteMotors(MOTOR_SPEED, MOTOR_SPEED);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  pwmWriteMotors(MOTOR_SPEED, MOTOR_SPEED);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

/* ======== ULTRASONIC FUNCTION ======== */
long getDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) return -1;

  return duration * 0.034 / 2;
}
