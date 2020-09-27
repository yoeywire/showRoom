#pragma once

#include <string>
#include <iostream>

struct ledStrip
{
public:
	ledStrip(uint32_t NumLeds) {
		ledstr.reserve(3*NumLeds);
	}

	unsigned r;

private:
	std::string ledstr;
	
};