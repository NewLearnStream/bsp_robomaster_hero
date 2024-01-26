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
* @file   : bsp_cpu.c
* @author : xiongqulin
* @date   : 25 Dev 2023
* @brief  :
*
*********************************************************************************************************
*/

#include "bsp_cpu.h"

static void system_clock_config();

void bsp_cpu_init()
{
    HAL_Init();
    system_clock_config();
}

static void system_clock_config()
{

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitTypeDef rcc_os_init = {
        .OscillatorType      = RCC_OSCILLATORTYPE_HSI,
        .HSIState            = RCC_HSI_ON,
        .HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT,
        .PLL.PLLState        = RCC_PLL_ON,
        .PLL.PLLSource       = RCC_PLLSOURCE_HSI,
        .PLL.PLLM            = 8,
        .PLL.PLLN            = 180,
        .PLL.PLLP            = RCC_PLLP_DIV2, // 16Mhz / 8 *180 / 2 = 180Mhz
        .PLL.PLLQ            = 4,
    };

    HAL_RCC_OscConfig(&rcc_os_init);

    RCC_ClkInitTypeDef rcc_clk_init = {
        .ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                     RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
        .SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK,
        .AHBCLKDivider  = RCC_SYSCLK_DIV1,
        .APB1CLKDivider = RCC_HCLK_DIV4,
        .APB2CLKDivider = RCC_HCLK_DIV4,
    };

    HAL_RCC_ClockConfig(&rcc_clk_init, FLASH_LATENCY_5);

    HAL_PWREx_EnableOverDrive();
}