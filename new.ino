#include <SoftwareSerial.h>
#include <DHT.h>

/* ======== BLUETOOTH ======== */
SoftwareSerial BT(10, 11); // RX, TX

/* ======== ULTRASONIC ======== */
#define TRIG_PIN  12
#define ECHO_PIN  13

/* ======== MQ SENSOR ======== */
#define MQ2_PIN   A0

/* ======== LIGHT SENSOR ======== */
#define LDR_PIN   A1

/* ======== DHT SENSOR ======== */
#define DHTPIN    2
#define DHTTYPE   DHT22

DHT dht(DHTPIN, DHTTYPE);

/* ======== MOTOR DRIVER ======== */
#define ENA  3
#define ENB  9

#define IN1  4
#define IN2  5
#define IN3  6
#define IN4  7

#define MOTOR_SPEED 170

/* ======== LED ======== */
#define LED_PIN 8

/* ======== THRESHOLDS ======== */
#define LIGHT_LOW_THRESHOLD   800
#define LIGHT_HIGH_THRESHOLD  100
#define GAS_THRESHOLD         400
#define TEMP_THRESHOLD        45

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(MQ2_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(LED_PIN, OUTPUT);   // LED setup

  dht.begin();

  BT.println("Smart AI Robot Ready 🚀");
}

void loop() {

  long distance = getDistance();
  int gasValue = analogRead(MQ2_PIN);
  int lightValue = analogRead(LDR_PIN);
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
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void turnRight() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

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
