/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"

/* Static variables */


extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif // COMPILE_TOUCH_FUNCTIONS

/**
  * @brief  This function initializes all parts required for the application
  * @retval None
  */
void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);

    // Set starting stage
    setStage(STARTING_SCREEN);

    // Init peripherals
    initButton();
    initGyro();
    initRNG();

    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#endif // COMPILE_TOUCH_FUNCTIONS


}

/**
  * @brief  This function plays a demo of the screen
  * @retval None
  */
void LCD_Visual_Demo(void)
{
	visualDemo();
}

#if COMPILE_TOUCH_FUNCTIONS == 1
/**
  * @brief  This function runs a demo of how the touch functionality works
  * @retval None
  */
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_GREEN);
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_RED);
		} else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_Clear(0, LCD_COLOR_GREEN);
		}
	}
}
#endif // COMPILE_TOUCH_FUNCTIONS

/**
  * @brief  This function initializes the button
  * @retval None
  */
void initButton() {
	initializeInterruptButton();
}

/**
  * @brief  This function initializes the gyro
  * @retval None
  */
void initGyro() {
	gyroInit();
}

/**
  * @brief  This function initializes the RNG peripheral
  * @retval None
  */
void initRNG() {
	RNGInit();
}

/**
  * @brief  This function shows the starting screen
  * @retval None
  */
void showStartingScreen() {
	startingScreen();
	return;
}

/**
  * @brief  This function shows the game screen
  * @retval None
  */
void showGameScreen() {
	gameScreen();
	return;
}

/**
  * @brief  This function polls for touch on the start screen
  * @retval bool
  */
bool pollStartScreen() {
	return startScreenPolling(&StaticTouchData);
}

/**
  * @brief  This function starts the actual game
  * @retval None
  */
void runGame(enum GAME_MODE mode) {
	playGame(mode);
}

/**
  * @brief  This function shows the final screen
  * @retval None
  */
void showFinalScreen() {
	finalScreen();
}

/**
  * @brief  This function polls for touch on the final screen
  * @retval bool
  */
bool pollFinalScreen() {
	return finalScreenPolling(&StaticTouchData);
}



