#ifndef shieldDurationDisplay_h
#define shieldDurationDisplay_h

#include "gameObject.h"
#include "gameManager.h"
#include "textDisplay.h"

class shieldDurationDisplay: public gameObject{
protected:
	sprite _shieldDurationDisplay;
	textDisplay* _shieldDuration;	//will display the time remaining till the power up is over

	double puDuration;	//holds the number of seconds the shield will be active on the player

	//these variables are to countdown every second, not every processing cycle
	float countdownDelay;
	Uint32 timeElapsed;

public:
	shieldDurationDisplay();
	~shieldDurationDisplay();

	void setNumber(double _duration);
	void init(); //loads a sprite for the various states
	void update(SDL_Event evt);
};

#endif