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
* @file   : bsp_can.c
* @author : xiongqulin
* @date   : 25 Dev 2023
* @brief  :
*
*********************************************************************************************************
*/

#include "bsp_can.h"

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

void bsp_can_init()
{
    hcan1.Instance                  = CAN1;
    hcan1.Init.Prescaler            = 5;
    hcan1.Init.Mode                 = CAN_MODE_NORMAL;
    hcan1.Init.SyncJumpWidth        = CAN_SJW_1TQ;
    hcan1.Init.TimeSeg1             = CAN_BS1_3TQ;
    hcan1.Init.TimeSeg2             = CAN_BS2_5TQ;
    hcan1.Init.TimeTriggeredMode    = DISABLE;
    hcan1.Init.AutoBusOff           = ENABLE;
    hcan1.Init.AutoWakeUp           = ENABLE;
    hcan1.Init.AutoRetransmission   = DISABLE;
    hcan1.Init.ReceiveFifoLocked    = DISABLE;
    hcan1.Init.TransmitFifoPriority = DISABLE;
    HAL_CAN_Init(&hcan1);

    hcan2.Instance                  = CAN2;
    hcan2.Init.Prescaler            = 5;
    hcan2.Init.Mode                 = CAN_MODE_NORMAL;
    hcan2.Init.SyncJumpWidth        = CAN_SJW_1TQ;
    hcan2.Init.TimeSeg1             = CAN_BS1_3TQ;
    hcan2.Init.TimeSeg2             = CAN_BS2_5TQ;
    hcan2.Init.TimeTriggeredMode    = DISABLE;
    hcan2.Init.AutoBusOff           = DISABLE;
    hcan2.Init.AutoWakeUp           = DISABLE;
    hcan2.Init.AutoRetransmission   = DISABLE;
    hcan2.Init.ReceiveFifoLocked    = DISABLE;
    hcan2.Init.TransmitFifoPriority = DISABLE;
    HAL_CAN_Init(&hcan2);
}

void bsp_can_deinit()
{
    HAL_CAN_DeInit(&hcan1);
    HAL_CAN_DeInit(&hcan2);
}

void HAL_CAN_MspInit(CAN_HandleTypeDef *canHandle)
{
    if (canHandle->Instance == CAN1)
    {

        __HAL_RCC_CAN1_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();

        GPIO_InitTypeDef gpio_init_can1 = {
            .Pin       = GPIO_PIN_0 | GPIO_PIN_1,
            .Mode      = GPIO_MODE_AF_PP,
            .Pull      = GPIO_NOPULL,
            .Speed     = GPIO_SPEED_FREQ_VERY_HIGH,
            .Alternate = GPIO_AF9_CAN1,
        };

        HAL_GPIO_Init(GPIOD, &gpio_init_can1);
    }
    else if (canHandle->Instance == CAN2)
    {
        __HAL_RCC_CAN2_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        GPIO_InitTypeDef gpio_init_can2 = {
            .Pin       = GPIO_PIN_12 | GPIO_PIN_13,
            .Mode      = GPIO_MODE_AF_PP,
            .Pull      = GPIO_NOPULL,
            .Speed     = GPIO_SPEED_FREQ_VERY_HIGH,
            .Alternate = GPIO_AF9_CAN2,
        };

        HAL_GPIO_Init(GPIOB, &gpio_init_can2);
    }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef *canHandle)
{
    if (canHandle->Instance == CAN1)
    {
        __HAL_RCC_CAN1_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0 | GPIO_PIN_1);
        HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
    }
    else if (canHandle->Instance == CAN2)
    {
        __HAL_RCC_CAN2_CLK_DISABLE();

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12 | GPIO_PIN_13);
        HAL_NVIC_DisableIRQ(CAN2_TX_IRQn);
        HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
    }
}

void CAN1_RX0_IRQHandler(void)
{
    HAL_CAN_IRQHandler(&hcan1);
}

void CAN2_TX_IRQHandler(void)
{
    HAL_CAN_IRQHandler(&hcan2);
}