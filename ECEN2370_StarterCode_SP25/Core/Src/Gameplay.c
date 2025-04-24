/*
 * Gameplay.c
 *
 *  Created on: Apr 20, 2025
 *      Author: olivi
 */

#include "Gameplay.h"

static enum PLAYER player = PLAYER_TWO;
static int COIN_COLUMN = 3;
static int GAME_BOARD[NUM_ROWS][NUM_COLS];
static STMPE811_TouchData StaticTouchData;
static bool DROP_COIN = false;

void initGame() {
	for(int i = 0; i < NUM_ROWS; i++) {
		for(int j = 0; j < NUM_COLS; j++) {
			GAME_BOARD[i][j] = EMPTY_SPACE;
		}
	}

	player = PLAYER_TWO;

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
	while(!DROP_COIN) {
		showCoin(COIN_SELECTION_PHASE);
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			StaticTouchData.y = LCD_PIXEL_HEIGHT - StaticTouchData.y;

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

		return false;
	}
}

void playGame() {
	initGame();
	while(!gameOver()) {
		switchPlayers();
		DROP_COIN = false;
		placeCoin();
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

bool isWinner() {

	int col = COIN_COLUMN;
	int row = -1;

	// Find row where coin was dropped
	for(int i = 0; i < NUM_ROWS; i++) {
		if(GAME_BOARD[i][col] == player) {
			row = i;
			break;
		}
	}

	if(row != -1) {
		// Check row
		int row_count = 1;
		int col_var = col - 1;

		// Check left of cell
		while(col_var >= 0 && GAME_BOARD[row][col_var] == player) {
			row_count++;
			col_var--;
		}

		// Check right of cell
		col_var = col + 1;
		while(col_var < NUM_COLS && GAME_BOARD[row][col_var] == player) {
			row_count++;
			col_var++;
		}

		if(row_count >= 4) {
			return true;
		}

		// Check col
		int col_count = 1;
		int row_var = row - 1;

		// Check above cell
		while(row_var >= 0 && GAME_BOARD[row_var][col] == player) {
			col_count++;
			row_var--;
		}

		// Check below cell
		row_var = row + 1;
		while(row_var < NUM_ROWS && GAME_BOARD[row_var][col] == player) {
			col_count++;
			row_var++;
		}

		if(col_count >= 4) {
			return true;
		}

		// Check diagonal #1
		int diagonal1_count = 1;
		row_var = row - 1;
		col_var = col - 1;

		// Check diagonal that starts from bottom left and goes to top right
		while(row_var >= 0 && col_var >= 0 && GAME_BOARD[row_var][col_var] == player) {
			diagonal1_count++;
			row_var--;
			col_var--;
		}

		row_var = row + 1;
		col_var = col + 1;
		while(row_var < NUM_ROWS && col_var < NUM_COLS && GAME_BOARD[row_var][col_var] == player) {
			diagonal1_count++;
			row_var++;
			col_var++;
		}

		if(diagonal1_count >= 4) {
			return true;
		}

		// Check diagonal #2
		int diagonal2_count = 1;
		row_var = row + 1;
		col_var = col - 1;

		// Check diagonal that starts from top left and goes to bottom right
		while(row_var < NUM_ROWS && col_var >= 0 && GAME_BOARD[row_var][col_var] == player) {
			diagonal2_count++;
			row_var++;
			col_var--;
		}

		row_var = row - 1;
		col_var = col + 1;
		while(row_var >= 0 && col_var < NUM_COLS && GAME_BOARD[row_var][col_var] == player) {
			diagonal2_count++;
			row_var--;
			col_var++;
		}

		if(diagonal2_count >= 4) {
			return true;
		}

	}

	return false;
}

bool isTie() {
	for(int i = 0; i < NUM_ROWS; i++) {
		if(GAME_BOARD[i][NUM_COLS - 1] == -1) {
			return false;
		}
	}

	return true;
}

bool gameOver() {
	return isTie() || isWinner();
}

void EXTI0_IRQHandler(void) {
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	DROP_COIN = dropCoin();
	__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
