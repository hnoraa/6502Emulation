#pragma once
#include <cstdint>
class cpu
{
public:
	cpu();

	void loadProgram(uint8_t *ram);
	void run();
	void executeOpCode();

	uint8_t opcode;				// first part of the instruction
	uint8_t operand;			// last part of the instruction

	uint16_t programCounter;	// program counter register (holds current instruction)
private:
	uint8_t _ram[0xFFFF];		// 64k ($0000 - 00FF)
	uint8_t _lowByte;
	uint8_t _highByte;

	// registers
	uint8_t _regA;	// accumulator
	uint8_t _regX;	// x Index
	uint8_t _regY;	// y Index
	uint8_t _regP;	// processor status
	uint16_t _regS;	// stack pointer

	// flags
	bool _fN;	// negative: 1 - negative, 0 - positive
	bool _fV;	// overflow: set whenever an arithmetic, storage, or logical operation produces a result too large to be represented in a byte. always assumes signed bytes, so anything greater than 127 or less than -127 will result in this flag being set to 1, otherwise it's cleared to 0.
	bool _f1;	// always 1: always set to 1
	bool _fB;	// break:  set when the program executes a BRK instruction
	bool _fD;	// decimal: does BCD to binary conversion
	bool _fI;	// interrupt: when set to 1, interrupts are disabled
	bool _fZ;	// zero: set to 1 whenever an arithmetic, storage, or logical operation produces a result equal to zero, otherwise it is cleared to 0
	bool _fC;	// carry: this bit holds the the most significant bit that is carried beyond the 8 bits of a byte

	bool _isRunning;
};

