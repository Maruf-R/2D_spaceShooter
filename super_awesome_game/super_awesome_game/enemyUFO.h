#ifndef enemyUFO_h
#define enemyUFO_h

#include "gameObject.h"
#include "gameManager.h"
#include "sound.h"

class enemyUFO: public gameObject{
protected:
	sprite _enemyUFO;
	sprite _explosion;
	
	sound explosionSnd;	//explosion sound

public:
	enemyUFO();
	enemyUFO(int X, int Y);	//overloaded constructor which allows me to set the enemies position
	~enemyUFO();

	void init(); //loads a sprite for the various states
	void move(); //moves the sprite
	void update(SDL_Event evt);

	void onUpdate(SDL_Event evt);
	void onDestroy(SDL_Event evt);
};

#endif