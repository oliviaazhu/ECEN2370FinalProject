/*
 * State.c
 *
 *  Created on: Apr 30, 2025
 *      Author: olivi
 */

#ifndef SRC_STATE_C_
#define SRC_STATE_C_

#include "State.h"

static enum GAME_STAGE state;

/**
  * @brief  This function gets the current stage of the application
  * @retval enum GAME_STAGE
  */
enum GAME_STAGE getStage() {
	return state;
}

/**
  * @brief  This function sets the current stage of the application
  * @retval None
  */
void setStage(enum GAME_STAGE gameStage) {
	state = gameStage;
}


#endif /* SRC_STATE_C_ */
