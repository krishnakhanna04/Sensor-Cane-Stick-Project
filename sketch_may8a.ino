// Pin definitions
const int trigPin = 7; // Trigger pin of ultrasonic sensor
const int echoPin = 8; // Echo pin of ultrasonic sensor
const int motorPin = 3; // Vibration motor pin
const int buzzerPin = 13; // Buzzer pin

// Constants
const int distanceThresholdFar = 20; // Threshold for far distance (in cm)
const int distanceThresholdNear = 10; // Threshold for near distance (in cm)

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Measure distance
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // Control buzzer and motor based on distance
  if (distance < distanceThresholdNear) {
    // Obstacle is near
    digitalWrite(buzzerPin, HIGH); // Turn on buzzer
    analogWrite(motorPin, 255); // Set motor to maximum vibration
  } else if (distance < distanceThresholdFar) {
    // Obstacle is neither too near nor too far
    digitalWrite(buzzerPin, LOW); // Turn on buzzer
    analogWrite(motorPin, 128); // Set motor to medium vibration
  } else {
    // Obstacle is far away
    digitalWrite(buzzerPin, LOW); // Turn off buzzer
    analogWrite(motorPin, 0); // Turn off motor
  }
  
  // Wait before next measurement
  delay(100);
}
