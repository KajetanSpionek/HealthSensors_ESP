//static char *connectionString = "HostName=MEKG-hub-MobilneEKG.azure-devices.net;DeviceId=HealthSensor_1;SharedAccessKey=Y1fQPkDsI6au4/BUC45pseQcHrQKmOhHZk448Wm0pmg=";
static char *connectionString = "HostName=iothub-HealthSensors.azure-devices.net;DeviceId=4F2D;SharedAccessKey=tyhcmnP2zlLG8yyh9/usj8Vx6oEMMRBpjfKkXGy4oIU=";

const char *onSuccess = "\"Successfully invoke device method\"";
const char *notFound = "\"No method found\"";


// Initialization of IotHub connctor
void initIothub(void) {
  
  iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, MQTT_Protocol);
  if (iotHubClientHandle == NULL) {
    //Serial.println("Failed on IoTHubClient_CreateFromConnectionString.");
    while (1);
  }
  IoTHubClient_LL_SetOption(iotHubClientHandle, "product_info", "ActivePath_HealthSensors-ESP");
  IoTHubClient_LL_SetMessageCallback(iotHubClientHandle, receiveMessageCallback, NULL);
  IoTHubClient_LL_SetDeviceMethodCallback(iotHubClientHandle, deviceMethodCallback, NULL);
  IoTHubClient_LL_SetDeviceTwinCallback(iotHubClientHandle, twinCallback, NULL);
  sendMsg(0xA8, 0x01);
}

// Function called when ESP gets result from Azure about recently sent message
static void sendCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void *userContextCallback) {
    if (IOTHUB_CLIENT_CONFIRMATION_OK == result) {
        //Serial.println("Message sent to Azure IoT Hub");
        sendCmd(0xC1);
    } else {
       // Serial.println("Failed to send message to Azure IoT Hub");
        sendCmd(0xC4);
    }
}

/* Twin handling */
void twinCallback(DEVICE_TWIN_UPDATE_STATE updateState, const unsigned char *payLoad,
                  size_t size, void *userContextCallback) {
    
    char *temp = (char *)malloc(size + 1);
    for (int i = 0; i < size; i++) {
        temp[i] = (char)(payLoad[i]);
    }
    temp[size] = '\0';
    parseTwinMessage(temp);
    free(temp);
}

IOTHUBMESSAGE_DISPOSITION_RESULT receiveMessageCallback(IOTHUB_MESSAGE_HANDLE message, void *userContextCallback) {
    
    IOTHUBMESSAGE_DISPOSITION_RESULT result;
    const unsigned char *buffer;
    size_t size;
    if (IoTHubMessage_GetByteArray(message, &buffer, &size) != IOTHUB_MESSAGE_OK) {
        //Serial.println("Unable to IoTHubMessage_GetByteArray.");
        result = IOTHUBMESSAGE_REJECTED;
    } else {
        /*buffer is not zero terminated*/
        char *temp = (char *)malloc(size + 1);

        if (temp == NULL) {
            return IOTHUBMESSAGE_ABANDONED;
        }

        strncpy(temp, (const char *)buffer, size);
        temp[size] = '\0';
        //Serial.printf("Receive C2D message: %s.\r\n", temp);
        free(temp);
    }
    return IOTHUBMESSAGE_ACCEPTED;
}

int deviceMethodCallback(const char *methodName, const unsigned char *payload,
                        size_t size, unsigned char **response, size_t *response_size,
                        void *userContextCallback) {
                          
    //Serial.printf("Try to invoke method %s.\r\n", methodName);
    const char *responseMessage = onSuccess;
    int result = 200;

    if (strcmp(methodName, "MeasurementRequest") == 0) {
        
        sendMeasurementRequest(payload);
    }
    else {
        //Serial.printf("No method %s found.\r\n", methodName);
        responseMessage = notFound;
        result = 404;
    }

    *response_size = strlen(responseMessage);
    *response = (unsigned char *)malloc(*response_size);
    strncpy((char *)(*response), responseMessage, *response_size);

    return result;
}
