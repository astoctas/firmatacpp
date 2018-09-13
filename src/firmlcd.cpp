#include "firmlcd.h"

#include <iostream>


namespace firmata {
	LCD::LCD(FirmIO* firmIO) : Base(firmIO) {
	};

	LCD::~LCD() {};

	void LCD::printLCD(uint8_t row, const char* str) {

		std::vector<uint8_t> data;
		data.push_back(FIRMATA_LCD_REQUEST);
		data.push_back(FIRMATA_LCD_PRINT);
		data.push_back(row);

		string bytes(str);
		int length = bytes.length();

		for (int i = 0; i < length; i++) {
			data.push_back(bytes[i] & 0x7F);
			data.push_back((bytes[i] >> 7) & 0x7F);
		}

		sysexCommand(data);
	}

	void LCD::pushLCD(const char* str) {

		std::vector<uint8_t> data;
		data.push_back(FIRMATA_LCD_REQUEST);
		data.push_back(FIRMATA_LCD_PUSH);

		string bytes(str);
		int length = bytes.length();

		for (int i = 0; i < length; i++) {
			data.push_back(bytes[i] & 0x7F);
			data.push_back((bytes[i] >> 7) & 0x7F);
		}

		sysexCommand(data);
	}

	void LCD::clearLCD() {
		sysexCommand({ FIRMATA_LCD_REQUEST , FIRMATA_LCD_CLEAR });
	}


}