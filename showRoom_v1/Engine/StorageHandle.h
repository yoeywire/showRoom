#pragma once
#define _CRT_SECURE_NO_WARNINGS	


#include <fstream>
#include <sstream>
#include <string>

#include "wx/log.h"

#include "Utils/EngineStructures.h"
#include "Utils/Effect.h"



std::ostream& operator<<(std::ostream& os, const Effect& fx);
std::ostream& operator<<(std::ostream& os, const RgbColor& col);
std::istream& operator>>(std::istream& is, const Effect& fx);



class StorageHandle
{
public:
	StorageHandle();
	~StorageHandle();

	Effect getEffect(uint16_t effNum);
	bool setEffect(uint16_t effNum, Effect effect);

private:
	std::string getFileName(FileType type, uint16_t num);

};

