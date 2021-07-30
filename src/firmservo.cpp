#include "firmservo.h"

#include <iostream>


namespace firmata {
	Servo::Servo(FirmIO* firmIO) : Base(firmIO) {
	};

	Servo::~Servo() {};


	void Servo::servoAttach(uint8_t deviceNum) {
		sysexCommand({ FIRMATA_SERVO_REQUEST, FIRMATA_SERVO_ATTACH, deviceNum });
	};

	void Servo::servoWrite(uint8_t deviceNum, uint8_t value) {
		uint8_t value_lsb = FIRMATA_LSB(value);
		uint8_t value_msb = FIRMATA_MSB(value);

		sysexCommand({ FIRMATA_SERVO_REQUEST, FIRMATA_SERVO_WRITE, deviceNum, value_lsb, value_msb });
	};




}
