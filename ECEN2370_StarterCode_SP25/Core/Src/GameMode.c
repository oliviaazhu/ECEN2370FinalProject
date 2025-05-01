/*
 * GameMode.c
 *
 *  Created on: May 1, 2025
 *      Author: olivi
 */
#include "GameMode.h"

static enum GAME_MODE gameMode;

/**
  * @brief  This function returns the current game mode
  * @retval enum GAME_MODE
  */
enum GAME_MODE getGameMode(){
	return gameMode;
}

/**
  * @brief  This function sets the current game mode
  * @retval None
  */
void setGameMode(enum GAME_MODE mode) {
	gameMode = mode;
	return;
}
