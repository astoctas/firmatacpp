#include "firmaccelstepper.h"

#include <iostream>
#include <cmath>

using namespace std;

#define MAX_SIGNIFICAND 8388608 // 2^23

namespace firmata {
	AccelStepper::AccelStepper(FirmIO* firmIO) : Base(firmIO) {
	};

	AccelStepper::~AccelStepper() {};

	/**
	* Asks the arduino to configure a stepper motor with the given config to allow asynchronous control of the stepper
	* @param {number} deviceNum Device number for the stepper (range 0-5, expects steppers to be setup in order from 0 to 5)
	* @param {number} type One of this.STEPPER.TYPE.*: 
	  DRIVER: 1,
      TWO_WIRE: 2,
      THREE_WIRE: 3,
      FOUR_WIRE: 4
	* @param {number} stepSize: 
		WHOLE: 0,
		HALF: 1
	* @param {number} stepOrMotor1Pin If using EasyDriver type stepper driver, this is direction pin, otherwise it is motor 1 pin
	* @param {number} dirOrMotor2Pin If using EasyDriver type stepper driver, this is step pin, otherwise it is motor 2 pin
	* @param {number} [motorPin3] Only required if type == this.STEPPER.TYPE.FOUR_WIRE
	* @param {number} [motorPin4] Only required if type == this.STEPPER.TYPE.FOUR_WIRE
	*/

	void AccelStepper::configStepper(uint8_t deviceNum, uint8_t type, uint8_t stepSize, uint8_t dirOrMotor1Pin, uint8_t dirOrMotor2Pin, uint8_t motorPin3, uint8_t motorPin4, uint8_t enablePin) {
		
		uint8_t iface = ((type & 0x07) << 4) | ((stepSize & 0x07) << 1);

		if (enablePin) {
			iface = iface | 0x01;
		}

		std::vector<uint8_t> data = { FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_CONFIG, deviceNum, iface, dirOrMotor1Pin, dirOrMotor2Pin };
		if (motorPin3) data.push_back(motorPin3);
		if (motorPin4) data.push_back(motorPin4);
		if (enablePin) data.push_back(enablePin);

		sysexCommand(data);
	};

	void AccelStepper::setAccelStepper(uint8_t deviceNum, double accel) {
		uint8_t* encoded = encodeCustomFloat(accel);
		sysexCommand({ FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_ACCEL, deviceNum, encoded[0], encoded[1], encoded[2], encoded[3] });
	}

	void AccelStepper::setSpeedStepper(uint8_t deviceNum, double speed) {
		uint8_t* encoded = encodeCustomFloat(speed);
		sysexCommand({ FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_SPEED, deviceNum, encoded[0], encoded[1], encoded[2], encoded[3] });
	}

	void AccelStepper::stopStepper(uint8_t deviceNum) {
		sysexCommand({ FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_STOP, deviceNum });
	}

	void AccelStepper::enablePinsStepper(uint8_t deviceNum, uint8_t enable1, uint8_t enable2)
	{
		sysexCommand({ FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_ENABLE_PINS, deviceNum, enable1, enable2 });
	}

	uint8_t AccelStepper::getStatus(uint8_t deviceNum) {
		return status[deviceNum];
	}

	/**
	* Asks the arduino to move a stepper a number of steps at a specific speed
	* (and optionally with and acceleration and deceleration)
	* speed is in units of .01 rad/sec
	* accel and decel are in units of .01 rad/sec^2
	* TODO: verify the units of speed, accel, and decel
	* @param {number} deviceNum Device number for the stepper (range 0-5)
	* @param {number} direction One of this.STEPPER.DIRECTION.*
	* @param {number} steps Number of steps to make
	* @param {number} speed
	* @param {number|function} accel Acceleration or if accel and decel are not used, then it can be the callback
	* @param {number} [decel]
	*/

	void AccelStepper::stepStepper(uint8_t deviceNum, int32_t steps) {
		status[deviceNum] = 1;
		uint8_t* encoded = encode32BitSignedInteger(steps);
		sysexCommand({ FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_STEP, deviceNum, encoded[0], encoded[1], encoded[2], encoded[3], encoded[4] });
	}


	bool AccelStepper::handleSysex(uint8_t command, std::vector<uint8_t> data)
	{
		if (command == FIRMATA_STEPPER_REQUEST) {

			uint8_t stepCommand = data[0];

			if (stepCommand == FIRMATA_STEPPER_MOVE_COMPLETE) {
				uint8_t deviceNum = data[1];
				status[deviceNum] = 0;

			}


			return true;
		}
		return false;
	}

	uint8_t* AccelStepper::encode32BitSignedInteger(int32_t data) {
		uint8_t encoded[5] = {};
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

	uint8_t* AccelStepper::encodeCustomFloat(double input) {
		uint8_t encoded[4] = {};
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
