#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <time.h>

void setup() {
    initUart();
    initWifi();
    initTime();
}
uint8_t data = 0x15;
int incomingByte = 0; 

void loop() {
    if (Serial.available() > 0) receiverStm(Serial.read());
}
