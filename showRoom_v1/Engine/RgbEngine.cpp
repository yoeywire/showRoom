/*NAME:		RgbEngine.cpp
* AUTHOR:	Yoran Staal
*
* DESCRIPTION: The core of the led control part of the software. The GUI sends updates to
* this class, and the class will handle it. The updates will be received intantaneously.
* This class also determines the RGB values that the leds will have, dependend on the mode
* that the engine is in. The RGB data is never updated more than 30 times, which would be 
* a waste of processing power.
*/

#include "RgbEngine.h"


RgbEngine::RgbEngine() {
	leds.reserve(DATA_SIZE);
	for (uint32_t i = 0; i < DATA_SIZE; i++) {
		leds.push_back(0x00);
		leds.push_back(0x00);
		leds.push_back(0x00);
	}

	staticColor.r = 255;
	staticColor.g = 255;
	staticColor.b = 255;

	rainbowCol.r = 250;
	rainbowCol.g = 0;
	rainbowCol.b = 0;

	std::thread timingTrigger(&RgbEngine::updateInterrupt, this);
	timingTrigger.detach();
}



RgbEngine::~RgbEngine() {
	delete rgbData;
	delete dataGateAddr;
}



void RgbEngine::updateInterrupt() {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	while (true) {
		end = std::chrono::steady_clock::now();
		//wxLogDebug("<TimingEngine> frame time %d [ms]", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
		begin = std::chrono::steady_clock::now();

		std::this_thread::sleep_for(std::chrono::microseconds(INTERVAL));
		update();
	}

}






void RgbEngine::update() {
	switch (mode) {
	case staticMode:
		setColorAll(staticColor);
		rgbData->setData(leds);
		break;

	case effectMode1:
		rainbow();
		break;
	case effectMode2: 
		fxEngine->effectUpdate();
		break;
	}
}



void RgbEngine::inputBtnChange(uint32_t buttonID) {

	switch (buttonID) {
	case 10001:
		mode = staticMode;
		break;
	case 10002:
		mode = effectMode1;
		break;
	case 10003:
		mode = effectMode2;
		break;
	}
}





void RgbEngine::inputSldChange(uint32_t sliderID, uint32_t value) {

	switch (sliderID) {
	case 10101:	
		dim = value;
		break;
	case 10102: 
		staticColor.r = value;
		break;
	case 10103:
		staticColor.g = value;
		break;
	case 10104:
		staticColor.b = value;
		break;
	}
}



void RgbEngine::fxParameterChange(FxParameter fxParType, float value) {

}



void RgbEngine::rainbow() {

	if (fade > 240) {
		if (direction == 2) {
			direction = 0;
		}
		else {
			direction++;
		}
		fade = 0;
	}

	if (direction == 0) {
		rainbowCol.r = 250 - fade;
		rainbowCol.g = fade;
		rainbowCol.b = 0;
	}
	else if (direction == 1) {
		rainbowCol.r = 0;
		rainbowCol.g = 250 - fade;
		rainbowCol.b = fade;
	}
	else {
		rainbowCol.r = fade;
		rainbowCol.g = 0;
		rainbowCol.b = 250 - fade;
	}
	fade += 6;

	setColorAll(rainbowCol);
	rgbData->setData(leds);
}




//Function that sets the color of a single LED
void RgbEngine::setColorSingle(uint16_t ledNr, RgbColor col) {
	uint16_t ledIt = 3 * ledNr;
	leds[ledIt] = col.r * dim / 255;
	leds[ledIt+1] = col.g * dim / 255;
	leds[ledIt+2] = col.b * dim / 255;
}




void RgbEngine::setColorAll(RgbColor col) {
	
	for (int i = 0; i < 3 * NUM_LEDS; i += 3) {
		leds[i] = col.r * dim / 255;
		leds[i + 1] = col.g * dim / 255;
		leds[i + 2] = col.b * dim / 255;
	}	
}