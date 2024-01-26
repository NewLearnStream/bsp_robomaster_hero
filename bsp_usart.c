/**
*********************************************************************************************************
* Copyright (C) 2023-2026 by xiongqulin - All Rights Reserved.                                              *
*                                                                                                       *
* This file is part of the project.                                                                     *
*                                                                                                       *
* This file can not be copied and/or distributed without the express permission of the project owner.   *
*********************************************************************************************************/

/**
*********************************************************************************************************
* @file   : bsp_usart.h
* @author : xiongqulin
* @date   : 18 Jan 2024
* @brief  :
*
*********************************************************************************************************
*/

#include "bsp_usart.h"

UART_HandleTypeDef huart1;
static DMA_HandleTypeDef hdma_usart1_rx;

void bsp_usart_init()
{
    huart1.Instance          = USART1;
    huart1.Init.BaudRate     = 100000;
    huart1.Init.WordLength   = UART_WORDLENGTH_8B;
    huart1.Init.StopBits     = UART_STOPBITS_1;
    huart1.Init.Parity       = UART_PARITY_NONE;
    huart1.Init.Mode         = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle)
{
    if (uartHandle->Instance == USART1)
    {
        __HAL_RCC_DMA2_CLK_ENABLE();

        __HAL_RCC_USART1_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();

        GPIO_InitTypeDef gpio_init = {
            .Pin       = GPIO_PIN_6 | GPIO_PIN_7,
            .Mode      = GPIO_MODE_AF_PP,
            .Pull      = GPIO_NOPULL,
            .Speed     = GPIO_SPEED_FREQ_VERY_HIGH,
            .Alternate = GPIO_AF7_USART1,
        };

        HAL_GPIO_Init(GPIOB, &gpio_init);

        hdma_usart1_rx.Instance                 = DMA2_Stream2;
        hdma_usart1_rx.Init.Channel             = DMA_CHANNEL_4;
        hdma_usart1_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
        hdma_usart1_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
        hdma_usart1_rx.Init.MemInc              = DMA_MINC_ENABLE;
        hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_usart1_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
        hdma_usart1_rx.Init.Mode                = DMA_CIRCULAR;
        hdma_usart1_rx.Init.Priority            = DMA_PRIORITY_HIGH;
        hdma_usart1_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
        HAL_DMA_Init(&hdma_usart1_rx);

        __HAL_LINKDMA(uartHandle, hdmarx, hdma_usart1_rx);
    }
}

void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart1);
}

void DMA2_Stream2_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_usart1_rx);
}