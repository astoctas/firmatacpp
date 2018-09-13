#include "firmaccelstepper.h"

#include <iostream>
#include <cmath>

using namespace std;

#define MAX_SIGNIFICAND 8388608 // 2^23

namespace firmata {
	AccelStepper::AccelStepper(FirmIO* firmIO) : Base(firmIO) {
	};

	AccelStepper::~AccelStepper() {};

	void AccelStepper::configStepper(uint8_t deviceNum, uint8_t type, uint8_t stepSize, uint8_t stepOrMotor1Pin, uint8_t dirOrMotor2Pin, uint8_t motorOrEnablePin3, uint8_t motorOrInvertPin4, uint8_t enablePin, uint8_t invertPins) {
		
		uint8_t iface = ((type & 0x07) << 4) | ((stepSize & 0x07) << 1);

		if (type == 1 && motorOrEnablePin3) {
			iface = iface | 0x01;
		} else if (enablePin) {
			iface = iface | 0x01;
		}

		std::vector<uint8_t> data = { FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_CONFIG, deviceNum, iface, stepOrMotor1Pin, dirOrMotor2Pin };
		if (motorOrEnablePin3) data.push_back(motorOrEnablePin3);
		if (motorOrInvertPin4) data.push_back(motorOrInvertPin4);
		if (enablePin) data.push_back(enablePin);
		if (invertPins) data.push_back(invertPins);

		sysexCommand(data);
	};

	void AccelStepper::setAccelStepper(uint8_t deviceNum, double accel) {
		const uint8_t* encoded = encodeCustomFloat(accel);
		sysexCommand({ FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_ACCEL, deviceNum, encoded[0], encoded[1], encoded[2], encoded[3] });
	}

	void AccelStepper::setSpeedStepper(uint8_t deviceNum, double speed) {
		const uint8_t* encoded = encodeCustomFloat(speed);
		sysexCommand({ FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_SPEED, deviceNum, encoded[0], encoded[1], encoded[2], encoded[3] });
	}

	void AccelStepper::stopStepper(uint8_t deviceNum) {
		sysexCommand({ FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_STOP, deviceNum });
	}

	void AccelStepper::enableOutputsStepper(uint8_t deviceNum)
	{
		sysexCommand({ FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_ENABLE, deviceNum, 0x01 });
	}


	void AccelStepper::disableOutputsStepper(uint8_t deviceNum)
	{
		sysexCommand({ FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_ENABLE, deviceNum, 0x00 });
	}

	uint8_t AccelStepper::getStatus(uint8_t deviceNum) {
		return status[deviceNum];
	}

	void AccelStepper::stepStepper(uint8_t deviceNum, int32_t steps) {
		status[deviceNum] = 1;
		const uint8_t* encoded = encode32BitSignedInteger(steps);
		enableOutputsStepper(deviceNum);
		sysexCommand({ FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_STEP, deviceNum, encoded[0], encoded[1], encoded[2], encoded[3], encoded[4] });
	}


	bool AccelStepper::handleSysex(uint8_t command, std::vector<uint8_t> data)
	{
		if (command == FIRMATA_STEPPER_REQUEST) {

			uint8_t stepCommand = data[0];

			if (stepCommand == FIRMATA_STEPPER_MOVE_COMPLETE) {
				uint8_t deviceNum = data[1];
				disableOutputsStepper(deviceNum);
				status[deviceNum] = 0;
			}


			return true;
		}
		return false;
	}

	const uint8_t* AccelStepper::encode32BitSignedInteger(int32_t data) {
		static uint8_t encoded[5] = {};
		uint8_t negative = data < 0;

		uint32_t d = abs((long)data);

		encoded[0] = d & 0x7F;
		encoded[1] = (d >> 7) & 0x7F;
		encoded[2] = (d >> 14) & 0x7F;
		encoded[3] = (d >> 21) & 0x7F;
		encoded[4] = (d >> 28) & 0x07;

		if (negative) {
			encoded[4] |= 0x08;
		}

		return encoded;
	}

	const uint8_t* AccelStepper::encodeCustomFloat(double input) {
		static uint8_t encoded[4] = {};
		uint8_t exponent = 0;
		uint8_t sign = input < 0 ? 1 : 0;

		//input = abs((long)input);
		double base10 = floor(log10(input));

		// Shift decimal to start of significand
		exponent += base10;
		input /= pow(10, base10);

		// Shift decimal to the right as far as we can
		while ((input - trunc(input) > 0) // ES FLOAT?
			&& input < MAX_SIGNIFICAND) {
			exponent -= 1;
			input *= 10;
		}
		// Reduce precision if necessary
		while (input > MAX_SIGNIFICAND) {
			exponent += 1;
			input /= 10;
		}
		input = trunc(input);
		exponent += 11;

		encoded[0] = (uint16_t)input & 0x7f;
		encoded[1] = ((uint16_t)input >> 7) & 0x7f;
		encoded[2] = ((uint16_t)input >> 14) & 0x7f;
		encoded[3] = ((uint16_t)input >> 21) & 0x03 | (exponent & 0x0f) << 2 | (sign & 0x01) << 6;

		return encoded;
	}

}
