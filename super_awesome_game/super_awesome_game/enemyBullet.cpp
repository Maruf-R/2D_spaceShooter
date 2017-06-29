#include "enemyBullet.h"

enemyBullet::enemyBullet(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToEnemyBulletList(this);
}

enemyBullet::enemyBullet(int posX, int posY, std::string _bullet){
	init();	//calls the init function to initialise the player

	_enemyBullet.load_SpriteSheet(_bullet.c_str(), 1, 0xffffff);

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToEnemyBulletList(this);

	position.x = posX;
	position.y = posY;
	/*position.w = displaySprite->getOffset().w;
	position.h = displaySprite->getOffset().h;*/
}

enemyBullet::~enemyBullet(){
}

void enemyBullet::init(){
	_enemyBullet.load_SpriteSheet("purple enemy laser.bmp", 1, 0xffffff);
	set_displaySprite(&_enemyBullet);

	//MUST SET INITIAL POSITION TO THE SAME VALUE AS PLAYER POSITION VALUE
	position.x = 0;
	position.y = 0;
}

//moves the sprite to the new location at an incremental speed
void enemyBullet::move(){
	position.y += 6;
	
	//checks if enemyBullet has gone off screen, if so then deletes
	if(position.y <= 0){
		alive = false;
		active = false;
	}
}

void enemyBullet::update(SDL_Event evt){
	move();
}