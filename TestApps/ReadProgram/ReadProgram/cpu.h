#pragma once
#include <cstdint>
class cpu
{
public:
	cpu();

	void loadProgram();
	void run();
	void executeOpCode();

	uint8_t opcode;
	uint16_t programCounter;
private:
	uint8_t getNextOpcode();

	uint8_t ram[0xFFFF];		// 64k
	uint8_t romBasic[8192];
	uint8_t romKernel[8192];
	uint8_t lowByte;
	uint8_t highByte;
	uint16_t stackPointer;
	uint16_t statusRegister;
	bool isRunning;
};

