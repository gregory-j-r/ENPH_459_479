#include <Arduino.h>
#include "PL_Telemetry_ESP32.h"

const char* ssid = "Krusty Krab";
const char* password = "WithCheese25";

const char* varNames[] = {"var0","var1","var2","var3","var4","var5","var6","var7","var8","var9"};

PL_Telemetry_ESP32 telemetry(
    ssid,
    password,
    IPAddress(192,168,137,50), // ESP’s static IP
    IPAddress(192,168,137,1),  // The receiving PCs IP address
    12345,                     // UDP port
    varNames
);

void setup() {
    Serial.begin(115200);
    telemetry.begin();
}

int a = 1;
int last = millis();
int startT = millis();

void loop() {
    float values[10];

    for(int i=0;i<10;i++) {
        values[i] = (i%2==0) ? a : -a;
    }
    values[9] = sin(float(millis()-startT)/1000.0);

    if(millis()-last > 10) {
        a = -a;
        last = millis();
    }

    telemetry.sendSnapshot(values, micros());

    delay(1); // ~1kHz
}
