#include "CPU6502.h"
#include "Bus.h"

CPU6502::CPU6502()
{
	// look up table for all of the opcodes it is an initializer list of initializer lists
	// each list has:
	// mnemonic
	// function pointer to the opcode function (ex: &a::BRK for Break)
	// function pointer to the address mode function (ex: &a::IMM for immediate addressing mode)
	// number of clock cycles
	using a = CPU6502;	// using to create a shortcut to not type CPU6502 in the 16 x 16 matrix
	lookup = {
		{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	};
}

CPU6502::~CPU6502()
{

}

// inputs
void CPU6502::Reset()
{
	a = 0x00;
	x = 0x00;
	y = 0x00;
	sp = 0x00;
	pc = 0x0000;
	status = 0x00;
}

// clock 
void CPU6502::Clock()
{
	// execute the instruction when cycles is 0
	if (cycles == 0)
	{
		opcode = Read(pc);					// read the current opcode from the program counter - returns 1 byte
		pc++;								// increment program counter
		cycles = lookup[opcode].cycles;		// set the number of cycles from the opcode matrix

		// call the required address mode function for this opcode
		uint8_t additionalCycle1 = (this->*lookup[opcode].addrmode)();	

		// call the required operation function for this opcode
		uint8_t additionalCycle2 = (this->*lookup[opcode].operate)();

		// if the instruction and operation indicate the need for additional clock cycles, add a clock cycle
		cycles += (additionalCycle1 & additionalCycle1);
	}

	// decrement cycles count
	cycles--;
}

// bus coms
void CPU6502::Write(uint16_t addr, uint8_t data)
{
	bus->Write(addr, data);
}

uint8_t CPU6502::Read(uint16_t addr)
{
	return bus->Read(addr, false);
}

// addressing
uint8_t CPU6502::IMP() {
	// implied - there is no data as part of the instruction

	// implied means it could be operating on the accumulator
	// set fetched to the contents of the accumulator
	fetched = a;

	return 0;
}

uint8_t CPU6502::IMM() {
	// immediate - second byte of the instruction contains the operand

	// advance the program counter to get the next byte because the data is the second byte
	addrAbs = pc++;

	return 0;
}

uint8_t CPU6502::ZP0() {
	// zero page - in this mode, the page is 00 (the high byte) which is the zero page
	// read the low byte from the instruction because we already know that the high byte is 0
	addrAbs = Read(pc);	// read the program counter - get the low byte
	pc++;				// increment to get the page offset (address within the page)
	addrAbs &= 0x00ff;	// mask it with 0x00ff to get the correct address offset from the low byte

	return 0;
}

uint8_t CPU6502::ZPX() {
	// zero page x indexed - access the zero page with the x register and the low byte offset
	// this is useful for iterating through regions of memory (i.e. an array)
	addrAbs = (Read(pc) + x);	// read the program counter with the additional x register offset
	pc++;						// increment to get the page offset (address within the page)
	addrAbs &= 0x00ff;			// mask it with 0x00ff to get the correct address offset from the low byte

	return 0;
}

uint8_t CPU6502::ZPY() {
	// zero page y indexed - access the zero page with the y register and the low byte offset
	// this is useful for iterating through regions of memory (i.e. an array)
	addrAbs = (Read(pc) + y);	// read the program counter with the additional y register offset
	pc++;						// increment to get the page offset (address within the page)
	addrAbs &= 0x00ff;			// mask it with 0x00ff to get the correct address offset from the low byte

	return 0;
}

uint8_t CPU6502::REL() {
	// relative
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::ABS() {
	// absolute - get the full address in its natural form
	// address supplied with the instruction has the low and high bytes along with the instruction
	// this is a 3 byte instruction
	uint16_t low = Read(pc);
	pc++;

	uint16_t high = Read(pc);
	pc++;

	// or them together to get a 16 bit address word
	// shift high bit left 8 to move it into the high space of the addr and OR the low byte to combine the 2 into one 16 bit address
	addrAbs = (high << 8) | low;

	return 0;
}

uint8_t CPU6502::ABX() {
	// absolute x indexed - get the full address with the offset from the x register
	// address supplied with the instruction has the low and high bytes along with the instruction
	// this is a 3 byte instruction
	uint16_t low = Read(pc);
	pc++;

	uint16_t high = Read(pc);
	pc++;

	// or them together to get a 16 bit address word
	// shift high bit left 8 to move it into the high space of the addr and OR the low byte to combine the 2 into one 16 bit address
	addrAbs = (high << 8) | low;
	
	// increment the address with the value in the x register
	addrAbs += x;
	
	// caveat - if the address has changed to a different page, indicate that there may be an additional clock cycle
	// this checks to see if the high byte has changed (mask the address with the high byte)
	if((addrAbs & 0xff00) != (high << 8)) {
		return 1;
	} else {
		return 0;
	}
}

uint8_t CPU6502::ABY() {
	// absolute y indexed - get the full address with the offset from the y register
	// address supplied with the instruction has the low and high bytes along with the instruction
	// this is a 3 byte instruction
	uint16_t low = Read(pc);
	pc++;

	uint16_t high = Read(pc);
	pc++;

	// or them together to get a 16 bit address word
	// shift high bit left 8 to move it into the high space of the addr and OR the low byte to combine the 2 into one 16 bit address
	addrAbs = (high << 8) | low;
	
	// increment the address with the value in the y register
	addrAbs += y;
	
	// caveat - if the address has changed to a different page, indicate that there may be an additional clock cycle
	if((addrAbs & 0xff00) != (high << 8)) {
		return 1;
	} else {
		return 0;
	}
}

uint8_t CPU6502::IND() {
	// indirect - this is essentially how the cpu does pointers
	// second byte is memory location, third byte is page (high byte)
	// the supplied addess with the instruction is a pointer
	// query that address to get the actual address in memory
	
	// this first part is similar to abs
	uint16_t lowPtr = Read(pc);
	pc++;
	uint16_t highPtr = Read(pc);
	pc++;
	
	uint16_t ptr = (highPtr << 8) | lowPtr; 
	
	// then set the address to the ptr value 
	// this is reading the 16 bit data at the original address
	
	addrAbs = (Read(ptr + 1) << 8) | Read(ptr + 0);
	
	return 0;
}

uint8_t CPU6502::IZX() {
	// indirect x indexed
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::IZY() {
	// indirect y indexed
	uint8_t result = 0x00;
	return result;
}

// opcodes
uint8_t CPU6502::ADC()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::AND()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::ASL()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::BCC()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::BCS()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::BEQ()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::BIT()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::BMI()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::BNE()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::BPL()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::BRK()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::BVC()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::BVS()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::CLC()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::CLD()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::CLI()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::CLV()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::CMP()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::CPX()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::CPY()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::DEC()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::DEX()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::DEY()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::EOR()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::INC()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::INX()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::INY()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::JMP()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::JSR()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::LDA()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::LDX()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::LDY()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::LSR()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::NOP()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::ORA()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::PHA()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::PHP()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::PLA()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::PLP()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::ROL()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::ROR()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::RTI()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::RTS()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::SBC()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::SEC()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::SED()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::SEI()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::STA()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::STX()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::STY()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::TAX()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::TAY()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::TSX()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::TXA()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::TXS()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::TYA()
{
	uint8_t result = 0x00;
	return result;
}

uint8_t CPU6502::XXX()
{
	uint8_t result = 0x00;
	return result;
}

