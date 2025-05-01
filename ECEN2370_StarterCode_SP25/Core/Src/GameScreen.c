/*
 * Gameplay.c
 *
 *  Created on: Apr 20, 2025
 *      Author: olivi
 */

#include "GameScreen.h"

/**
  * @brief  This function displays the starting game screen
  * @retval None
  */
void startingScreen() {
	LCD_Clear(0, LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);

	// Write 'Choose Mode' text
	LCD_WriteString(CHOOSE_MODE_X, CHOOSE_MODE_Y, CHOOSE_MODE);

	LCD_SetTextColor(LCD_COLOR_BLACK);

	// Draw Player Mode Buttons
	LCD_Draw_Rectange_Fill(ONE_PLAYER_X, ONE_PLAYER_Y, BUTTON_WIDTH, BUTTON_HEIGHT, LCD_COLOR_WHITE);
	LCD_WriteString(ONE_PLAYER_TEXT_X, ONE_PLAYER_TEXT_Y, ONE_PLAYER_TEXT);

	LCD_Draw_Rectange_Fill(TWO_PLAYER_X, TWO_PLAYER_Y, BUTTON_WIDTH, BUTTON_HEIGHT, LCD_COLOR_WHITE);
	LCD_WriteString(TWO_PLAYER_TEXT_X, TWO_PLAYER_TEXT_Y, TWO_PLAYER_TEXT);
}

/**
  * @brief  This function displays the Connect Four game screen
  * @retval None
  */
void gameScreen() {
	LCD_Clear(0, LCD_COLOR_WHITE);

	// Draw rows
	for(int i = ROW_START_PIXEL; i < LCD_PIXEL_HEIGHT; i += ROW_SPACE) {
		LCD_Draw_Horizontal_Line(COL_START_PIXEL, i, LCD_PIXEL_WIDTH, LCD_COLOR_BLACK);
	}

	// Draw columns
	for(int i = COL_START_PIXEL; i < LCD_PIXEL_WIDTH; i += COL_SPACE) {
		LCD_Draw_Vertical_Line(i, ROW_START_PIXEL, LCD_PIXEL_HEIGHT - ROW_START_PIXEL, LCD_COLOR_BLACK);
	}

}

/**
  * @brief  This function displays the final game screen
  * @retval None
  */
void finalScreen() {
	LCD_Clear(0, LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);

	LCD_WriteString(GAME_OVER_X, GAME_OVER_Y, GAME_OVER);

	showWinText();

	showScore();

	showTime();

	// Draw Play Again btton
	LCD_Draw_Rectange_Fill(PLAY_AGAIN_X, PLAY_AGAIN_Y, BUTTON_WIDTH, BUTTON_HEIGHT, LCD_COLOR_WHITE);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_WriteString(PLAY_AGAIN_TEXT_X, PLAY_AGAIN_TEXT_Y, PLAY_AGAIN_TEXT);

}

/**
  * @brief  This function displays the running score
  * @retval None
  */
void showScore() {
	char redWinsString[MAX_NUMBER_SIZE];
	int redWins = getRedScore();
	snprintf(redWinsString, sizeof(redWinsString), "%d",redWins);

	LCD_SetTextColor(LCD_COLOR_RED);
	LCD_WriteString(RED_TEXT_X, RED_TEXT_Y, redWinsString);

	char* divider = ":";
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_WriteString(DIVIDER_X, DIVIDER_Y, divider);

	char yellowWinsString[MAX_NUMBER_SIZE];
	int yellowWins = getYellowScore();
	snprintf(yellowWinsString, sizeof(yellowWinsString), "%d", yellowWins);

	LCD_SetTextColor(LCD_COLOR_YELLOW);
	LCD_WriteString(YELLOW_TEXT_X, YELLOW_TEXT_Y, yellowWinsString);
	return;
}

/**
  * @brief  This function displays the amount of time the game took
  * @retval None
  */
void showTime() {
	int time = getTime();
	char seconds[MAX_NUMBER_SIZE];
	char timeToWin[TIME_MAX_SIZE] = "Time: ";
	char timeToWinEnd[SECONDS_MAX_SIZE] = " seconds";
	snprintf(seconds, sizeof(seconds), "%d", time);

	strcat(timeToWin, seconds);
	strcat(timeToWin, timeToWinEnd);

	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_WriteString(TIME_X, TIME_Y, timeToWin);
}

/**
  * @brief  This function displays who won
  * @retval None
  */
void showWinText() {
	// Select win text
	char *winText = "";

	enum PLAYER winner = getWinner();

	if(winner == PLAYER_ONE) {
		winText = RED_WON;
	}
	else if(winner == PLAYER_TWO) {
		winText = YELLOW_WON;
	}
	else {
		winText = TIE_WON;
	}

	LCD_WriteString(WIN_TEXT_X, WIN_TEXT_Y, winText);

	return;
}

/**
  * @brief  This function polls for which game mode is selected
  * @retval None
  */
bool startScreenPolling(STMPE811_TouchData* StaticTouchData) {
	/* If touch pressed */
	if (returnTouchStateAndLocation(StaticTouchData) == STMPE811_State_Pressed) {
		/* Touch valid */

		adjustTouch(StaticTouchData);

		printf("\nX: %03d\nY: %03d\n", StaticTouchData -> x, StaticTouchData -> y);

		if(TM_STMPE811_TouchInRectangle(StaticTouchData, ONE_PLAYER_X, ONE_PLAYER_Y, BUTTON_WIDTH, BUTTON_HEIGHT) > 0) {
			printf("One player mode\n");
			setGameMode(SINGLE_PLAYER_MODE);
			return true;
		}

		if(TM_STMPE811_TouchInRectangle(StaticTouchData, TWO_PLAYER_X, TWO_PLAYER_Y, BUTTON_WIDTH, BUTTON_HEIGHT) > 0) {
			printf("Two player mode\n");
			setGameMode(TWO_PLAYER_MODE);
			return true;
		}
	}

	return false;
}

/**
  * @brief  This function polls for if the user wants to play again
  * @retval None
  */
bool finalScreenPolling(STMPE811_TouchData* StaticTouchData) {
	/* If touch pressed */
	if (returnTouchStateAndLocation(StaticTouchData) == STMPE811_State_Pressed) {
		/* Touch valid */

		adjustTouch(StaticTouchData);

		printf("\nX: %03d\nY: %03d\n", StaticTouchData -> x, StaticTouchData -> y);

		if(TM_STMPE811_TouchInRectangle(StaticTouchData, PLAY_AGAIN_X, PLAY_AGAIN_Y, BUTTON_WIDTH, BUTTON_HEIGHT) > 0) {
			printf("Play Again \n");
			return true;
		}

	}

	return false;
}

/**
  * @brief  This function adjusts the TouchData so touch functionality works correctly
  * @retval None
  */
void adjustTouch(STMPE811_TouchData* StaticTouchData) {
	StaticTouchData -> y = LCD_PIXEL_HEIGHT - StaticTouchData -> y;
	return;
}

