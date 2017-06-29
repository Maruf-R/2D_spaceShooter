#include "splashScreen.h"

splashScreen::splashScreen(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToSplashList(this);
}

splashScreen::~splashScreen(){
}

void splashScreen::init(){
	_splashScreen.load_SpriteSheet("splash screen.bmp", 1, NULL);
	set_displaySprite(&_splashScreen);

	alive = true;
	active = true;

	splashDuration = 3000;
	timeElapsed = SDL_GetTicks();

	position.x = 0;
	position.y = 0;
}

void splashScreen::update(SDL_Event evt){
	if(timeElapsed + splashDuration < SDL_GetTicks()){
		active = false;
		alive = false;
	}
}