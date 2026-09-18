// Aren Khachaturian
// September 15, 2026 

// Ultrasonic Theremin
// Closer hand = higher pitch. Farther hand = lower pitch.

const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 8;
const int ledPin = 6;      

// The sensor stops "hearing" anything reliable much past ~40cm indoors,
// so we treat that as the far edge of the playable range.
const int minDistanceCm = 2;
const int maxDistanceCm = 40;
const int minFrequencyHz = 150;   // pitch when hand is far away
const int maxFrequencyHz = 1500;  // pitch when hand is close

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Send a short "chirp" pulse out the Trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure how long (in microseconds) it took for the echo to come back
  // The 30000 is a timeout so we don't get stuck waiting forever if nothing is in range
  long duration = pulseIn(echoPin, HIGH, 30000);

  // Convert that time into a distance in centimeters
  float distanceCm = duration * 0.034 / 2;

  if (duration == 0 || distanceCm > maxDistanceCm) {
    // Nothing in range - stay silent
    noTone(buzzerPin);
    analogWrite(ledPin, 0);
  } else {
    // Turn distance into a musical pitch
    int frequency = map((int)distanceCm, minDistanceCm, maxDistanceCm,
                         maxFrequencyHz, minFrequencyHz);
    tone(buzzerPin, frequency);

    // Closer hand = brighter LED
    int brightness = map((int)distanceCm, minDistanceCm, maxDistanceCm, 255, 30);
  
    analogWrite(ledPin, brightness);
  }

  // Demonstrates the distance.
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  delay(50);
}