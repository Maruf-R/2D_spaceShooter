#ifndef pauseMenu_h
#define pauseMenu_h

#include "gameObject.h"
#include "gameManager.h"

class pauseMenu: public gameObject{
protected:
	sprite gamePaused;	//game paused text image

	/*IN THE FUTURE I MAY WANT OTHER BUTTONS IN THE pauseMenu,
	THESE WILL GO HERE, THE STATE VARIABLE BELOW WILL BE USED TO SWITCH BETWEEN VARIOUS PAUSE MENU STATES*/

	int _state;	//the switch state

public:
	pauseMenu();
	~pauseMenu();

	void init(); //loads a sprite for the various states
	void input(SDL_Event evt);
	void update(SDL_Event evt);
};

#endif