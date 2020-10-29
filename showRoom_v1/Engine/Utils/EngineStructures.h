#pragma once
#include <cstdint>


struct RgbColor {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};


enum FxParameter { WAVEFORM, SPEED, RATE, GROUPS };
enum WaveFormType { SIN, RAMP, STEP };