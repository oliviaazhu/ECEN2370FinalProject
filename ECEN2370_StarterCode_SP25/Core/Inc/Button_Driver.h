/*
 * Button_Driver.h
 *
 *  Created on: Feb 11, 2025
 *      Author: Olivia Zhu
 */

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>

#define BUTTON_PORT GPIOA
#define BUTTON_PIN_VALUE GPIO_PIN_0

void initializeInterruptButton();

#endif /* BUTTON_DRIVER_H_ */
