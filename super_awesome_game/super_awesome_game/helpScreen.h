#ifndef helpScreen_h
#define helpScreen_h

#include "gameObject.h"
#include "gameManager.h"

class helpScreen: public gameObject{
protected:
	sprite _helpScreen_1;	//general help
	sprite _helpScreen_2;	//player help 1
	sprite _helpScreen_3;	//enemy help
	sprite _helpScreen_4;	//player help 2
	sprite _helpScreen_5;	//game help

	//variables to control the speed of transition frmo one page to another
	float responseTime;
	Uint32 timeElapsed;

	int _state;	//the switch state

public:
	helpScreen();
	~helpScreen();

	void init(); //loads a sprite for the various states
	void input(SDL_Event evt);
	void update(SDL_Event evt);
	void setNumber(double stateNumber);
};

#endif