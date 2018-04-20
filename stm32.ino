enum EspStates {
	stm_idle = 0,
    stm_route
};

#define STM_STARTBYTE 0x7E

/* Commands incoming from STM */
#define STM_CMD_ECG 			0x40
#define STM_CMD_PPG_RED 		0x41
#define STM_CMD_PPG_IR 			0x42

/* Comands sent to STM */
#define STM_SET_CLOCK			0xA1
#define STM_SET_DATE			0xA2
#define STM_PING				0xA4


void receiverStm(int msg) {

    uint8_t static rec = stm_idle;
    Serial.write(0x7E);
    Serial.write(STM_PING);
    Serial.write(0xF2);
	//uint8_t static in_case_cnt = 0;
	//uint8_t static box[3];

    // switch(rec) {
	// case stm_idle: // Search for starting byte (0x7E)
	// 		if (msg == STM_STARTBYTE) rec = stm_route;
    //         sendFrame(STM_PING, (uint8_t*) 0xAB, 1);
	// 		break;
    // case stm_route: // Routing
    //         rec = stm_idle;
    //         sendFrame(STM_PING, (uint8_t*) 0x47, 1);
    //         break;
    // default: break;
	// }

}