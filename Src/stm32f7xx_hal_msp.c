/**
 ******************************************************************************
 * File Name          : stm32f7xx_hal_msp.c
 * Description        : This file provides code for the MSP Initialization
 *                      and de-Initialization codes.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/**
 * @file stm32f7xx_hal_msp.c
 * @brief  SPI Stub HAL Ssetup
 * @author Bram Vlerick <bram.vlerick@openpixelsystems.org>
 * @version v0.1
 * @date 2020-03-23
 */

#include "main.h"
#include "stm32f7xx_hal_cortex.h"

/**
 * Initializes the Global MSP.
 */
void HAL_MspInit(void)
{
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_RCC_SYSCFG_CLK_ENABLE();
}

/**
 * @brief SPI MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hspi: SPI handle pointer
 * @retval None
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(hspi->Instance==SPI1)
	{
		/* Peripheral clock enable */
		__HAL_RCC_SPI1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();

		/**
		  SPI1 GPIO Configuration
		  PB3     ------> SPI1_SCK
		  PB4     ------> SPI1_MISO
		  PB5     ------> SPI1_MOSI
		  PA4     ------> SPI1_NSS
		  */
		GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/** NSS Pin */
		GPIO_InitStruct.Pin = GPIO_PIN_4;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/** Set NVIC Priority and enable SPI IRQ */
		HAL_NVIC_SetPriority(SPI1_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(SPI1_IRQn);
	}
}

/**
 * @brief SPI MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hspi: SPI handle pointer
 * @retval None
 */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
	if(hspi->Instance==SPI1)
	{
		/* Peripheral clock disable */
		__HAL_RCC_SPI1_CLK_DISABLE();

		/**SPI1 GPIO Configuration
		  PB3     ------> SPI1_SCK
		  PB4     ------> SPI1_MISO
		  PB5     ------> SPI1_MOSI
		  */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
	}
}

/**
 * @brief UART MSP Initialization
 * This function configures the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(huart->Instance==USART3)
	{
		/* Peripheral clock enable */
		__HAL_RCC_USART3_CLK_ENABLE();

		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**USART3 GPIO Configuration
		  PD8     ------> USART3_TX
		  PD9     ------> USART3_RX
		  */
		GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	}
}

/**
 * @brief UART MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
	if(huart->Instance==USART3)
	{
		/* Peripheral clock disable */
		__HAL_RCC_USART3_CLK_DISABLE();

		/**USART3 GPIO Configuration
		  PD8     ------> USART3_TX
		  PD9     ------> USART3_RX
		  */
		HAL_GPIO_DeInit(GPIOD, STLK_RX_Pin|STLK_TX_Pin);
	}
}
