#include "titleScreen.h"

titleScreen::titleScreen(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToTitleList(this);
}

titleScreen::~titleScreen(){
}

void titleScreen::init(){
	_titleScreen.load_SpriteSheet("title screen.bmp", 1, NULL);
	set_displaySprite(&_titleScreen);

	alive = true;
	active = true;

	position.x = 0;
	position.y = 0;
}

void titleScreen::update(SDL_Event evt){
}