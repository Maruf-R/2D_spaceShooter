#include "textDisplay.h"

textDisplay::textDisplay(int posX, int posY, int _fontSize, std::string _textName){
	fontSize = _fontSize;	//sets the font size of the text
	
	init();	//calls the init function to initialise the player

	position.x = posX;
	position.y = posY;

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToTextList(_textName.c_str(), this);
}

textDisplay::~textDisplay(){
}

void textDisplay::init(){
	//score text colour
	fontCol.r = 255;
	fontCol.g = 255;
	fontCol.b = 255;
	
	font = TTF_OpenFont("kenvector_futureFONT.ttf", fontSize);	//score text font
	_textDisplay = TTF_RenderText_Solid(font, result.c_str(), fontCol); //scoreText will display the value of result
	_text.loadText(_textDisplay);

	set_displaySprite(&_text);
	
	number = 0;

	alive = true;
	active = true;

	position.x = 700;
	position.y = 10;
}

void textDisplay::draw(SDL_Surface* scrn){
	//SDL_FillRect(scrn, &position, 0xff00ff);
	SDL_BlitSurface(_textDisplay, NULL, scrn, &position); //displays the score
}

void textDisplay::update(SDL_Event evt){
	scoreConv.str("");
	scoreConv << number;
	result = scoreConv.str();
	_textDisplay = TTF_RenderText_Solid(font, result.c_str(), fontCol); //scoreText will display the value of result
}


//function to set the players score
void textDisplay::setNumber(double _number){
	number = _number;	//the number passed in is stored in the number variable
	//std::cout<<"\nscore= " <<result;
}