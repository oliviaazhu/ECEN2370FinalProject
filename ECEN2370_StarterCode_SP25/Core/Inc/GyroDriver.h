/*
 * Gyro_Driver.h
 *
 *  Created on: Mar 20, 2025
 *      Author: Olivia Zhu
 */

#ifndef INC_GYRO_DRIVER_H_
#define INC_GYRO_DRIVER_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "ErrorHandling.h"

#define WHO_AM_I 0xF
#define CTRL_REG1 0x20
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define OUT_Y_L 0x2a
#define OUT_Y_H 0x2b

#define SPI_PORT GPIOF
#define SPI5_SCK_PIN GPIO_PIN_7
#define SPI5_MISO_PIN GPIO_PIN_8
#define SPI5_MOSI_PIN GPIO_PIN_9

#define SPI_NSS_PORT GPIOC
#define SPI5_NSS_PIN GPIO_PIN_1

#define ONE_BYTE 1

#define GYRO_READ 0x80
#define GYRO_WRITE 0x00

#define GYRO_POWER 0x08

#define CR1_CONFIGURE 0x07
#define CR4_CONFIGURE 0x30
#define CR5_CONFIGURE 0x80

#define RECEIVED_DATA_DEFAULT 0x00

#define THRESHOLD 2000

void gyroInit();

void gyroPower();

int16_t gyroGetY();

void gyroConfigure();

void gyroWriteRegisters(SPI_HandleTypeDef* hspi, uint8_t address, uint8_t data);

uint8_t gyroReadRegisters(SPI_HandleTypeDef* hspi, uint8_t address);

void gyroSPIStatus();

void gyroEnableSlave();

void gyroDisableSlave();


#endif /* INC_GYRO_DRIVER_H_ */
