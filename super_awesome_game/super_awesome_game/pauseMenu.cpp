#include "pauseMenu.h"

/*const int pScreen_1 = 0;
const int pScreen_2 = 1;
const int pScreen_3 = 2;
const int pScreen_4 = 3;
const int pScreen_5 = 4;*/

pauseMenu::pauseMenu(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToPauseMenuList(this);
}

pauseMenu::~pauseMenu(){
}

void pauseMenu::init(){
	gamePaused.load_SpriteSheet("pausedMenu_header.bmp", 1, 0xffffff);

	set_displaySprite(&gamePaused);

	_state = 0;

	alive = true;
	active = true;

	position.x = 300;
	position.y = 300;
}


void pauseMenu::input(SDL_Event evt){
}


void pauseMenu::update(SDL_Event evt){
	/*switch(_state){
	case hScreen_1:
		set_displaySprite(&_pauseMenu_1);
		break;

	case hScreen_2:
		set_displaySprite(&_pauseMenu_2);
		break;

	case hScreen_3:
		set_displaySprite(&_pauseMenu_3);
		break;

	case hScreen_4:
		set_displaySprite(&_pauseMenu_4);
		break;

	case hScreen_5:
		set_displaySprite(&_pauseMenu_5);
		break;

	default:
		break;
	}*/
}