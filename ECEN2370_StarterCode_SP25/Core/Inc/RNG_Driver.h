/*
 * RNG_Driver.h
 *
 *  Created on: Apr 24, 2025
 *      Author: olivi
 */

#ifndef INC_RNG_DRIVER_H_
#define INC_RNG_DRIVER_H_

#include <stdint.h>
#include "ErrorHandling.h"
#include "stm32f4xx_hal.h"

void RNGInit();

void RNGStatus();

uint32_t getRandomNumber();

#endif /* INC_RNG_DRIVER_H_ */
