#include "firmdc.h"

#include <iostream>


namespace firmata {
	DC::DC(FirmIO* firmIO) : Base(firmIO) {
	};

	DC::~DC() {};


	void DC::configDC(uint8_t deviceNum, uint8_t motorEnable, uint8_t motorPin1, uint8_t motorPin2) {
		sysexCommand({ FIRMATA_DC_REQUEST, FIRMATA_DC_CONFIG, deviceNum, motorEnable, motorPin1, motorPin2 });
	};

	void DC::DCturnOn(uint8_t deviceNum) {
		sysexCommand({ FIRMATA_DC_REQUEST, FIRMATA_DC_ON, deviceNum });
	};

	void DC::DCturnOff(uint8_t deviceNum) {
		sysexCommand({ FIRMATA_DC_REQUEST, FIRMATA_DC_OFF, deviceNum });
	};

	void DC::DCbrake(uint8_t deviceNum) {
		sysexCommand({ FIRMATA_DC_REQUEST, FIRMATA_DC_BRAKE, deviceNum });
	};

	void DC::DCinverse(uint8_t deviceNum) {
		sysexCommand({ FIRMATA_DC_REQUEST, FIRMATA_DC_INVERSE, deviceNum });
	};

	void DC::DCsetDir(uint8_t deviceNum, uint8_t dir) {
		sysexCommand({ FIRMATA_DC_REQUEST, FIRMATA_DC_DIR, deviceNum, dir });
	};

	void DC::DCsetSpeed(uint8_t deviceNum, uint8_t speed) {
		sysexCommand({ FIRMATA_DC_REQUEST, FIRMATA_DC_SPEED, deviceNum, speed });
	};




}
