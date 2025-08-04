// Alcohol + Obstacle Detection Car Project
#define trigPin 9
#define echoPin 10
#define alcoholPin A0
#define motor1A 2
#define motor1B 3
#define motor2A 4
#define motor2B 5
#define buzzer 6

int threshold = 400; // Alcohol level threshold (adjust after testing)

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(alcoholPin, INPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int alcoholValue = analogRead(alcoholPin);
  Serial.print("Alcohol Level: ");
  Serial.println(alcoholValue);

  if (alcoholValue > threshold) {
    // Alcohol detected
    stopCar();
    digitalWrite(buzzer, HIGH); // alert
    Serial.println("Alcohol Detected! Car won't start.");
    delay(1000);
    return; // skip the rest of loop
  } else {
    digitalWrite(buzzer, LOW);
  }

  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 15) {
    stopCar();
    Serial.println("Obstacle Detected! Car stopped.");
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
