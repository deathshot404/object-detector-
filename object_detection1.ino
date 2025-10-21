// HC-SR04 + IR (obstacle) -> Blink LED
// TRIG -> D9, ECHO -> D10, IR OUT -> D8, LED -> D7 (with 220Ω), common GND

const int TRIG = 9;
const int ECHO = 10;
const int IRPIN = 8;
const int LEDPIN = 7;

const int DIST_THRESHOLD = 35;           // cm - adjust to taste
const unsigned long PULSE_TIMEOUT = 30000UL; // 30 ms timeout

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(IRPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
  Serial.begin(9600);
}

int measureDistanceCM() {
  // Trigger a 10 µs pulse
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  unsigned long dur = pulseIn(ECHO, HIGH, PULSE_TIMEOUT);
  if (dur == 0UL) return 999; // out of range / no echo
  int dist = int((dur * 0.0343) / 2.0 + 0.5);
  return dist;
}

void loop() {
  int distance = measureDistanceCM();
  int irRaw = digitalRead(IRPIN);   // read IR module output

  // MOST IR obstacle modules are active-LOW: OUT = LOW when object is detected.
  // If your module outputs HIGH on detection, change the next line to (irRaw == HIGH)
  bool irDetected = (irRaw == LOW);

  bool ultrasonicDetected = (distance > 0 && distance <= DIST_THRESHOLD);

  // Debug on serial monitor (helps in Tinkercad too)
  Serial.print("Dist(cm): ");
  Serial.print(distance);
  Serial.print("  IRraw: ");
  Serial.print(irRaw);
  Serial.print("  -> IRdet: ");
  Serial.print(irDetected ? "YES" : "NO");
  Serial.print("  Ultradet: ");
  Serial.println(ultrasonicDetected ? "YES" : "NO");

  if (irDetected || ultrasonicDetected) {
    // obstacle detected — blink LED
    digitalWrite(LEDPIN, HIGH);
    delay(150);
    digitalWrite(LEDPIN, LOW);
    delay(150);
  } else {
    digitalWrite(LEDPIN, LOW);
    delay(80);
  }
}
