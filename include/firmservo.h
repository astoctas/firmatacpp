#ifndef __FIRMSERVO_H__
#define __FIRMSERVO_H__

#include <firmatacpp_export.h>
#include "firmata_constants.h"
#include "firmbase.h"
#include "firmio.h"

#include <functional>
using namespace std;

#define FIRMATA_SERVO_REQUEST		0x04
#define FIRMATA_SERVO_CONFIG		0x70
#define FIRMATA_SERVO_ATTACH		0x01
#define FIRMATA_SERVO_WRITE			0x02


namespace firmata {

	class FIRMATACPP_EXPORT Servo : virtual Base {
	public:
		Servo(FirmIO *firmIO);
		virtual ~Servo();

		void servoAttach(uint8_t deviceNum);
		void servoWrite(uint8_t deviceNum, uint8_t value);

	protected:
	//	virtual bool handleSysex(uint8_t command, std::vector<uint8_t> data);

	private:
	};

}

#endif // !__FIRMSERVO_H__

