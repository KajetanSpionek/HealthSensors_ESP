enum EspStates {
	stm_idle = 0,
    stm_route,
    stm_ppg_red,
    stm_ppg_ir
};

#define STM_STARTBYTE 0x7E

/* Commands incoming from STM */
#define STM_CMD_ECG 			0x40
#define STM_CMD_PPG_RED 		0x41
#define STM_CMD_PPG_IR 			0x42
	// cmd ack/nack by STM
#define STM_ACK					0x11
#define STM_NACK				0x14

/* Comands sent to STM */
#define STM_SET_CLOCK			0xA1
#define STM_SET_DATE			0xA2
#define STM_WIFI				0xA4
#define STM_CLOUD_RDY			0xA8
#define STM_REQUEST_MEASUREMENT 0xAA
	// Data ack/nack by esp/cloud
#define STM_DATA_ACK			0xC1
#define STM_DATA_NACK			0xC4


void receiverStm(int msg) {

    uint8_t static rec = 0;
	uint8_t static in_case_cnt = 0;
	uint8_t static box[21];
    // sendCmd(msg);
    // Serial.println(msg);

    switch(rec) {
	case 0: // Search for starting byte (0x7E)
	 		if (msg == 0x7E) rec = 1;
	 		break;
    case 1: // Routing
            if (msg == 0x40) rec = 2;
            else if (msg == 0x41) rec = 3;
            else rec = 0;
             break;
     case 3: // Receiving STM_CMD_PPG_RED
            box[in_case_cnt] = msg;
			in_case_cnt+= 1;
			if(in_case_cnt == 21) {
				in_case_cnt = 0;
				rec = 0;
                prepMessageMeasurement(0x00, (char*) box);
			}
         break;
     default: break;
	 }

}