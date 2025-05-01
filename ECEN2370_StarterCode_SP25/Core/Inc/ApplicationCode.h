/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include "GameScreen.h"
#include "stm32f4xx_hal.h"
#include "Button_Driver.h"
#include "State.h"

#include <stdio.h>


#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

void ApplicationInit(void);
void LCD_Visual_Demo(void);

#if (COMPILE_TOUCH_FUNCTIONS == 1)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1)

void initButton();
void initGyro();
void initRNG();

void showStartingScreen();

void showGameScreen();

bool pollStartScreen();

void runGame(enum GAME_MODE mode);

void showFinalScreen();

bool pollFinalScreen();

#endif /* INC_APPLICATIONCODE_H_ */
