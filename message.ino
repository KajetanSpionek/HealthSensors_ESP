void prepMessageMeasurement(int type, char *payload) { // payload has size of 21
    // int ses, int meas, int pack, int type, 
    StaticJsonBuffer<256> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["deviceId"] = DEVICE_ID;
    if (type == 0) 
        root["messageType"] = "PPG_RED";
    else if (type == 1)
        root["messageType"] = "PPG_IR";
    else            
        root["messageType"] = "ECG";

    root["sessionId"] = payload[0] << 8 | payload[1];
    root["measurementId"]= payload[2];
    root["packageId"] = payload[3] << 8 | payload[4];
    
    JsonArray& data = root.createNestedArray("data");
    
    for (uint8_t _j = 0; _j < 4; _j++) {
        data.add(payload[4*_j] << 24 | payload[4*_j+1] << 16 | payload[4*_j+2] << 8 | payload[4*_j+4]);
    } 

    char static box[256];
    root.printTo(box, 256);
    sendMessage(iotHubClientHandle, box);
}

void prepMessageHeathBeat(char *payload) {

    StaticJsonBuffer<64> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["deviceId"] = DEVICE_ID;
    root["messageType"] = "HB";

    root.printTo(payload, 64);
}

static void sendMessage(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, char *buffer) {
    IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray((const unsigned char *)buffer, strlen(buffer));
    
    if (messageHandle == NULL) {
        //Serial.println("Unable to create a new IoTHubMessage.");
    }
    else {
        //Serial.printf("Sending message: %s.\r\n", buffer);
        if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle, sendCallback, NULL) != IOTHUB_CLIENT_OK) {
            //Serial.println("Failed to hand over the message to IoTHubClient.");
        }
        else {
           // Serial.println("IoTHubClient accepted the message for delivery.");
        }
        IoTHubMessage_Destroy(messageHandle);
    }
}

int interval;

void parseTwinMessage(char *message) {
    
    StaticJsonBuffer<256> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(message);

    if (!root.success()) {
        //Serial.printf("Parse %s failed.\r\n", message);
        return;
    }

    if (root["desired"]["interval"].success()) {
        interval = root["desired"]["interval"];
    }
    else if (root.containsKey("interval")) {
        interval = root["interval"];
    }
}