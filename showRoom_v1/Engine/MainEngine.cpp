/*NAME:		MainEngine.h
* AUTHOR:	Yoran Staal
*
* DESCRIPTION: The core of the control part of the software. The GUI sends all updates to
* this class, and they will be handles here. The updates will be received intantaneously.
* There is also a seperate thread that takes care of frame updates (30 FPS). Dependend on
* the mode that the engine is in it will write the static RGB values or let the fxEngine
* class take care of it.
*/

#include "MainEngine.h"


MainEngine::MainEngine() {
	leds.reserve(DATA_SIZE);
	for (uint32_t i = 0; i < DATA_SIZE; i++) {
		leds.push_back(0x00);
		leds.push_back(0x00);
		leds.push_back(0x00);
	}

	staticColor.r = 255;
	staticColor.g = 255;
	staticColor.b = 255;

	fxEngine->setEffectCol(staticColor);

	rainbowCol.r = 250;
	rainbowCol.g = 0;
	rainbowCol.b = 0;

	std::thread timingTrigger(&MainEngine::updateInterrupt, this);
	timingTrigger.detach();

	Effect fx{ "Test1", RAMP, FORWARD, 110, 1, 360, 100, 0, 50, 1, 1, 0, {255, 255, 0}};
	StorageHandle store;

	store.setEffect(1, fx);
	store.getEffect(1);

}



MainEngine::~MainEngine() {
	delete rgbData;
	delete dataGateAddr;
	delete fxEngine;
}



// Timer that calls the update function. Clock lines for debugging purposes
void MainEngine::updateInterrupt() {
	// std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	// std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	while (true) {
		// end = std::chrono::steady_clock::now();
		// wxLogDebug("<TimingEngine> frame time %d [ms]", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
		// begin = std::chrono::steady_clock::now();
		std::this_thread::sleep_for(std::chrono::microseconds(INTERVAL));
		update();
	}

}






void MainEngine::update() {
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



void MainEngine::inputBtnChange(uint32_t buttonID) {

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





void MainEngine::inputSldChange(uint32_t sliderID, uint32_t value) {

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

	fxEngine->setEffectCol(staticColor);
}



void MainEngine::fxParameterChange(FxParameter fxParType, float value) {
	fxEngine->setFxParameter(fxParType, value);
}



void MainEngine::rainbow() {

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
void MainEngine::setColorSingle(uint16_t ledNr, RgbColor col) {
	uint16_t ledIt = 3 * ledNr;
	leds[ledIt] = col.r * dim / 255;
	leds[ledIt+1] = col.g * dim / 255;
	leds[ledIt+2] = col.b * dim / 255;
}




void MainEngine::setColorAll(RgbColor col) {
	for (int i = 0; i < 3 * NUM_LEDS; i += 3) {
		leds[i] = col.r * dim / 255;
		leds[i + 1] = col.g * dim / 255;
		leds[i + 2] = col.b * dim / 255;
	}	
}