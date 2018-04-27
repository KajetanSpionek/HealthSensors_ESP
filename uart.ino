void initUart() {
    Serial.begin(115200);
}

void sendTime(uint8_t h, uint8_t m, uint8_t s) {
    uint8_t time[3] = {h, m, s};
    sendFrame(STM_SET_CLOCK, time, 3);
}

void sendDate(uint8_t d, uint8_t m, uint8_t y, uint8_t wd) {
    uint8_t date[4] = {d, m, y, wd};
    sendFrame(STM_SET_DATE, date, 4);
}

void sendFrame(uint8_t cmd, uint8_t* data, uint8_t len) {
    //Serial.printf("Payload message: %s\r\n", data);
    Serial.write(0x7E);
    Serial.write(cmd);
    Serial.write(data, len);
}

void sendMsg(uint8_t cmd, uint8_t msg) {
    Serial.write(0x7E);
    Serial.write(cmd);
    Serial.write(msg);
}

void sendCmd(uint8_t cmd) {
    uint8_t ack[2] = {0x7E, cmd};
    Serial.write(ack, 2);
}

void sendMeasurementRequest(const unsigned char* payload) {
    sendFrame(0xAA, (uint8_t*) payload, 26);
}