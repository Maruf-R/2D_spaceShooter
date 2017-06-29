#include "helpScreen.h"

const int hScreen_1 = 0;
const int hScreen_2 = 1;
const int hScreen_3 = 2;
const int hScreen_4 = 3;
const int hScreen_5 = 4;
const int returnToTitle = 5;

helpScreen::helpScreen(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToHelpList(this);
}

helpScreen::~helpScreen(){
}

void helpScreen::init(){
	_helpScreen_1.load_SpriteSheet("general help.bmp", 1, NULL);
	_helpScreen_2.load_SpriteSheet("player help 1.bmp", 1, NULL);
	_helpScreen_3.load_SpriteSheet("enemy help.bmp", 1, NULL);
	_helpScreen_4.load_SpriteSheet("player help 2.bmp", 1, NULL);
	_helpScreen_5.load_SpriteSheet("game help.bmp", 1 , NULL);

	set_displaySprite(&_helpScreen_1);

	responseTime = 500;
	timeElapsed = SDL_GetTicks();

	_state = 0;

	alive = true;
	active = true;

	position.x = 0;
	position.y = 0;
}


void helpScreen::input(SDL_Event evt){
	if(evt.type == SDL_KEYDOWN){
		if(responseTime + timeElapsed < SDL_GetTicks()){
			if(evt.key.keysym.sym == SDLK_RIGHT){
				if(_state < 5){
					_state += 1;
				}
			}

			if(evt.key.keysym.sym == SDLK_LEFT){
				if(_state > 0){
					_state += -1;
				}
			}

			if(evt.key.keysym.sym == SDLK_ESCAPE){
				active = false;
				//alive = false;
			}
			timeElapsed = SDL_GetTicks();
		}
	}
}


void helpScreen::update(SDL_Event evt){
	switch(_state){
	case hScreen_1:
		set_displaySprite(&_helpScreen_1);
		break;

	case hScreen_2:
		set_displaySprite(&_helpScreen_2);
		break;

	case hScreen_3:
		set_displaySprite(&_helpScreen_3);
		break;

	case hScreen_4:
		set_displaySprite(&_helpScreen_4);
		break;

	case hScreen_5:
		set_displaySprite(&_helpScreen_5);
		break;

	case returnToTitle:
		active = false;
		//alive = false;
		break;
	default:
		break;
	}
}

void helpScreen::setNumber(double stateNumber){
	_state = stateNumber;
}