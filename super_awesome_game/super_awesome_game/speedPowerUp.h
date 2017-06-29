#ifndef speedPowerUp_h
#define speedPowerUp_h

#include "gameObject.h"
#include "gameManager.h"

//Makes a sprite object for the shield power up, deals with it's various states, movement and updates

class speedPowerUp: public gameObject{
protected:
	sprite _sPowerUp;

	//shield power up timer
	float duration;
	Uint32 timeElapsed;

public:
	speedPowerUp();
	speedPowerUp(int posX, int posY);	//overloaded constructor to position powerUp at same position as enemy
	~speedPowerUp();

	void init(); //loads a sprite for the various states
	void update(SDL_Event evt);

	void onUpdate(SDL_Event evt);
	void onDestroy(SDL_Event evt);
};

#endif