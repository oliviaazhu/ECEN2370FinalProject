/*
 * Gameplay.h
 *
 *  Created on: Apr 20, 2025
 *      Author: olivi
 */

#ifndef INC_GAMEPLAY_H_
#define INC_GAMEPLAY_H_

#include "LCD_Driver.h"
#include "RNG_Driver.h"
#include "GyroDriver.h"
#include "GameMode.h"
#include <stdbool.h>

#define DEFAULT_COL 3

#define NUM_ROWS 6
#define ROW_START_PIXEL 80
#define ROW_SPACE (LCD_PIXEL_HEIGHT - ROW_START_PIXEL) / 6
#define TOP_ROW 0
#define BOTTOM_ROW 5
#define FIRST_COL 0
#define	SEVENTH_COL 6

#define NUM_COLS 7
#define COL_START_PIXEL 0
#define COL_SPACE (LCD_PIXEL_WIDTH - COL_START_PIXEL) / 7

#define COIN_SELECTION_LOCATION 60
#define COIN_CENTER(x, offset) ((x * offset) + (offset / 2))
#define COIN_SIZE 10

#define EMPTY_SPACE -1
#define COIN_SELECTION_PHASE -1

#define TIMER_OFFSET 1
#define SECONDS_CONVERSION 1000

#define FOUR_IN_A_ROW 4

#define DELAY_TIME 100
#define DELAY_BETWEEN_TURNS 1000

#define STARTING_COUNT 1


enum PLAYER {
	PLAYER_ONE,
	PLAYER_TWO,
	TIE
};

void initGame();

void clearCoin();

void showCoin(int row);

void placeCoin();

bool dropCoin();

void playGame(enum GAME_MODE gameMode);

void switchPlayers();

bool isWinner();

bool isTie();

bool gameOver();

void onePlayerMode();

void twoPlayerMode();

int getRedScore();

int getYellowScore();

enum PLAYER getWinner();

int getTime();


#endif /* INC_GAMEPLAY_H_ */
