# 🚨 Obstacle Detection System using Ultrasonic and IR Sensors

## 📘 Project Overview
This project is a **simple obstacle detection model** built using an **Arduino UNO**, an **Ultrasonic Sensor (HC-SR04)**, and an **Infrared (IR) Sensor**.  
It detects objects in front of the sensors and activates an **LED indicator** when an obstacle is within a certain range.

This system demonstrates the basic concept behind **robot navigation**, **automated parking systems**, and **collision avoidance** in embedded electronics.

---

## ⚙️ How It Works
The project uses two types of sensors for accurate detection:

- 🧭 **Ultrasonic Sensor (HC-SR04)**: Measures the distance between the sensor and an obstacle by sending ultrasonic pulses and timing the echo.
- 🌒 **IR Sensor**: Detects nearby objects based on infrared light reflection — ideal for close-range detection.
- 💡 **LED Indicator**: Turns ON whenever an obstacle is detected by either sensor.

Both sensors provide input to the Arduino, which then decides when to activate the LED based on distance and detection logic.

---

## 🧩 Components Used
| Component | Quantity | Description |
|------------|-----------|-------------|
| Arduino UNO | 1 | Main microcontroller board |
| Ultrasonic Sensor (HC-SR04) | 1 | Measures distance using ultrasonic sound waves |
| IR Sensor Module | 1 | Detects obstacles using infrared reflection |
| LED | 1 | Visual indication of obstacle presence |
| 220Ω Resistor | 1 | Limits current through LED |
| Jumper Wires | As needed | For circuit connections |
| Breadboard | 1 | For assembling the circuit |

---

## 🔌 Circuit Connections
| Component | Arduino Pin | Description |
|------------|-------------|-------------|
| Ultrasonic Sensor Trig | D9 | Sends ultrasonic pulse |
| Ultrasonic Sensor Echo | D10 | Receives reflected pulse |
| IR Sensor OUT | D2 | Detects nearby objects |
| LED | D13 | Lights up when obstacle detected |
| VCC (Ultrasonic + IR) | 5V | Power supply |
| GND (All) | GND | Common ground |

---

## 📸 Circuit Diagram / Setup
<img width="900" height="600" alt="image" src="https://github.com/user-attachments/assets/ca4d9a5d-4147-46f3-98f8-2f5fd8b1d124" />


## 💻 Arduino Code
 ``` bash
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

 ```
 

