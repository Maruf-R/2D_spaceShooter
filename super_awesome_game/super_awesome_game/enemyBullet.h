#ifndef enemyBullet_h
#define enemyBullet_h

#include "gameObject.h"
#include "gameManager.h"

//Makes a sprite object for playerButton, deals with it's various states, movement, key inputs, and updates

class enemyBullet: public gameObject{
protected:
	sprite _enemyBullet;

public:
	enemyBullet();
	enemyBullet(int posX, int posY, std::string _bullet);	//overloaded constructor to position enemyBullet at same position as player
	~enemyBullet();

	void init(); //loads a sprite for the various states
	void move(); //moves the sprite
	void update(SDL_Event evt);
};

#endif