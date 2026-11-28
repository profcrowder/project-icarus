

1. **Pressure regulation:** The Arduino reads a potentiometer that represents a pressure sensor. It then compares the simulated pressure with a target entered in the Serial Monitor. The LED indicates when the compressor would be requested and the indicator turns off when the target is reached.
2. **Countdown:** Once the target pressure is reached, the LCD displays a 10-to-0 countdown. The program then displays that the demonstration is complete.

## Hardware
- Arduino Uno
- 16x2 LCD compatible with the `LiquidCrystal` library
- 10 kΩ potentiometer for simulated pressure input
- LED and 220 Ω resistor for compressor-status indication
- Breadboard and jumper wires

## Wiring
| Part | Arduino connection |
|---|---|
| LCD RS | D12 |
| LCD E | D11 |
| LCD D4 | D5 |
| LCD D5 | D4 |
| LCD D6 | D3 |
| LCD D7 | D2 |
| LCD VSS, RW, K | GND |
| LCD VDD | 5V |
| LCD A | 5V through suitable current limiting, if required by the module |
| Pressure potentiometer center pin | A0 |
| Pressure potentiometer outer pins | 5V and GND |
| Compressor-status LED anode | D8 through 220 Ω resistor |
| Compressor-status LED cathode | GND |

## How to run
1. Open `Project_Icarus.ino` in the Arduino IDE or recreate the circuit in Tinkercad Circuits.
2. Select **Arduino Uno** and upload the sketch.
3. Open Serial Monitor at **9600 baud** and select **Newline** as the line ending.
4. Enter the target pressure as a binary whole number. For example, enter `1010` to set a target of 10 simulated pressure units.
5. Turn the potentiometer to raise the simulated pressure. The LED on D8 indicates the compressor request.
6. When the simulated pressure reaches the target, the indicator turns off and the LCD begins the countdown.

## Input format
The Serial Monitor input is to be interpreted as binary digits (`0` and `1`); Valid target range idealy is 0 through 100 decimal (binary `0` through `1100100`).


## Deliverables
- `Project_Icarus.ino` — Arduino source code
- `README.md` — project description, wiring, and operating instructions
- `Wiring_Guide.txt` — quick wiring reference

## Tinkercad design
https://www.tinkercad.com/things/gv3hVEmLSE1-2026fa-engr-2304-83001-otu-jesse
