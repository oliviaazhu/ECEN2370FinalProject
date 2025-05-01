/*
 * Gameplay.h
 *
 *  Created on: Apr 20, 2025
 *      Author: olivi
 */

#ifndef INC_GAMESCREEN_H_
#define INC_GAMESCREEN_H_

#include "Gameplay.h"

#define CHOOSE_MODE "Choose your mode"
#define CHOOSE_MODE_X 0
#define CHOOSE_MODE_Y 20

#define BUTTON_WIDTH 215
#define BUTTON_HEIGHT 40

#define ONE_PLAYER_X 15
#define ONE_PLAYER_Y 60

#define ONE_PLAYER_TEXT "One Player Mode"
#define ONE_PLAYER_TEXT_X (ONE_PLAYER_X + 5)
#define ONE_PLAYER_TEXT_Y (ONE_PLAYER_Y + 10)

#define TWO_PLAYER_X 15
#define TWO_PLAYER_Y 130

#define TWO_PLAYER_TEXT "Two Player Mode"
#define TWO_PLAYER_TEXT_X (TWO_PLAYER_X + 5)
#define TWO_PLAYER_TEXT_Y (TWO_PLAYER_Y + 10)

#define GAME_OVER "GAME OVER"
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

#define TIME_MAX_SIZE 25
#define TIME_X 10
#define TIME_Y 155

#define SECONDS_MAX_SIZE 10

#define PLAY_AGAIN_X 15
#define PLAY_AGAIN_Y 180

#define PLAY_AGAIN_TEXT "Play Again"
#define PLAY_AGAIN_TEXT_X (PLAY_AGAIN_X + 5)
#define PLAY_AGAIN_TEXT_Y (PLAY_AGAIN_Y + 10)

#define MAX_NUMBER_SIZE 5

#define RED_WON "Red won!"
#define YELLOW_WON "Yellow won!"
#define TIE_WON "Tie!"

void startingScreen();

void gameScreen();

void finalScreen();

bool startScreenPolling(STMPE811_TouchData* StaticTouchData);

bool finalScreenPolling(STMPE811_TouchData* StaticTouchData);

void showScore();

void showTime();

void showWinText();

void adjustTouch(STMPE811_TouchData* StaticTouchData);

#endif /* INC_GAMESCREEN_H_ */
