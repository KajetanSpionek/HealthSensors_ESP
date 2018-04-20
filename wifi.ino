static char *ssid = "2.4G-vnet-B95CB2";
static char *pass = "84uplj80oxv7qaws";

void initWifi() {
    
    // Attempt to connect to Wifi network:
    Serial.printf("Attempting to connect to SSID: %s.\r\n", ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
    uint8_t mac[6];
    WiFi.macAddress(mac);
    Serial.printf("You device with MAC address %02x:%02x:%02x:%02x:%02x:%02x connects to %s failed! Waiting 10 seconds to retry.\r\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], ssid);
    WiFi.begin(ssid, pass);
    delay(10000);
  }
  Serial.printf("Connected to wifi %s.\r\n", ssid);
}