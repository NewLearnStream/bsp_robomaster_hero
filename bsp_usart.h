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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "stm32f4xx.h"

void bsp_usart_init();

extern UART_HandleTypeDef huart1;

#ifdef __cplusplus
}
#endif // __cplusplus
