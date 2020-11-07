
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
	generateWave();
	calcSpeedIncr();

}



void FxEngine::setFxParameter(FxParameter fxPrm, float value) {
	wxLogDebug("<fxEngine> Updating fx");

	switch (fxPrm) {
	case WAVEFORM:
		curFx.form = static_cast<WaveFormType>(static_cast<int>(value));
		generateWave();
		break;
	case SPEED:
		curFx.bpm = value;
		calcSpeedIncr();
		break;
	case RATE:
		curFx.bpm = value;
		calcSpeedIncr();
		break;
	case DIRECTION:
		curFx.direction = static_cast<Direction>(static_cast<int>(value));
		calcSpeedIncr();
		break;
	case GROUPS:
		phase.setGroups(value);
		break;
	case HIGH:
		curFx.high = value;
		generateWave();
		break;
	case LOW:
		curFx.low = value;
		generateWave();
		break;
	case DUTYCYCLE:
		curFx.dutycycle = value;
		generateWave();
		break;
	}
}



void FxEngine::setEffectCol(RgbColor col) {
	curFx.color = col;
}



// Function updates rgb values of a new frame
void FxEngine::effectUpdate() {
	uint16_t phaseBuf = 0;
	phase.setStartPhase(startPh);		// Set the start phase to the correct value,

	startPh += speedIncr;			// This is done for the next frame
	
	if (startPh > 360) {
		startPh -= 360;
	}
	else if (startPh < 0) {
		startPh += 360;
	}

	//Apply the effect to all leds
	int ledCnt = 0; 
	while(ledCnt < NUM_LEDS) {
		phaseBuf = phase.setForNextLed();
		dim = 255 * wave[phaseBuf];
		setColorSingle(ledCnt, curFx.color);
		ledCnt++;
	}

	// phase.debug();
	rgbData->setData(leds);

}



// Function that generates a wave value array
void FxEngine::generateWave() {

	//reset the counter
	waveVal = 0;

	//TODO: Make this work with floats!
	highF = (float)curFx.high*0.01;
	lowF = (float)curFx.low*0.01;
	hiloDif = curFx.high - curFx.low;
	hiloAvr = (curFx.high + curFx.low) / 2;

	switch (curFx.form)
	{
	case SIN:
		for (auto& w : wave) {
			w = (hiloDif * 0.5 * sin(waveVal * 2 * 3.1415 / WAVE_WIDTH) + 0.5 + hiloAvr) / 100;

			if (w < 0) {
				w = 0;
			}
			else if (w > 1) {
				w = 1;
			}
			waveVal++;
		}
		break;

	case RAMP:
		for (auto& w : wave) {
			w = (hiloDif * waveVal / (WAVE_WIDTH - 1) + hiloAvr - (hiloDif / 2)) / 100;

			if (w < 0) {
				w = 0;
			}
			else if (w > 1) {
				w = 1;
			}
			waveVal++;
		}
		break;

	case INVRAMP:
		for (auto& w : wave) {
			w = (hiloDif * (WAVE_WIDTH - waveVal) / (WAVE_WIDTH - 1) + hiloAvr - (hiloDif / 2)) / 100;

			if (w < 0) {
				w = 0;
			}
			else if (w > 1) {
				w = 1;
			}
			waveVal++;
		}

		break;

	case STEP:
		float hiF = (float)curFx.high * 0.01;
		float loF = (float)curFx.low * 0.01;

		for (auto& w : wave) {
			if (waveVal < curFx.dutycycle * 0.01 * (WAVE_WIDTH - 1)) {
				w = hiF;
			}
			else {
				w = loF;
			}
			waveVal++;
		}

		break;
	}
}


//Function that sets the color of a single LED
void FxEngine::setColorSingle(uint16_t ledNr, RgbColor col) {
	uint16_t ledIt = 3 * ledNr;
	leds[ledIt] = curFx.color.r * dim / 255;
	leds[ledIt + 1] = curFx.color.g * dim / 255;
	leds[ledIt + 2] = curFx.color.b * dim / 255;
}


// Function that calculates the increment in the wave array per frame
void FxEngine::calcSpeedIncr() {
	speedIncr = (int)(curFx.bpm * curFx.bpm * WAVE_WIDTH) * 0.000277;			// bpm*rate*wavewidth/60 seconds/30 frames * 0.5?
	if (curFx.direction == REVERSE)
		speedIncr = -speedIncr;
}
