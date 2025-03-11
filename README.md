# Density-Based Traffic Control System

## Overview
This project implements a two-way lane traffic control system using an FSM (Finite State Machine) on an Arduino board. It detects vehicle presence using IR sensors and dynamically controls traffic lights to improve efficiency.

## How It Works
- The system monitors two lanes using IR sensors.
- LEDs represent traffic signals (Red, Yellow, Green).
- The FSM controls traffic flow based on sensor inputs:
  - If a vehicle is detected in Lane 1, it gets a green signal, and Lane 2 remains red.
  - If a vehicle is detected in Lane 2, it gets a green signal, and Lane 1 remains red.
  - A transition delay (yellow light) ensures smooth switching.
  - Default state: Both lanes have red lights.

## Hardware Components
- 1 x Arduino Uno
- 2 x IR Sensors
- 6 x LEDs (2 Red, 2 Yellow, 2 Green)
- 6 x Resistors (220Ω each)
- 2 x Breadboards
- Jumper Wires

## Code Explanation
The Arduino sketch follows these steps:
1. **Initialization**: Sets up digital pins for LED output and IR sensor input.
2. **State Machine Execution**:
   - Default state: Both signals are red.
   - Checks IR sensor values (T1, T2) for vehicle detection.
   - Changes traffic signals accordingly using `setColor()` function.
   - Implements intermediate yellow-light transition.
3. **Timer Interrupt**:
   - `softInterr()` updates sensor readings every 50ms.

## Setup & Installation
1. **Wiring**:
   - Connect LEDs to digital pins (10, 9, 8 for Lane 1, 13, 12, 11 for Lane 2).
   - Connect IR sensors to analog pins A0 and A1.
2. **Uploading Code**:
   - Install the Arduino IDE.
   - Upload the provided `.ino` file.
   - Open the Serial Monitor to view IR sensor readings.

## Demonstration
- When a vehicle blocks an IR sensor, the corresponding lane gets a green signal.
- When the vehicle leaves, the signal turns yellow briefly before switching back to red.
- If both lanes detect vehicles, priority is assigned to one lane based on predefined logic.

## Future Improvements
- Add a real-time display for countdown timers.
- Implement adaptive timing based on traffic density.
- Integrate IoT for remote monitoring.

---


