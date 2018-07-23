#include <iostream>
#pragma once
#include <windows.h>
#include "firmata.h"
#include "interfaz.h"
#include "firmserial.h"
#include <vector>

#ifndef WIN32
#include "unistd.h"
#endif

/*
 * Detect first serial port with a StandardFirmata interface
 * Read analog inputs A0 and A1 and digital pin 2 (eg, a Playstation analog stick + button)
 * as well as I2C address 8 (eg, the slave_sender example that comes with Arduino IDE)
 * and print to stdout
 */

std::vector<firmata::Interfaz> i;

typedef void (__cdecl *MYPROC)(int);
typedef void (__cdecl *REPORT)(uint8_t, uint8_t);


int main(int argc, const char* argv[])
{
	HINSTANCE hinstLib;
	MYPROC ProcAdd;
	REPORT ProcReport;
	hinstLib = LoadLibrary("FirmataDll.dll");
	ProcAdd = (MYPROC)GetProcAddress(hinstLib, "Open");
	ProcReport = (REPORT)GetProcAddress(hinstLib, "reportAnalog");
	(ProcAdd)(4);
	(ProcReport)(1,1);
	//firmata::Interfaz j("COM4");
	//i.push_back(j);
	
	//i.at(0).f->pinMode(1, 1);
}
