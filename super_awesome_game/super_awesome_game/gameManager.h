#ifndef gameManager_h
#define gameManager_h

#include "gameObject.h"	//may not need to include gameObject here as it is derived through textDisplay, shieldPowerUp...etc
#include "textDisplay.h"
#include "sound.h"
#include "music.h"
#include "shieldPowerUp.h"
#include "speedPowerUp.h"
#include "shield.h"
#include "speed.h"
#include <vector>
#include <map>

//Manages the game (the objects in the game)

class gameManager{
protected:
	//------------------------LISTS---------------------------
	
	//---------------------STATE LISTS------------------------
	std::vector<gameObject*> splashList;
	std::vector<gameObject*> titleList;
	std::vector<gameObject*> helpList;
	std::vector<gameObject*> scoreList;
	std::map<std::string, gameObject*> buttonList;

	//---------------------LEVEL LISTS------------------------
	std::vector<gameObject*> levelList;

	//-----------------INGAME RELATED LISTS-------------------
	//player
	std::vector<gameObject*> playerList;
	std::vector<gameObject*> playerBullet_List;
	std::vector<gameObject*> playerLives_List;
	//enemies
	std::vector<gameObject*> enemyList;
	std::vector<gameObject*> enemyBullet_List;
	//power ups
	std::vector<gameObject*> shieldPowerUpList;
	std::vector<gameObject*> speedPowerUpList;
	std::vector<gameObject*> shield_powerList;
	std::vector<gameObject*> speed_powerList;

	std::vector<gameObject*> backgroundList;
	std::map<std::string, gameObject*> textDisplay_List;

	std::vector<gameObject*> pauseMenu_List;	//in-game pause menu

	//****************************UI STUFF****************************
	//------------power up duration displays------------
	std::map<std::string, gameObject*> powerUpDurationDisplay_List;	//displays currently the duration of the speed and shield power ups

	//-------------------------------------------------------------

	//these variables are for regulating the frame rate
	int frameRate;
	int startTime;
	//-------------------------------------------------------------

	bool allG_Active;	//holds the active state of all game objects
	//variables to regulate the puase call
	float useDelay;	//holds the delay time between activation
	Uint32 uDelayTimeElapse;
	//-------------------------------------------------------------

	int gameState;	//to switch between the game states

	//these variables hold the duration of each power up effect
	int shieldDur;
	int speedDur;

	music inGameBackground_Music;	//in-game background music
	sound titleBkgrndMusic;	//title screen music

	//--sound effects--
	sound shieldPW_Snd;
	sound speedPW_Snd;


	//player stuff
	int playerLives;	//keeps count of how many lives the player has left
	float playerScore;	//keeps count of the players score
	int shieldPowerUp_streak;	//holds the streak, every 5 kills the player will get a shield power up
	int speedPowerUp_streak;	//holds the streak, every 8 kills the player will get a speed power up

	//*****coolision check booleans*****
	//bullet to...
	bool bulletToEnemy_collCheck;	//player bullet to enemy
	bool bulletToPlayer_collCheck;	//enemy bullet to player
	//player to...
	bool playerToShieldPowerUp_collCheck;	//player to shield power up
	bool playerToSpeedPowerUp_collCheck;	//player to speed power up
	bool playerBulletToEnemyBullet_collCheck;	//player bullet to enemy bullet
	bool playerToEnemy_collCheck;	//player to enemy
	//shield to...
	bool shieldToEnemy_collCheck;	//shield to enemy
	bool shieldToEnemyBullet_collCheck;	//shield to enemy bullet

	gameManager();	//from this constructor being protected, I can tell this class is using a singleton pattern design

	/*static pointer used here to ensure only one is made
	the pointer will point to a new gameManager object
	it is also a GLOBAL variable*/
	static gameManager* pSharedGameManager;

public:
	void init();	//initialises the various variables required for the game
	void resetStart_newGame();	//calls objects required for a new game

	static gameManager* sharedGameManager();

	//these functions add another object to the end of the vectors
	void addToSplashList(gameObject* tempGameObj);	//for splash screen
	void addToTitleList(gameObject* tempGameObj);	//for title screen
	void addToHelpList(gameObject* tempGameObj);	//for help screen
	void addToScoreList(gameObject* tempGameObj);	//for score screen
	void addToButtonList(std::string buttonName, gameObject* tempGameObj);	//for all buttons

	//---------------------LEVEL LISTS----------------------------------------
	void addToLevelList(gameObject* tempGameObj);	//for levels

	//-----------------INGAME RELATED LISTS-----------------------------------
	//player
	void addToPlayerList(gameObject* tempGameObj);	//for the player
	void addToPlayerBulletList(gameObject* tempGameObj);	//for the players bullets
	void addToPlayerLives(gameObject* tempGameObj);	//for the players lives counter display
	//enemy
	void addToEnemyList(gameObject* tempGameObj);	//for the enemies
	void addToEnemyBulletList(gameObject* tempGameObj);	//for the enemy bullets
	//power up
	void addToShieldPowerUpList(gameObject* tempGameObj);	//for the shield power up
	void addToSpeedPowerUpList(gameObject* tempGameObj);	//for the speed power up
	void addtoShieldPowerEffect_List(gameObject* tempGameObj);	//for the shield power effect
	void addtoSpeedPowerEffect_List(gameObject* tempGameObj);	//for the speed power effect

	void addToBackgroundList(gameObject* tempGameObj);	//for the background
	void addToTextList(std::string textName, gameObject* tempGameObj);	//for score text

	void addToPauseMenuList(gameObject* tempGameObj);	//for the ingame pause menu

	//****************************UI STUFF****************************
	//------------power up duration displays------------
	void addToPowerUpDurationDisplay(std::string _name, gameObject* tempGameObj);	//for the power up duration displays


	//object list for the various game states
	void _splash(SDL_Surface* scrn, SDL_Event evt);
	void _title(SDL_Surface* scrn, SDL_Event evt);
	void _help(SDL_Surface* scrn, SDL_Event evt);
	void _game(SDL_Surface* scrn, SDL_Event evt);
	void _score(SDL_Surface* scrn, SDL_Event evt);
	//this function will contain all collision statements for all object in the game state
	void _gameCollision();

	//checks for collision between 2 game objects
	bool collisionChecker(gameObject* tempGameObj_1, gameObject* tempGameObj_2);

	//changes the active state of all game objects
	void switchActive();

	//switched between the various game states
	void gameStateSwitcher(SDL_Surface* scrn, SDL_Event evt);

	void set_ALL_ToFalse(gameObject* tempGameObj);	//sets the active and alive for these list of objects to false
	void destroyGameObjects();	//destroys game objects
	void sweepLists();	//this will clear out dead objects from all lists
	void regulateFrameRate();	//function to regulate frame rate
};

#endif gameManager_h