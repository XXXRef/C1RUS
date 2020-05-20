#include <cstddef>

#include "utils.hpp"

std::size_t MARKER_BODYEND();
std::size_t getEIP();

std::size_t MARKER_BODYBEGIN() {
	std::size_t curEIP = getEIP();
	const std::size_t offsetTillFuncBegin = 0x9;
	return curEIP - offsetTillFuncBegin;
}

std::size_t getEIP() {
	std::size_t stackCanary;
	std::size_t* stackIter = &stackCanary;
	//stack now:
	//eip 2
	//ebp 1
	//stackCanary 0
	//stackIter
	return stackIter[3];
}

int main() {
	std::size_t pVirusBodyBegin = MARKER_BODYBEGIN();
	std::size_t pVirusBodyEnd = MARKER_BODYEND();

	//instruction <-
}

std::size_t MARKER_BODYEND() {
	std::size_t curEIP = getEIP();
	const std::size_t offsetTillFuncEnd = 0x14;
	return curEIP + offsetTillFuncEnd;
}