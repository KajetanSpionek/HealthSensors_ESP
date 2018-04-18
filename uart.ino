void initUart() {
    Serial.begin(115200);
}

void sendTime(uint8_t h, uint8_t m, uint8_t s) {
    uint8_t time[3] = {h, m, s};
    sendFrame(0xA1, time, 3);
}

void sendDate(uint8_t d, uint8_t m, uint8_t y, uint8_t wd) {
    uint8_t date[4] = {d, m, y, wd};
    sendFrame(0xA2, date, 4);
}

void sendFrame(uint8_t cmd, uint8_t* data, uint8_t len) {
    Serial.write(0x7E);
    Serial.write(cmd);
    Serial.write(data, len);
}