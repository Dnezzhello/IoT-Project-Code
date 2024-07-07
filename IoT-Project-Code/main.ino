#include <LiquidCrystal_I2C.h>

#define MOISTUREPIN A0
#define RELAY 3
#define WETVALUE 389
#define DRYVAlUE 989
#define MIN_MOISTURE_PERCENTAGE 20
#define TARGET_MOISTURE_PERCENTAGE 70

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    // initialise the lcd
    lcd.init();
    lcd.backlight();

    // show welcoming message
    welcomMessage();
}

void loop()
{
    float soilMoisture = readSoilMoisture();

    showInfo(soilMoisture, false);

    if (soilMoisture < MIN_MOISTURE_PERCENTAGE)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SOIL IS DRY");
        lcd.setCursor(0, 1);
        lcd.print("PUMP WORKING");

        delay(1000);

        digitalWrite(RELAY, HIGH); // turn on the pump
        

        while (true)
        {
            showInfo(soilMoisture, true);
            soilMoisture = readSoilMoisture();

            if (soilMoisture > TARGET_MOISTURE_PERCENTAGE)
            {
                digitalWrite(RELAY, LOW); // turn off the pump

                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("PUMP STOPPED");

                break;
            }
            delay(500);
        }
    }

    delay(3000);
}

void welcomMessage()
{

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

void showInfo(float m, bool isWaterPumping)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    String text = "Moist: " + String(m, 1) + "%";
    lcd.print(text);

    if (isWaterPumping)
    {
        lcd.setCursor(0, 1);
        lcd.print("PUMP WORKING");
    }
}

float readSoilMoisture()
{
    int sensorValue = analogRead(MOISTUREPIN); // get value from sensor

    if (isnan(sensorValue))
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Moist. FAILED");
    }
    int moisturePercent = map(sensorValue, WETVALUE, DRYVAlUE, 0, 100); // convert the value into mositure percent
    moisturePercent = constrain(moisturePercent, 0, 100);

    return moisturePercent;
}
