/*
 * RNG_Driver.c
 *
 *  Created on: Apr 24, 2025
 *      Author: olivi
 */

#include "RNG_Driver.h"

static HAL_StatusTypeDef RNG_Status;
static RNG_HandleTypeDef RNG_Handle;

void RNGInit() {
	__HAL_RCC_RNG_CLK_ENABLE();
	RNG_Handle.Instance = RNG;
	RNG_Status = HAL_RNG_Init(&RNG_Handle);
	RNGStatus();

}

void RNGStatus() {
	APPLICATION_ASSERT(RNG_Status == HAL_OK);
	return;
}

uint32_t getRandomNumber() {
	uint32_t randomNum;
	RNG_Status = HAL_RNG_GenerateRandomNumber(&RNG_Handle, &randomNum);
	RNGStatus();
	return randomNum;
}

