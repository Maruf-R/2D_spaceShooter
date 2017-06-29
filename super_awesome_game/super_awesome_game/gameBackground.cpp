#include "gameBackground.h"

gameBackground::gameBackground(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToBackgroundList(this);
}

gameBackground::gameBackground(int X, int Y){
	init();	//calls the init function to initialise the player

	position.x = X;
	position.y = Y;

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToBackgroundList(this);
}

gameBackground::~gameBackground(){
}

void gameBackground::init(){
	_gameBackground.load_SpriteSheet("darkPurple.bmp", 1, NULL);
	_gameBackground_2.load_SpriteSheet("darkPurple.bmp", 1, NULL);

	set_displaySprite(&_gameBackground);

	state = UPDATE_STATE;

	screenH = 960;

	position.x = 0;
	position.y = 0;
	/*position.w = displaySprite->getOffset().w;
	position.h = displaySprite->getOffset().h;*/

	bkgrnd_2_pos.x = 0;
	bkgrnd_2_pos.y = screenH;
}

//moves the sprite to the new location at an incremental speed
void gameBackground::move(){
	position.y -= 3;
	bkgrnd_2_pos.y -= 3;
}

void gameBackground::update(SDL_Event evt){
	move();

	if(position.y <= -screenH){
		position.y += screenH * 2;
	}

	if(bkgrnd_2_pos.y <= -screenH){
		bkgrnd_2_pos.y += screenH * 2;
	}
}

void gameBackground::draw(SDL_Surface* _scrn){
	SDL_BlitSurface(_gameBackground.getImage(), &position, _scrn, NULL);
	SDL_BlitSurface(_gameBackground_2.getImage(), &bkgrnd_2_pos, _scrn, NULL);
}