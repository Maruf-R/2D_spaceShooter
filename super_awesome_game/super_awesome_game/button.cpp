#include "button.h"

button::button(){
	init();	//calls the init function to initialise the player

	//anything the player class makes gets pushed on to the end of the playerlist vector
	//gameManager::sharedGameManager() -> ;
}

button::button(int posX, int posY, std::string _buttonName, std::string _up, std::string _over, std::string _down){
	init();	//calls the init function to initialise the player

	down.load_SpriteSheet(_down.c_str(), 1, NULL);
	idle.load_SpriteSheet(_up.c_str(), 1, NULL);
	over.load_SpriteSheet(_over.c_str(), 1, NULL);

	//anything the player class makes gets pushed on to the end of the playerlist vector
	gameManager::sharedGameManager() -> addToButtonList(_buttonName.c_str(), this);

	position.x = posX;
	position.y = posY;
}

button::~button(){
	std::cout<<"\nbutton destroyed";
}

void button::init(){
	down.load_SpriteSheet("play_DOWN.bmp", 1, NULL);
	idle.load_SpriteSheet("play_UP.bmp", 1, NULL);
	over.load_SpriteSheet("play_OVER.bmp", 1, NULL);

	set_displaySprite(&idle);

	//button sound effects
	mouseOver.load("rollover.wav", -1, -1);
	mouseClick.load("click.wav", -1, -1);

	//MUST SET INITIAL POSITION TO THE SAME VALUE AS PLAYER POSITION VALUE
	position.x = 0;
	position.y = 0;
}


void button::input(SDL_Event evt){
	set_displaySprite(&idle);

	if(evt.type == SDL_MOUSEBUTTONDOWN){ //Checks for mouse button down click
		if(evt.button.button == SDL_BUTTON_LEFT){ //checks if the mouse button clicked is left click
			if(evt.motion.x > position.x && evt.motion.x < (position.w+position.x)){ //checks for collision in x axis
				if(evt.motion.y > position.y && evt.motion.y < (position.h+position.y)){ //checks for collision in y axis
					set_displaySprite(&down);
					mouseClick.play();
					std::cout<<"\nbutton clicked!";

					active = false;
				} //COLLISION CHECK .y
			} //COLLISION CHECK .x
		} //SDL_BUTTON_LEFT
	} //MOUSEBUTTONDOWN

	if(evt.type == SDL_MOUSEMOTION){
		if(evt.motion.x > position.x && evt.motion.x < (position.w+position.x)){ //checks for collision in x axis
			if(evt.motion.y > position.y && evt.motion.y < (position.h+position.y)){ //checks for collision in y axis
				set_displaySprite(&over);
				mouseOver.play();
				std::cout<<"\nmouse over!";
			} //COLLISION CHECK .y
		} //COLLISION CHECK .x
	}
}

void button::update(SDL_Event evt){
	set_displaySprite(&idle);
}