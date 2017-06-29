#include "speedDurationDisplay.h"

speedDurationDisplay::speedDurationDisplay(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToPowerUpDurationDisplay("speedPWDur", this);
}

speedDurationDisplay::~speedDurationDisplay(){
}

void speedDurationDisplay::init(){
	_speedDurationDisplay.load_SpriteSheet("inactive speed power up.bmp", 1, 0x3a2e3f);
	set_displaySprite(&_speedDurationDisplay);

	position.x = 920;
	position.y = 910;

	//the timer
	_speedDuration = new textDisplay(position.x - 30, position.y, 32, "speedDuration");

	alive = true;
	active = true;

	puDuration = 5;

	//these variables are to countdown every second, not every processing cycle
	countdownDelay = 1000;	//will countdown a second every second
	timeElapsed = SDL_GetTicks();
}

void speedDurationDisplay::setNumber(double _duration){
	puDuration = _duration;
	_speedDuration -> setNumber(puDuration);
}

void speedDurationDisplay::update(SDL_Event evt){
	if(puDuration > 0){
		if(countdownDelay + timeElapsed < SDL_GetTicks()){
			_speedDuration -> setNumber(puDuration);
			puDuration -= 1;
			timeElapsed = SDL_GetTicks();
		}
	}
}