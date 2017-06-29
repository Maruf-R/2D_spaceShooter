#include "speedPowerUp.h"

speedPowerUp::speedPowerUp(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToSpeedPowerUpList(this);
}

speedPowerUp::speedPowerUp(int posX, int posY){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToSpeedPowerUpList(this);

	position.x = posX;
	position.y = posY;
	/*position.w = displaySprite->getOffset().w;
	position.h = displaySprite->getOffset().h;*/
}

speedPowerUp::~speedPowerUp(){
}

void speedPowerUp::init(){
	_sPowerUp.load_SpriteSheet("powerupBlue_bolt.bmp", 1, 0x3a2e3f);
	set_displaySprite(&_sPowerUp);

	duration = 5000;
	timeElapsed = SDL_GetTicks();

	active = true;
	alive = true;

	state = UPDATE_STATE;

	//MUST SET INITIAL POSITION TO THE SAME VALUE AS PLAYER POSITION VALUE
	position.x = 0;
	position.y = 0;
}

void speedPowerUp::update(SDL_Event evt){
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

void speedPowerUp::onUpdate(SDL_Event evt){
	if(timeElapsed + duration < SDL_GetTicks()){
		state = DESTROY_STATE;
	}
}

void speedPowerUp::onDestroy(SDL_Event evt){
	active = false;
	alive = false;
}