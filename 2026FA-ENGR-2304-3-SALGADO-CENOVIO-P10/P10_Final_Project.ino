// 2026FA-ENGR-2304-3-SALGADO-CENOVIO-P10
// Pressure Control + Rocket Countdown
// Arduino Uno R3

#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

// PIN CONNECTIONS
const int targetDial = A0;
const int compressorDial = A1;

const int compressorPin = 0b0111;  // D7
const int launchLED = 0b0111;       // D7

// Four pressure indicator LEDs
const int pressureLEDs[] = {
  0b0100,  // D4
  0b1000,  // D8
  0b1100,  // D12
  0b1101   // D13
};

// PRESSURE SETTINGS
const int adcMax = 0b1111111111;
const float maxPressure = 0b1111;

const int countdownStart = 0b1010;

void setup() {

  Serial.begin(0b10010110000000);

  pinMode(targetDial, INPUT);
  pinMode(compressorDial, INPUT);

  pinMode(compressorPin, OUTPUT);
  pinMode(launchLED, OUTPUT);

  for (int i = 0; i < 0b100; i++) {
    pinMode(pressureLEDs[i], OUTPUT);
  }

  digitalWrite(compressorPin, LOW);
  digitalWrite(launchLED, LOW);

  lcd.begin(0b10000, 0b10);
  lcd.setBacklight(1);

  lcd.print("Pressure Control");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");

  Serial.println("--- ENGR 2304 Project ---");
  Serial.println("Pressure Control Initialized");

  delay(0b111110100);

  // PART 1: PRESSURE CONTROL

  float targetPressure = 0;
  float currentPressure = 0;

  while (true) {

    // Read both potentiometers

    int targetValue = analogRead(targetDial);
    int compressorValue = analogRead(compressorDial);

    // Convert readings to PSI (0-15)

    targetPressure =
      (targetValue / (float)adcMax) * maxPressure;

    currentPressure =
      (compressorValue / (float)adcMax) * maxPressure;

    // Display pressure information

    lcd.clear();

    lcd.print("Target:");
    lcd.print(targetPressure, 1);
    lcd.print(" PSI");

    lcd.setCursor(0, 1);
    lcd.print("Current:");
    lcd.print(currentPressure, 1);

    Serial.print("Target Pressure: ");
    Serial.print(targetPressure);
    Serial.println(" PSI");

    Serial.print("Current Pressure: ");
    Serial.print(currentPressure);
    Serial.println(" PSI");

    // Compressor control

    if (currentPressure < targetPressure) {

      digitalWrite(compressorPin, HIGH);

      Serial.println("Compressor ON");

    } else {

      digitalWrite(compressorPin, LOW);

      Serial.println("Target Reached");

    }

    // Update four pressure LEDs

    for (int i = 0; i < 0b100; i++) {

      float threshold =
        targetPressure * (i + 1) / 0b100;

      if (currentPressure >= threshold) {
        digitalWrite(pressureLEDs[i], HIGH);
      } else {
        digitalWrite(pressureLEDs[i], LOW);
      }
    }

    // Exit when target pressure is reached

    if (currentPressure >= targetPressure) {
      digitalWrite(compressorPin, LOW);
      break;
    }

    delay(0b111110100);
  }

  // PART 2: PRESSURE SUCCESS

  digitalWrite(compressorPin, LOW);

  Serial.println("Pressure Target Successfully Reached!");

  lcd.clear();
  lcd.print("Pressure Ready!");

  lcd.setCursor(0, 1);
  lcd.print("Starting Launch");

  delay(0b1111101000);

  // PART 3: ROCKET COUNTDOWN

  Serial.println("Rocket Countdown Starting!");

  for (int count = countdownStart; count >= 0; count--) {

    lcd.clear();

    lcd.print("Rocket Launch:");

    lcd.setCursor(0, 1);
    lcd.print("Countdown: ");
    lcd.print(count);

    Serial.print("Countdown: ");
    Serial.println(count);

    delay(0b1111101000);
  }

  // PART 4: LAUNCH COMPLETE

  digitalWrite(launchLED, HIGH);

  lcd.clear();
  lcd.print("LAUNCH COMPLETE!");

  lcd.setCursor(0, 1);
  lcd.print("Mission Success!");

  Serial.println("Countdown Complete!");
  Serial.println("LAUNCH COMPLETE!");
  Serial.println("Mission Successful!");

}

void loop() {
  // Runs once during setup()
}
