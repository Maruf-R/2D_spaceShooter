#include "shieldDurationDisplay.h"

shieldDurationDisplay::shieldDurationDisplay(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToPowerUpDurationDisplay("shieldPWDur", this);
}

shieldDurationDisplay::~shieldDurationDisplay(){
}

void shieldDurationDisplay::init(){
	_shieldDurationDisplay.load_SpriteSheet("inactive shield power up.bmp", 1, 0x3a2e3f);
	set_displaySprite(&_shieldDurationDisplay);

	position.x = 10;
	position.y = 920;

	//displays the timer countdown
	_shieldDuration = new textDisplay(position.x + 40, position.y - 5, 32, "shieldDuration");
	
	alive = true;
	active = true;

	puDuration = 7;

	//these variables are to countdown every second, not every processing cycle
	countdownDelay = 1000;	//will countdown a second every second
	timeElapsed = SDL_GetTicks();
}


void shieldDurationDisplay::setNumber(double _duration){
	puDuration = _duration;
	_shieldDuration -> setNumber(puDuration);
}

void shieldDurationDisplay::update(SDL_Event evt){
	if(puDuration > 0){
		if(countdownDelay + timeElapsed < SDL_GetTicks()){
			_shieldDuration -> setNumber(puDuration);
			puDuration -= 1;
			timeElapsed = SDL_GetTicks();
		}
	}
}