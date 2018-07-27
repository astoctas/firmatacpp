#include "interfaz.h"
#include <windows.h>
#include <WinUser.h>
#include <iostream>
#include <future>

using namespace std;

namespace firmata {

	Interfaz::Interfaz(char* port) {
		if (f != NULL) {
			MessageBox(0, "Firmata Exists", "Interfaz", MB_OK);
			return;
		}

		try {
			serial::Serial m_serial(port, 57600);
			if(!m_serial.isOpen())	m_serial.open();
			m_serial.flush();
			m_serial.setDTR();
			m_serial.close();
			_sleep(4000); // 4 segs para reporte de version

			serialio = new firmata::FirmSerial(port);
			f = new firmata::Firmata<firmata::Base, firmata::I2C, firmata::Stepper>(serialio);
			try
			{
				//auto handle = std::async (std::launch::async, &Interfaz::parse, this);
				//parseThread.join();
				//parseThread.detach();
			}
			catch (const std::exception &ex)
			{
				std::cout << "Thread exited with exception: " << ex.what() << "\n";
			}
			
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

	void Interfaz::parse() {
		while (true) {
			//cout << "parse" << endl;;
			try {
				if(serialio->isOpen() && serialio->available())
					f->parse();
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
		}
	}




}