#include "CPU.h"
#include <fstream>
#include <iostream>

CPU::CPU() 
{

}

CPU::CPU(std::string romPath, bool debug)
{
	// read the ROM data from the file and store it in _romData
	if (!loadROM(romPath))
    {
        // if the ROM failed to load, print an error message
        std::cerr << "Failed to load ROM: " << romPath << std::endl;
    }

	// instantiate the ROM header from the first 16 bytes of the ROM data
	_header = ROMHeader(_romData.data(), _romData.size());
	_debug = debug;
    if (_debug) {
        std::cout << "ROM loaded successfully: " << romPath << std::endl;
        // print out the ROM header information for debugging purposes
        std::cout << "ROM Header Information:" << std::endl;
        _header.printHeaderBytes();
	}
}

CPU::~CPU()
{
}

void CPU::reset()
{
}

void CPU::step()
{
}

bool CPU::loadROM(std::string filePath)
{
    // open in binary mode to prevent newline translation and allow seeking
    // open at end to get size immediately, then read from beginning
    std::ifstream fl(filePath, std::ios::binary | std::ios::ate);
	if (!fl) return false;

    // get length of file and initialize buffer
    std::streamsize len = fl.tellg();
	if (len <= 0) return false;

    _romData.resize(static_cast<size_t>(len));

    // set seek to beginning and read bytes into return buffer
    fl.seekg(0, std::ios::beg);
	if (!fl.read(reinterpret_cast<char*>(_romData.data()), len)) return false;

	return true;
}