**# Pressure Control + Rocket Countdown**



\*\*Course:\*\* 2026FA ENGR 2304 3 SALGADO CENOVIO P10\\

\*\*Project:\*\* Pressure Control + Rocket Countdown\\

\*\*Board:\*\* Arduino Uno R3\\

\*\*Programming Language:\*\* Arduino C++\\

\*\*LCD Library:\*\* Adafruit\_LiquidCrystal\\

\*\*Serial Monitor Baud Rate:\*\* 9600



**## Table of Contents**



1\.  \[Project Overview](#1-project-overview)

2\.  \[Parts and Materials](#2-parts-and-materials)

3\.  \[Circuit Connections](#3-circuit-connections)

4\.  \[How the Program Works](#4-how-the-program-works)

5\.  \[Libraries](#5-libraries)

6\.  \[How to Run the Project](#6-how-to-run-the-project)

7\.  \[Troubleshooting](#7-troubleshooting)

8\.  \[Important Code Notes](#8-important-code-notes)

9\.  \[Project Summary](#9-project-summary)



**## 1. Project Overview**



The Pressure Control + Rocket Countdown project demonstrates an

Arduino-based pressure-control simulation followed by a countdown

sequence.



Two potentiometers provide adjustable analog readings:



&#x20; -----------------------------------------------------------------------

&#x20; Input                   Purpose                 Arduino Pin

&#x20; ----------------------- ----------------------- -----------------------

&#x20; Target pressure dial    Sets the desired        A0

&#x20;                         pressure                



&#x20; Current pressure dial   Represents the          A1

&#x20;                         current/compressor      

&#x20;                         pressure                

&#x20; -----------------------------------------------------------------------



The Arduino converts both analog readings into a pressure range of

\*\*0--15 PSI\*\*. It compares the current pressure with the target

pressure, controls the D7 output, and updates four pressure indicator

LEDs.



When the current pressure reaches the target pressure, the program stops

the pressure-control stage and begins a countdown from 10 to 0. At the

end of the countdown, the LCD displays the completion message and the D7

output turns on.



\*\*Project limitation:\*\* Pressure is simulated using potentiometer

readings. The circuit does not measure actual pressure with a pressure

sensor, and the countdown does not control or launch a real rocket.



**## 2. Parts and Materials**



&#x20; ------------------------------------------------------------------------

&#x20;                     **Quantity Component**             **Purpose**

&#x20; ---------------------------- --------------------- ---------------------

&#x20;                            1 Arduino Uno R3        Main controller



&#x20;                            1 Breadboard            Circuit assembly



&#x20;                            2 Potentiometers        Target and current

&#x20;                                                    pressure inputs



&#x20;                            1 16×2 LCD with I2C     Displays pressure and

&#x20;                              backpack              countdown information



&#x20;                            4 LEDs                  Pressure level

&#x20;                                                    indicators



&#x20;                            1 LED                   Launch indicator



&#x20;                            5 Current-limiting      Protect the LEDs

&#x20;                              resistors, typically  

&#x20;                              220--330 Ω            



&#x20;                    As needed Jumper wires          Circuit connections



&#x20;                            1 USB cable             Programming and power

&#x20; ------------------------------------------------------------------------



A real motor or compressor must not be connected directly to an Arduino

output pin. Any physical load would require a suitable driver circuit

and separate power arrangement.



**## 3. Circuit Connections**



**### 3.1 Potentiometer Connections**



Each potentiometer has three terminals. Connect the middle terminal,

also called the wiper, to the assigned analog input.



&#x20; **Potentiometer      Middle/Wiper Pin   Outer Pins**

&#x20; ------------------ ------------------ ------------

&#x20; Target pressure    A0                 5V and GND

&#x20; Current pressure   A1                 5V and GND



The two outer wires can be swapped if you want the dial to increase in

the opposite direction. Make sure the Arduino and circuit share a common

GND connection.



**### 3.2 LCD Connections**



The 16×2 LCD uses I2C communication.



&#x20; **LCD Pin   Arduino Uno R3**

&#x20; --------- ----------------

&#x20; SDA       A4

&#x20; SCL       A5

&#x20; VCC       5V

&#x20; GND       GND



The program initializes the LCD using:



``` cpp

Adafruit\_LiquidCrystal lcd(0);

```



**### 3.3 LED and Output Connections**



&#x20; **Component                     Arduino Pin**

&#x20; --------------------------- -------------

&#x20; Pressure LED 1                         D4

&#x20; Pressure LED 2                         D8

&#x20; Pressure LED 3                        D12

&#x20; Pressure LED 4                        D13

&#x20; Compressor control output              D7

&#x20; Launch indicator output                D7



Connect each LED through its own current-limiting resistor. The LED

anode (long leg) connects to the Arduino output through the resistor.

The cathode (short leg) connects to GND.



\*\*Important:\*\* The supplied program assigns both `compressorPin` and

`launchLED` to D7. They are therefore the same physical output, not two

independent outputs. D7 is used during the pressure-control stage and is

set HIGH at the end of the countdown. If separate compressor and launch

outputs are required, assign them to different pins and update the

wiring and code to match.



**## 4. How the Program Works**



**### 4.1 Part 1: System Initialization**



When the Arduino starts, the program:



1\.  Starts Serial communication at 9600 baud.

2\.  Sets A0 and A1 as analog inputs.

3\.  Configures the pressure LEDs and D7 as outputs.

4\.  Turns the outputs off initially.

5\.  Initializes the LCD.

6\.  Displays `Pressure Control` and `System Ready`.



**### 4.2 Part 2: Pressure Control**



The program continuously reads both potentiometers.



&#x20; **Reading   Function**

&#x20; --------- ------------------

&#x20; A0        Target pressure

&#x20; A1        Current pressure



The Arduino converts each 10-bit analog reading, ranging from 0 to 1023,

into a pressure value from 0 to 15 PSI.



\*\*Pressure conversion formula:\*\*



``` cpp

pressure = (analogReading / 1023.0) \* 15;

```



When the current pressure is below the target pressure, D7 is set HIGH

and the Serial Monitor displays `Compressor ON`.



When the current pressure reaches or exceeds the target pressure, D7 is

set LOW and the program exits the pressure-control loop.



**### 4.3 Part 3: Pressure Indicator LEDs**



The four pressure LEDs show progress toward the selected target

pressure.



&#x20; **LED                Arduino Pin   Pressure Level**

&#x20; ---------------- ------------- ----------------

&#x20; Pressure LED 1              D4    25% of target

&#x20; Pressure LED 2              D8    50% of target

&#x20; Pressure LED 3             D12    75% of target

&#x20; Pressure LED 4             D13   100% of target



The LEDs update while the pressure-control loop is running. Each LED

turns on when the current pressure reaches its assigned percentage of

the target.



**### 4.4 Part 4: Rocket Countdown**



After the target pressure is reached:



1\.  The compressor output is turned off.

2\.  The LCD displays `Pressure Ready!`.

3\.  The LCD displays `Starting Launch`.

4\.  The program waits one second.

5\.  The countdown begins at 10 and continues down to 0.

6\.  Each countdown number remains displayed for approximately one

&#x20;   second.

7\.  The countdown values are also printed in the Serial Monitor.



**### 4.5 Part 5: Launch Complete**



When the countdown finishes:



\-   D7 is set HIGH.

\-   The LCD displays `LAUNCH COMPLETE!`.

\-   The LCD displays `Mission Success!`.

\-   The Serial Monitor prints the completion messages.



The program runs once during `setup()`. The `loop()` function is empty,

so the sequence does not automatically restart.

