#include "speed.h"

speed::speed(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addtoSpeedPowerEffect_List(this);
}

speed::speed(int posX, int posY){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addtoSpeedPowerEffect_List(this);

	position.x = posX;
	position.y = posY;
	/*position.w = displaySprite->getOffset().w;
	position.h = displaySprite->getOffset().h;*/
}

speed::~speed(){
}

void speed::init(){
	_speed.load_SpriteSheet("speed.bmp", 1, 0x3a2e3f); //colour code for white is 0xffffff
	set_displaySprite(&_speed);

	duration = 6000;
	timeElapsed = SDL_GetTicks();

	state = UPDATE_STATE;

	//MUST SET INITIAL POSITION TO THE SAME VALUE AS PLAYER POSITION VALUE
	position.x = 0;
	position.y = 0;
}

void speed::update(SDL_Event evt){
	switch(state){
	case UPDATE_STATE:
		onUpdate(evt);
		break;

	case DESTROY_STATE:
		onDestroy(evt);
		break;
	default:
		break;
	}
}

void speed::onUpdate(SDL_Event evt){
	if(timeElapsed + duration < SDL_GetTicks()){
		state = DESTROY_STATE;
	}
}

void speed::onDestroy(SDL_Event evt){
	active = false;
	alive = false;
}