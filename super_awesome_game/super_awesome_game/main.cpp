#include <iostream>
#include "include\SDL.h"
#include <SDL_mixer.h>
#include "sprite.h"
#include "gameObject.h"
#include "splashScreen.h"
#include "titleScreen.h"
#include "helpScreen.h"
#include "pauseMenu.h"
#include "scoreScreen.h"
#include "button.h"
#include "player.h"
#include "playerLives.h"
#include "textDisplay.h"
#include "shieldDurationDisplay.h"
#include "speedDurationDisplay.h"
#include "firstLevel.h"
#include "gameManager.h"
using namespace std;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 960;

int main(int argc, char** argv){
	
	/*-------------------------------------
		INITIALISATION
	-------------------------------------*/
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
	TTF_Init();
	
	/*-------------------------------------
		VARIABLE DECLARATION
	-------------------------------------*/
	SDL_Surface* screen;
	SDL_Event	 evt;
	bool		 running;
	
	//screens
	splashScreen* _splashScrn;
	titleScreen* _titleScrn;
	helpScreen* _helpScrn;
	scoreScreen* _scoreScrn;

	//buttons
	button* _play;
	button* _help;
	//button* _quit;

	//levels
	firstLevel* level_1;

	//pause menu
	pauseMenu* _pauseMenu;

	//text displays
	textDisplay* pScore;

	//power up duration displays
	shieldDurationDisplay* _shieldDDisplay;	//shield
	speedDurationDisplay* _speedDDisplay;	//speed

	//player
	player* player1;
	//player life
	playerLives* _pLives;

	/*-------------------------------------
		VARIABLE INITIALISATIONS
	-------------------------------------*/
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
	running = true;

	//screens
	_splashScrn = new splashScreen;
	_titleScrn = new titleScreen;
	_helpScrn = new helpScreen;
	_scoreScrn = new scoreScreen;

	//buttons
	_play = new button(400, 410, "play", "play_UP.bmp", "play_OVER.bmp", "play_DOWN.bmp");
	_help = new button(_play->getX(), _play->getY()+70, "help", "help_UP.bmp", "help_OVER.bmp", "help_DOWN.bmp");


	//levels
	level_1 = new firstLevel;

	//pause menu
	_pauseMenu = new pauseMenu;

	//text displays
	pScore = new textDisplay(900, 10, 32, "pScore");

	//power up duration displays
	_shieldDDisplay = new shieldDurationDisplay;	//shield
	_speedDDisplay = new speedDurationDisplay;	//speed

	//player
	player1 = new player;
	//player lives
	_pLives = new playerLives;

	/*-------------------------------------
		game loop
	-------------------------------------*/
	SDL_EnableKeyRepeat(1, 1);
	while(running){  //checks to see if programme is still running

		/*-------------------------------------
			event loop
		-------------------------------------*/
		while(SDL_PollEvent(&evt)){
			if(evt.type == SDL_QUIT){
				running = false;
			}	//ends game loop
			
		}	//end of event loop
		/*-------------------------------------
			update game world
		-------------------------------------*/
		
		
		/*-------------------------------------
			update screen
		-------------------------------------*/
		SDL_FillRect(screen, NULL, 0x000000);

		gameManager::sharedGameManager() -> gameStateSwitcher(screen, evt);	//calls the draw function through gameManager
		
		gameManager::sharedGameManager() -> regulateFrameRate();	//frame rate regulator
		gameManager::sharedGameManager() -> sweepLists();	//sweeper

		SDL_Flip(screen);	//refreshes screen

	}	//end of game loop

	//Quit
	SDL_Quit();	//quits SDL
	TTF_Quit();	//quits Text
	Mix_CloseAudio();	//quits sound

	return 0;
}	//end of programme