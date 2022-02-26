#include "Bus.h"

Bus::Bus()
{
	// clear RAM
	for (auto& i : ram) i = 0x00;

	// connect CPU
	cpu.ConnectBus(this);
}

Bus::~Bus()
{

}

void Bus::Write(uint16_t addr, uint8_t data)
{
	// reserve the full range of the RAM
	if (addr >= 0x0000 && addr <= 0xffff)
	{
		// write to the device (RAM only at this time)
		ram[addr] = data;
	}
}

uint8_t Bus::Read(uint16_t addr, bool readOnly)
{
	if (addr >= 0x0000 && addr <= 0xffff)
	{
		return ram[addr];
	}
	
	return 0x00;
}