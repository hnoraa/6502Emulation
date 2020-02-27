#pragma once
#include <cstdint>
class cpu
{
public:
	cpu();

	void loadProgram(uint8_t *ram);
	void run();
	void executeOpCode();

	uint8_t opcode;
	uint16_t programCounter;
private:
	uint8_t getNextOpcode();

	uint8_t _ram[0xFFFF];		// 64k
	uint8_t _romBasic[8192];
	uint8_t _romKernel[8192];
	uint8_t _lowByte;
	uint8_t _highByte;
	uint16_t _stackPointer;
	uint16_t _statusRegister;
	bool _isRunning;
};

