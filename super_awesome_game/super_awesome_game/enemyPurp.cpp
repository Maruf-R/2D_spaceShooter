#include "enemyPurp.h"

enemyPurp::enemyPurp(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToEnemyList(this);
}

enemyPurp::enemyPurp(int X, int Y){
	init();	//calls the init function to initialise the player

	position.x = X;
	position.y = Y;

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToEnemyList(this);
}

enemyPurp::~enemyPurp(){
}

void enemyPurp::init(){
	//sprites
	_enemyPurp.load_SpriteSheet("purple enemy.bmp", 1, 0xffffff);
	_explosion.load_SpriteSheet("Explosion.bmp", 12, 0xffffff);

	//sounds
	bulletSnd.load("enemy laser sound effect.wav", -1, -1);
	explosionSnd.load("explosion sound effect.wav", -1, -1);

	//bullet cooldown variables
	shotCD  = 2500;
	timeElapsed = SDL_GetTicks();

	set_displaySprite(&_enemyPurp);

	state = UPDATE_STATE;

	position.x = 700;
	position.y = 200;
	/*position.w = displaySprite->getOffset().w;
	position.h = displaySprite->getOffset().h;*/
}

//moves the sprite to the new location at an incremental speed
void enemyPurp::move(){
	position.x += -1;
	position.y += 1;

	//checks if enemyPurp has gone off screen, if so then deletes
	if(position.y >= 960){
		alive = false;
		active = false;
	}
}

void enemyPurp::update(SDL_Event evt){
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

void enemyPurp::onUpdate(SDL_Event evt){
	move();

	if(timeElapsed + shotCD < SDL_GetTicks()){
		_bullet = new enemyBullet(position.x + position.w/2, position.y + position.h/2, "purple enemy laser.bmp");
		bulletSnd.play();	//sound played when bullet fired
		timeElapsed = SDL_GetTicks();
	}
}

void enemyPurp::onDestroy(SDL_Event evt){
	set_displaySprite(&_explosion);
	displaySprite->animate(false);
	explosionSnd.play();	//sound played when enemy dies and explodes

	if(displaySprite -> getOffset().x >= (displaySprite -> getImage()->w - displaySprite -> getOffset().w)){
		active = false;
		alive = false;
	}
}