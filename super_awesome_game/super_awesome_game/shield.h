#ifndef shield_h
#define shield_h

#include "gameObject.h"
#include "gameManager.h"

//Makes a sprite object for the shield power up, deals with it's various states, movement and updates

class shield: public gameObject{
protected:
	sprite _shield;

	//shield duration
	float duration;
	Uint32 timeElapsed;

public:
	shield();
	shield(int posX, int posY);	//overloaded constructor to position powerUp at same position as enemy
	~shield();

	void init(); //loads a sprite for the various states
	void update(SDL_Event evt);

	void onUpdate(SDL_Event evt);
	void onDestroy(SDL_Event evt);
};

#endif