#pragma warning( disable : 4309 )		//because of char range

#ifndef Included_MutexedData
#define Included_MutexedData

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
	std::vector<uint8_t> data;

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

	std::vector<uint8_t> getData() {
		mtx.lock();
		std::vector<uint8_t> dataOut = data;
		mtx.unlock();
		return dataOut;
	}

	bool setData(const std::vector<uint8_t> &newData) {
		if (newData.size() == dataSize) {
			mtx.lock();
			data = newData;
			mtx.unlock();
			return true;
		}
		else {
			return false;
		}
	}
};

#endif