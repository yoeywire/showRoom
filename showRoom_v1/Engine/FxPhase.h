#pragma once

#include "wx/log.h"

#define NUM_LEDS 296
#define WAVE_WIDTH 1024


class FxPhase
{
public:
	FxPhase();
	void setGroups(uint16_t groups);
	void setStartPhase(uint16_t Phase);
	uint16_t setForNextLed();

	void debug() {
		wxLogDebug("<rgbEngine> Final phase: %d", phase);
		wxLogDebug("<rgbEngine> Phase incr: %f", phaseIncr);
	}

private:
	float phaseFlt;
	float phaseIncr;
	uint16_t phase;
	uint16_t dir;

	void checkRange();
};

