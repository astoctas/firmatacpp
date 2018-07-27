#include <iostream>
#pragma once
#include <windows.h>
#include "firmata.h"
#include "interfaz.h"
#include "firmserial.h"

using namespace std;

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

typedef void (__stdcall *OPEN)(LPSTR);
typedef LPSTR (__stdcall *ENUM)();
typedef void (__stdcall *DW)(WORD, WORD);
typedef void (__stdcall *RA)(WORD, WORD);
typedef DWORD (__stdcall *AR)(LPSTR);


int main(int argc, const char* argv[])
{
	HINSTANCE hinstLib;
	hinstLib = LoadLibrary("FirmataDll.dll");
	OPEN ProcAdd = (OPEN)GetProcAddress(hinstLib, "Open");
	ENUM ProcEnum = (ENUM)GetProcAddress(hinstLib, "EnumeratePorts");
	DW digitalWrite = (DW)GetProcAddress(hinstLib, "digitalWrite");
	RA reportAnalog = (DW)GetProcAddress(hinstLib, "reportAnalog");
	AR analogRead = (AR)GetProcAddress(hinstLib, "analogRead");
	//cout << (ProcEnum)();
	char port[5] = "COM6";
	(ProcAdd)(port);
	(reportAnalog)(1, 1);
	(reportAnalog)(2, 1);
	(reportAnalog)(3, 1);
	(reportAnalog)(4, 1);
	(reportAnalog)(5, 1);
	(reportAnalog)(6, 1);
	while (true) {
		/*
		(digitalWrite)(13, 1);
		Sleep(500);
		(digitalWrite)(13, 0);
		Sleep(500);
		*/
		Sleep(100);
		DWORD a = (analogRead)("A1");
		cout << a << endl;


	}
}
