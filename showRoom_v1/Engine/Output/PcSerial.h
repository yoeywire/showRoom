#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<windows.h>
#include<iostream>
#include<atlstr.h>
#include<string.h>
#include "wx/log.h"

#define BAUD_RATE 400000


class PcSerial
{
public:
	//pcSerial();
	//~pcSerial();

	int ReadByte(CString PortSpecifier);
	bool WriteComPort(CString PortSpecifier, std::vector<uint8_t> data, uint32_t byteSize);
};

