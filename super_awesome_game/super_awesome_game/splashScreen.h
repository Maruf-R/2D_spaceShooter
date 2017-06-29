#ifndef splashScreen_h
#define splashScreen_h

#include "gameObject.h"
#include "gameManager.h"

class splashScreen: public gameObject{
protected:
	sprite _splashScreen;

public:
	splashScreen();
	~splashScreen();

	int timeElapsed;
	float splashDuration;

	void init(); //loads a sprite for the various states
	void update(SDL_Event evt);
};

#endif