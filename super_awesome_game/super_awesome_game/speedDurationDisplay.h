#ifndef speedDurationDisplay_h
#define speedDurationDisplay_h

#include "gameObject.h"
#include "gameManager.h"
#include "textDisplay.h"

class speedDurationDisplay: public gameObject{
protected:
	sprite _speedDurationDisplay;
	textDisplay* _speedDuration;	//will display the time remaining till the power up is over

	double puDuration;

	//these variables are to countdown every second, not every processing cycle
	float countdownDelay;
	Uint32 timeElapsed;

public:
	speedDurationDisplay();
	~speedDurationDisplay();

	void setNumber(double _duration);
	void init(); //loads a sprite for the various states
	void update(SDL_Event evt);
};

#endif