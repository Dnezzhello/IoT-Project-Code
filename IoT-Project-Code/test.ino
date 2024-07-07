#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define MOISTUREPIN A0
#define RELAY 6
#define GREEN_LED 3
#define RED_LED 4
#define DHTPIN 2
#define DHTTYPE DHT11
#define WETVALUE 0
#define DRYVAlUE 1023

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(9600);

    // initialise dht sensor
    dht.begin();

    // initialise LCD
    lcd.init();
    lcd.backlight();
    lcd.clear();

    // setup output pin
    pinMode(RELAY, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    // supply power to all pins
    digitalWrite(RELAY, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    delay(1000);

    // welcoming message
    lcd.setCursor(0, 0);
    lcd.print("3CS1 Project");
    delay(1000);

    lcd.setCursor(0, 0);
    lcd.print("IRRIGATION");

    lcd.setCursor(0, 1);
    lcd.print("SYSTEM IS ON");
    delay(3000);

    lcd.clear();
}

void loop()
{
    show_temperature();
    /*

  lcd.setCursor(0, 0);
  if (value > 950) {
    digitalWrite(6, LOW); // ปั๊มน้ำเปิด
    digitalWrite(3, LOW); // ไฟ LED ที่ D3 ปิด
    digitalWrite(4, HIGH); // ไฟ LED ที่ D4 เปิด
    lcd.print("Water Pump is ON ");
    Serial.println("Relay is ON");
  } else {
    digitalWrite(6, HIGH); // ปั๊มน้ำปิด
    digitalWrite(3, HIGH); // ไฟ LED ที่ D3 เปิด
    digitalWrite(4, LOW); // ไฟ LED ที่ D4 ปิด
    lcd.print("Water Pump is OFF");
    Serial.println("Relay is OFF");
  }

  // แสดงสถานะความชื้นบนจอ LCD
  lcd.setCursor(0, 1);
  if (value < 300) {
    lcd.print("Moisture : HIGH");
  } else if (value >= 300 && value <= 950) {
    lcd.print("Moisture : MID ");
  } else if (value > 950) {
    lcd.print("Moisture : LOW ");
  }
    */
}

void show_temperature()
{
    float temp = dht.readTemperature();

    if (isnan(temp))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }
    Serial.println(temp);
    lcd.setCursor(0, 0);
    lcd.print(temp);
}

void show_humidity()
{
}

void test() {

}

void show_moisture()
{
    int sensorValue = analogRead(MOISTUREPIN);

    int moisturePercent = map(sensorValue, WETVALUE, DRYVAlUE, 0, 100);

    // Ensure the percentage is within the bounds of 0% to 100%
    moisturePercent = constrain(moisturePercent, 0, 100);
    // Serial.println(value);
    lcd.setCursor(1, 0);
    lcd.print('Moist:');
    lcd.setCursor(1, 7);
    lcd.print(moisturePercent, 1);

    if (moisturePercent > 50) {
        digitalWrite()
    }

    lcd.print(MO) if (value > 950)
    {
        digitalWrite(2, LOW);
        lcd.setCursor(0, 0);
        lcd.print("Water Pump is ON ");
    }
    else
    {
        digitalWrite(2, HIGH);
        lcd.setCursor(0, 0);
        lcd.print("Water Pump is OFF");
    }

    if (value < 300)
    {
        lcd.setCursor(0, 1);
        lcd.print("Moisture : HIGH");
    }
    else if (value > 300 && value < 950)
    {
        lcd.setCursor(0, 1);
        lcd.print("Moisture : MID ");
    }
    else if (value > 950)
    {
        lcd.setCursor(0, 1);
        lcd.print("Moisture : LOW ");
    }
}