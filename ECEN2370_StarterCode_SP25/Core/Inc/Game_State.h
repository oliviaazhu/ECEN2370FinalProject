/*
 * Gameplay.h
 *
 *  Created on: Apr 20, 2025
 *      Author: olivi
 */

#ifndef INC_GAME_STATE_H_
#define INC_GAME_STATE_H_

#include "LCD_Driver.h"
#include "Gameplay.h"

#define TIMER_OFFSET 1

enum GAME_STAGE {
    STARTING_SCREEN,
	GAME_SCREEN,
	FINAL_SCREEN
};

void gameFlowInit();

void startingScreen();

void gameScreen();

void finalScreen();

void LCD_Start_Screen_Polling(void);

void gameFlow();

void finalScreenPolling();


#endif /* INC_GAME_STATE_H_ */
