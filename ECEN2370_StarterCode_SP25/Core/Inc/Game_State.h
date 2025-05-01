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
#define SECONDS_CONVERSION 1000

#define CHOOSE_MODE_X 0
#define CHOOSE_MODE_Y 20

#define BUTTON_WIDTH 215
#define BUTTON_HEIGHT 40

#define ONE_PLAYER_X 15
#define ONE_PLAYER_Y 60

#define ONE_PLAYER_TEXT_X (ONE_PLAYER_X + 5)
#define ONE_PLAYER_TEXT_Y (ONE_PLAYER_Y + 10)

#define TWO_PLAYER_X 15
#define TWO_PLAYER_Y 130

#define TWO_PLAYER_TEXT_X (TWO_PLAYER_X + 5)
#define TWO_PLAYER_TEXT_Y (TWO_PLAYER_Y + 10)

#define GAME_OVER_X 65
#define GAME_OVER_Y 70

#define WIN_TEXT_X 50
#define WIN_TEXT_Y 100

#define RED_TEXT_X 95
#define RED_TEXT_Y 130

#define DIVIDER_X 120
#define DIVIDER_Y 130

#define YELLOW_TEXT_X 145
#define YELLOW_TEXT_Y 130

#define TIME_X 10
#define TIME_Y 155

#define PLAY_AGAIN_X 15
#define PLAY_AGAIN_Y 180

#define PLAY_AGAIN_TEXT_X (PLAY_AGAIN_X + 5)
#define PLAY_AGAIN_TEXT_Y (PLAY_AGAIN_Y + 10)

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

void showScore();

void showTime();

void showWinText();

#endif /* INC_GAME_STATE_H_ */
