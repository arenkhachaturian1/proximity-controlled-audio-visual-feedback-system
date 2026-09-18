# proximity-controlled-audio-visual-feedback-system
Arduino-based proximity-controlled audio-visual feedback system using an HC-SR04 ultrasonic sensor to map hand distance to piezo-buzzer pitch and PWM LED brightness.

## Included Components 
- Arduino Uno
- HC-SR04 ultrasonic distance sensor
- Blue LED
- Piezo Buzzer
- Resistors (220Ω), breadboard, jumper wires

## Code Explanation 

1. **Send a chirp:** The sketch pulses the `trigPin` HIGH for 10 
   microseconds, sending an ultrasonic "chirp" out from the sensor.

2. **Measure the echo:** `pulseIn()` listens on `echoPin` and measures 
   how long the echo takes to return, with a 30ms timeout so the loop 
   never hangs if nothing is in range.

3. **Convert time to distance:** The pulse duration is converted to 
   centimeters using the speed of sound (`duration * 0.034 / 2`).

4. **Check range:** Distances beyond 40cm (the sensor's reliable indoor 
   range) or a timed-out reading are treated as "nothing detected," so 
   the buzzer and LED both turn off.

5. **Map distance to pitch:** Within range (2–40cm), `map()` converts 
   distance into a frequency between 150Hz (far) and 1500Hz (close), 
   played through the buzzer with `tone()`.

6. **Map distance to brightness:** The same distance value is mapped to 
   an LED brightness between 30 (dim, far) and 255 (bright, close), 
   written via `analogWrite()`.

## Key Functions Used
- `pulseIn()` — measures echo pulse duration for distance calculation
- `map()` — converts distance readings into frequency and brightness ranges
- `tone()` / `noTone()` — generates and stops variable-pitch audio output
- `analogWrite()` — controls LED brightness via PWM
- `Serial.print()` — outputs live distance readings for debugging

## Files
- `proximity_controlled_feedback_system.ino` — full Arduino sketch

## Author
Aren Khachaturian — Electrical Engineering, UCLA  
September 2026
