#ifndef		__INTERFAZ_H_
#define		__INTERFAZ_H_

#include "firmata.h"
#include "firmio.h"
#include "firmbase.h"
#include "firmi2c.h"
#include "firmserial.h"

namespace firmata {

	class Interfaz 
	{
	public:
		Interfaz(char* port);
		~Interfaz();

		firmata::Firmata<firmata::Base, firmata::I2C>* f = NULL;
		firmata::FirmSerial* serialio;
	};
}

#endif