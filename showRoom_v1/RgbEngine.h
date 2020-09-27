/*NAME:		RgbEngine.h
* AUTHOR:	Yoran Staal
* 
* DESCRIPTION: The core of the led control part of the software. The GUI sends updates to
* this class, and the class will handle it. The updates will be received intantaneously.
* This class also determines the RGB values that the leds will have, dependend on the mode 
* that the engine is in. It is being waked up by the timing class (which handles the effect 
* waveforms as well) 30 times/second. So the RGB data is never updated more than 30 times,
* which would be a waste of processing power.
*/

#pragma once

// This is needed to make the wx log library work without warnings
#define _CRT_SECURE_NO_WARNINGS	

#include<string.h>
#include<iostream>
#include<array>
#include"DataGate.h"
#include"utils/mutexedData.h"
#include"FxPhase.h"

#include "wx/log.h"

// Number of leds are defined, as well as the number of bytes
#define NUM_LEDS 296
#define DATA_SIZE NUM_LEDS*3

#define FRAME_RATE 30
#define INTERVAL 1000000/FRAME_RATE

#define WAVE_WIDTH 1024

enum Mode {staticMode , effectMode1, effectMode2};

struct RgbColor {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};



class RgbEngine
{
public:
	RgbEngine();
	~RgbEngine();

	void inputBtnChange(uint32_t setting);
	void inputSldChange(uint32_t sliderID, uint32_t value);
	
	

private:
	void update();
	void updateInterrupt();
	void setColorAll(RgbColor col);
	void setColorSingle(uint16_t ledNr, RgbColor col);
	void step(uint16_t widthHigh, uint16_t widthLow, bool reverse, RgbColor col1, RgbColor col2);
	void rainbow();
	std::string leds;

	mutexedData* rgbData = new mutexedData(NUM_LEDS);
	DataGate* dataGateAddr = new DataGate(rgbData, DATA_SIZE);

	//TimingEngine* timingEngine = new TimingEngine(this);
	Mode mode = staticMode;
	RgbColor staticColor;

	//Rainbow fx init values
	uint16_t fade = 0;
	uint8_t direction = 0;
	RgbColor rainbowCol;

	//fx init values;
	FxPhase phase;
	uint16_t startPh = 360;
	uint16_t rate = 10;
	RgbColor offCol;
	std::array <float, WAVE_WIDTH> wave = {};
	float waveVal = 0;
};