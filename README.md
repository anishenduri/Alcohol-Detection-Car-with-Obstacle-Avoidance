# Alcohol Detection & Obstacle Avoidance Car 🚫🛑

This Arduino-based smart vehicle stops the engine if alcohol is detected on the driver’s breath and also avoids collisions using an ultrasonic sensor.

---

## 📺 YouTube Demo  
Watch the full project video here:(https://youtu.be/2AZcMt4PPo8)

---

## 🧪 Features
- **Alcohol Detection:** Uses MQ‑3 sensor to detect ethanol vapor; engine start is blocked if alcohol is present.
- **Obstacle Avoidance:** Uses HC‑SR04 ultrasonic sensor to detect objects within ~15 cm and stops the car to avoid collisions.
- **Integrated Logic:** Alcohol detection takes priority. If the driver's breath is clean, ultrasonic sensor keeps checking distance and controls movement.

---

## 🔌 Hardware Components
- Arduino UNO  
- MQ‑3 Alcohol Sensor  
- HC‑SR04 Ultrasonic Sensor  
- L298N Motor Driver Module  
- DC Motors (2×)  
- Buzzer (optional alert)  
- Relay Module (optional ignition simulation)  
- Breadboard, jumper wires, power source

---

## 🧠 Circuit & Wiring
- **MQ‑3 Sensor:** VCC → 5 V, GND → GND, A0 → A0  
- **HC‑SR04 Sensor:** Trig → Pin 9, Echo → Pin 10  
- **Motor Driver:** Motor control pins connected to Arduino digital pins 2, 3, 4, 5  
- **Buzzer (optional):** → Digital pin 6  
- **Relay (optional):** Replace direct motor wiring to simulate ignition Cut-Off

Visual wiring diagram and images can be added in the `/images` folder.

---

## 💻 Arduino Code

File: `alcohol_detection_car.ino`

```cpp
#define trigPin 9
#define echoPin 10
#define alcoholPin A0
#define motor1A 2
#define motor1B 3
#define motor2A 4
#define motor2B 5
#define buzzer 6

int threshold = 400; // Calibrate after testing

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(alcoholPin, INPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int alcoholValue = analogRead(alcoholPin);
  Serial.println(alcoholValue);

  if (alcoholValue > threshold) {
    stopCar();
    digitalWrite(buzzer, HIGH);
    Serial.println("Alcohol detected! Car blocked.");
    delay(1000);
    return;
  } else {
    digitalWrite(buzzer, LOW);
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;

  Serial.println(distance);

  if (distance < 15) {
    stopCar();
    Serial.println("Obstacle detected! Stopped.");
  } else {
    moveForward();
  }

  delay(200);
}

void moveForward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void stopCar() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
}
