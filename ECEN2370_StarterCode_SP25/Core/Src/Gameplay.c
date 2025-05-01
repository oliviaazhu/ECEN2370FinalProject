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
static int WIN_COUNTER[2];
static enum PLAYER winner;
static int gameTime;

/**
  * @brief  This function initializes the game
  * @retval None
  */
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

/**
  * @brief  This function clears the coin from the display
  * @retval None
  */
void clearCoin() {
	int coin_x = COIN_CENTER(COIN_COLUMN, COL_SPACE);
	LCD_Draw_Circle_Fill(coin_x, COIN_SELECTION_LOCATION, COIN_SIZE, LCD_COLOR_WHITE);
}

/**
  * @brief  This function displays the coin
  * @retval None
  */
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

/**
  * @brief  This function allows a user to place a coin
  * @retval None
  */
void placeCoin() {

	while(!DROP_COIN) {
		showCoin(COIN_SELECTION_PHASE);
		int yValue = gyroGetY();
			if(yValue < -THRESHOLD){
				if(COIN_COLUMN > FIRST_COL) {
					clearCoin();
					COIN_COLUMN--;
					HAL_Delay(DELAY_TIME);
				}
			}
			else if(yValue > THRESHOLD){
				if(COIN_COLUMN < SEVENTH_COL) {
					clearCoin();
					COIN_COLUMN++;
					HAL_Delay(DELAY_TIME);
				}
			}

			HAL_Delay(DELAY_TIME);

	}

	clearCoin();

	return;
}

/**
  * @brief  This function drops the coin in the respective column
  * @retval bool
  */
bool dropCoin() {
	if(GAME_BOARD[TOP_ROW][COIN_COLUMN] != EMPTY_SPACE) {
		return false;
	}
	else {
		for(int i = BOTTOM_ROW; i >= TOP_ROW; i--) {
			if(GAME_BOARD[i][COIN_COLUMN] == EMPTY_SPACE) {
				GAME_BOARD[i][COIN_COLUMN] = player;
				showCoin(i);
				return true;
			}
		}

		return false;
	}
}

/**
  * @brief  This function starts the game
  * @retval None
  */
void playGame(enum GAME_MODE gameMode) {
	initGame();
	if(gameMode == SINGLE_PLAYER_MODE) {
		onePlayerMode();
	}
	else if(gameMode == TWO_PLAYER_MODE) {
		twoPlayerMode();
	}

	if(isTie()) {
		winner = TIE;
		return;
	}

	winner = player;

	return;
}

/**
  * @brief  This function plays the game in single player mode
  * @retval None
  */
void onePlayerMode() {

	uint32_t start_time = HAL_GetTick();
	while(!gameOver()) {
		switchPlayers();
		COIN_COLUMN = DEFAULT_COL;
		if(player == PLAYER_TWO) {
			uint32_t randNum = getRandomNumber();
			COIN_COLUMN = randNum % NUM_COLS;
			while(!dropCoin()) {
				randNum = getRandomNumber();
				COIN_COLUMN = randNum % NUM_COLS;
			}
			HAL_Delay(DELAY_BETWEEN_TURNS);
		}
		else {
			DROP_COIN = false;
			placeCoin();
		}
	}
	uint32_t end_time = HAL_GetTick();
	gameTime = ((end_time - start_time) / SECONDS_CONVERSION);

	return;

}

/**
  * @brief  This function plays the game in two player mode
  * @retval None
  */
void twoPlayerMode() {

	uint32_t start_time = HAL_GetTick();
	while(!gameOver()) {
		switchPlayers();
		COIN_COLUMN = DEFAULT_COL;
		DROP_COIN = false;
		placeCoin();
	}
	uint32_t end_time = HAL_GetTick();
	gameTime = ((end_time - start_time) / SECONDS_CONVERSION);

	return;
}

/**
  * @brief  This function switches the current player
  * @retval None
  */
void switchPlayers() {
	if(player == PLAYER_ONE) {
		player = PLAYER_TWO;
	}
	else {
		player = PLAYER_ONE;
	}

	return;
}

/**
  * @brief  This function determines if the current player won the game
  * @retval bool
  */
bool isWinner() {

	int col = COIN_COLUMN;
	int row = EMPTY_SPACE;

	// Find row where coin was dropped
	for(int i = 0; i < NUM_ROWS; i++) {
		if(GAME_BOARD[i][col] == player) {
			row = i;
			break;
		}
	}

	if(row != EMPTY_SPACE) {
		// Check row
		int row_count = STARTING_COUNT;
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

		if(row_count >= FOUR_IN_A_ROW) {
			WIN_COUNTER[player]++;
			return true;
		}

		// Check col
		int col_count = STARTING_COUNT;
		int row_var = row - 1;

		// Check below cell
		row_var = row + 1;

		while(row_var < NUM_ROWS && GAME_BOARD[row_var][col] == player) {
			col_count++;
			row_var++;
		}

		if(col_count >= FOUR_IN_A_ROW) {
			WIN_COUNTER[player]++;
			return true;
		}

		// Check diagonal #1
		int diagonal1_count = STARTING_COUNT;
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

		if(diagonal1_count >= FOUR_IN_A_ROW) {
			WIN_COUNTER[player]++;
			return true;
		}

		// Check diagonal #2
		int diagonal2_count = STARTING_COUNT;
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

		if(diagonal2_count >= FOUR_IN_A_ROW) {
			WIN_COUNTER[player]++;
			return true;
		}

	}

	return false;
}

/**
  * @brief  This function determines if the game was a tie
  * @retval bool
  */
bool isTie() {
	for(int i = TOP_ROW; i < NUM_COLS; i++) {
		if(GAME_BOARD[TOP_ROW][i] == EMPTY_SPACE) {
			return false;
		}
	}

	WIN_COUNTER[TIE]++;
	return true;
}

/**
  * @brief  This function determines if the game is over
  * @retval bool
  */
bool gameOver() {
	return isTie() || isWinner();
}

/**
  * @brief  This function returns the running red score
  * @retval int
  */
int getRedScore() {
	return WIN_COUNTER[PLAYER_ONE];
}

/**
  * @brief  This function returns the running yellow score
  * @retval int
  */
int getYellowScore() {
	return WIN_COUNTER[PLAYER_TWO];
}

/**
  * @brief  This function returns the winner
  * @retval enum PLAYER
  */
enum PLAYER getWinner() {
	return winner;
}

/**
  * @brief  This function returns how long the last game took
  * @retval int
  */
int getTime() {
	return gameTime;
}

void EXTI0_IRQHandler(void) {
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	if(!gameOver()) {
		DROP_COIN = dropCoin();
	}
	__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
