#ifndef playerBullet_h
#define playerBullet_h

#include "gameObject.h"
#include "gameManager.h"

//Makes a sprite object for playerButton, deals with it's various states, movement, key inputs, and updates

class playerBullet: public gameObject{
protected:
	sprite _playerBullet;

public:
	playerBullet();
	playerBullet(int posX, int posY);	//overloaded constructor to position playerBullet at same position as player
	~playerBullet();

	void init(); //loads a sprite for the various states
	void move(); //moves the sprite
	void update(SDL_Event evt);
};

#endif