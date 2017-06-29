#include "enemyYell.h"

enemyYell::enemyYell(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToEnemyList(this);
}

enemyYell::enemyYell(int X, int Y){
	init();	//calls the init function to initialise the player

	position.x = X;
	position.y = Y;

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToEnemyList(this);
}

enemyYell::~enemyYell(){
}

void enemyYell::init(){
	//sprites
	_enemyYell.load_SpriteSheet("yellow enemy.bmp", 1, 0xffffff);
	_explosion.load_SpriteSheet("Explosion.bmp", 12, 0xffffff);

	//sounds
	bulletSnd.load("enemy laser sound effect.wav", -1, -1);
	explosionSnd.load("explosion sound effect.wav", -1, -1);

	//bullet cooldown variables
	shotCD  = 1000;
	timeElapsed = SDL_GetTicks();

	set_displaySprite(&_enemyYell);

	state = UPDATE_STATE;

	position.x = 700;
	position.y = 200;
	/*position.w = displaySprite->getOffset().w;
	position.h = displaySprite->getOffset().h;*/
}

//moves the sprite to the new location at an incremental speed
void enemyYell::move(){
	position.y += 2;

	//checks if enemyYell has gone off screen, if so then deletes
	if(position.y >= 960){
		alive = false;
		active = false;
	}
}

void enemyYell::update(SDL_Event evt){
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

void enemyYell::onUpdate(SDL_Event evt){
	move();

	if(timeElapsed + shotCD < SDL_GetTicks()){
		_bullet = new enemyBullet(position.x + position.w/2, position.y + position.h/2, "yellow enemy laser.bmp");
		bulletSnd.play();	//sound played when bullet fired
		timeElapsed = SDL_GetTicks();
	}
}

void enemyYell::onDestroy(SDL_Event evt){
	set_displaySprite(&_explosion);
	displaySprite->animate(false);
	explosionSnd.play();	//sound played when enemy dies and explodes

	if(displaySprite -> getOffset().x >= (displaySprite -> getImage()->w - displaySprite -> getOffset().w)){
		active = false;
		alive = false;
	}
}