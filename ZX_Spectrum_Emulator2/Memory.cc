#include <fstream>
#include "Memory.h"

ROM::ROM(const char * filename)
{
	std::fstream romfile;
	romfile.open(filename, std::ios::in | std::ios::ate);
	_contents.resize(romfile.tellg());
	romfile.seekg(0);
	romfile.read(reinterpret_cast<char*>(&_contents[0]), _contents.size());
	_addr_mask = _contents.size() - 1;
}
void AddressSpace::write(unsigned address, uint8_t value, bool io) {
	if (io == true)
		_io.write(address, value);
	else{
		unsigned offset = address & 0x3fff;
		unsigned page = address >> 14;

		switch (page) {
		case 0:
			break;
		case 1:
			_ram.write((_io.vid() ? 7 : 5) << 14 | offset, value);
			break;
		case 2:
			_ram.write( 2 << 14 | offset, value);
			break;
		case 3:
			_ram.write(_io.ram() << 14 | offset, value);
			break;
		default:
			break;
		}
	}

}

uint8_t AddressSpace::read(unsigned address, bool io) {

	if (io == true)
		return _io.read(address);
	else{
			unsigned offset = address & 0x3fff;
			unsigned page = (address >> 14) & 0x03;

			switch (page) {
			case 0:
				return _rom.read(_io.rom() << 14 | offset);
				break;
			case 1:
				return _ram.read((_io.vid() ? 7 : 5) << 14 | offset);
				break;
			case 2:
				return _ram.read(2 << 14 | offset);
				break;
			case 3:
				return _ram.read(_io.ram() << 14 | offset);
				break;
			default:
				return 0;
				break;
			}

		}
}


