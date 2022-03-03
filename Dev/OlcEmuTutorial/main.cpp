#include<iostream>
#include <bitset>

enum FLAGS6502
{
	C = (1 << 0),		// carry
	Z = (1 << 1),		// zero
	I = (1 << 2),		// disable interrupts
	D = (1 << 3),		// decimal mode
	B = (1 << 4),		// break
	U = (1 << 5),		// unused
	V = (1 << 6),		// overflow - signed
	N = (1 << 7),		// negative - signed
};

uint8_t status = 0x00;

uint8_t getFlag(FLAGS6502 flag)
{
	return ((status & flag) > 0) ? 1 : 0;
}

void setFlag(FLAGS6502 flag, bool v)
{
	if (v)
	{
		status |= flag;
	}
	else
	{
		status &= ~flag;
	}
}

void printResultsTable ()
{
	std::cout << "Status register:\t" << std::bitset<8>(status) << std::endl;
	std::cout << "Carry flag:\t\t" << (getFlag(C) & 0xff) << std::endl;
	std::cout << "Zero flag:\t\t" << (getFlag(Z) & 0xff) << std::endl;
	std::cout << "Disable Interrupts flag:" << (getFlag(I) & 0xff) << std::endl;
	std::cout << "Decimal flag:\t\t" << (getFlag(D) & 0xff) << std::endl;
	std::cout << "Break flag:\t\t" << (getFlag(B) & 0xff) << std::endl;
	std::cout << "Unused flag:\t\t" << (getFlag(U) & 0xff) << std::endl;
	std::cout << "Overflow flag:\t\t" << (getFlag(V) & 0xff) << std::endl;
	std::cout << "Negative flag:\t\t" << (getFlag(N) & 0xff) << std::endl << std::endl;
}

int main()
{
	char a;
	std::cout << "Test" << std::endl;
	
	printResultsTable();
	std::cin >> a;

	// toggle each flag on
	setFlag(C, true);
	std::cout << "Status register:\t" << std::bitset<8>(status) << " ";
	setFlag(Z, true);
	std::cout << std::bitset<8>(status) << " ";
	setFlag(I, true);
	std::cout << std::bitset<8>(status) << " ";
	setFlag(D, true);
	std::cout << std::bitset<8>(status) << " ";
	setFlag(B, true);
	std::cout << std::bitset<8>(status) << " ";
	setFlag(U, true);
	std::cout << std::bitset<8>(status) << " ";
	setFlag(V, true);
	std::cout << std::bitset<8>(status) << " ";
	setFlag(N, true);
	std::cout << std::bitset<8>(status) << std::endl << std::endl;

	printResultsTable();
	std::cin >> a;

	// toggle each flag off
	setFlag(C, false);
	std::cout << "Status register:\t" << std::bitset<8>(status) << " ";
	setFlag(Z, false);
	std::cout << std::bitset<8>(status) << " ";
	setFlag(I, false);
	std::cout << std::bitset<8>(status) << " ";
	setFlag(D, false);
	std::cout << std::bitset<8>(status) << " ";
	setFlag(B, false);
	std::cout << std::bitset<8>(status) << " ";
	setFlag(U, false);
	std::cout << std::bitset<8>(status) << " ";
	setFlag(V, false);
	std::cout << std::bitset<8>(status) << " ";
	setFlag(N, false);
	std::cout << std::bitset<8>(status) << std::endl << std::endl;

	printResultsTable();

	return 0;
}