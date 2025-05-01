/*
 * Gyro_Driver.c
 *
 *  Created on: Mar 20, 2025
 *      Author: Olivia Zhu
 */

#include "GyroDriver.h"

static HAL_StatusTypeDef HALStatus;
static SPI_HandleTypeDef hSPI5 = {0};

void gyroInit() {

	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_SPI5_CLK_ENABLE();

	GPIO_InitTypeDef SPI_SCK;
	SPI_SCK.Pin = SPI5_SCK_PIN;
	SPI_SCK.Mode = GPIO_MODE_AF_PP;
	SPI_SCK.Pull = GPIO_NOPULL;
	SPI_SCK.Speed = GPIO_SPEED_FREQ_LOW;
	SPI_SCK.Alternate = GPIO_AF5_SPI5;
	HAL_GPIO_Init(SPI_PORT, &SPI_SCK);

	GPIO_InitTypeDef SPI_MISO;
	SPI_MISO.Pin = SPI5_MISO_PIN;
	SPI_MISO.Mode = GPIO_MODE_AF_PP;
	SPI_MISO.Pull = GPIO_NOPULL;
	SPI_MISO.Speed = GPIO_SPEED_FREQ_LOW;
	SPI_MISO.Alternate = GPIO_AF5_SPI5;
	HAL_GPIO_Init(SPI_PORT, &SPI_MISO);

	GPIO_InitTypeDef SPI_MOSI;
	SPI_MOSI.Pin = SPI5_MOSI_PIN;
	SPI_MOSI.Mode = GPIO_MODE_AF_PP;
	SPI_MOSI.Pull = GPIO_NOPULL;
	SPI_MOSI.Speed = GPIO_SPEED_FREQ_LOW;
	SPI_MOSI.Alternate = GPIO_AF5_SPI5;
	HAL_GPIO_Init(SPI_PORT, &SPI_MOSI);

	GPIO_InitTypeDef SPI_NSS;
	SPI_NSS.Pin = SPI5_NSS_PIN;
	SPI_NSS.Mode = GPIO_MODE_OUTPUT_PP;
	SPI_NSS.Pull = GPIO_NOPULL;
	SPI_NSS.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SPI_NSS_PORT, &SPI_NSS);
	gyroDisableSlave();

	hSPI5.Instance = SPI5;

	SPI_InitTypeDef SPI5_Init;
	SPI5_Init.Mode = SPI_MODE_MASTER;
	SPI5_Init.Direction = SPI_DIRECTION_2LINES;
	SPI5_Init.DataSize = SPI_DATASIZE_8BIT;
	SPI5_Init.CLKPolarity = SPI_POLARITY_LOW;
	SPI5_Init.CLKPhase = SPI_PHASE_1EDGE;
	SPI5_Init.NSS = SPI_NSS_SOFT;
	SPI5_Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	SPI5_Init.FirstBit = SPI_FIRSTBIT_MSB;
	SPI5_Init.TIMode = SPI_TIMODE_DISABLE;
	SPI5_Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;

	hSPI5.Init = SPI5_Init;

	HALStatus = HAL_SPI_Init(&hSPI5);
	gyroSPIStatus();

	gyroPower();
	gyroConfigure();

	return;

}

void gyroPower() {
	gyroWriteRegisters(&hSPI5, CTRL_REG1, GYRO_POWER);
	return;
}

int16_t gyroGetY() {
	uint8_t lowerY = gyroReadRegisters(&hSPI5, OUT_Y_L);
	uint8_t higherY = gyroReadRegisters(&hSPI5, OUT_Y_H);

	int16_t fullY = (int16_t)((higherY << 8) | lowerY);

	// printf("Y: %d\n", fullY);

	return fullY;
}


void gyroConfigure() {
	gyroWriteRegisters(&hSPI5, CTRL_REG1, CR1_CONFIGURE);
	gyroWriteRegisters(&hSPI5, CTRL_REG4, CR4_CONFIGURE);
	gyroWriteRegisters(&hSPI5, CTRL_REG5, CR5_CONFIGURE);
	return;
}

void gyroWriteRegisters(SPI_HandleTypeDef* hspi, uint8_t address, uint8_t data) {

	uint8_t command = GYRO_WRITE | address;
	uint8_t registerData = gyroReadRegisters(hspi, address);
	registerData |= data;

	gyroEnableSlave();

	while(HAL_GPIO_ReadPin(SPI_NSS_PORT, SPI5_NSS_PIN) != GPIO_PIN_RESET);

	// Send write command and address
	HALStatus = HAL_SPI_Transmit(hspi, &command, ONE_BYTE, HAL_MAX_DELAY);
	gyroSPIStatus();

	// Send data
	HALStatus = HAL_SPI_Transmit(hspi, &registerData, ONE_BYTE, HAL_MAX_DELAY);
	gyroSPIStatus();

	gyroDisableSlave();

	return;
}

uint8_t gyroReadRegisters(SPI_HandleTypeDef* hspi, uint8_t address) {

	uint8_t command = GYRO_READ | address;
	uint8_t receivedData = RECEIVED_DATA_DEFAULT;

	gyroEnableSlave();

	while(HAL_GPIO_ReadPin(SPI_NSS_PORT, SPI5_NSS_PIN) != GPIO_PIN_RESET);

	// Send read command and address
	HALStatus = HAL_SPI_Transmit(hspi, &command, ONE_BYTE, HAL_MAX_DELAY);
	gyroSPIStatus();

	// Read data
	HALStatus = HAL_SPI_Receive(hspi, &receivedData, ONE_BYTE, HAL_MAX_DELAY);
	gyroSPIStatus();

	gyroDisableSlave();

	return receivedData;

}

void gyroSPIStatus() {
	APPLICATION_ASSERT(HALStatus == HAL_OK);
	return;
}

void gyroEnableSlave() {
	HAL_GPIO_WritePin(SPI_NSS_PORT, SPI5_NSS_PIN, GPIO_PIN_RESET);
	return;
}

void gyroDisableSlave() {
	HAL_GPIO_WritePin(SPI_NSS_PORT, SPI5_NSS_PIN, GPIO_PIN_SET);
	return;
}
