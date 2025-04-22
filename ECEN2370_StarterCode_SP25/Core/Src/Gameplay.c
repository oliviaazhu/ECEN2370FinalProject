/*
 * Gameplay.c
 *
 *  Created on: Apr 20, 2025
 *      Author: olivi
 */

#include "Gameplay.h"

static enum PLAYER player = PLAYER_ONE;
static int COIN_COLUMN = 3;
static int GAME_BOARD[NUM_ROWS][NUM_COLS];
static STMPE811_TouchData StaticTouchData;

void initGame() {
	for(int i = 0; i < NUM_ROWS; i++) {
		for(int j = 0; j < NUM_COLS; j++) {
			GAME_BOARD[i][j] = EMPTY_SPACE;
		}
	}

	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	return;
}

void clearCoin() {
	int coin_x = COIN_CENTER(COIN_COLUMN, COL_SPACE);
	LCD_Draw_Circle_Fill(coin_x, COIN_SELECTION_LOCATION, COIN_SIZE, LCD_COLOR_WHITE);
}

void showCoin(int row) {

	int coin_x = COIN_CENTER(COIN_COLUMN, COL_SPACE);
	int coin_y = COIN_CENTER(row, ROW_SPACE) + ROW_START_PIXEL;

	if(row == COIN_SELECTION_PHASE) {
		coin_y = COIN_SELECTION_LOCATION;
	}
	uint16_t coin_color;

	if(player == PLAYER_ONE) {
		coin_color = LCD_COLOR_RED;
	}
	else if(player == PLAYER_TWO) {
		coin_color = LCD_COLOR_YELLOW;
	}

	LCD_Draw_Circle_Fill(coin_x, coin_y, COIN_SIZE, coin_color);
}

void placeCoin() {
//	LCD_Draw_Rectange_Fill(0, 0, 120, 320, LCD_COLOR_BLACK);
//	LCD_Draw_Rectange_Fill(120, 0, 120, 320, LCD_COLOR_BLUE);
	while(1) {
		showCoin(COIN_SELECTION_PHASE);
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			StaticTouchData.y = LCD_PIXEL_HEIGHT - StaticTouchData.y;

			if (TM_STMPE811_TouchInRectangle(&StaticTouchData, 85, 20, 68, 20) > 0) {
				bool dropSuccess = dropCoin();

				if(dropSuccess) {
					COIN_COLUMN = 3;
					return;
				}
			}

			if(TM_STMPE811_TouchInRectangle(&StaticTouchData, 0, 0, 120, 320) > 0) {
				if(COIN_COLUMN > 0) {
					clearCoin();
					COIN_COLUMN--;
				}
			}

			if(TM_STMPE811_TouchInRectangle(&StaticTouchData, 120, 0, 120, 320) > 0) {
				if(COIN_COLUMN < NUM_COLS - 1) {
					clearCoin();
					COIN_COLUMN++;
				}
			}

		}
		else {
			// printf("Not pressed\n");

		}
	}
}

bool dropCoin() {
	if(GAME_BOARD[0][COIN_COLUMN] >= 0) {
		return false;
	}
	else {
		for(int i = NUM_ROWS - 1; i >= 0; i--) {
			if(GAME_BOARD[i][COIN_COLUMN] == EMPTY_SPACE) {
				GAME_BOARD[i][COIN_COLUMN] = player;
				showCoin(i);
				clearCoin();
				return true;
			}
		}

		return true;
	}
}

void playGame(GAME gameMode) {
	initGame();
	while(1) {
		if(gameMode)
		placeCoin();
		switchPlayers();

	}
	return;
}

void switchPlayers() {
	if(player == PLAYER_ONE) {
		player = PLAYER_TWO;
	}
	else {
		player = PLAYER_ONE;
	}

	return;
}

void isWinner() {
	return;
}

bool gameOver() {
	return;
}
