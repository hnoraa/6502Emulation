#pragma once
#include <cstdint>
#include <vector>
#include <string>

// forward declare bus
class Bus;

class CPU6502
{
public:
	enum FLAGS6502
	{
		C = (1 << 0),		// carry
		Z = (1 << 1),		// zero
		I = (1 << 2),		// disable interrupts
		D = (1 << 3),		// decimal mode
		B = (1 << 4),		// break
		U = (1 << 5),		// unused
		V = (1 << 6),		// overflow - signed
		N = (1 << 7),		// negative - signed
	};
	
	CPU6502();
	~CPU6502();

	// coms with bus
	void ConnectBus(Bus* n) { bus = n;  }

	// registers
	uint8_t a = 0x00;		// accumulator
	uint8_t x = 0x00;		// x register
	uint8_t y = 0x00;		// y register
	uint8_t sp = 0x00;		// stack pointer
	uint16_t pc = 0x0000;	// program counter
	uint8_t status = 0x00;	// status register

	// addressing modes - returns 1 or 0 if additional cycles are needed
	uint8_t IMP();			// implied	
	uint8_t IMM();			// immediate
	uint8_t ZP0();			// zero page
	uint8_t ZPX();			// zero page x
	uint8_t ZPY();			// zero page y
	uint8_t REL();			// relative
	uint8_t ABS();			// absolute - directly access memory address using absolute value
	uint8_t ABX();			// absolute x
	uint8_t ABY();			// absolute y
	uint8_t IND();			// indirect indexed
	uint8_t IZX();			// indirect indexed x
	uint8_t IZY();			// indirect indexed y

	// opcodes - returns 1 or 0 if additional cycles are needed	
	uint8_t ADC();			// add with carry
	uint8_t AND();			// and
	uint8_t ASL();			// shift accumulator one bit left 
	uint8_t BCC();			// branch on carry clear
	uint8_t BCS();			// branch on carry set
	uint8_t BEQ();			// branch on result 0
	uint8_t BIT();			// test bits in memory with accumulator
	uint8_t BMI();			// branch on result minus
	uint8_t BNE();			// branch on result not 0
	uint8_t BPL();			// branch on result plus
	uint8_t BRK();			// break (force)
	uint8_t BVC();			// branch on overflow clear
	uint8_t BVS();			// branch on overflow set
	uint8_t CLC();			// clear carry flag
	uint8_t CLD();			// clear decimal mode flag
	uint8_t CLI();			// clear interrupt disable flag
	uint8_t CLV();			// clear overflow flag
	uint8_t CMP();			// compare memory with accumulator
	uint8_t CPX();			// compare memory with x register
	uint8_t CPY();			// compare memory with y register
	uint8_t DEC();			// decrement by 1
	uint8_t DEX();			// decrement x register by 1
	uint8_t DEY();			// decrement y register by 1
	uint8_t EOR();			// exclusive or
	uint8_t INC();			// increment by 1
	uint8_t INX();			// increment x register by 1
	uint8_t INY();			// increment y register by 1
	uint8_t JMP();			// jump
	uint8_t JSR();			// jump to subroutine
	uint8_t LDA();			// load into accumulator
	uint8_t LDX();			// load into x register
	uint8_t LDY();			// load into y register
	uint8_t LSR();			// shift accumulator one bit right
	uint8_t NOP();			// no operation
	uint8_t ORA();			// or
	uint8_t PHA();			// push accumulator on stack
	uint8_t PHP();			// push processor on stack	(status register)
	uint8_t PLA();			// pull accumulator from stack
	uint8_t PLP();			// pull processor on stack (status register)
	uint8_t ROL();			// rotate left one bit
	uint8_t ROR();			// rotate right one bit
	uint8_t RTI();			// return from interrupt
	uint8_t RTS();			// return from subroutine
	uint8_t SBC();			// subtract memory from accumulator with borrow
	uint8_t SEC();			// set carry flag
	uint8_t SED();			// set decimal flag
	uint8_t SEI();			// set disable interrupt flag
	uint8_t STA();			// store accumulator in memory
	uint8_t STX();			// store x register in memory
	uint8_t STY();			// store y register in memory
	uint8_t TAX();			// transfer accumulator to x register
	uint8_t TAY();			// transfer accumulator to y register
	uint8_t TSX();			// transfer stack pointer to x register
	uint8_t TXA();			// transfer x register to accumulator
	uint8_t TXS();			// transfer x register to stack pointer
	uint8_t TYA();			// transfer y register to accumulator
	uint8_t XXX();			// illegal opcodes catchall

	// inputs
	void Clock();			// clock cycles

	// these 3 inputs need to run asynchronously and interrupt the processor at any time
	void Reset();			// reset the registers
	void Irq();				// interrupt request signal (standard interrupts, can be ignored if if the interrupt disabled flag is set)
	void Nmi();				// non-maskable interrupt request signal (not disableable)

	// helpers - fetch data from the appropriate source and store it into the fetched variable
	uint8_t Fetch();
	uint8_t fetched = 0x00;

	// memory location (absolute)
	uint16_t addrAbs = 0x0000;

	// relative address
	uint16_t addrRel = 0x00;

	// current opcode
	uint8_t opcode = 0x00;

	// number of cycles in the current instruction
	uint8_t cycles = 0;
private:
	Bus *bus = nullptr;
	void Write(uint16_t addr, uint8_t data);
	uint8_t Read(uint16_t addr);

	uint8_t GetFlag(FLAGS6502 flag);
	void SetFlag(FLAGS6502 flag, bool v);

	// struct to hold the 16 x 16 table of opcodes
	struct INSTRUCTION
	{
		std::string name;								// opcode mnemonic (3 letter name)
		uint8_t(CPU6502::* operate)(void) = nullptr;	// function pointer to the operation mode (which opcode)
		uint8_t(CPU6502::* addrmode)(void) = nullptr;	// function pointer to the address mode
		uint8_t cycles = 0;								// number of clock cycles the instruction requires to execute
	};

	std::vector<INSTRUCTION> lookup;
};
