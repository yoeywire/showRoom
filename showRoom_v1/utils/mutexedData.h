#pragma warning( disable : 4309 )		//because of char range

#ifndef Included_mutexedData
#define Included_mutexedData

#include <string>
#include <iostream>
#include <mutex>

#include "wx/log.h"


class mutexedData
{
private:
	std::mutex mtx;
	uint32_t dataSize = 296;	//hardcoded

public:
	std::string data;

	mutexedData(uint32_t dataSize) {
		wxLogDebug("<Mutexed data> Initializing mutexed data");
		data.reserve(3*dataSize);

		for (uint32_t i = 0; i < dataSize; i++) {
			data.push_back(0x00);
			data.push_back(0x00);
			data.push_back(0x00);
		}
	}

	~mutexedData() {

	}

	const char* getData() {
		mtx.lock();
		const char* dataOut = data.c_str();
		mtx.unlock();
		return dataOut;
	}

	void setData(std::string newData) {
		mtx.lock();
		data = newData;
		mtx.unlock();
	}
};

#endif