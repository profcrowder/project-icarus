
/* 2026FA-ENGR-2304-83001-OTU-JESSE-P10 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int pressurePin = A0;
const int compressorLED = 8;
const int maxPressure = 100;

int targetPressure = 0;
int currentPressure = 0;

bool targetEntered = false;
bool countdownStarted = false;
bool countdownFinished = false;

void setup() {
  pinMode(compressorLED, OUTPUT);

  Serial.begin(9600);
  Serial.setTimeout(100);

  lcd.begin(16, 2);

  lcd.print("Project Icarus");
  lcd.setCursor(0, 1);
  lcd.print("Enter target PSI");

  Serial.println("Project Icarus");
  Serial.println("Enter target pressure in binary.");
  Serial.println("Example: 101 = 5, 110010 = 50");
}

bool getTargetPressure() {
  if (Serial.available() == 0) {
    return false;
  }

  String input = Serial.readStringUntil('\n');
  input.trim();

  if (input.length() == 0) {
    return false;
  }

  int number = 0;

  for (int i = 0; i < input.length(); i++) {
    char digit = input.charAt(i);

    if (digit != '0' && digit != '1') {
      Serial.println("Please enter binary digits only.");
      return false;
    }

    number = (number * 2) + (digit - '0');

    if (number > maxPressure) {
      Serial.println("Pressure cannot be over 100.");
      return false;
    }
  }

  targetPressure = number;
  return true;
}

void updatePressure() {
  int reading = analogRead(pressurePin);
  currentPressure = map(reading, 0, 1023, 0, maxPressure);
}

void controlPressure() {
  updatePressure();

  lcd.setCursor(0, 0);
  lcd.print("Now:");
  lcd.print(currentPressure);
  lcd.print(" Target:");
  lcd.print(targetPressure);
  lcd.print("   ");

  if (currentPressure < targetPressure) {
    digitalWrite(compressorLED, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Compressor: ON  ");

    Serial.print("Current pressure: ");
    Serial.println(currentPressure);
  } 
  else {
    digitalWrite(compressorLED, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Target reached  ");

    Serial.println("Target pressure reached.");
    countdownStarted = true;
  }

  delay(250);
}

void runCountdown() {
  digitalWrite(compressorLED, LOW);

  for (int i = 10; i >= 0; i--) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Countdown:");

    lcd.setCursor(0, 1);
    lcd.print(i);
    lcd.print(" seconds");

    Serial.print("Countdown: ");
    Serial.println(i);

    delay(1000);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Countdown done!");

  lcd.setCursor(0, 1);
  lcd.print("System finished");

  Serial.println("Countdown complete.");

  countdownFinished = true;
}

void loop() {
  if (!targetEntered) {
    if (getTargetPressure()) {
      targetEntered = true;

      Serial.print("Target pressure set to: ");
      Serial.println(targetPressure);

      lcd.clear();
      lcd.print("Target set to:");
      lcd.setCursor(0, 1);
      lcd.print(targetPressure);

      delay(1500);
    }
  }

  if (targetEntered && !countdownStarted) {
    controlPressure();
  }

  if (countdownStarted && !countdownFinished) {
    runCountdown();
  }
}

