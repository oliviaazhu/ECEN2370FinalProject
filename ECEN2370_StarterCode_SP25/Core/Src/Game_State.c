/*
 * Gameplay.c
 *
 *  Created on: Apr 20, 2025
 *      Author: olivi
 */

#include <Game_State.h>

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
			gameLength = ((end_time - start_time) / 1000) + TIMER_OFFSET;
			printf("%d\n", gameLength);
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

	LCD_WriteString(0, 20, text);

	LCD_SetTextColor(LCD_COLOR_BLACK);

	LCD_Draw_Rectange_Fill(15, 60, 215, 40, LCD_COLOR_WHITE);
	LCD_WriteString(20, 70, onePlayerModeText);

	LCD_Draw_Rectange_Fill(15, 130, 215, 40, LCD_COLOR_WHITE);
	LCD_WriteString(20, 140, twoPlayerModeText);
}

/**
  * @brief  This function displays the Connect Four game screen
  * @retval None
  */
void gameScreen() {
	LCD_Clear(0, LCD_COLOR_WHITE);

	for(int i = ROW_START_PIXEL; i <= LCD_PIXEL_HEIGHT; i += ROW_SPACE) {
		LCD_Draw_Horizontal_Line(COL_START_PIXEL, i, LCD_PIXEL_WIDTH, LCD_COLOR_BLACK);
	}

	for(int i = COL_START_PIXEL; i <= LCD_PIXEL_WIDTH; i += COL_SPACE) {
		LCD_Draw_Vertical_Line(i, ROW_START_PIXEL, LCD_PIXEL_HEIGHT - ROW_START_PIXEL, LCD_COLOR_BLACK);
	}

}

void finalScreen() {
	LCD_Clear(0, LCD_COLOR_BLACK);

	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);
	char *text = "GAME OVER";
	LCD_WriteString(65, 70, text);

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

	LCD_WriteString(50, 100, winText);

	char redWinsString[5];
	int redWins = getRedScore();
	snprintf(redWinsString, sizeof(redWinsString), "%d",redWins);

	LCD_SetTextColor(LCD_COLOR_RED);
	LCD_WriteString(95, 130, &redWinsString);

	char* divider = ":";
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_WriteString(120, 130, divider);

	char yellowWinsString[5];
	int yellowWins = getYellowScore();
	snprintf(yellowWinsString, sizeof(yellowWinsString), "%d", yellowWins);

	LCD_SetTextColor(LCD_COLOR_YELLOW);
	LCD_WriteString(145, 130, &yellowWinsString);


	LCD_Draw_Rectange_Fill(15, 160, 215, 40, LCD_COLOR_WHITE);
	char *playAgainText = "Play Again";
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_WriteString(55, 170, playAgainText);

}


void LCD_Start_Screen_Polling(void) {
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			StaticTouchData.y = LCD_PIXEL_HEIGHT - StaticTouchData.y; // Make macro
			if(TM_STMPE811_TouchInRectangle(&StaticTouchData, 15, 60, 215, 40) > 0) {
				printf("One player mode \n");
				state = GAME_SCREEN;
				gameMode = SINGLE_PLAYER_MODE;
				return;
			}

			if(TM_STMPE811_TouchInRectangle(&StaticTouchData, 15, 130, 215, 40) > 0) {
				printf("Two player mode \n");
				state = GAME_SCREEN;
				gameMode = TWO_PLAYER_MODE;
				return;
			}
		} else {
			/* Touch not pressed */
			// printf("Not Pressed\n\n");
		}
	}
}

void finalScreenPolling() {
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			StaticTouchData.y = LCD_PIXEL_HEIGHT - StaticTouchData.y; // Make macro
			if(TM_STMPE811_TouchInRectangle(&StaticTouchData, 15, 160, 215, 40) > 0) {
				printf("Play Again \n");
				state = GAME_SCREEN;
				return;
			}

		} else {
			/* Touch not pressed */
			// printf("Not Pressed\n\n");
		}
	}
}

