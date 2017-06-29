#include "music.h"

music::music(){
	volume = -1;
}

music::~music(){
	Mix_FreeMusic(snd);
}

void music::play(){
	Mix_PlayMusic(snd, -1);
}

void music::load(std::string sndFile, int _volume){
	snd = Mix_LoadMUS(sndFile.c_str());
	Mix_VolumeMusic(_volume);
	
	if(snd == NULL){
		std::cout<<"\nerror: could not load music file";
		system("puase");
	}		
}

void music::stop(){
	Mix_HaltMusic();
}

void music::pause(){
	Mix_PauseMusic();
}

void music::resume(){
	Mix_ResumeMusic();
}