#ifndef __FIRMDC_H__
#define __FIRMDC_H__

#include <firmatacpp_export.h>
#include "firmata_constants.h"
#include "firmbase.h"
#include "firmio.h"

#include <functional>
using namespace std;

#define FIRMATA_DC_REQUEST		0x52
#define FIRMATA_DC_CONFIG		0x00
#define FIRMATA_DC_ON			0x01
#define FIRMATA_DC_OFF			0x02
#define FIRMATA_DC_BRAKE		0x03
#define FIRMATA_DC_INVERSE		0x04
#define FIRMATA_DC_DIR			0x05
#define FIRMATA_DC_SPEED		0x06


namespace firmata {

	class FIRMATACPP_EXPORT DC : virtual Base {
	public:
		DC(FirmIO *firmIO);
		virtual ~DC();

		void configDC(uint8_t deviceNum, uint8_t motorEnable, uint8_t motorPin1, uint8_t motorPin2);
		void DCturnOn(uint8_t deviceNum);
		void DCturnOff(uint8_t deviceNum);
		void DCbrake(uint8_t deviceNum);
		void DCinverse(uint8_t deviceNum);
		void DCsetDir(uint8_t deviceNum, uint8_t dir);
		void DCsetSpeed(uint8_t deviceNum, uint8_t speed);

	protected:
	//	virtual bool handleSysex(uint8_t command, std::vector<uint8_t> data);

	private:
	};

}

#endif // !__FIRMDC_H__

