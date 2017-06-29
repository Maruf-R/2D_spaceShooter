#ifndef scoreScreen_h
#define scoreScreen_h

#include "gameObject.h"
#include "gameManager.h"
#include "textDisplay.h"

class scoreScreen: public gameObject{
protected:
	sprite _scoreScreen;
	textDisplay* _scoreDisp;	//will display the actual score

	double score;	//will hold the score

public:
	scoreScreen();
	~scoreScreen();

	void setNumber(double _score);	//will take in the score of the player
	void init(); //loads a sprite for the various states
	void update(SDL_Event evt);
};

#endif