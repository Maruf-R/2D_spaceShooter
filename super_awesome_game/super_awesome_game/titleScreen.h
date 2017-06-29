#ifndef titleScreen_h
#define titleScreen_h

#include "gameObject.h"
#include "gameManager.h"

class titleScreen: public gameObject{
protected:
	sprite _titleScreen;

public:
	titleScreen();
	~titleScreen();

	void init(); //loads a sprite for the various states
	void update(SDL_Event evt);
};

#endif