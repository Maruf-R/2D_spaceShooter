#include "shieldPowerUp.h"

shieldPowerUp::shieldPowerUp(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToShieldPowerUpList(this);
}

shieldPowerUp::shieldPowerUp(int posX, int posY){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToShieldPowerUpList(this);

	position.x = posX;
	position.y = posY;
	/*position.w = displaySprite->getOffset().w;
	position.h = displaySprite->getOffset().h;*/
}

shieldPowerUp::~shieldPowerUp(){
}

void shieldPowerUp::init(){
	_powerUp.load_SpriteSheet("powerupBlue_shield.bmp", 1, 0x3a2e3f);
	set_displaySprite(&_powerUp);

	duration = 5000;
	timeElapsed = SDL_GetTicks();

	state = UPDATE_STATE;

	//MUST SET INITIAL POSITION TO THE SAME VALUE AS PLAYER POSITION VALUE
	position.x = 0;
	position.y = 0;
}

void shieldPowerUp::update(SDL_Event evt){
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

void shieldPowerUp::onUpdate(SDL_Event evt){
	if(timeElapsed + duration < SDL_GetTicks()){
		state = DESTROY_STATE;
	}
}

void shieldPowerUp::onDestroy(SDL_Event evt){
	active = false;
	alive = false;
}