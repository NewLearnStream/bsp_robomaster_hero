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
* @file   : bsp_gpio.c
* @author : xiongqulin
* @date   : 3 Jan 2024
* @brief  :
*
*********************************************************************************************************
*/

#include "bsp_gpio.h"

void bsp_gpio_init()
{
    GPIO_InitTypeDef gpio_init;

    gpio_init.Pin   = GPIO_PIN_7;
    gpio_init.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pin   = GPIO_PULLUP;
    gpio_init.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOE, &gpio_init);
}
