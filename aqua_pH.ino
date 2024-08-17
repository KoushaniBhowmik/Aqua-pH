#include <LiquidCrystal.h>

// Initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13); // RS, EN, D4, D5, D6, D7

const int analogInPin = A0; // Analog pin for pH sensor
int buf[10]; // Buffer for storing sensor readings
int temp = 0; // Temporary variable for sorting
unsigned long int avgValue = 0; // Average value
float phValue = 0; // pH value

void setup() {
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Measure pH");
  lcd.setCursor(0, 1);
  lcd.print("Value .......");
  delay(2000);
 
  lcd.clear();
}

void loop() {
  // Read and store sensor values
  for (int i = 0; i < 10; i++) {
    buf[i] = analogRead(analogInPin);
    delay(10);
  }
  
  // Sort buffer array (Simple Bubble Sort)
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  
  // Calculate average of the middle 6 values
  avgValue = 0;
  for (int i = 2; i < 8; i++) {
    avgValue += buf[i];
  }
  
  // Convert the average value to pH
  float pHVol = (float)avgValue * 5.0 / 1024 / 6; // Adjust 6 if necessary
  phValue = -5.70 * pHVol + 22.8;
  phValue = 14.2 - phValue; // If needed, adjust this formula based on calibration
  
  // Print pH value to Serial Monitor
  Serial.printlm("Team Equinox");
  Serial.print("pH Value: ");
  Serial.print(phValue);
  
  // Display pH value on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pH Value");
  lcd.setCursor(3, 1);
  lcd.print(phValue, 2); // Print with 2 decimal places
  
  delay(900); // Delay before the next reading
}
