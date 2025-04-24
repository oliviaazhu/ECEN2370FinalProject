/*
 * Button_Driver.c
 *
 *  Created on: Feb 11, 2025
 *      Author: Olivia Zhu
 */

#include "Button_Driver.h"

void initializeInterruptButton() {
	GPIO_InitTypeDef button;
	button.Pin = BUTTON_PIN_VALUE;
	button.Mode = GPIO_MODE_IT_RISING;
	button.Pull = GPIO_NOPULL;
	button.Speed = GPIO_SPEED_FREQ_LOW;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(BUTTON_PORT, &button);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	return;
}


