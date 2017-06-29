#include "scoreScreen.h"

scoreScreen::scoreScreen(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToScoreList(this);
}

scoreScreen::~scoreScreen(){
}

void scoreScreen::init(){
	_scoreScreen.load_SpriteSheet("score screen.bmp", 1, NULL);
	set_displaySprite(&_scoreScreen);

	position.x = 0;
	position.y = 0;

	score = 0;

	//displays the timer countdown
	_scoreDisp = new textDisplay(450, 400, 64, "scoreDisp");

	alive = true;
	active = true;
}


void scoreScreen::setNumber(double _score){
	score = _score;
}

void scoreScreen::update(SDL_Event evt){
	_scoreDisp -> setNumber(score);
}