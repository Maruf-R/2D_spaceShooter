#include "sprite.h"
#include "baseObject.h"

//constructor
sprite::sprite(){
	image = SDL_LoadBMP("X.bmp");
}

//destructor
sprite::~sprite(){
	SDL_FreeSurface(image);	//frees up the memory held by the image
}

//LOADS AN IMAGE
void sprite::loadImage(std::string file){
	image = SDL_LoadBMP(file.c_str());

	//images offset
	offset.x = offset.y = 0;
	offset.w = image->w;
	offset.h = image->h;
}


//loads text here
void sprite::loadText(SDL_Surface* _texDis){
	image = _texDis;
	
	//offset for text
	offset.x = offset.y = 0;
}


//LOADS A SPRITE SHEET
//takes a sting variable for the image name
void sprite::load_SpriteSheet(std::string file, int numOfImgs, int colorKey){
	image = SDL_LoadBMP(file.c_str());
	SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorKey);	//sets the colour key, by default to 0x008000

	//images offset
	offset.x = offset.y = 0;
	offset.w = image->w / numOfImgs;	//sets the offset.w to the width of a single image of sprite sheet
	offset.h = image->h;
}


//ANIMATES THE SPRITE SHEET
//Displays one image on the spritesheet at a time, moving along at intervals of offset.w
void sprite::animate(bool loop){
	if(offset.x < (image->w - offset.w)){
		offset.x += offset.w;
	}
	
	if(loop){
		if(offset.x >= (image->w - offset.w)){
			offset.x = 0;
		}
	}
}

//gets the image
SDL_Surface* sprite::getImage(){
	return image;
}

SDL_Rect sprite::getOffset(){
	return offset;
}