#include "firstLevel.h"

firstLevel::firstLevel(){
	init();
	_background = new gameBackground();

	state = UPDATE_STATE;

	gameManager::sharedGameManager() -> addToLevelList(this);
}

void firstLevel::init(){
	nextWaveTCounter = 7000;
	timeElapsed = SDL_GetTicks();

	wave = 5;

	active = true;
	alive = true;
}

void firstLevel::update(SDL_Event evt){
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

void firstLevel::onCreate(){
	init();
	state = UPDATE_STATE;
}

void firstLevel::onUpdate(SDL_Event evt){
	if(active && alive){
		if(wave >= 0){
			if(timeElapsed + nextWaveTCounter < SDL_GetTicks()){
				wave -= 1;
				_yellEnemy = new enemyYell(200, 10);
				_enemy = new enemyUFO(400, 10);
				_purEnemy = new enemyPurp(600, 10);

				timeElapsed = SDL_GetTicks();
			}
		}
	}

	if(wave == -1){
		active = false;
		//alive = false;
	}
}

void firstLevel::onDestroy(SDL_Event evt){
	active = false;
	alive = false;
}