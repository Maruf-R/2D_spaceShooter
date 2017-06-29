#include "sound.h"

sound::sound(){
	channel = -1;
	volume = -1;
}

sound::~sound(){
	Mix_FreeChunk(snd);
}

void sound::play(){
	Mix_PlayChannel(channel, snd, 0);
	Mix_VolumeChunk(snd, volume);
}

void sound::load(std::string sndFile, int _channel, int _volume){
	channel = _channel;
	
	snd = Mix_LoadWAV(sndFile.c_str());
	volume = Mix_VolumeChunk(snd, _volume);
	
	if(snd == NULL){
		std::cout<<"\nerror: could not load sound file";
		system("puase");
	}		
}

void sound::stop(){
	Mix_HaltChannel(channel);
}

void sound::pause(){
	Mix_Pause(channel);
}

void sound::resume(){
	Mix_Resume(channel);
}