#include "firmstepper.h"

#include <iostream>


namespace firmata {
	Stepper::Stepper(FirmIO* firmIO) : Base(firmIO) {
	};

	Stepper::~Stepper() {};

	/**
	* Asks the arduino to configure a stepper motor with the given config to allow asynchronous control of the stepper
	* @param {number} deviceNum Device number for the stepper (range 0-5, expects steppers to be setup in order from 0 to 5)
	* @param {number} type One of this.STEPPER.TYPE.*
	* @param {number} stepsPerRev Number of steps motor takes to make one revolution
	* @param {number} stepOrMotor1Pin If using EasyDriver type stepper driver, this is direction pin, otherwise it is motor 1 pin
	* @param {number} dirOrMotor2Pin If using EasyDriver type stepper driver, this is step pin, otherwise it is motor 2 pin
	* @param {number} [motorPin3] Only required if type == this.STEPPER.TYPE.FOUR_WIRE
	* @param {number} [motorPin4] Only required if type == this.STEPPER.TYPE.FOUR_WIRE
	*/

	void Stepper::configStepper(uint8_t deviceNum, uint8_t type, uint16_t stepsPerRev, uint8_t dirOrMotor1Pin, uint8_t dirOrMotor2Pin, uint8_t motorPin3, uint8_t motorPin4) {
		
		uint8_t stepsPerRev_lsb = FIRMATA_LSB(stepsPerRev);
		uint8_t stepsPerRev_msb = FIRMATA_MSB(stepsPerRev);

		sysexCommand({ FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_CONFIG, deviceNum, type, stepsPerRev_lsb, stepsPerRev_msb, dirOrMotor1Pin, dirOrMotor2Pin, motorPin3, motorPin4 });
	};

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

	void Stepper::stepStepper(uint8_t deviceNum, uint8_t direction, uint32_t steps, uint16_t speed, uint16_t accel, uint16_t decel) {

		uint8_t steps_lsb = FIRMATA_LSB(steps);
		uint8_t steps_msb = FIRMATA_MSB(steps);
		uint8_t steps_msb2 = FIRMATA_MSB2(steps);

		uint8_t speed_lsb = FIRMATA_LSB(speed);
		uint8_t speed_msb = FIRMATA_MSB(speed);
		uint8_t accel_lsb = FIRMATA_LSB(accel);
		uint8_t accel_msb = FIRMATA_MSB(accel);
		uint8_t decel_lsb = FIRMATA_LSB(decel);
		uint8_t decel_msb = FIRMATA_MSB(decel);

		sysexCommand({ FIRMATA_STEPPER_REQUEST, FIRMATA_STEPPER_STEP, deviceNum, direction, steps_lsb, steps_msb, steps_msb2, speed_lsb, speed_msb, accel_lsb, accel_msb, decel_lsb, decel_msb });
	}


	bool Stepper::handleSysex(uint8_t command, std::vector<uint8_t> data)
	{
		if (command == FIRMATA_STEPPER_REQUEST) {

			uint8_t deviceNum = data[0];

			return true;
		}
		return false;
	}



}
