static char *ssid = "2.4G-vnet-B95CB2";
static char *pass = "84uplj80oxv7qaws";

void initWifi() {
    // Attempt to connect to Wifi network:
    // Serial.printf("Attempting to connect to SSID: %s.\r\n", ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, pass);
        delay(3000);
    }
    // Serial.printf("Connected to wifi %s.\r\n", ssid);
}