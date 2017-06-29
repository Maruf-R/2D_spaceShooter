#ifndef playerLives_h
#define playerLives_h

#include "gameObject.h"
#include "gameManager.h"

class playerLives: public gameObject{
protected:
	sprite _playerLives_1;	//general help
	sprite _playerLives_2;	//player help 1
	sprite _playerLives_3;	

	int _state;	//the switch state

public:
	playerLives();
	~playerLives();

	void init(); //loads a sprite for the various states
	void update(SDL_Event evt);
	void setNumber(double _lives);
};

#endif