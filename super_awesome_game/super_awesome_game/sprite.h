#ifndef sprite_h
#define sprite_h

#include "include\SDL.h"
#include <string>

// Contains functions which handle the loading, display and animation of images

class sprite{
protected:
	SDL_Surface* image;
	SDL_Rect	 offset;

public:
	sprite();	//loads a default image
	~sprite();	//releases memory

	//for loading an image
	void loadImage(std::string file);
	void loadText(SDL_Surface* _textDis);

	void animate(bool loop);	//ANIMATES THE SPRITE SHEET, takes a boolean to determine whether the animation loops
	void load_SpriteSheet(std::string file, int numOfImgs, int colorKey);	//loads a sprite sheet and sets its offset

	//for image
	SDL_Surface* getImage();
	SDL_Rect getOffset();
};

#endif