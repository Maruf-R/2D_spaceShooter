#include "gameObject.h"

gameObject::gameObject(){
}

gameObject::~gameObject(){
}

//blits the sprite to the screen, at a specific location (location is frmo gameObject which inherited the position from baseObject
void gameObject::draw(SDL_Surface* scrn){
	//SDL_FillRect(scrn, &position, 0xff00ff);	//for testing the hit box
	SDL_BlitSurface(displaySprite->getImage(), &displaySprite->getOffset(), scrn, &position);
}

/*using a pointer here to point to the address of the existing object instead of making ANOTHER copy of it, which would take up twice the
 *memory. Instead it takes up only the memory of a pointer (the size of a char), theremore more efficient*/
void gameObject::set_displaySprite(sprite* spr){
	displaySprite = spr;
}

//updates the sprite
void gameObject::update(SDL_Event evt){
}

//take inputs
void gameObject::input(SDL_Event evt){
}

//function to display scores
void gameObject::setNumber(double _number){
}


//setters for boolean variables
void gameObject::setActive(bool status){
	active = status;
}

void gameObject::setAlive(bool status){
	alive = status;
}

void gameObject::setState(int _state){
	state = _state;
}

//getters for boolean variable
bool gameObject::getActive(){
	return active;
}

bool gameObject::getAlive(){
	return alive;
}

int gameObject::getState(){
	return state;
}