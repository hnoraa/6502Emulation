// ReadHeader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

const char nl = '\n';

char* readFileBytes(std::string);
void printHeaderBytes(const char*);

int main()
{
    std::ifstream stream;

    std::string fN;
    std::cout << "Enter ROM file path: ";
    std::getline(std::cin, fN);

    std::cout << "Loading ROM\n" << fN << nl;
    char* buffer = readFileBytes(fN);
    printHeaderBytes(buffer);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

char* readFileBytes(std::string name)
{
    // open in binary mode to prevent newline translation and allow seeking
    std::ifstream fl(name, std::ios::binary);

    // start seeking at end of file to get file length
    fl.seekg(0, std::ios::end);

    // get length of file and initialize buffer
    size_t len = fl.tellg();
    std::cout << "ROM Length: " << len << " bytes." << nl;
    char* ret = new char[len];

    // set seek to beginning and read bytes into return buffer
    fl.seekg(0, std::ios::beg);
    fl.read(ret, len);
    fl.close();

    return ret;
}

void printHeaderBytes(const char* buffer)
{
    for (int i = 0; i < 16 - 1; i++) {
        /*
            char in C++ is 1 byte, so char* is fine for reading raw bytes.
            However, when you cast buffer[i] to unsigned int, if the byte is >= 0x80, buffer[i](a signed char) will be negative, and casting to unsigned int will produce large values(like 0xffffffcd).

            Solution:
                Cast to unsigned char first, then to unsigned int :
        */
        std::cout << "0x" << std::hex << (unsigned int)(unsigned char)buffer[i] << nl;
    }
}