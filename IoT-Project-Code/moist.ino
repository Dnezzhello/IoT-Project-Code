#include "DHT.h"

DHT dht(2, DHT11);

void setup() {
    Serial.begin(9600);

    dht.begin();
}

void loop() {
    int sensorValue = analogRead(A0);
    int max = 0;
    int min = sensorValue;
    int counter;


    if (sensorValue > max) {
        max = sensorValue;
    }
    if (sensorValue < min) {
        min = sensorValue;
    }
    delay(1000);
    counter = counter + 1;

    if (counter == 30) {
        Serial.println('\n\n final \n\n');
        Serial.print('max: ');
        Serial.print(max);
        Serial.println('min: ');
        Serial.print(min);
    }

}