/*NAME:		RgbEngine.cpp
* AUTHOR:	Yoran Staal
*
* DESCRIPTION: The core of the led control part of the software. The GUI sends updates to
* this class, and the class will handle it. The updates will be received intantaneously.
* This class also determines the RGB values that the leds will have, dependend on the mode
* that the engine is in. It is being waked up by the timing class (which handles the effect
* waveforms as well) 30 times/second. So the RGB data is never updated more than 30 times,
* which would be a waste of processing power.
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

	offCol.r = 0;
	offCol.g = 0;
	offCol.b = 0;

	for (auto& w : wave) {
		w = waveVal / (WAVE_WIDTH-1);
		waveVal++;
	}
	
//	for (auto& w : wave) {
//		if (waveVal < (WAVE_WIDTH - 1) / 2) {
//			w = 1;
//		}
//		else {
//			w = 0;
//		}
//		waveVal++;
//	}

//	for (auto& w : wave) {
//		if (waveVal < (WAVE_WIDTH - 1) / 2) {
//			w = sin(waveVal*2*3.1415/WAVE_WIDTH);
//		}
//		else {
//			w = 0;
//		}
//		waveVal++;
//	}

	phase.setGroups(1);

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
	if (mode == staticMode) {
		setColorAll(staticColor);
		rgbData->setData(leds);
	}
	else if (mode == effectMode1) {
		rainbow();
	}
	else if (mode == effectMode2) {
		step(10, 20, false, staticColor, offCol);
	}
}



void RgbEngine::inputBtnChange(uint32_t setting) {
	//wxLogDebug("<rgbEngine> Updating color");
	if(setting < 10) {
		mode = staticMode;
		switch (setting) {
		case 0:
			staticColor.r = 250;
			staticColor.g = 0;
			staticColor.b = 0;
			break;
		case 1:
			staticColor.r = 0;
			staticColor.g = 250;
			staticColor.b = 0;
			break;
		case 2:
			staticColor.r = 0;
			staticColor.g = 0;
			staticColor.b = 250;
			break;
		}
	}
	else {
		if (setting == 11) {
			mode = effectMode1;
		}
		if (setting == 12) {
			mode = effectMode2;
		}
	}
}



void RgbEngine::inputSldChange(uint32_t sliderID, uint32_t value) {
	switch (sliderID) {
	case 10101: 
		wxLogDebug("<rgbEngine> Updating groups, sliderID: %i", sliderID);
		phase.setGroups(value);
		break;
	case 10102: 
		wxLogDebug("<rgbEngine> Updating rate, sliderID: %i", sliderID);
		rate = value;
		break;
	}
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




void RgbEngine::step(uint16_t form, uint16_t widthLow, bool reverse, RgbColor col1, RgbColor col2) {
	
	RgbColor fxCol;
	uint16_t phaseBuf;
	fxCol.r = 0;
	fxCol.g = 0;

	if (startPh > 360) {
		startPh -= 360;
	}

	phase.setStartPhase(startPh);
	startPh += rate;
	

	for (int ledCnt = 0; ledCnt < NUM_LEDS; ledCnt++) {
		phaseBuf = phase.setForNextLed();
		fxCol.b = 255*wave[phaseBuf];
		setColorSingle(ledCnt, fxCol);
	}

	phase.debug();
	rgbData->setData(leds);

}



void RgbEngine::setColorSingle(uint16_t ledNr, RgbColor col) {
	uint16_t ledIt = 3 * ledNr;
	leds[ledIt] = col.r;
	leds[ledIt+1] = col.g;
	leds[ledIt+2] = col.b;
}




void RgbEngine::setColorAll(RgbColor col) {
	
	for (int i = 0; i < 3 * NUM_LEDS; i += 3) {
		leds[i] = col.r;
		leds[i + 1] = col.g;
		leds[i + 2] = col.b;
	}	
}

