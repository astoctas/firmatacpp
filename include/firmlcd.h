#ifndef __FIRMLCD_H__
#define __FIRMLCD_H__

#include <firmatacpp_export.h>
#include "firmata_constants.h"
#include "firmbase.h"
#include "firmio.h"

using namespace std;

#define FIRMATA_MSB2(x)					(((x) >> 14) & 0x7F)

#define FIRMATA_LCD_REQUEST	0x03
#define FIRMATA_LCD_PRINT 0x00
#define FIRMATA_LCD_PUSH  0x01
#define FIRMATA_LCD_CLEAR 0x02


namespace firmata {

	class FIRMATACPP_EXPORT LCD : virtual Base {
	public:
		LCD(FirmIO *firmIO);
		virtual ~LCD();

		void printLCD(uint8_t row, const char* str);
		void pushLCD(const char* str);
		void clearLCD();
	protected:
//		virtual bool handleSysex(uint8_t command, std::vector<uint8_t> data);

	private:
	};

}

#endif // !__FIRMLCD_H__

