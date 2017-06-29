#include "shield.h"

shield::shield(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addtoShieldPowerEffect_List(this);
}

shield::shield(int posX, int posY){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addtoShieldPowerEffect_List(this);

	position.x = posX;
	position.y = posY;
	/*position.w = displaySprite->getOffset().w;
	position.h = displaySprite->getOffset().h;*/
}

shield::~shield(){
}

void shield::init(){
	_shield.load_SpriteSheet("shield.bmp", 1, 0x3a2e3f); //colour code for white is 0xffffff
	set_displaySprite(&_shield);

	duration = 7000;
	timeElapsed = SDL_GetTicks();

	state = UPDATE_STATE;

	//MUST SET INITIAL POSITION TO THE SAME VALUE AS PLAYER POSITION VALUE
	position.x = 0;
	position.y = 0;
}

void shield::update(SDL_Event evt){
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

void shield::onUpdate(SDL_Event evt){
	if(timeElapsed + duration < SDL_GetTicks()){
		state = DESTROY_STATE;
	}
}

void shield::onDestroy(SDL_Event evt){
	active = false;
	alive = false;
}