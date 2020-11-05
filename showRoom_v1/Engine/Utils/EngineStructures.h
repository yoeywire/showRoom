#pragma once
#include <cstdint>
#include <iostream> // std::cout


struct RgbColor {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

enum FileType {EFFECT};
enum FxParameter { WAVEFORM, SPEED, RATE, DIRECTION, GROUPS, HIGH, LOW, DUTYCYCLE };
enum WaveFormType { SIN, RAMP, INVRAMP, STEP};
enum Direction {FORWARD, REVERSE};
