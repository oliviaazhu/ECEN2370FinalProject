/*
 * Gameplay.c
 *
 *  Created on: Apr 20, 2025
 *      Author: olivi
 */

#include "Game_State.h"

static STMPE811_TouchData StaticTouchData;
static enum GAME_STAGE state = STARTING_SCREEN;
static enum GAME_MODE gameMode;
static enum PLAYER winner;
static int gameLength = 0;


void gameFlowInit() {
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;
	return;
}

void gameFlow() {
	switch(state) {
		case STARTING_SCREEN:
			startingScreen();
			LCD_Start_Screen_Polling();
			break;
		case GAME_SCREEN:
			uint32_t start_time = HAL_GetTick();
			gameScreen();
			winner = playGame(gameMode);
			uint32_t end_time = HAL_GetTick();
			gameLength = ((end_time - start_time) / SECONDS_CONVERSION) + TIMER_OFFSET;
			state = FINAL_SCREEN;
			break;
		case FINAL_SCREEN:
			finalScreen();
			finalScreenPolling();
			break;
		default:
			break;
	}

	return;
}



/**
  * @brief  This function displays the starting game screen
  * @retval None
  */
void startingScreen() {
	LCD_Clear(0, LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);

	char *text = "Choose your mode";
	char *onePlayerModeText = "One Player Mode";
	char *twoPlayerModeText = "Two Player Mode";

	// Write 'Choose Mode' text
	LCD_WriteString(CHOOSE_MODE_X, CHOOSE_MODE_Y, text);

	LCD_SetTextColor(LCD_COLOR_BLACK);

	// Draw Player Mode Buttons
	LCD_Draw_Rectange_Fill(ONE_PLAYER_X, ONE_PLAYER_Y, BUTTON_WIDTH, BUTTON_HEIGHT, LCD_COLOR_WHITE);
	LCD_WriteString(ONE_PLAYER_TEXT_X, ONE_PLAYER_TEXT_Y, onePlayerModeText);

	LCD_Draw_Rectange_Fill(TWO_PLAYER_X, TWO_PLAYER_Y, BUTTON_WIDTH, BUTTON_HEIGHT, LCD_COLOR_WHITE);
	LCD_WriteString(TWO_PLAYER_TEXT_X, TWO_PLAYER_TEXT_Y, twoPlayerModeText);
}

/**
  * @brief  This function displays the Connect Four game screen
  * @retval None
  */
void gameScreen() {
	LCD_Clear(0, LCD_COLOR_WHITE);

	// Draw rows
	for(int i = ROW_START_PIXEL; i <= LCD_PIXEL_HEIGHT; i += ROW_SPACE) {
		LCD_Draw_Horizontal_Line(COL_START_PIXEL, i, LCD_PIXEL_WIDTH, LCD_COLOR_BLACK);
	}

	// Draw columns
	for(int i = COL_START_PIXEL; i <= LCD_PIXEL_WIDTH; i += COL_SPACE) {
		LCD_Draw_Vertical_Line(i, ROW_START_PIXEL, LCD_PIXEL_HEIGHT - ROW_START_PIXEL, LCD_COLOR_BLACK);
	}

}

void finalScreen() {
	LCD_Clear(0, LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);

	char *text = "GAME OVER";
	LCD_WriteString(GAME_OVER_X, GAME_OVER_Y, text);

	showWinText();

	showScore();

	showTime();

	// Draw Play Again btton
	LCD_Draw_Rectange_Fill(PLAY_AGAIN_X, PLAY_AGAIN_Y, BUTTON_WIDTH, BUTTON_HEIGHT, LCD_COLOR_WHITE);
	char *playAgainText = "Play Again";
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_WriteString(PLAY_AGAIN_TEXT_X, PLAY_AGAIN_TEXT_Y, playAgainText);

}

void showScore() {
	char redWinsString[5];
	int redWins = getRedScore();
	snprintf(redWinsString, sizeof(redWinsString), "%d",redWins);

	LCD_SetTextColor(LCD_COLOR_RED);
	LCD_WriteString(RED_TEXT_X, RED_TEXT_Y, &redWinsString);

	char* divider = ":";
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_WriteString(DIVIDER_X, DIVIDER_Y, divider);

	char yellowWinsString[5];
	int yellowWins = getYellowScore();
	snprintf(yellowWinsString, sizeof(yellowWinsString), "%d", yellowWins);

	LCD_SetTextColor(LCD_COLOR_YELLOW);
	LCD_WriteString(YELLOW_TEXT_X, YELLOW_TEXT_Y, &yellowWinsString);
	return;
}

void showTime() {
	char seconds[5]; // magic numbers??
	char timeToWin[25] = "Time: ";
	char timeToWinEnd[10] = " seconds";
	snprintf(seconds, sizeof(seconds), "%d", gameLength);

	strcat(timeToWin, seconds);
	strcat(timeToWin, timeToWinEnd);

	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_WriteString(TIME_X, TIME_Y, &timeToWin);
}

void showWinText() {
	// Select win text
	char *winText = "";

	if(winner == PLAYER_ONE) {
		winText = "Red won!";
	}
	else if(winner == PLAYER_TWO) {
		winText = "Yellow won!";
	}
	else {
		winText = "Tie!";
	}

	LCD_WriteString(WIN_TEXT_X, WIN_TEXT_Y, winText);

	return;
}


void LCD_Start_Screen_Polling(void) {
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			StaticTouchData.y = LCD_PIXEL_HEIGHT - StaticTouchData.y; // Make macro
			if(TM_STMPE811_TouchInRectangle(&StaticTouchData, ONE_PLAYER_X, ONE_PLAYER_Y, BUTTON_WIDTH, BUTTON_HEIGHT) > 0) {
				printf("One player mode \n");
				state = GAME_SCREEN;
				gameMode = SINGLE_PLAYER_MODE;
				return;
			}

			if(TM_STMPE811_TouchInRectangle(&StaticTouchData, TWO_PLAYER_X, TWO_PLAYER_Y, BUTTON_WIDTH, BUTTON_HEIGHT) > 0) {
				printf("Two player mode \n");
				state = GAME_SCREEN;
				gameMode = TWO_PLAYER_MODE;
				return;
			}
		}
	}
}

void finalScreenPolling() {
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			StaticTouchData.y = LCD_PIXEL_HEIGHT - StaticTouchData.y; // Make macro
			if(TM_STMPE811_TouchInRectangle(&StaticTouchData, PLAY_AGAIN_X, PLAY_AGAIN_Y, BUTTON_WIDTH, BUTTON_HEIGHT) > 0) {
				printf("Play Again \n");
				state = GAME_SCREEN;
				return;
			}

		}
	}
}

