/*
 * Gameplay.c
 *
 *  Created on: Apr 20, 2025
 *      Author: olivi
 */

#include <Game_State.h>

static STMPE811_TouchData StaticTouchData;
static enum GAME_STAGE state = STARTING_SCREEN;

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
			gameScreen();
			playGame();
			break;
		case FINAL_SCREEN:
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
				return;
			}

			if(TM_STMPE811_TouchInRectangle(&StaticTouchData, 15, LCD_PIXEL_HEIGHT - 130, 215, 40) > 0) {
				printf("TWo player mode \n");
				state = GAME_SCREEN;
				return;
			}
		} else {
			/* Touch not pressed */
			// printf("Not Pressed\n\n");
		}
	}
}
