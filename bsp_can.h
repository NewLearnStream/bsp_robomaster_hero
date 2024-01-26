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
* @file   : bsp_can.h
* @author : xiongqulin
* @date   : 25 Dev 2023
* @brief  :
*
*********************************************************************************************************
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "stm32f4xx.h"

void bsp_can_init();

void bsp_can_deinit();

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

#ifdef __cplusplus
}
#endif // __cplusplus