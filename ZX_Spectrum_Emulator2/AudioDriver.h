#ifndef AUDIODRIVER_H_
#define AUDIODRIVER_H_

#include <SDL2/SDL.h>

#include <queue>
class AudioDriver
{
protected:
	SDL_AudioDeviceID _dev;
	SDL_AudioSpec _spec;



	short _level;
	std::queue<int> queue;
public:
	AudioDriver();
	~AudioDriver();

	void add_sam();

	void callback(short * buffer, size_t len);

	void set_level(short level) {
		_level = level;
	}
};




#endif
