#ifndef player_h
#define player_h

#include "gameObject.h"
#include "gameManager.h"
#include "sound.h"
#include "playerBullet.h"

//Makes a sprite object for player, deals with it's various states, movement, key inputs, and updates

class player: public gameObject{
protected:
	bool key[5];	//for player key presses
	double speed;	//player speed

	//all the player sprites (states)
	sprite left;
	sprite idle;
	sprite right;

	sound snd;	//bullet fired sound
	playerBullet* _bullet;	//bullet

	//for bullet fire cooldown
	float shootCD;	//cooldown
	Uint32 timeElapsed;	//keeps track of how much time has passed since a bullet was last fired

public:
	player();
	~player();

	void init(); //loads a sprite for the various states
	void move(int X, int Y); //moves the sprite
	void input(SDL_Event evt); //takes player input, key presses etc.
	void update(SDL_Event evt);

	void onCreate();
	void onUpdate(SDL_Event evt);
	void onDestroy(SDL_Event evt);

	void setNumber(double _spd);
};

#endif


//JUST TEMPORARYILY STORING THIS CODE HERE INCASE I NEED IT
/*if(evt.type == SDL_KEYDOWN){
		if(evt.key.keysym.sym == SDLK_a){
			move(-1, 0);
		}

		if(evt.key.keysym.sym == SDLK_d){
			move(1, 0);
		}

		if(evt.key.keysym.sym == SDLK_w){
			move(0, -1);
		}

		if(evt.key.keysym.sym == SDLK_s){
			move(0, 1);
		}

		//shoot
		if(evt.key.keysym.sym == SDLK_SPACE){
			_bullet = new bullet(position.x, position.y);
		}

		if(evt.key.keysym.sym == SDLK_ESCAPE){
			position.x = 100;
			position.y = 100;
		}
	}*/