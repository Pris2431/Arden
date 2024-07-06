#include <LiquidCrystal.h>

#define sensorPin A2 /temp sensor/
#define LDRpin A1 /LDR sensor/
#define MQ2pin A0 /gas sensor/

#define Threshold 400

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(LDRpin, INPUT);
  pinMode(MQ2pin, INPUT);
  lcd.begin(16, 2);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
  lcd.print("Sensors online");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Read sensor values
  int lm35Reading = analogRead(sensorPin);
  float voltage = lm35Reading * (5.0 / 1024.0);
  float temperatureC = voltage * 100;

  int ldrReading = analogRead(LDRpin);

  int sensorValue = analogRead(MQ2pin);

  // Display sensor readings on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("LDR: ");
  lcd.print(ldrReading);

  lcd.setCursor(8, 1);
  lcd.print("Gas: ");
  lcd.print(sensorValue);

  // Check conditions and display maintenance message if needed
  if (temperatureC > 25 || sensorValue > Threshold || ldrReading < 100) {
    lcd.setCursor(0, 1);
    lcd.print("Maintenance needed");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Good condition    ");
  }
  

  // Display sensor readings and maintenance status on Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print("C  |  ");
  Serial.print("LDR Value: ");
  Serial.print(ldrReading);
  Serial.print("  |  ");
  Serial.print("Gas Sensor Value: ");
  Serial.print(sensorValue);
  if (temperatureC > 30 || sensorValue > Threshold || ldrReading < 100) {
    Serial.println(" | Maintenance needed");
  } else {
    Serial.println(" | Good condition");
  }
  
  delay(1000);
}