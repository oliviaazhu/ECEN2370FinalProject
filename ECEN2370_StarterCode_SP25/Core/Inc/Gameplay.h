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
#include <stdbool.h>

#define NUM_ROWS 6
#define ROW_START_PIXEL 80
#define ROW_SPACE (LCD_PIXEL_HEIGHT - ROW_START_PIXEL) / 6

#define NUM_COLS 7
#define COL_START_PIXEL 0
#define COL_SPACE (LCD_PIXEL_WIDTH - COL_START_PIXEL) / 7

#define COIN_SELECTION_LOCATION 60
#define COIN_CENTER(x, offset) ((x * offset) + (offset / 2))
#define COIN_SIZE 10

#define EMPTY_SPACE -1
#define COIN_SELECTION_PHASE -1


enum PLAYER {
	PLAYER_ONE,
	PLAYER_TWO,
	TIE
};

enum GAME_MODE {
	SINGLE_PLAYER_MODE,
	TWO_PLAYER_MODE
};

void initGame();

void clearCoin();

void showCoin(int row);

void placeCoin();

bool dropCoin();

enum PLAYER playGame(enum GAME_MODE gameMode);

void switchPlayers();

bool isWinner();

bool isTie();

bool gameOver();

void onePlayerMode();

void twoPlayerMode();

int getRedScore();

int getYellowScore();


#endif /* INC_GAMEPLAY_H_ */
