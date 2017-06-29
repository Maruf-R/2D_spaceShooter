#ifndef textDisplay_h
#define textDisplay_h

#include "gameObject.h"
#include "gameManager.h"
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <sstream>

class textDisplay: public gameObject{
protected:
	sprite _text;
	SDL_Surface* _textDisplay;
	TTF_Font* font;	//font for score
	SDL_Color fontCol;	//text colour for font
	int fontSize;

	std::ostringstream scoreConv;
	std::string result;

	double number;	//will hold a number

public:
	textDisplay(int posX, int posY, int _fontSize, std::string _textName);	//position and name the text
	~textDisplay();

	void init(); //loads a sprite for the various states
	void draw(SDL_Surface* scrn);	//text score on screen
	void update(SDL_Event evt);	//updates the text
	void setNumber(double _number);	//function to set the players score
};

#endif