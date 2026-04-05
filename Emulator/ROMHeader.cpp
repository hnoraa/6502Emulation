#include "ROMHeader.h"
#include <stdexcept>

ROMHeader::ROMHeader(const uint8_t* buffer)
{
	if (!load(buffer)) {
		throw std::runtime_error("Invalid NES ROM header");
	}
}

ROMHeader::~ROMHeader()
{
}

bool ROMHeader::load(const uint8_t* buffer)
{
	// first check that the buffer is EXACTLY 16 bytes
	if (sizeof(buffer) != 16) {
		return false;
	}

	// here we load the header from the header bytes and populate the properties
	std::memcpy(_signature, buffer, 4);	// get the signature

	// populate the rest of the headers except for zero fill
	_prgRamSize = buffer[4];
	_chrRomSize = buffer[5];
	_flags6 = buffer[6];
	_flags7 = buffer[7];
	_prgRamSize = buffer[8];
	_flags9 = buffer[9];
	_flags10 = buffer[10];

	// get the unused bytes
	std::memcpy(_zeroFill, buffer + 11, 1);

	return true;
}