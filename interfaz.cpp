#include "interfaz.h"
#include <windows.h>
#include <WinUser.h>


namespace firmata {

	Interfaz::Interfaz(char* port) {
		if (f != NULL) {
			MessageBox(0, "Firmata Exists", "Interfaz", MB_OK);
			return;
		}

		try {
			serialio = new firmata::FirmSerial(port);
			f = new firmata::Firmata<firmata::Base, firmata::I2C>(serialio);
		}
		catch (firmata::IOException e) {
			MessageBox(0, e.what(), "IO Exception", MB_OK);
		}
		catch (firmata::NotOpenException e) {
			MessageBox(0, e.what(), "NotOpen Exception", MB_OK);
		}
	};

	Interfaz::~Interfaz() {
	}


}