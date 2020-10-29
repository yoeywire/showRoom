
#include "FxEngine.h"


FxEngine::FxEngine(mutexedData* RgbData) {
	rgbData = RgbData;

	leds.reserve(DATA_SIZE);
	for (uint32_t i = 0; i < DATA_SIZE; i++) {
		leds.push_back(0x00);
		leds.push_back(0x00);
		leds.push_back(0x00);
	}

	phase.setGroups(1);
	generateWave(SIN);

}




void FxEngine::setFxParameter(FxParameter fxPrm, float value) {

	switch (fxPrm) {
	case WAVEFORM:
		form = static_cast<WaveFormType>(static_cast<int>(value));
		generateWave(form);
		break;
	case SPEED:

		break;
	case RATE:

		break;
	case GROUPS:
		phase.setGroups(value);
		break;
	}
}




void FxEngine::effectUpdate() {

	RgbColor fxCol;
	uint16_t phaseBuf;
	fxCol.r = 0;
	fxCol.g = 0;

	if (startPh > 360) {
		startPh -= 360;
	}

	phase.setStartPhase(startPh);	// Set the start phase to the correct value
	startPh += rate;				// This is done for the next effect frame

	//Apply the effect to all leds
	for (int ledCnt = 0; ledCnt < NUM_LEDS; ledCnt++) {
		phaseBuf = phase.setForNextLed();
		fxCol.b = 255 * wave[phaseBuf];
		setColorSingle(ledCnt, fxCol);
	}

	phase.debug();
	rgbData->setData(leds);

}



void FxEngine::generateWave(WaveFormType waveType) {

	//reset the counter
	waveVal = 0;

	// Sinewave
	if (waveType == SIN) {
		for (auto& w : wave) {
			w = sin(waveVal * 2 * 3.1415 / WAVE_WIDTH);
			if (w < 0) {
				w = 0;
			}
			else if (w > 1) {
				w = 1;
			}
			waveVal++;
		}
	}

	// Ramp
	else if (waveType == RAMP) {
		for (auto& w : wave) {
			w = waveVal / (WAVE_WIDTH - 1);
			waveVal++;
		}
	}
	
	// Step
	else if (waveType == STEP) {
		for (auto& w : wave) {
			if (waveVal < (WAVE_WIDTH - 1) / 2) {
				w = 1;
			}
			else {
				w = 0;
			}
			waveVal++;
		}
	}
}


//Function that sets the color of a single LED
void FxEngine::setColorSingle(uint16_t ledNr, RgbColor col) {
	uint16_t ledIt = 3 * ledNr;
	leds[ledIt] = col.r;
	leds[ledIt + 1] = col.g;
	leds[ledIt + 2] = col.b;
}




//void FxEngine::setColorAll(RgbColor col) {
//	for (int i = 0; i < 3 * NUM_LEDS; i += 3) {
//		leds[i] = col.r;
//		leds[i + 1] = col.g;
//		leds[i + 2] = col.b;
//	}
//}