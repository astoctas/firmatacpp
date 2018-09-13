#ifndef __FIRMACCELSTEPPER_H__
#define __FIRMACCELSTEPPER_H__

#include <firmatacpp_export.h>
#include "firmata_constants.h"
#include "firmbase.h"
#include "firmio.h"

#include <functional>
using namespace std;

#define FIRMATA_MSB2(x)					(((x) >> 14) & 0x7F)

 #define FIRMATA_STEPPER_REQUEST	0x62
 #define FIRMATA_STEPPER_CONFIG		0x00
 #define FIRMATA_STEPPER_STEP		0x02
 #define FIRMATA_STEPPER_ENABLE		0x04
 #define FIRMATA_STEPPER_STOP		0x05
 #define FIRMATA_STEPPER_REPORT_POSITION		0x06
 #define FIRMATA_STEPPER_ACCEL	0x08
 #define FIRMATA_STEPPER_SPEED		0x09
 #define FIRMATA_STEPPER_MOVE_COMPLETE		0x0a

namespace firmata {

	class FIRMATACPP_EXPORT AccelStepper : virtual Base {
	public:
		AccelStepper(FirmIO *firmIO);
		virtual ~AccelStepper();

		void configStepper(uint8_t deviceNum, uint8_t type, uint8_t stepSize, uint8_t stepOrMotor1Pin, uint8_t dirOrMotor2Pin, uint8_t motorOrEnablePin3 = 0, uint8_t motorOrInvertPin4 = 0, uint8_t enablePin = 0, uint8_t invertPins = 0);
		void stepStepper(uint8_t deviceNum, int32_t steps);

		void setSpeedStepper(uint8_t deviceNum, double speed);
		void setAccelStepper(uint8_t deviceNum, double accel);
		void stopStepper(uint8_t deviceNum);
		void enableOutputsStepper(uint8_t deviceNum);
		void disableOutputsStepper(uint8_t deviceNum);

		uint8_t getStatus(uint8_t deviceNum);
	protected:
		virtual bool handleSysex(uint8_t command, std::vector<uint8_t> data);

	private:
		uint8_t status[1024];
		const uint8_t * encodeCustomFloat(double input);
		const uint8_t* encode32BitSignedInteger(int32_t data);
	};

}

#endif // !__FIRMACCELSTEPPER_H__
