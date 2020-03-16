// loadRom.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Example file: "D:\Roms\nesTest_USA.nes"

#include <iostream>  
#include <fstream>
#include <string>

const char nl = '\n';

char* readFileBytes(const char*);

int main()
{
    const char* fN = "D:\\Roms\\legendOfZelda.nes";
    char cont;
    std::ifstream stream;

    std::cout << "Loading ROM\n" << fN << nl;
    char* buffer = readFileBytes(fN);

    int n = 1;

    std::cout << "Read n bytes from buffer? ";
    std::cin >> n;
    std::cout << nl;

    std::cout << "Reading first " << (n-1) << " bytes." << nl;
    std::cin >> cont;

    for (int i = 0; i < n - 1; i++) {
        std::cout << "0x" << std::hex << (unsigned int)buffer[i] << nl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
char* readFileBytes(const char* name)
{
    std::ifstream fl(name);

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