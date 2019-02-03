#include <LiquidCrystal.h>
#include "dht.h"

#define DHTPIN A7

dht dhtSensor;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Initializing!");
  lcd.setCursor(0, 1);
  lcd.print("DriveGreen(r)...");
  delay(1000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  int chk = dhtSensor.read11(DHTPIN);
  
  if(dhtSensor.temperature != -999 && dhtSensor.humidity != -999) {
    Serial.print("Temperature = ");
    Serial.print(dhtSensor.temperature);
    Serial.println("C");
    Serial.print("Humidity = ");
    Serial.print(dhtSensor.humidity);
    Serial.println("%");
    double satVapPres = 6.11 * pow(10, (7.5 * dhtSensor.temperature) / (237.3 + dhtSensor.temperature));
    double vapPres = dhtSensor.humidity * satVapPres;
    Serial.println("Vapor pressure = ");
    Serial.println(vapPres);
    double absHumid = (2165 * vapPres)/(dhtSensor.temperature + 273.16);
    //double totalWeight = vapPres * 9.8;
    Serial.print("Total water weight = ");
    Serial.print(absHumid / 1000);
    Serial.println("kg");
    
    
    lcd.setCursor(0,0);
    lcd.print("Temperature = ");
    lcd.setCursor(0, 1);
    lcd.print(dhtSensor.temperature);
    lcd.setCursor(5, 1);
    lcd.print("C");  
    delay(1000);
    lcd.clear();
     
    lcd.setCursor(0,0);
    lcd.print("Humidity = ");
    lcd.setCursor(0, 1);
    lcd.print(dhtSensor.humidity);
    lcd.setCursor(5, 1);
    lcd.print("%");
    delay(1000);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.println("Vapor pressure = ");
    lcd.setCursor(0, 1);
    lcd.print(vapPres);
    delay(1000);
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("Water mass = ");
    lcd.setCursor(0, 1);
    lcd.print(absHumid / 1000);
    lcd.setCursor(5, 1);
    lcd.print("kg/m^3"); 
    delay(1000);  
    lcd.clear();
}
}
