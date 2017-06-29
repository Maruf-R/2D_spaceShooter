#ifndef enemyYell_h
#define enemyYell_h

#include "gameObject.h"
#include "gameManager.h"
#include "sound.h"
#include "enemyBullet.h"

class enemyYell: public gameObject{
protected:
	sprite _enemyYell;
	sprite _explosion;

	sound bulletSnd;	//bullet fire sound
	sound explosionSnd;	//explosion sound
	enemyBullet* _bullet;	//bullet

	//fire rate timer
	float shotCD;	//holds the cooldown for fire rate
	Uint32 timeElapsed;	//holds the time passed since the last shot was fired

public:
	enemyYell();
	enemyYell(int X, int Y);	//overloaded constructor which allows me to set the enemies position
	~enemyYell();

	void init();	//loads a sprite for the various states
	void move();	//moves the sprite
	void update(SDL_Event evt);

	void onUpdate(SDL_Event evt);
	void onDestroy(SDL_Event evt);
};

#endif