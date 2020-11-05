/*NAME:		MainEngine.h
* AUTHOR:	Yoran Staal
* 
* DESCRIPTION: The core of the control part of the software. The GUI sends all updates to 
* this class, and they will be handles here. The updates will be received intantaneously.
* There is also a seperate thread that takes care of frame updates (30 FPS). Dependend on
* the mode that the engine is in it will write the static RGB values or let the fxEngine 
* class take care of it.
*/

#pragma once

// This is needed to make the wx log library work without warnings
#define _CRT_SECURE_NO_WARNINGS	

#include <string.h>
#include <iostream>
#include <array>

#include "Output/DataGate.h"
#include "utils/mutexedData.h"
#include "Utils/EngineStructures.h"
#include "FxEngine.h"
#include "StorageHandle.h"
#include "Utils/Effect.h"

#include "wx/log.h"

// The different engine modes
enum Mode {staticMode , effectMode1, effectMode2};


class MainEngine
{
public:
	MainEngine();
	~MainEngine();

	void inputBtnChange(uint32_t buttonID);							// Takes care of button value changes
	void inputSldChange(uint32_t sliderID, uint32_t value);			// Takes care of slider value changes
	void fxParameterChange(FxParameter fxParType, float value);		// Takes care of fx parameter changes

private:
	void update();											// Function that updates the RGB values
	void updateInterrupt();									// This function is a timer that wakes up the thread
	void setColorAll(RgbColor col);							// Function that updates all leds to one color
	void setColorSingle(uint16_t ledNr, RgbColor col);		// Function that updates one led to a color
	void rainbow();											// RAINBOW


	std::string leds;										// 'uint_8 array' that holds all RGB values within the class
	mutexedData* rgbData = new mutexedData(NUM_LEDS);		// 

	DataGate* dataGateAddr = new DataGate(rgbData, DATA_SIZE);
	FxEngine* fxEngine = new FxEngine(rgbData);

	//Mode parameters
	Mode mode = staticMode;
	RgbColor staticColor;
	uint8_t dim = 255;

	//Rainbow fx init values
	uint16_t fade = 0;
	uint8_t direction = 0;
	RgbColor rainbowCol;

};
