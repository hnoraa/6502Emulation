#include "CPU.h"
#include <fstream>

CPU::CPU(std::string romPath)
{

}

CPU::~CPU()
{
    delete[] _romData;
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
    std::ifstream fl(filePath, std::ios::binary);

    // start seeking at end of file to get file length
    fl.seekg(0, std::ios::end);

    // get length of file and initialize buffer
    size_t len = fl.tellg();
    char* ret = new char[len];

    // set seek to beginning and read bytes into return buffer
    fl.seekg(0, std::ios::beg);
    fl.read(ret, len);
    fl.close();

    // set the buffer to ret and clear ret
    _romData = (uint8_t*)ret;
    delete[] ret;

	return false;
}