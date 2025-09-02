// Pin definitions
const int trigPin = 7; // Trigger pin of ultrasonic sensor
const int echoPin = 8; // Echo pin of ultrasonic sensor
const int motorPin = 3; // Vibration motor pin
const int buzzerPin = 13; // Buzzer pin
const int ledPin = 5; 
// Constants
const int distanceThresholdFar = 25; // Threshold for far distance (in cm)
const int distanceThresholdNear = 10; // Threshold for near distance (in cm)

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
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
    for (int i = 0; i <= 255; i += 5) {
      analogWrite(ledPin, HIGH);
      analogWrite(buzzerPin, 255); // Increase buzzer intensity gradually
      analogWrite(motorPin, 255); // Set motor to maximum vibration
      
      
    }
  } else if (distance < distanceThresholdFar) {
    // Obstacle is neither too near nor too far
    for (int i = 0; i <= 255; i += 5) {
    analogWrite(buzzerPin, i); // Set buzzer to maximum intensity
    analogWrite(motorPin, 128); // Set motor to medium vibration
    digitalWrite(ledPin, HIGH);
    delay(10);
    }
  } else {
    // Obstacle is far away
    analogWrite(buzzerPin, 0); // Turn off buzzer
    analogWrite(motorPin, 0); // Turn off motor
    digitalWrite(ledPin, LOW);
  }
  
  // Wait before next measurement
  delay(100);
}
