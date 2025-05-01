/*
 * ErrorHandling.c
 *
 *  Created on: Mar 20, 2025
 *      Author: Olivia Zhu
 */
#include "ErrorHandling.h"

/**
  * @brief  This function suspends the application if a condition is not met
  * @retval None
  */
void APPLICATION_ASSERT(bool value) {
	if(value == false) {
		while(true) {

		}
	}

	return;
}
