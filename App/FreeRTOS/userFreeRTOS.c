/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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

#include "userFreeRTOS.h"

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
cJSON *cJSONData = NULL;
cJSON_Hooks cJSONHooks = {.free_fn = vPortFree, .malloc_fn = pvPortMalloc};
char *cJSONStr = NULL;
CoreData coreData = {.name = "STM32H732ZGT6", .temperature = 0, .time = 0};
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};
/* Definitions for flash_led */
osThreadId_t flash_ledHandle;
const osThreadAttr_t flash_led_attributes = {
    .name = "flash_led",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};
/* Definitions for usart1_printf */
osThreadId_t usart1_printfHandle;
const osThreadAttr_t usart1_printf_attributes = {
    .name = "usart1_printf",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};
/* Definitions for usart1_printf */
osThreadId_t lcd_printfHandle;
const osThreadAttr_t lcd_printf_attributes = {
    .name = "lcd_printf",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */
    cJSON_InitHooks(&cJSONHooks);
    cJSONData = cJSON_CreateObject();
    cJSON_AddStringToObject(cJSONData, "name", "STM32H732ZGT6");
    cJSON_AddNumberToObject(cJSONData, "temperature", 0);
    cJSON_AddNumberToObject(cJSONData, "time", xTaskGetTickCount());
    /* USER CODE END Init */
    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of defaultTask */
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

    /* creation of flash_led */
    flash_ledHandle = osThreadNew(Start_flash_led, NULL, &flash_led_attributes);

    /* creation of usart1_printf */
    usart1_printfHandle = osThreadNew(Start_usart1_printf, NULL, &usart1_printf_attributes);

    /* creation of lcd_printf */
    lcd_printfHandle = osThreadNew(Start_lcd_printf, NULL, &lcd_printf_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
    /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
    /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Start_flash_led */
/**
 * @brief Function implementing the flash_led thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Start_flash_led */
void Start_flash_led(void *argument)
{
    /* USER CODE BEGIN Start_flash_led */
    /* Infinite loop */
    for (;;)
    {
        LED1_Toggle;
        osDelay(1000);
    }
    /* USER CODE END Start_flash_led */
}

/* USER CODE BEGIN Header_Start_usart1_printf */
/**
 * @brief Function implementing the usart1_printf thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Start_usart1_printf */
void Start_usart1_printf(void *argument)
{
    /* USER CODE BEGIN Start_usart1_printf */
    /* Infinite loop */
    for (;;)
    {
        HAL_DTS_GetTemperature(&hdts, &(coreData.temperature));
        // cJSON *midCJSON = cJSON_GetObjectItem(cJSONData, "temperature");
        // if (midCJSON)
        // {
        //     cJSON_SetNumberValue(midCJSON, temperature);
        // }
        // midCJSON = cJSON_GetObjectItem(cJSONData, "time");
        // if (midCJSON)
        // {
        //     cJSON_SetNumberValue(midCJSON, xTaskGetTickCount()/1000);
        // }
        // cJSONStr = cJSON_Print(cJSONData);
        // printf("%s\r\n", cJSONStr);
        osDelay(500);
    }
    /* USER CODE END Start_usart1_printf */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void Start_lcd_printf(void *argument)
{
    /* USER CODE BEGIN Start_usart1_printf */
    /* Infinite loop */
    char midStr[64] = "";
    LCD_SetDirection(Direction_V_Flip);
    LCD_SetBackColor(LCD_BLACK); //	设置背景色
    LCD_Clear();                 // 清屏
    LCD_SetAsciiFont(&ASCII_Font12);
    TickType_t midTime = xTaskGetTickCount();
    uint16_t fps = 0;
    for (;;)
    {
        coreData.time = xTaskGetTickCount();
        if (coreData.time - midTime < 1000)
        {
            fps++;
        }
        else
        {
            sprintf(midStr, "FPS:%3d", fps);
            LCD_DisplayText(10, 34, midStr);
            fps = 0;
            midTime = coreData.time;
        }
        sprintf(midStr, "CPU T:%ld", coreData.temperature);
        LCD_DisplayText(10, 10, midStr);
        strcpy(midStr, "");
        sprintf(midStr, "Time:%ld", coreData.time);
        LCD_DisplayText(10, 22, midStr);
        Clock_Needle(coreData.time / 720000, 32);
        Clock_Needle(coreData.time / 60000, 48);
        Clock_Sec(coreData.time / 1000, 64);
        User_Image(240 - 96 - 1, 0, "BHS", (uint16_t *)Image_BHS_32x32);
    }
    /* USER CODE END Start_usart1_printf */
}
/* USER CODE END Application */
