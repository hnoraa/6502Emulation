#pragma once
#include <string>

class ROMHeader
{
public:
	ROMHeader(const uint8_t* buffer);
	~ROMHeader();
private:
	// the "NES" + 0x1A signature that identifies the file as a valid NES ROM
	uint8_t _signature[4];
	
	// PRG ROM size in 16Kb units
	uint8_t _prgRomSize;

	// CHR ROM size in 8Kb units
	uint8_t _chrRomSize;

	// Flags 6: mapper low nibble, mirroring, battery, trainer
	uint8_t _flags6;

	// Flags 7: mapper high nibble, NES 2.0, etc. 
	uint8_t _flags7;

	// PRG RAM size in 8Kb units
	uint8_t _prgRamSize;

	// Flag 9: TV system
	uint8_t _flags9;

	// Flags 10: TV system, PRG/CHR RAM, bus conflicts
	uint8_t _flags10;
	
	// the empty/unused padding
	uint8_t _zeroFill[5];

	// load the header from the rom
	// return true if the header is valid
	bool load(const uint8_t* buffer);
};

