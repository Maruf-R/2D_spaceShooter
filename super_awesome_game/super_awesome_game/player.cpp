#include "player.h"

const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;
const int FIRE = 4;

player::player(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToPlayerList(this);
}

player::~player(){
}

//loads a sprite for the various states
void player::init(){
	left.load_SpriteSheet("playerLeft.bmp", 1, 0xffffff);
	idle.load_SpriteSheet("player_Idle.bmp", 1, 0x3a2e3f);
	right.load_SpriteSheet("playerRight.bmp", 1, 0xffffff);

	snd.load("player laser sound effect.wav", -1, -1);

	key[RIGHT] = false;
	key[LEFT] = false;
	key[UP] = false;
	key[DOWN] = false;
	key[FIRE] = false;

	//bullet cooldown variables
	shootCD = 600;
	timeElapsed = SDL_GetTicks();
	//-------------------------

	speed = 5;

	set_displaySprite(&idle);

	state = CREATE_STATE;
	alive = true;
	active = true;
}

//moves the sprite to the new location at an incremental speed
void player::move(int X, int Y){
	position.x = position.x + X;
	position.y = position.y + Y;
}

//takes player input, key presses etc.
void player::input(SDL_Event evt){
	if(evt.type == SDL_KEYDOWN){
		if(evt.key.keysym.sym == SDLK_a){
			move(-speed, 0);
		}

		if(evt.key.keysym.sym == SDLK_d){
			if((position.x + position.w) < 960){
				move(speed, 0);
			}
		}

		if(evt.key.keysym.sym == SDLK_w){
			move(0, -speed);
		}

		if(evt.key.keysym.sym == SDLK_s){
			if((position.y + position.h) < 960){
				move(0, speed);
			}
		}

		//shoot
		if(evt.key.keysym.sym == SDLK_SPACE){
			if(timeElapsed + shootCD < SDL_GetTicks()){
				_bullet = new playerBullet(position.x + position.w/2, position.y + position.h/2);
				snd.play();	//sound played when bullet fired
				timeElapsed = SDL_GetTicks();
			}
		}
	}
}

//changes player speed
void player::setNumber(double _spd){
	speed = _spd;
}

void player::update(SDL_Event evt){
	set_displaySprite(&idle);

	switch(state){
	case CREATE_STATE:
		onCreate();
		break;

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


void player::onCreate(){
	position.y = 880;
	if(position.x < 200){
		position.x += 5;
		active = false;
	}

	else{
		state = UPDATE_STATE;
		active = true;
	}
}

void player::onUpdate(SDL_Event evt){
	//sets sprite state
	if(evt.type == SDL_KEYDOWN){
		if(evt.key.keysym.sym == SDLK_d){
			set_displaySprite(&right);
		}

		if(evt.key.keysym.sym == SDLK_a){
			set_displaySprite(&left);
		}
	}
}

void player::onDestroy(SDL_Event evt){
	active = false;
	alive = false;
}