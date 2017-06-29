#ifndef sound_h
#define sound_h

#include "include\SDL_mixer.h"
#include <iostream>
#include <string>

class sound{
protected:
	Mix_Chunk* snd;

	int channel;	//for the channel
	int volume;	//sound volume

public:
	sound();
	~sound();

	void play();
	void stop();

	void pause();
	void resume();

	void load(std::string sndFile, int _channel, int _volume);
};

#endif