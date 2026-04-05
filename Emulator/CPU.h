#pragma once
#include <string>
#include "ROMHeader.h"

class CPU
{
public:
	CPU(std::string romPath);
	~CPU();

	void reset();
	void step();

	
private:
	std::string _romPath;

    // variable to hold the bytes of the ROM
    uint8_t* _romData;

	// the header of the ROM, which contains metadata about the ROM and how to load it
	ROMHeader _header;

	// the PRG ROM data, which contains the program code to execute
	uint8_t* _prgRom;

	// the CHR ROM data, which contains the graphics data for the game
	uint8_t* _chrRom;

	// load the ROM from a file
	// return true if the ROM was loaded successfully
	bool loadROM(std::string filePath);
};

