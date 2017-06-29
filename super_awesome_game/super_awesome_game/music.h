#ifndef music_h
#define music_h

#include "include\SDL_mixer.h"
#include <iostream>
#include <string>

class music{
protected:
	Mix_Music* snd;

	int volume;	//music volume

public:
	music();
	~music();

	void play();
	void stop();

	void pause();
	void resume();

	void load(std::string sndFile, int _volume);
};

#endif