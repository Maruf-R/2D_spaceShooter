#ifndef gameBackground_h
#define gameBackground_h

#include "gameObject.h"
#include "gameManager.h"
//can put sound here if I want background music to be played with background

class gameBackground: public gameObject{
protected:
	sprite _gameBackground;
	sprite _gameBackground_2;

	SDL_Rect bkgrnd_2_pos;

	double screenH;

public:
	gameBackground();
	gameBackground(int X, int Y);	//overloaded constructor
	~gameBackground();

	void init(); //loads the images
	void move(); //moves the background images
	void update(SDL_Event evt);
	void draw(SDL_Surface* _scrn);
};

#endif