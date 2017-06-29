#include "playerBullet.h"

playerBullet::playerBullet(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToPlayerBulletList(this);
}

playerBullet::playerBullet(int posX, int posY){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToPlayerBulletList(this);

	position.x = posX;
	position.y = posY;
	/*position.w = displaySprite->getOffset().w;
	position.h = displaySprite->getOffset().h;*/
}

playerBullet::~playerBullet(){
}

void playerBullet::init(){
	_playerBullet.load_SpriteSheet("player laser.bmp", 1, 0x2cb45f);
	set_displaySprite(&_playerBullet);

	//MUST SET INITIAL POSITION TO THE SAME VALUE AS PLAYER POSITION VALUE
	position.x = 0;
	position.y = 0;
}

//moves the sprite to the new location at an incremental speed
void playerBullet::move(){
	position.y -= 6;
	
	//checks if playerBullet has gone off screen, if so then deletes
	if(position.y <= 0){
		alive = false;
		active = false;
	}
}

void playerBullet::update(SDL_Event evt){
	move();
}