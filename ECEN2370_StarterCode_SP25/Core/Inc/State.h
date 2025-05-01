/*
 * State.h
 *
 *  Created on: Apr 30, 2025
 *      Author: olivi
 */

#ifndef INC_STATE_H_
#define INC_STATE_H_

enum GAME_STAGE {
    STARTING_SCREEN,
	STARTING_SCREEN_POLLING,
	GAME_SCREEN,
	PLAY_GAME,
	FINAL_SCREEN,
	FINAL_SCREEN_POLLING
};


enum GAME_STAGE getStage();

void setStage(enum GAME_STAGE gameStage);

#endif /* INC_STATE_H_ */
