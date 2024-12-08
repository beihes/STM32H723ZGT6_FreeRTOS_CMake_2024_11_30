/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "constHead.h"

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    SCB_EnableICache();    // 使能ICache
    SCB_EnableDCache();    // 使能DCache
    HAL_Init();            // HAL初始化
    SystemClock_Config();  // 时钟初始化
    MX_USART1_UART_Init(); // 串口初始化
    MX_DTS_Init();
    SPI_LCD_Init();                                        // LCD的SPI初始化
    HAL_DTS_Start(&hdts);                                  // HAL的DTS初始化
    LED_Init();                                            // LED初始化
    printf("SYSClock:%ld\r\n", HAL_RCC_GetSysClockFreq()); // 打印频率
    CJSON_Test();                                          // cJSON测试
    //OSPI_W25Qxx_Init();                                 //W25Q64初始化
    FatFs_Check();     // 判断FatFs是否挂载成功，若没有创建FatFs则格式化SD卡
    FatFs_GetVolume(); // 计算设备容量
    getCoreData()->drivers.fatfs=FatFs_FileTest();  // 文件创建和写入测试

    osKernelInitialize(); /* Call init function for freertos objects (in freertos.c) */
    MX_FREERTOS_Init();
    osKernelStart();

    while (1)
    {
        /* USER CODE END WHILE */
        /* USER CODE BEGIN 3 */
    }
}
