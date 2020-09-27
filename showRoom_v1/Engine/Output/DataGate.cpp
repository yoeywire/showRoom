#include "DataGate.h"


// Constructor starts up the output thread 
DataGate::DataGate(mutexedData* dataAddr, uint32_t byteSize) {
	leds = dataAddr;

	num_bytes = byteSize;
	wxLogDebug("<DataGate> Starting output thread");
	std::thread TimeOutThread(&DataGate::outputThread, this);
	TimeOutThread.detach();
	wxLogDebug("<DataGate> Output thread started");
}



// Output thread that sends data to Arduino
void DataGate::outputThread() {
	while (true) {
		char receive = pcSerial.ReadByte(PORT);							// Wait for the Arduino to allow data

		if (receive == 'A') {											// If Arduino sent permission ('A')
			const char* startAddr = leds->getData();					// Get the latest data from the memory
			pcSerial.WriteComPort(PORT, startAddr, num_bytes);			// Write to COM using the pcSerial object
		}
		
	}
}