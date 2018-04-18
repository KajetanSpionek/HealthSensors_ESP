void initUart() {
    Serial.begin(115200);
}

void sendTime(uint8_t h, uint8_t m, uint8_t s) {
    // Load variables table
    uint8_t time[3] = {h, m, s};
    sendFrame(0xAB, time, 3);
}



void sendFrame(uint8_t cmd, uint8_t* data, uint8_t len) {

    Serial.write(0x7E);
    Serial.write(cmd);
    Serial.write(data, len);
}