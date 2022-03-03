#ifndef _BUS_H
#define _BUS_H

#include <cstdint>
#include <array>

#include "CPU6502.h"

class Bus {
public:
	Bus();
	~Bus();
	
	// bus actions
	void Write(uint16_t addr, uint8_t data);
	uint8_ Read(uint16_t addr, bool readOnly=false);
	
	// devices attached to the bus
	std::array<uint8_t, 64 * 1024> ram;
};
#endif
