#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <thread> 
#include "../Utils/mutexedData.h"
#include "PcSerial.h"
#include "wx/log.h"

#define NUM_LEDS 296
#define PORT "COM3"

class DataGate
{
public:
	DataGate(mutexedData* dataAddr, uint32_t byteSize);
	void outputThread();

private:
	PcSerial pcSerial;
	uint32_t num_bytes;

	//mutexedData* leds = new mutexedData(NUM_LEDS);
	mutexedData* leds = nullptr;
};

