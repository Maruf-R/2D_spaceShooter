#include <iostream>
#include "gameManager.h"

//#define DEBUG

//gameState switch variables
const int SPLASHS = 0;
const int TITLES = 1;
const int HELPS = 2;
const int GAMES = 3;
const int SCORES = 4;

//power up stuff
shieldPowerUp* shPowerUp;
speedPowerUp* spdPowerUp;
shield* _pShield;
speed* _pSpeed;

//global static instance of gameManager class set to point at nothing by default
gameManager* gameManager::pSharedGameManager = NULL;

gameManager::gameManager(){
	//frame rate regulator variables
	frameRate = 60;
	startTime = 0;

	//in-game background music
	inGameBackground_Music.load("background music.wav", 80);
	inGameBackground_Music.play();
	inGameBackground_Music.pause();

	//title screen music
	titleBkgrndMusic.load("titleS_Music.wav", -1, -1);

	//--sound effects--
	shieldPW_Snd.load("shieldPW_SFX.wav", -1, -1);
	speedPW_Snd.load("speedPW_SFX.wav", -1, -1);

	//game state starts from splash
	gameState = SPLASHS;

	init();

	std::cout << "\ncreating game manager";
}

/*---------------------------------------------------------
sharedGameManager() 
returns a single instance of the gameManager clss

Checks to see if the pointer is already pointing at an instance of gameManager,
if not then it points to a new gameManager
then returns pointer
---------------------------------------------------------*/
gameManager* gameManager::sharedGameManager(){
	if(pSharedGameManager == NULL){
		pSharedGameManager = new gameManager();
	}

	return pSharedGameManager;
}

void gameManager::init(){
	//all game objects active state is set to true by default
	allG_Active = true;
	//variables to regulate the puase call
	useDelay = 500;	//holds the delay time between activation
	uDelayTimeElapse = SDL_GetTicks();

	//these variables hold the duration of each power up effect
	//keep these values up to date with those in the respected power up duration display classes
	shieldDur = 7;
	speedDur = 5;


	//player stuff
	playerLives = 3;
	playerScore = 0;
	shieldPowerUp_streak = 0;
	speedPowerUp_streak = 0;

	//collision check booleans
	bulletToEnemy_collCheck = false;
	bulletToPlayer_collCheck = false;

	playerToShieldPowerUp_collCheck = false;
	playerToSpeedPowerUp_collCheck = false;
	playerBulletToEnemyBullet_collCheck = false;
	playerToEnemy_collCheck = false;

	shieldToEnemy_collCheck = false;
	shieldToEnemyBullet_collCheck = false;
}

void gameManager::resetStart_newGame(){
	init();
	inGameBackground_Music.play();

	for(int i=0; i<levelList.size(); i++){
		levelList.at(i) -> setActive(true);
		levelList.at(i) -> setState(10);
	}

	for(int i=0; i<playerList.size(); i++){
		playerList.at(i) -> setState(10);
	}

	for(int i=0; i<playerLives_List.size(); i++){
		playerLives_List.at(i) -> setNumber(3);
		playerLives_List.at(i) -> setActive(true);
	}
}


/*-------------------------------------------------------------------
These functions add another object to the end of the vectors
They accept pointers of gameObject
-------------------------------------------------------------------*/

//---------------------STATE LISTS------------------------
//splash list
void gameManager::addToSplashList(gameObject* tempGameObj){
	splashList.push_back(tempGameObj);
}

//title list
void gameManager::addToTitleList(gameObject* tempGameObj){
	titleList.push_back(tempGameObj);
}

//help list
void gameManager::addToHelpList(gameObject* tempGameObj){
	helpList.push_back(tempGameObj);
}

//score list
void gameManager::addToScoreList(gameObject* tempGameObj){
	scoreList.push_back(tempGameObj);
}

//button list
void gameManager::addToButtonList(std::string buttonName, gameObject* tempGameObj){
	buttonList[buttonName] = tempGameObj;
}


//---------------------LEVEL LISTS------------------------
void gameManager::addToLevelList(gameObject* tempGameObj){
	levelList.push_back(tempGameObj);
}


//-----------------INGAME RELATED LISTS-------------------
//***************************player******************************
//player
void gameManager::addToPlayerList(gameObject* tempGameObj){
	playerList.push_back(tempGameObj);
}

//player bullets
void gameManager::addToPlayerBulletList(gameObject* tempGameObj){
	playerBullet_List.push_back(tempGameObj);
}

//player lives
void gameManager::addToPlayerLives(gameObject* tempGameObj){
	playerLives_List.push_back(tempGameObj);
}

//***********************enemy***********************************
//enemies
void gameManager::addToEnemyList(gameObject* tempGameObj){
	enemyList.push_back(tempGameObj);
}

//enemy bullets
void gameManager::addToEnemyBulletList(gameObject* tempGameObj){
	enemyBullet_List.push_back(tempGameObj);
}

//************************power-ups***************************
//shield power up
void gameManager::addToShieldPowerUpList(gameObject* tempGameObj){
	shieldPowerUpList.push_back(tempGameObj);
}

//speed power up
void gameManager::addToSpeedPowerUpList(gameObject* tempGameObj){
	speedPowerUpList.push_back(tempGameObj);
}

//***********************POWER EFFECTS***************************
//shield
void gameManager::addtoShieldPowerEffect_List(gameObject* tempGameObj){
	shield_powerList.push_back(tempGameObj);
}

//speed
void gameManager::addtoSpeedPowerEffect_List(gameObject* tempGameObj){
	speed_powerList.push_back(tempGameObj);
}


//background
void gameManager::addToBackgroundList(gameObject* tempGameObj){
	backgroundList.push_back(tempGameObj);
}

//text displays
void gameManager::addToTextList(std::string textName, gameObject* tempGameObj){
	textDisplay_List[textName] = tempGameObj;
}

//game pause menu
void gameManager::addToPauseMenuList(gameObject* tempGameObj){
	pauseMenu_List.push_back(tempGameObj);
}

//power up duration displays
void gameManager::addToPowerUpDurationDisplay(std::string _name, gameObject* tempGameObj){
	powerUpDurationDisplay_List[_name] = tempGameObj;
}


//draws objects in the vector on to the screen
//all the below functions first check if the object is alive & active before it carries out its function (update, input or draw)

//SPLASH
void gameManager::_splash(SDL_Surface* scrn, SDL_Event evt){
	for(int i=0; i<splashList.size(); i++){
		if(splashList.at(i) -> getAlive() /*&& splashList.at(i) -> getActive()*/){
			splashList.at(i) -> draw(scrn);
			splashList.at(i) -> update(evt);
		}

		else{
			gameState = TITLES;
		}
	}
}

//TITLE
void gameManager::_title(SDL_Surface* scrn, SDL_Event evt){
	titleBkgrndMusic.play();

	for(int i=0; i<titleList.size(); i++){
		if(titleList.at(i) -> getAlive()){
			titleList.at(i) -> draw(scrn);
			titleList.at(i) -> update(evt);

			//**********************************buttons********************************
			//play button
			if(buttonList.at("play") -> getAlive()){
				buttonList.at("play") -> draw(scrn);
				buttonList.at("play") -> input(evt);
			}

			else{
				titleBkgrndMusic.stop();
				gameState = GAMES;	//switch to game state
			}

			if(buttonList.at("play") -> getActive() == false){
				titleBkgrndMusic.stop();
				gameState = GAMES;	//switch to game state
			}

			//help button
			if(buttonList.at("help") -> getAlive()){
				buttonList.at("help") -> draw(scrn);
			}

			if(buttonList.at("help") -> getActive()){
				buttonList.at("help") -> input(evt);
			}

			else{
				titleBkgrndMusic.stop();
				gameState = HELPS;	//switch to help state
			}
		}
	}

	for(int i=0; i<helpList.size(); i++){
		helpList.at(i) -> setNumber(0);
		helpList.at(i) -> setActive(true);
	}

	resetStart_newGame();

}

//HELP
void gameManager::_help(SDL_Surface* scrn, SDL_Event evt){
	inGameBackground_Music.pause();

	for(int i=0; i<helpList.size(); i++){
		if(helpList.at(i) -> getAlive() && helpList.at(i) -> getActive()){
			helpList.at(i) -> draw(scrn);
		}

		if(helpList.at(i) -> getActive()){
			helpList.at(i) -> input(evt);
			helpList.at(i) -> update(evt);
		}

		else{
			buttonList.at("help") -> setActive(true);
			buttonList.at("play") -> setActive(true);
			gameState = TITLES;
		}
	}
}

//score
void gameManager::_score(SDL_Surface* scrn, SDL_Event evt){
	for(int i=0; i<scoreList.size(); i++){
		if(scoreList.at(i) -> getAlive() && scoreList.at(i) -> getActive()){
			scoreList.at(i) -> draw(scrn);
		}

		if(scoreList.at(i) -> getActive()){
			scoreList.at(i) -> update(evt);
			scoreList.at(i) -> setNumber(playerScore);
		}

		if(textDisplay_List.at("scoreDisp") -> getAlive() && textDisplay_List.at("scoreDisp") -> getActive()){
			textDisplay_List.at("scoreDisp") -> draw(scrn);
			textDisplay_List.at("scoreDisp") -> update(evt);
		}
	}

	if(evt.type == SDL_KEYDOWN){
		if(evt.key.keysym.sym == SDLK_ESCAPE){
			buttonList.at("play") -> setActive(true);
			gameState = TITLES;
		}
	}
}


//GAME
void gameManager::_game(SDL_Surface* scrn, SDL_Event evt){
	inGameBackground_Music.resume();

	/*calls the allG_Active funtion which switches the active state
	of all game object (used to puase and resume the game*/
	if(evt.type == SDL_KEYDOWN){
		if(evt.key.keysym.sym == SDLK_ESCAPE){
			switchActive();
		}
	}


	//**************************BACKGROUND LISTS******************************************************
	for(int i=0; i<backgroundList.size(); i++){
		if(backgroundList.at(i) -> getAlive()){
			backgroundList.at(i) -> draw(scrn);
		}

		if(backgroundList.at(i) -> getAlive() && backgroundList.at(i) -> getActive() && allG_Active == true){
			backgroundList.at(i) -> update(evt);
		}
	}

	//****************************LEVEL LISTS*********************************************************
	for(int i=0; i<levelList.size(); i++){
		if(levelList.at(i) -> getAlive() && levelList.at(i) -> getActive() && allG_Active == true){
			levelList.at(i) -> update(evt);
		}

		if(levelList.at(i) -> getActive() == false){
			destroyGameObjects();
			inGameBackground_Music.stop();
			gameState = SCORES;
		}
	}

	//****************************SCORE TEXT LIST******************************************************
	//player score display
	if(textDisplay_List.at("pScore") -> getAlive()){
		textDisplay_List.at("pScore") -> draw(scrn);
	}

	if(textDisplay_List.at("pScore") -> getActive() && allG_Active == true){
		textDisplay_List.at("pScore") -> setNumber(playerScore);	//used to display the score on screen
		textDisplay_List.at("pScore") -> update(evt);
	}


	//****************************PLAYER LIST*********************************************************
	for(int i=0; i<playerList.size(); i++){
		if(playerList.at(i) -> getAlive() /*&& playerList.at(i) -> getActive()*/){
			playerList.at(i) -> draw(scrn);
			playerList.at(i) -> update(evt);
		}

		if(playerList.at(i) -> getAlive() && playerList.at(i) -> getActive() && allG_Active == true){
			playerList.at(i) -> input(evt);
		}

		//*********************check to see if player is alive********************
		if(playerLives < 1){
			playerList.at(i) -> setActive(false);
			destroyGameObjects();
			inGameBackground_Music.stop();
			gameState = SCORES;	//switches to score state as soon as player loses all (3) lives
		}

		//if the speed power up effect is inactive then the player speed will be a default of 5
		if(speed_powerList.empty()){
			playerList.at(i) -> setNumber(5);
		}
	}

	//****************************PLAYER BULLET LIST**************************************************
	for(int i=0; i<playerBullet_List.size(); i++){
		if(playerBullet_List.at(i) -> getAlive()){
			playerBullet_List.at(i) -> draw(scrn);
		}

		if(playerBullet_List.at(i) -> getAlive() && playerBullet_List.at(i) -> getActive() && allG_Active == true){
			playerBullet_List.at(i) -> update(evt);
		}
	}

	//****************************PLAYER LIVES LIST**************************************************
	for(int i=0; i<playerLives_List.size(); i++){
		if(playerLives_List.at(i) -> getAlive()){
			playerLives_List.at(i) -> draw(scrn);
		}

		if(playerLives_List.at(i) -> getAlive() && playerLives_List.at(i) -> getActive() && allG_Active == true){
			playerLives_List.at(i) -> update(evt);

			//sets the lives display in accordance to the number of lives the player has left
			playerLives_List.at(i) -> setNumber(playerLives);
		}
	}


	//**************************SHIELD POWER UP LIST**********************************************************
	for(int i=0; i<shieldPowerUpList.size(); i++){
		if(shieldPowerUpList.at(i) -> getAlive()){
			shieldPowerUpList.at(i) -> draw(scrn);
		}

		if(shieldPowerUpList.at(i) -> getAlive() && shieldPowerUpList.at(i) -> getActive() && allG_Active == true){
			shieldPowerUpList.at(i) -> update(evt);
		}

		for(int b=0; b<playerList.size(); b++){
			playerToShieldPowerUp_collCheck = collisionChecker(playerList.at(b), shieldPowerUpList.at(i));

			if(playerToShieldPowerUp_collCheck){
				shieldPW_Snd.play();
				shieldPowerUpList.at(i) -> setState(30);
				_pShield = new shield(playerList.at(b)->getX(), playerList.at(b)->getY());
				powerUpDurationDisplay_List.at("shieldPWDur") -> setNumber(shieldDur);

				playerToShieldPowerUp_collCheck = false;
			}
		}
	}

	//***************************************SPEED POWER UP**********************************************
	for(int i=0; i<speedPowerUpList.size(); i++){
		if(speedPowerUpList.at(i) -> getAlive()){
			speedPowerUpList.at(i) -> draw(scrn);
		}

		if(speedPowerUpList.at(i) -> getAlive() && speedPowerUpList.at(i) -> getActive() && allG_Active == true){
			speedPowerUpList.at(i) -> update(evt);
		}

		for(int b=0; b<playerList.size(); b++){
			playerToSpeedPowerUp_collCheck = collisionChecker(playerList.at(b), speedPowerUpList.at(i));

			if(playerToSpeedPowerUp_collCheck){
				speedPW_Snd.play();
				speedPowerUpList.at(i) -> setState(30);
				playerList.at(b) -> setNumber(10);	//sets player speed to 10
				_pSpeed = new speed(playerList.at(b)->getX(), playerList.at(b)->getY());
				powerUpDurationDisplay_List.at("speedPWDur") -> setNumber(speedDur);

				playerToSpeedPowerUp_collCheck = false;
			}
		}
	}

	//*********************POWER UP EFFECT LIST********************************************************
	//shield power up effect
	for(int i=0; i<shield_powerList.size(); i++){
		if(shield_powerList.at(i) -> getAlive()){
			shield_powerList.at(i) -> draw(scrn);
		}

		if(shield_powerList.at(i) -> getAlive() && shield_powerList.at(i) -> getActive() && allG_Active == true){
			shield_powerList.at(i) -> update(evt);

			//will display the shield power up duration timer so long as the shield is alive
			if(powerUpDurationDisplay_List.at("shieldPWDur") -> getAlive() && powerUpDurationDisplay_List.at("shieldPWDur") -> getActive()){
				powerUpDurationDisplay_List.at("shieldPWDur") -> update(evt);
			}
		}
	}

	//sets timer display to 0 if shield power up eefect is inactive
	if(shield_powerList.empty()){
		powerUpDurationDisplay_List.at("shieldPWDur") -> setNumber(0);
	}

	//speed power up effect
	for(int i=0; i<speed_powerList.size(); i++){
		if(speed_powerList.at(i) -> getAlive()){
			speed_powerList.at(i) -> draw(scrn);
		}

		if(speed_powerList.at(i) -> getAlive() && speed_powerList.at(i) -> getActive() && allG_Active == true){
			speed_powerList.at(i) -> update(evt);

			//will display the speed power up effect duration timer as long as the shield is alive
			if(powerUpDurationDisplay_List.at("speedPWDur") -> getAlive() && powerUpDurationDisplay_List.at("speedPWDur") -> getActive()){
				powerUpDurationDisplay_List.at("speedPWDur") -> update(evt);
			}
		}
	}

	//sets timer display to 0 if speed power up eefect is inactive
	if(speed_powerList.empty()){
		powerUpDurationDisplay_List.at("speedPWDur") -> setNumber(0);
	}


	//******************POWER UP DURATION DISPLAYS*****************************************************
	//shield and speed icons
	if(powerUpDurationDisplay_List.at("shieldPWDur") -> getAlive()){
		powerUpDurationDisplay_List.at("shieldPWDur") -> draw(scrn);
	}

	if(powerUpDurationDisplay_List.at("speedPWDur") -> getAlive()){
		powerUpDurationDisplay_List.at("speedPWDur") -> draw(scrn);
	}


	//*************************ENEMY LIST**************************************************************
	for(int i=0; i<enemyList.size(); i++){
		if(enemyList.at(i) -> getAlive()){
			enemyList.at(i) -> draw(scrn);
		}

		if(enemyList.at(i) -> getAlive() && enemyList.at(i) -> getActive() && allG_Active == true){
			enemyList.at(i) -> update(evt);
		}
	}

	//************************ENEMY BULLET LIST********************************************************
	for(int i=0; i<enemyBullet_List.size(); i++){
		if(enemyBullet_List.at(i) -> getAlive()){
			enemyBullet_List.at(i) -> draw(scrn);
		}

		if(enemyBullet_List.at(i) -> getAlive() && enemyBullet_List.at(i) -> getActive() && allG_Active == true){
			enemyBullet_List.at(i) -> update(evt);
		}
	}


	//****************************************POWER UP DURATION DISPLAYS***********************************

	//shield duration text display
	if(textDisplay_List.at("shieldDuration") -> getAlive()){
		textDisplay_List.at("shieldDuration") -> draw(scrn);
	}

	if(textDisplay_List.at("shieldDuration") -> getAlive() && textDisplay_List.at("shieldDuration") -> getActive() && allG_Active == true){
		textDisplay_List.at("shieldDuration") -> update(evt);
	}

	//----------------------------------------------------------------------------------------------------

	//speed duration text display
	if(textDisplay_List.at("speedDuration") -> getAlive()){
		textDisplay_List.at("speedDuration") -> draw(scrn);
	}

	if(textDisplay_List.at("speedDuration") -> getAlive() && textDisplay_List.at("speedDuration") -> getActive() && allG_Active == true){
		textDisplay_List.at("speedDuration") -> update(evt);
	}


	//**************************GAME PUASE MENU*******************************************************
	if(allG_Active == false){
		for(int i=0; i<pauseMenu_List.size(); i++){
			if(pauseMenu_List.at(i) -> getAlive() && pauseMenu_List.at(i) -> getActive()){
				pauseMenu_List.at(i) -> draw(scrn);
			}
		}
	}
	//***************************************************************************************************

	_gameCollision();	//calls the collision function
}


//changes the active state of all game objects
void gameManager::switchActive(){
	if(useDelay + uDelayTimeElapse < SDL_GetTicks()){
		if(allG_Active){
			allG_Active = false;
			std::cout<<"game paused";
			inGameBackground_Music.pause();
		}

		else{
			allG_Active = true;
			std::cout<<"game resumed";
			inGameBackground_Music.resume();
		}
		uDelayTimeElapse = SDL_GetTicks();
	}
}


//this function will contain all collision statements for all object in the game state
void gameManager::_gameCollision(){
	//the player to enemy collision can be found in the for loop for enemy list

	//****************************PLAYER BULLET LIST**************************************************
	for(int i=0; i<playerBullet_List.size(); i++){
		//************check if any of the bullets hit any enemies*************
		for(int b=0; b<enemyList.size(); b++){
			bulletToEnemy_collCheck = collisionChecker(playerBullet_List.at(i), enemyList.at(b));

			if(bulletToEnemy_collCheck){
				//set active and alive for both objects to false here
				//player bullet
				playerBullet_List.at(i) -> setActive(false);
				playerBullet_List.at(i) -> setAlive(false);

				//enemy
				enemyList.at(b) -> setState(30);

				playerScore += 1;	//add 1 point to player score

				//***********shield power up*************
				if(shieldPowerUp_streak < 4){
					shieldPowerUp_streak += 1;
				}

				else{
					//put power up spawn here
					shPowerUp = new shieldPowerUp(enemyList.at(b)->getX(), enemyList.at(b)->getY());
					shieldPowerUp_streak = 0;
				}

				//***********speed power up***************
				if(speedPowerUp_streak < 6){
					speedPowerUp_streak += 1;
				}

				else{
					spdPowerUp = new speedPowerUp(enemyList.at(b)->getX()+30, enemyList.at(b)->getY()+30);
					speedPowerUp_streak = 0;
				}
			}
		}

		//************check if any of the bullets hit any enemiy bullets*************
		for(int b=0; b<enemyBullet_List.size(); b++){
			playerBulletToEnemyBullet_collCheck = collisionChecker(playerBullet_List.at(i), enemyBullet_List.at(b));

			if(playerBulletToEnemyBullet_collCheck){
				//player bullet
				playerBullet_List.at(i) -> setActive(false);
				playerBullet_List.at(i) -> setAlive(false);

				//enemy bullet
				enemyBullet_List.at(b) -> setActive(false);
				enemyBullet_List.at(b) -> setAlive(false);
			}
		}
	}


	//**************************POWER UP LIST**********************************************************
	/*the power up collision list is in the power up list in game state function
	due to the fact putting it here causes it to be buggy*/

	//****************************POWER UP EFFECT******************************
	//sheild
	for(int i=0; i<shield_powerList.size(); i++){
		//to player check
		for(int b=0; b<playerList.size(); b++){
			//updates the position of the power (shield) to the players position
			shield_powerList.at(i)->setX(playerList.at(b)->getX() - 17);
			shield_powerList.at(i)->setY(playerList.at(b)->getY() - 16);
		}

		//to enemies check
		for(int c=0; c<enemyList.size(); c++){
			shieldToEnemy_collCheck = collisionChecker(enemyList.at(c), shield_powerList.at(i));

			if(shieldToEnemy_collCheck){
				//enemy
				enemyList.at(c) -> setState(30);
				shieldToEnemy_collCheck = false;
				
			}
		}

		//to enemy bullets check
		for(int d=0; d<enemyBullet_List.size(); d++){
			shieldToEnemyBullet_collCheck = collisionChecker(enemyBullet_List.at(d), shield_powerList.at(i));

			if(shieldToEnemyBullet_collCheck){
				//enemy
				enemyBullet_List.at(d) -> setActive(false);
				enemyBullet_List.at(d) -> setAlive(false);
				shieldToEnemyBullet_collCheck = false;
			}
		}
	}

	//speed
	for(int i=0; i<speed_powerList.size(); i++){
		//to player check
		for(int b=0; b<playerList.size(); b++){
			//updates the position of the power (shield) to the players position
			speed_powerList.at(i)->setX(playerList.at(b)->getX() + 42.5);
			speed_powerList.at(i)->setY(playerList.at(b)->getY() + 75);
		}
	}


	//****************************ENEMY************************
	for(int i=0; i<enemyList.size(); i++){
		if(shield_powerList.empty()){  //checks to see first if the player has a shield on, if so then all player to enemy collision will be ignored
			for(int b=0; b<playerList.size(); b++){
				playerToEnemy_collCheck = collisionChecker(playerList.at(b), enemyList.at(i));

				if(playerToEnemy_collCheck){
					//enemy
					enemyList.at(i) -> setState(30);

					//player
					if(playerLives >= 1){
						playerLives -= 1;

						//reset player position
						playerList.at(b) -> setX(480);
						playerList.at(b) -> setY(880);

						//resets kill streaks
						shieldPowerUp_streak = 0;
						speedPowerUp_streak = 0;

						playerToEnemy_collCheck = false;
					}
				}
			}
		}
	}

	//***************************ENEMY BULLET************************
	for(int i=0; i<enemyBullet_List.size(); i++){
		//**************check if any of the bullets hit the player*************
		for(int b=0; b<playerList.size(); b++){
			bulletToPlayer_collCheck = collisionChecker(enemyBullet_List.at(i), playerList.at(b));

			if(bulletToPlayer_collCheck){
				//enemy bullet
				enemyBullet_List.at(i) -> setActive(false);
				enemyBullet_List.at(i) -> setAlive(false);

				//player
				if(playerLives >= 1){
					playerLives -= 1;

					//reset player position
					playerList.at(b) -> setX(480);
					playerList.at(b) -> setY(880);

					//resets kill streaks
					shieldPowerUp_streak = 0;
					speedPowerUp_streak = 0;

					bulletToPlayer_collCheck = false;
				}
			}
		}
	}
}


//the game state switcher
void gameManager::gameStateSwitcher(SDL_Surface* scrn, SDL_Event evt){

#if defined DEBUG
	std::cout<<"\n" <<gameState;
#endif

	switch (gameState)
	{
	case SPLASHS:
		_splash(scrn, evt);
		break;

	case TITLES:
		_title(scrn, evt);
		break;

	case HELPS:
		_help(scrn, evt);
		break;

	case GAMES:
		_game(scrn, evt);
		break;

	case SCORES:
		_score(scrn, evt);
		break;

	default:
		break;
	}
}


//---------------collision checker------------------------
bool gameManager::collisionChecker(gameObject* tempGameObj_1, gameObject* tempGameObj_2){
	/*if tempGameObj_1 collides with tempGameObj_2
	**then set active and alive for both tempGameObj_1 and tempGameObj_2 to false*/

	if((tempGameObj_1 -> getX() + tempGameObj_1 -> getW() > tempGameObj_2 -> getX() &&
		tempGameObj_1 -> getX() + tempGameObj_1 -> getW() < tempGameObj_2 -> getX() + tempGameObj_2 -> getW() &&
		tempGameObj_1 -> getY() + tempGameObj_1 -> getH() > tempGameObj_2 -> getY() &&
		tempGameObj_1 -> getY() + tempGameObj_1 -> getH() < tempGameObj_2 -> getY() + tempGameObj_2 -> getH()) ||
		//second check
		(tempGameObj_1-> getX() + tempGameObj_1 -> getW() > tempGameObj_2 -> getX() &&
		tempGameObj_1 -> getX() < tempGameObj_2 -> getX() + tempGameObj_2 -> getW() &&
		tempGameObj_1 -> getY() < tempGameObj_2 -> getY() + tempGameObj_2 -> getH() &&
		tempGameObj_1 -> getY() + tempGameObj_1 -> getH() > tempGameObj_2 -> getY())){
			std::cout<<"\ncollision";
			return true;
	}

	else{
		return false;
	}
}


//************************game object to false setter****************************
void gameManager::set_ALL_ToFalse(gameObject* tempGameObj){
	tempGameObj -> setActive(false);
	tempGameObj -> setAlive(false);
}

//********************destroys the game objects listed in it*********************
void gameManager::destroyGameObjects(){

	//player bullets
	for(int i=0; i<playerBullet_List.size(); i++){
		set_ALL_ToFalse(playerBullet_List.at(i));
	}

	//************power-ups************
	//shield
	for(int i=0; i<shieldPowerUpList.size(); i++){
		set_ALL_ToFalse(shieldPowerUpList.at(i));
	}

	//speed
	for(int i=0; i<speedPowerUpList.size(); i++){
		set_ALL_ToFalse(speedPowerUpList.at(i));
	}

	//*******power-up effects**********
	//shield
	for(int i=0; i<shield_powerList.size(); i++){
		set_ALL_ToFalse(shield_powerList.at(i));
	}
	
	//speed
	for(int i=0; i<speed_powerList.size(); i++){
		set_ALL_ToFalse(speed_powerList.at(i));
	}


	//************enemy stuff**********
	//enemy
	for(int i=0; i<enemyList.size(); i++){
		set_ALL_ToFalse(enemyList.at(i));
	}

	//enemy bullets
	for(int i=0; i<enemyBullet_List.size(); i++){
		set_ALL_ToFalse(enemyBullet_List.at(i));
	}
}


//--------------------------framerate regulator-------------------------
void gameManager::regulateFrameRate(){
	if(SDL_GetTicks()-startTime < 1000/frameRate){
		SDL_Delay(1000/frameRate - (SDL_GetTicks() - startTime));
	}
	startTime = SDL_GetTicks();
}


//**********************************SWEEPER**********************************
void gameManager::sweepLists(){
	//level list
	for(int i=0; i<levelList.size(); i++){
		if(levelList.at(i) -> getAlive() == false){
			delete levelList.at(i);
			levelList.erase(levelList.begin() +i);
		}
	}

	//*******************************player*******************************
	//player
	for(int i=0; i<playerList.size(); i++){
		if(playerList.at(i) -> getAlive() == false){
			delete playerList.at(i);
			playerList.erase(playerList.begin() +i);
		}
	}

	//player bullets
	for(int i=0; i<playerBullet_List.size(); i++){
		if(playerBullet_List.at(i) -> getAlive() == false){
			delete playerBullet_List.at(i);
			playerBullet_List.erase(playerBullet_List.begin() +i);
		}
	}

	//******************************power ups****************************
	//shield
	for(int i=0; i<shieldPowerUpList.size(); i++){
		if(shieldPowerUpList.at(i) -> getAlive() == false){
			delete shieldPowerUpList.at(i);
			shieldPowerUpList.erase(shieldPowerUpList.begin() +i);
		}
	}

	//speed
	for(int i=0; i<speedPowerUpList.size(); i++){
		if(speedPowerUpList.at(i) -> getAlive() == false){
			delete speedPowerUpList.at(i);
			speedPowerUpList.erase(speedPowerUpList.begin() +i);
		}
	}

	//shield power effects
	for(int i=0; i<shield_powerList.size(); i++){
		if(shield_powerList.at(i) -> getAlive() == false){
			delete shield_powerList.at(i);
			shield_powerList.erase(shield_powerList.begin() +i);
		}
	}

	//speed power effects
	for(int i=0; i<speed_powerList.size(); i++){
		if(speed_powerList.at(i) -> getAlive() == false){
			delete speed_powerList.at(i);
			speed_powerList.erase(speed_powerList.begin() +i);
		}
	}

	//****************************enemy********************************
	//enemies
	for(int i=0; i<enemyList.size(); i++){
		if(enemyList.at(i) -> getAlive() == false){
			delete enemyList.at(i);
			enemyList.erase(enemyList.begin() +i);
		}
	}

	//enemy bullet list
	for(int i=0; i<enemyBullet_List.size(); i++){
		if(enemyBullet_List.at(i) -> getAlive() == false){
			delete enemyBullet_List.at(i);
			enemyBullet_List.erase(enemyBullet_List.begin() +i);
		}
	}
}