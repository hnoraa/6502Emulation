#include "ROMHeader.h"
#include <stdexcept>
#include <iostream>

ROMHeader::ROMHeader()
{
}

ROMHeader::ROMHeader(const uint8_t* buffer, size_t length)
{
	if (!load(buffer, length)) {
		throw std::runtime_error("Invalid NES ROM header");
	}
}

ROMHeader::~ROMHeader()
{
}

bool ROMHeader::load(const uint8_t* buffer, size_t length)
{
	// first check that the buffer is EXACTLY 16 bytes
	if (!buffer || length < 16) return false;

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
	std::memcpy(_zeroFill, buffer + 11, 5);

	// validate the signature
	if (std::memcmp(_signature, "NES\x1A", 4) != 0) return false;

	return true;
}

void ROMHeader::printHeaderBytes()
{
	// DEBUG method to print out the header bytes for debugging purposes
	const char nl = '\n';

	// Signature as ASCII and hex
	std::cout << "Signature: ";
	for (int i = 0; i < 4; ++i) std::cout << static_cast<char>(_signature[i]);
	std::cout << "  ";
	for (int i = 0; i < 4; ++i) std::cout << "0x" << std::hex << (unsigned int)(unsigned char)_signature[i] << ' ';
	std::cout << std::dec << nl;

	// Numeric fields
	std::cout << "PRG ROM Size (16KB units): 0x" << std::hex << (unsigned int)_prgRomSize
		<< " (" << std::dec << (unsigned int)_prgRomSize * 16 << " KB)" << nl;

	std::cout << "CHR ROM Size (8KB units): 0x" << std::hex << (unsigned int)_chrRomSize
		<< " (" << std::dec << (unsigned int)_chrRomSize * 8 << " KB)" << nl;

	std::cout << "Flags6:  0x" << std::hex << (unsigned int)_flags6 << std::dec << nl;
	std::cout << "Flags7:  0x" << std::hex << (unsigned int)_flags7 << std::dec << nl;
	std::cout << "PRG RAM Size (8KB units): 0x" << std::hex << (unsigned int)_prgRamSize << std::dec << nl;
	std::cout << "Flags9:  0x" << std::hex << (unsigned int)_flags9 << std::dec << nl;
	std::cout << "Flags10: 0x" << std::hex << (unsigned int)_flags10 << std::dec << nl;

	// Zero-fill / padding (print each element)
	std::cout << "ZeroFill/Padding: ";
	for (int i = 0; i < 5; ++i) {
		std::cout << "0x" << std::hex << (unsigned int)_zeroFill[i] << ' ';
	}
	std::cout << std::dec << nl;
}