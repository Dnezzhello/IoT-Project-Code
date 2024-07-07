#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define MOISTUREPIN A0
#define RELAY 3
#define DHTPIN 2
#define DHTTYPE DHT11
#define WETVALUE 0
#define DRYVAlUE 1023
#define MIN_MOISTURE_PERCENTAGE 40

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
     // initialise the lcd
    lcd.init();
    lcd.backlight();

    // initialise dht sensor
    dht.begin();

    // indicate that the pump is not working yet
    digitalWrite(RELAY, LOW);

    // show welcoming message
    welcomMessage();
}

void loop() {
    float airTemperature = readAirTemperature();
    float airHumidity = readAirHumidity();
    float soilMoisture = readSoilMoisture();

    showInfo(airTemperature, airHumidity, soilMoisture);

    if (soilMoisture < MIN_MOISTURE_PERCENTAGE) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("DRY SOIL");
        lcd.setCursor(0,1);
        lcd.print("PUMP WORKING");
        
        digitalWrite(RELAY, HIGH); // turn on the pump
        delay(3000);
        digitalWrite(RELAY, LOW); // turn off the pump
    }

    delay(4000);
}

void welcomMessage() {
   
    lcd.setCursor(0, 0);
    lcd.print("3CS1 Project");
    delay(3000);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("IRRIGATION");
    delay(2000);

    lcd.setCursor(0, 1);
    lcd.print("System is on");
    delay(2000);

    lcd.clear();
}

void showInfo(float t, float h, float m) {
    lcd.clear();
    // first line: temperature and humidity read from dht sensor
    String firstLine = "T:" + String(t, 1) + "C  H:" + String(h, 1) + "%";
    lcd.setCursor(0,0);
    lcd.print(firstLine);
    
    // second line: soil moisture read from the resistive sensor
    lcd.setCursor(0,1);
    String secondLine = "M:" + String(m, 1) + "%";
    lcd.print(secondLine);
}

float readAirTemperature() {
    float t = dht.readTemperature();

    if (isnan(t)) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("TEMP. FAILED");
        return;
    }

    return t;
}

float readAirHumidity() {
    float h = dht.readHumidity();

    if (isnan(h)) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("HUMID. FAILED");
        return;
    }

    return h;
}

float readSoilMoisture() {
    int sensorValue = analogRead(MOISTUREPIN); // get value from sensor

    if (isnan(sensorValue)) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Moist. FAILED");
    }
    int moisturePercent = map(sensorValue, WETVALUE, DRYVAlUE, 0, 100); // convert the value into mositure percent
    moisturePercent = constrain(moisturePercent, 0, 100);

    return moisturePercent;
}



