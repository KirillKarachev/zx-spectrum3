#ifndef IO_H_
#define IO_H_

#include <cstdint>
#include "AudioDriver.h"

class IO
{
protected:
	uint8_t _port_fe { 0x00 };
	uint8_t _port_7ffd { 0x00 };
	uint8_t _ear { 0xfe };


	uint8_t _key_matrix[8] { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };/////////или тут

	AudioDriver * _adrv;

public:
	IO(AudioDriver * drv): _adrv(drv) {}

	void write(unsigned address, uint8_t value);
	uint8_t read(unsigned address) const;

	uint8_t border() const { return _port_fe & 0x07; }
	uint8_t mem() const {return _port_7ffd;}
	uint8_t ram() const {return _port_7ffd & 0x07;}
	uint8_t rom() const {return ((_port_7ffd & 0x10) == 0) ? 0 : 1;}

	bool vid() const {return (_port_7ffd & 0x08) != 0;};



	void keydown(unsigned row, unsigned col);
	void keyup(unsigned row, unsigned col);
	void set_ear(uint8_t ear) { _ear = ear & 1; }

};





#endif
