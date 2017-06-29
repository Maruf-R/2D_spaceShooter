#include "playerLives.h"

const int hScreen_1 = 0;
const int hScreen_2 = 1;
const int hScreen_3 = 2;
const int hScreen_4 = 3;

playerLives::playerLives(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToPlayerLives(this);
}

playerLives::~playerLives(){
}

void playerLives::init(){
	_playerLives_1.load_SpriteSheet("life 1.bmp", 1, 0xffffff);
	_playerLives_2.load_SpriteSheet("life 2.bmp", 1, 0xffffff);
	_playerLives_3.load_SpriteSheet("life 3.bmp", 1, 0xffffff);

	set_displaySprite(&_playerLives_3);

	_state = hScreen_4;

	alive = true;
	active = true;

	position.x = 0;
	position.y = 0;
}


void playerLives::update(SDL_Event evt){
	switch(_state){
	case hScreen_1:
		set_displaySprite(NULL);
		active = false;
		//alive = false;
		break;

	case hScreen_2:
		set_displaySprite(&_playerLives_1);
		break;

	case hScreen_3:
		set_displaySprite(&_playerLives_2);
		break;

	case hScreen_4:
		set_displaySprite(&_playerLives_3);
		break;
	default:
		break;
	}
}

void playerLives::setNumber(double _lives){
	_state = _lives;
}