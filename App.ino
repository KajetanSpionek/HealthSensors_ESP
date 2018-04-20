#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <time.h>
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTProtocol_HTTP.h>
#include <AzureIoTUtility.h>
#include <ArduinoJson.h>

static IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle;
static WiFiClientSecure sslClient;

#define DEVICE_ID "4F2D"

uint8_t data = 0x15;
int incomingByte = 0; 
char payload_data[256];
char payload_hb[64];

void setup() {
    initUart();
    initWifi();
    initTime();
    initIothub();
    prepMessageHeathBeat(payload_hb);
}

void loop() {
    if (Serial.available() > 0) receiverStm(Serial.read());
    sendMessage(iotHubClientHandle, payload_hb);
    IoTHubClient_LL_DoWork(iotHubClientHandle);
    delay(5000);
}
