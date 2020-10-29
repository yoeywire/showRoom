#pragma once

// This is needed to make the wx log library work without warnings
#define _CRT_SECURE_NO_WARNINGS	

#include <cstdint>
#include <array>
#include <string>

#include "Utils/EngineStructures.h"
#include "FxPhase.h"
#include "Utils/mutexedData.h"


// Number of leds are defined, as well as the number of bytes
#define NUM_LEDS 296
#define DATA_SIZE NUM_LEDS*3

#define FRAME_RATE 30
#define INTERVAL 1000000/FRAME_RATE

#define WAVE_WIDTH 1024




class FxEngine
{
public:
	FxEngine(mutexedData* rgbData);
	void setFxParameter(FxParameter fxPrm, float value);
	void effectUpdate();


private:
	
	void setColorSingle(uint16_t ledNr, RgbColor col);

	void generateWave(WaveFormType WaveType);

	std::string leds;
	mutexedData* rgbData =  nullptr;
	FxPhase phase;


	//fx foreground parameters
	WaveFormType form = SIN;
	float BPM = 120;
	float multiplier = 1;
	uint16_t startPh = 360;
	RgbColor col1;
	RgbColor col2;

	//fx background values
	uint16_t rate = 10;

	std::array <float, WAVE_WIDTH> wave = {};
	float waveVal = 0;
};

