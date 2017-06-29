#include "include\SDL.h"
#include "baseObject.h"

/*-------------------------------------
	SETTERS
-------------------------------------*/
void baseObject::setX(int sx){
	position.x = sx;
}
	
void baseObject::setY(int sy){
	position.y = sy;
}
	
void baseObject::setH(int sh){
	position.h = sh;
}
	
void baseObject::setW(int sw){
	position.w = sw;
}


/*-------------------------------------
	GETTERS
-------------------------------------*/
int baseObject::getX(){
	return position.x;
}
	
int baseObject::getY(){
	return position.y;
}
	
int baseObject::getH(){
	return position.h;
}
	
int baseObject::getW(){
	return position.w;
}


SDL_Rect baseObject::getPosition(){
	return position;
}