#include <Servo.h>
#include <SoftwareSerial.h>

// Bluetooth: RX (D10), TX (D11)
SoftwareSerial BT(10, 11); // RX, TX

// Motor pins
const int IN1 = 2;
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5;

// Relay pin
const int relayPin = 8;

// Servo pin
const int servoPin = 9;

Servo seedValve;

void setup() {
  // Motor setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Relay setup
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Pump OFF

  // Servo setup
  seedValve.attach(servoPin);
  seedValve.write(0); // Closed position

  // Serial monitor
  Serial.begin(9600);
  Serial.println("Serial monitor ready.");

  // Bluetooth
  BT.begin(9600);
  Serial.println("Bluetooth ready on SoftwareSerial. Awaiting commands...");
}

void loop() {
  if (BT.available()) {
    char cmd = BT.read();

    // Log command
    Serial.print("Received Bluetooth command: ");
    Serial.println(cmd);

    switch (cmd) {
      case 'F': moveForward(); Serial.println("Action: Move Forward"); break;
      case 'B': moveBackward(); Serial.println("Action: Move Backward"); break;
      case 'L': turnLeft(); Serial.println("Action: Turn Left"); break;
      case 'R': turnRight(); Serial.println("Action: Turn Right"); break;
      case 'S': stopMotors(); Serial.println("Action: Stop"); break;

      case 'O': seedValve.write(120); Serial.println("Action: Open Seed Valve (40°)"); break;
      case 'C': seedValve.write(0);  Serial.println("Action: Close Seed Valve (0°)"); break;

      case 'W': digitalWrite(relayPin, HIGH); Serial.println("Action: Water Pump ON"); break;
      case 'w': digitalWrite(relayPin, LOW);  Serial.println("Action: Water Pump OFF"); break;

      default: Serial.println("Warning: Unknown command"); break;
    }
  }
}

// Movement functions
void moveForward() {
  stopMotors();
  delay(200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  stopMotors();
  delay(200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  stopMotors();
  delay(200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  stopMotors();
  delay(200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
