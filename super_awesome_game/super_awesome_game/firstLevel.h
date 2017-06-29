#ifndef firstLevel_h
#define firstLevel_h

#include "gameManager.h"
#include "gameObject.h"
#include "enemyUFO.h"
#include "enemyPurp.h"
#include "enemyYell.h"
#include "gameBackground.h"

class firstLevel: public gameObject{
protected:
	//enemies
	enemyUFO* _enemy;
	enemyPurp* _purEnemy;
	enemyYell* _yellEnemy;

	//background
	gameBackground* _background;

	int wave;	//determines how many waves there are going to be

	float nextWaveTCounter;	//the time till the next wave hits
	Uint32 timeElapsed;	//keeps track of how much time has passed since the last wave hit

public:
	firstLevel();

	void init();

	void update(SDL_Event evt);

	void onCreate();
	void onUpdate(SDL_Event evt);
	void onDestroy(SDL_Event evt);
};

#endif