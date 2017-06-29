#ifndef gameObject_h
#define gameObject_h
#include "baseObject.h"
#include "sprite.h"

// sets, displays and draws a sprite, inherits and gets all attributes from basObject

class gameObject: public baseObject{
protected:
	sprite* displaySprite;
	bool	alive;
	bool	active;
	int		state;

	//static in front means they are global variables
	static const int CREATE_STATE = 10;
	static const int UPDATE_STATE = 20;
	static const int DESTROY_STATE = 30;

public:
	gameObject();
	virtual ~gameObject();

	//function to blit images to screen
	void set_displaySprite(sprite* spr);	//sets displaySprite to a sprite

	//using 'virtual' will call all functions with the same name in all classes
	virtual void draw(SDL_Surface* scrn);	//blits the sprite to screen
	virtual void update(SDL_Event evt);	//animates the sprite
	virtual void input(SDL_Event evt);	//takes mouse and keyboard inputs etc

	virtual void setNumber(double _number);	//will display a number as text, used by text display classes

	//setters for boolean variables
	void setActive(bool status);
	void setAlive(bool status);

	void setState(int _state);

	//getters for boolean variable
	bool getActive();
	bool getAlive();

	int getState();
};

#endif // ! gameObject_h
