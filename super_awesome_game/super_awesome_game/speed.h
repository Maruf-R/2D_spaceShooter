#ifndef speed_h
#define speed_h

#include "gameObject.h"
#include "gameManager.h"

//Makes a sprite object for the speed power up, deals with it's various states, movement and updates

class speed: public gameObject{
protected:
	sprite _speed;

	//speed duration
	float duration;
	Uint32 timeElapsed;

public:
	speed();
	speed(int posX, int posY);	//overloaded constructor to position powerUp at same position as enemy
	~speed();

	void init(); //loads a sprite for the various states
	void update(SDL_Event evt);

	void onUpdate(SDL_Event evt);
	void onDestroy(SDL_Event evt);
};

#endif