#include "cpu.h"

// constructor
cpu::cpu() {
	programCounter = 0x00;
	stackPointer = 0x01FF;
	isRunning = true;
}

// private
uint8_t cpu::getNextOpcode() {
	return ram[programCounter++];
}

// public
void cpu::loadProgram() {

}

void cpu::run() {

	while (isRunning) {
		opcode = getNextOpcode();

		executeOpCode();
	}
}

void cpu::executeOpCode() {
	switch (opcode) {
	case 0x01:	// ORA izx 6
		break;
	case 0x02:	// KIL
		break;
	case 0x03:	// SLO izx 8
		break;
	case 0x04:	// NOP zp 3
		break;
	case 0x05:	// ORA zp 3
		break;
	case 0x06:	// ASL zp5
		break;
	case 0x07:	// SLO zp 5
		break;
	case 0x08:	// PHP 3
		break;
	case 0x09:	// ORA imm 2
		break;
	case 0x0A:	// ASL 2
		break;
	case 0x0B:	// ANC imm 2
		break;
	case 0x0C:	// NOP abs 4
		break;
	case 0x0D:	// ORA abs 4
		break;
	case 0x0E:	// ASL abs 6
		break;
	case 0x0F:	// SLO abs 6
		break;
	case 0x10:	// BPL rel 2*
		break;
	case 0x11:	// ORA izy 5*
		break;
	case 0x12:	// KIL
		break;
	case 0x13:	// SLO izy 8
		break;
	case 0x14:	// NOP zpx 4
		break;
	case 0x15:	// ORA zpx 4
		break;
	case 0x16:	// ASL zpx 6
		break;
	case 0x17:	// SLO zpx 6
		break;
	case 0x18:	// CLC 2
		break;
	case 0x19:	// ORA aby 4*
		break;
	case 0x1A:	// NOP 2
		break;
	case 0x1B:	// SLO aby 7
		break;
	case 0x1C:	// NOP abx 4*
		break;
	case 0x1D:	// ORA abx 4*
		break;
	case 0x1E:	// ASL abx 7
		break;
	case 0x1F:	// SLO abx 7
		break;
	case 0x20:	// JSR abs 6
		break;
	case 0x21:	// AND izx 6
		break;
	case 0x22:	// KIL
		break;
	case 0x23:	// RLA izx 8
		break;
	case 0x24:	// BIT zp 3
		break;
	case 0x25:	// AND zp 3
		break;
	case 0x26:	// ROL zp 5
		break;
	case 0x27:	// RLA zp 5
		break;
	case 0x28:	// PLP 4
		break;
	case 0x29:	// AND imm 2
		break;
	case 0x2A:	// ROL 2
		break;
	case 0x2B:	// ANC imm2
		break;
	case 0x2C:	// BIT abs 4
		break;
	case 0x2D:	// AND abs 4
		break;
	case 0x2E:	// ROL abs 6
		break;
	case 0x2F:	// RLA abs 6
		break;
	case 0x30:	// BMI rel 2*
		break;
	case 0x31:	// AND izy 5*
		break;
	case 0x32:	// KIL
		break;
	case 0x33:	// RLA izy 8
		break;
	case 0x34:	// NOP zpx 4
		break;
	case 0x35:	// AND zpx 4
		break;
	case 0x36:	// ROL zpx 6
		break;
	case 0x37:	// RLA zpx 6
		break;
	case 0x38:	// SEC 2
		break;
	case 0x39:	// AND aby 4*
		break;
	case 0x3A:	// NOP 2
		break;
	case 0x3B:	// RLA aby 7
		break;
	case 0x3C:	// NOP abx 4*
		break;
	case 0x3D:	// AND abx 4*
		break;
	case 0x3E:	// ROL abx 7
		break;
	case 0x3F:	// RLA abx 7
		break;
	case 0x40:	// RTI 6
		break;
	case 0x41:	// EOR izx 6
		break;
	case 0x42:	// KIL
		break;
	case 0x43:	// SRE izx 8
		break;
	case 0x44:	// NOP zp 3
		break;
	case 0x45:	// EOR zp 3
		break;
	case 0x46:	// LSR zp 5
		break;
	case 0x47:	// SRE sp 5
		break;
	case 0x48:	// PHA 3
		break;
	case 0x49:	// EOR imm 2
		break;
	case 0x4A:	// LSR 2
		break;
	case 0x4B:	// ALR imm 2
		break;
	case 0x4C:	// JMP abs 3
		break;
	case 0x4D:	// EOR abs 4
		break;
	case 0x4E:	// LSR abs 6
		break;
	case 0x4F:	// SRE abs 6
		break;
	case 0x50:	// BVC rel 2*
		break;
	case 0x51:	// EOR izy 5*
		break;
	case 0x52:	// KIL
		break;
	case 0x53:	// SRE izy 8
		break;
	case 0x54:	// NOP zpx 4
		break;
	case 0x55:	// EOR zpx 4
		break;
	case 0x56:	// LSR zpx 6
		break;
	case 0x57:	// SRE zpx 6
		break;
	case 0x58:	// CLI 2
		break;
	case 0x59:	// EOR aby 4*
		break;
	case 0x5A:	// NOP 2
		break;
	case 0x5B:	// SRE aby 7
		break;
	case 0x5C:	// NOP abx 4*
		break;
	case 0x5D:	// EOR abx 4*
		break;
	case 0x5E:	// LSR abx 7
		break;
	case 0x5F:	// SRE abx 7
		break;
	case 0x60:	// RTS 6
		break;
	case 0x61:	// ADC izx 6
		break;
	case 0x62:	// KIL
		break;
	case 0x63:	// RRA izx 8
		break;
	case 0x64:	// NOP zp 3
		break;
	case 0x65:	// ADC zp 3
		break;
	case 0x66:	// ROR zp 5
		break;
	case 0x67:	// RRA zp 5
		break;
	case 0x68:	// PLA 4
		break;
	case 0x69:	// ADC imm 2
		break;
	case 0x6A:	// ROR 2
		break;
	case 0x6B:	// ARR imm 2
		break;
	case 0x6C:	// JMP ind 5
		break;
	case 0x6D:	// ADC abs 4
		break;
	case 0x6E:	// ROR abs 6
		break;
	case 0x6F:	// RRA abs 6
		break;
	case 0x70:	// BVS rel 2*
		break;
	case 0x71:	// ADC izy 5*
		break;
	case 0x72:	// KIL
		break;
	case 0x73:	// RRA izy 8
		break;
	case 0x74:	// NOP zpx 4
		break;
	case 0x75:	// ADC zpx 4
		break;
	case 0x76:	// ROR zpx 6
		break;
	case 0x77:	// RRA zpx 6
		break;
	case 0x78:	// SEI 2
		break;
	case 0x79:	// ADC aby 2*
		break;
	case 0x7A:	// NOP 2
		break;
	case 0x7B:	// RRA aby 7
		break;
	case 0x7C:	// NOP abx 4*
		break;
	case 0x7D:	// ADC abx 4*
		break;
	case 0x7E:	// ROR abx 7
		break;
	case 0x7F:	// RRA abx 7
		break;
	case 0x80:	// NOP imm 2
		break;
	case 0x81:	// STA izx 6
		break;
	case 0x82:	// NOP imm 2
		break;
	case 0x83:	// SAX izx 6
		break;
	case 0x84:	// STY zp 3
		break;
	case 0x85:	// STA zp 3
		break;
	case 0x86:	// STX zp 3
		break;
	case 0x87:	// SAX zp 3
		break;
	case 0x88:	// DEY 2
		break;
	case 0x89:	// NOP imm 2
		break;
	case 0x8A:	// TXA 2
		break;
	case 0x8B:	// XAA imm 2
		break;
	case 0x8C:	// STY abs 4
		break;
	case 0x8D:	// STA abs 4
		break;
	case 0x8E:	// STX abs 4
		break;
	case 0x8F:	// SAX abs 4
		break;
	case 0x90:	// BCC rel 2*
		break;
	case 0x91:	// STA izy 6
		break;
	case 0x92:	// KIL
		break;
	case 0x93:	// AHX izy 6
		break;
	case 0x94:	// STY zpx 5
		break;
	case 0x95:	// STA zpx 4
		break;
	case 0x96:	// STX zpy 4
		break;
	case 0x97:	// SAX zpy 4
		break;
	case 0x98:	// TYA 2
		break;
	case 0x99:	// STA aby 5
		break;
	case 0x9A:	// TXS 2
		break;
	case 0x9B:	// TAS aby 5
		break;
	case 0x9C:	// SHY abx 5
		break;
	case 0x9D:	// STA abx 5
		break;
	case 0x9E:	// SHX aby 5
		break;
	case 0x9F:	// AHX aby 5
		break;
	case 0xA0:	// LDY imm 2
		break;
	case 0xA1:	// LDA izx 6
		break;
	case 0xA2:	// LDX imm 2
		break;
	case 0xA3:	// LAX izx 6
		break;
	case 0xA4:	// LDY zp 3
		break;
	case 0xA5:	// LDA zp 3
		break;
	case 0xA6:	// LDX zp 3
		break;
	case 0xA7:	// LAX zp 3
		break;
	case 0xA8:	// TAY 2
		break;
	case 0xA9:	// LDA imm 2
		break;
	case 0xAA:	// TAX 2
		break;
	case 0xAB:	// LAX imm 2
		break;
	case 0xAC:	// LDY abs 4
		break;
	case 0xAD:	// LDA abs 4
		break;
	case 0xAE:	// LDX abs 4
		break;
	case 0xAF:	// LAX abs 4
		break;
	case 0xB0:	// BCS rel 2*
		break;
	case 0xB1:	// LDA izy 5*
		break;
	case 0xB2:	// KIL
		break;
	case 0xB3:	// LAX izy 5*
		break;
	case 0xB4:	// LDY zpx 4
		break;
	case 0xB5:	// LDA zpx 4
		break;
	case 0xB6:	// LDX zpy 4
		break;
	case 0xB7:	// LAX zpy 4
		break;
	case 0xB8:	// CLV 2
		break;
	case 0xB9:	// LDA aby 4*
		break;
	case 0xBA:	// TSX 2
		break;
	case 0xBB:	// LAS aby 4*
		break;
	case 0xBC:	// LDY abs 4*
		break;
	case 0xBD:	// LDA abx 4*
		break;
	case 0xBE:	// LDX aby 4*
		break;
	case 0xBF:	// LAX aby 4*
		break;
	case 0xC0:
		break;
	case 0xC1:
		break;
	case 0xC2:
		break;
	case 0xC3:
		break;
	case 0xC4:
		break;
	case 0xC5:
		break;
	case 0xC6:
		break;
	case 0xC7:
		break;
	case 0xC8:
		break;
	case 0xC9:
		break;
	case 0xCA:
		break;
	case 0xCB:
		break;
	case 0xCC:
		break;
	case 0xCD:
		break;
	case 0xCE:
		break;
	case 0xCF:
		break;
	case 0xD0:
		break;
	case 0xD1:
		break;
	case 0xD2:
		break;
	case 0xD3:
		break;
	case 0xD4:
		break;
	case 0xD5:
		break;
	case 0xD6:
		break;
	case 0xD7:
		break;
	case 0xD8:
		break;
	case 0xD9:
		break;
	case 0xDA:
		break;
	case 0xDB:
		break;
	case 0xDC:
		break;
	case 0xDD:
		break;
	case 0xDE:
		break;
	case 0xDF:
		break;
	case 0xE0:
		break;
	case 0xE1:
		break;
	case 0xE2:
		break;
	case 0xE3:
		break;
	case 0xE4:
		break;
	case 0xE5:
		break;
	case 0xE6:
		break;
	case 0xE7:
		break;
	case 0xE8:
		break;
	case 0xE9:
		break;
	case 0xEA:
		break;
	case 0xEB:
		break;
	case 0xEC:
		break;
	case 0xED:
		break;
	case 0xEE:
		break;
	case 0xEF:
		break;
	case 0xF0:
		break;
	case 0xF1:
		break;
	case 0xF2:
		break;
	case 0xF3:
		break;
	case 0xF4:
		break;
	case 0xF5:
		break;
	case 0xF6:
		break;
	case 0xF7:
		break;
	case 0xF8:
		break;
	case 0xF9:
		break;
	case 0xFA:
		break;
	case 0xFB:
		break;
	case 0xFC:
		break;
	case 0xFD:
		break;
	case 0xFE:
		break;
	case 0xFF:
		break;
	case 0x00:	// BRK 7
	default:
		// terminate
		isRunning = false;
		break;
	}
}