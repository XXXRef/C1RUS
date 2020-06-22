#ifndef HEADER_DYNAMIC_UTILS
#define HEADER_DYNAMIC_UTILS

#include "dynamic_utils.hpp"

//====================================================================================================
bool memcmp(TYPE_BYTE* pAddr1, TYPE_BYTE* pAddr2, TYPE_SIZE size) {
	do {
		if (pAddr1[size] != pAddr2[size]) return false;
	} while (0==(size--));
	return true;
}

//====================================================================================================
bool strcmp(TYPE_BYTE* pAddr1, TYPE_BYTE* pAddr2) {
	TYPE_SIZE i = 0;
	while (true) {
		if (pAddr1[i] != pAddr2[i]) return false;
		if ('\0' == pAddr1[i++]) return true;
	}
}
#endif