#include "PcSerial.h"


int PcSerial::ReadByte(CString PortSpecifier)
{
	DCB dcb;
	int retVal;
	BYTE Byte = 0;
	DWORD dwBytesTransferred;
	DWORD dwCommModemStatus;
	HANDLE hPort = CreateFile(

		PortSpecifier,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

	if (!GetCommState(hPort, &dcb))
		return 0x100;

	dcb.BaudRate = BAUD_RATE;	//Baud
	dcb.ByteSize = 8;			//8 data bits
	dcb.Parity = NOPARITY;		//no parity
	dcb.StopBits = ONESTOPBIT;	//1 stop

	if (!SetCommState(hPort, &dcb))
		return 0x100;

	SetCommMask(hPort, EV_RXCHAR | EV_ERR);			//receive character event
	WaitCommEvent(hPort, &dwCommModemStatus, 0);	//wait for character

	if (dwCommModemStatus & EV_RXCHAR)
		ReadFile(hPort, &Byte, 1, &dwBytesTransferred, 0);	//read 1

	else if (dwCommModemStatus & EV_ERR)
		retVal = 0x101;

	retVal = Byte;
	CloseHandle(hPort);

	return retVal;
}



bool PcSerial::WriteComPort(CString PortSpecifier, std::vector<uint8_t> data, uint32_t byteSize)
{
	DCB dcb;
	DWORD byteswritten;
	HANDLE hPort = CreateFile(
		PortSpecifier,
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

	if (!GetCommState(hPort, &dcb))
		return false;

	dcb.BaudRate = BAUD_RATE;	//Baud
	dcb.ByteSize = 8;			//8 data bits
	dcb.Parity = NOPARITY;		//no parity
	dcb.StopBits = ONESTOPBIT;	//1 stop

	if (!SetCommState(hPort, &dcb))
		return false;

	char* charData = new char[data.size()];
	std::copy(data.begin(), data.end(), charData);

	WriteFile(hPort, charData, byteSize, &byteswritten, NULL);

	bool retVal = true;
	CloseHandle(hPort); //close the handle
	return retVal;
}