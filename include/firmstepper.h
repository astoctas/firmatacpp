#ifndef __FIRMSTEPPER_H__
#define __FIRMSTEPPER_H__

#include <firmatacpp_export.h>
#include "firmata_constants.h"
#include "firmbase.h"
#include "firmio.h"

#include <functional>
using namespace std;

#define FIRMATA_MSB2(x)					(((x) >> 14) & 0x7F)

 #define FIRMATA_STEPPER_REQUEST	0x72
 #define FIRMATA_STEPPER_CONFIG		0x00
 #define FIRMATA_STEPPER_STEP		0x01

namespace firmata {

	class FIRMATACPP_EXPORT Stepper : virtual Base {
	public:
		Stepper(FirmIO *firmIO);
		virtual ~Stepper();

		void configStepper(uint8_t deviceNum, uint8_t type, uint16_t stepsPerRev, uint8_t dirOrMotor1Pin, uint8_t dirOrMotor2Pin, uint8_t motorPin3, uint8_t motorPin4);
		void stepStepper(uint8_t deviceNum, uint8_t direction, uint32_t steps, uint16_t speed, uint16_t accel, uint16_t decel);
	protected:
		virtual bool handleSysex(uint8_t command, std::vector<uint8_t> data);

	private:
	};

}

#endif // !__FIRMSTEPPER_H__
