#include "enemyUFO.h"

enemyUFO::enemyUFO(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToEnemyList(this);
}

enemyUFO::enemyUFO(int X, int Y){
	init();	//calls the init function to initialise the player

	position.x = X;
	position.y = Y;

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToEnemyList(this);
}

enemyUFO::~enemyUFO(){
}

void enemyUFO::init(){
	//sprites
	_enemyUFO.load_SpriteSheet("enemyUFO.bmp", 1, 0xffffff);
	_explosion.load_SpriteSheet("Explosion.bmp", 12, 0xffffff);

	//sounds
	explosionSnd.load("explosion sound effect.wav", -1, -1);

	set_displaySprite(&_enemyUFO);

	state = UPDATE_STATE;

	position.x = 700;
	position.y = 200;
	/*position.w = displaySprite->getOffset().w;
	position.h = displaySprite->getOffset().h;*/
}

//moves the sprite to the new location at an incremental speed
void enemyUFO::move(){
	position.y += 3;

	//checks if enemyUFO has gone off screen, if so then deletes
	if(position.y >= 960){
		alive = false;
		active = false;
	}
}

void enemyUFO::update(SDL_Event evt){
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

void enemyUFO::onUpdate(SDL_Event evt){
	displaySprite->animate(true);
	move();
}

void enemyUFO::onDestroy(SDL_Event evt){
	set_displaySprite(&_explosion);
	displaySprite->animate(false);
	explosionSnd.play();	//sound played when enemy dies and explodes

	if(displaySprite -> getOffset().x >= (displaySprite -> getImage()->w - displaySprite -> getOffset().w)){
		active = false;
		alive = false;
	}
}