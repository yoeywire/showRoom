#include "FxPhase.h"


FxPhase::FxPhase() {
	phaseFlt = 0;
	phase = 0;
	phaseIncr = 0;
}

void FxPhase::setGroups(uint16_t groups) {
	phaseIncr = (float) WAVE_WIDTH / groups;
}

void FxPhase::setStartPhase(uint16_t newPhase) {
	phaseFlt = WAVE_WIDTH * newPhase / 360;
	checkRange();
}

uint16_t FxPhase::setForNextLed() {
	phaseFlt += phaseIncr;
	checkRange();
	phase = phaseFlt;
	return phase;
}


void FxPhase::checkRange() {
	if (phaseFlt >= WAVE_WIDTH) {
		phaseFlt = phaseFlt - WAVE_WIDTH;
	}
}