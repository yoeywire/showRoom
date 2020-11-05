#pragma once

// This is needed to make the wx log library work without warnings
#define _CRT_SECURE_NO_WARNINGS	

#include <cstdint>
#include <array>
#include <string>

#include "Utils/EngineStructures.h"
#include "Utils/mutexedData.h"
#include "Utils/Effect.h"
#include "FxPhase.h"



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
	void setEffectCol(RgbColor col);


private:
	
	void setColorSingle(uint16_t ledNr, RgbColor col);
	void calcSpeedIncr();
	void generateWave();

	std::string leds;
	mutexedData* rgbData =  nullptr;
	FxPhase phase;


	//fx foreground parameters (stored inside effect structure)
	Effect curFx;
	

	//fx background values
	int16_t startPh = 0;
	uint16_t speedIncr = 0;
	uint8_t dim = 0;
	float highF;
	float lowF;
	int16_t hiloDif;
	int16_t hiloAvr;

	std::array <float, WAVE_WIDTH> wave = {};
	float waveVal = 0;
};

