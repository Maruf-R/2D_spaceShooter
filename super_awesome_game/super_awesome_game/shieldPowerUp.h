#ifndef shieldPowerUp_h
#define shieldPowerUp_h

#include "gameObject.h"
#include "gameManager.h"

//Makes a sprite object for the shield power up, deals with it's various states, movement and updates

class shieldPowerUp: public gameObject{
protected:
	sprite _powerUp;

	//shield power up timer
	float duration;
	Uint32 timeElapsed;

public:
	shieldPowerUp();
	shieldPowerUp(int posX, int posY);	//overloaded constructor to position powerUp at same position as enemy
	~shieldPowerUp();

	void init(); //loads a sprite for the various states
	void update(SDL_Event evt);

	void onUpdate(SDL_Event evt);
	void onDestroy(SDL_Event evt);
};

#endif