#ifndef button_h
#define button_h

#include "gameObject.h"
#include "gameManager.h"
#include "sound.h"
#include <iostream>

//Makes a sprite object for button, deals with it's various states, movement, key inputs, and updates

class button: public gameObject{
protected:
	//all the button sprites (states)
	sprite down;
	sprite idle;
	sprite over;

	//button sound effects
	sound mouseOver;
	sound mouseClick;

public:
	button();
	button(int posX, int posY, std::string _buttonName, std::string _up, std::string _over, std::string _down);	//overloaded constructor to position button
	~button();

	void init(); //loads a sprite for the various states
	void input(SDL_Event evt); //takes button input, key presses etc.
	void update(SDL_Event evt);
};

#endif