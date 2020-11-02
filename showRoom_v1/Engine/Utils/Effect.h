#pragma once

#include <string>
#include "EngineStructures.h"


struct Effect {
	std::string name = "test effect";

	WaveFormType form = SIN;
	float bpm = 120;
	float rate = 1;
	uint16_t phase = 0;

	uint16_t groups = 1;
	uint16_t blocks = 1;
	uint16_t wings = 0;

	RgbColor color;
};