#ifndef __USERFREERTOS_H
#define __USERFREERTOS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cMyLib.h"
#include "led.h"
#include "lcdMode.h"
#include "ospi_w25q64.h"
#include "fatFs.h"

void StartDefaultTask(void *argument);
void Start_flash_led(void *argument);
void Start_usart1_printf(void *argument);
void Start_lcd_printf(void *argument);
void Start_w25q64_RW(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

CoreData* getCoreData();

#ifdef __cplusplus
}
#endif

#endif //__USERFREERTOS_H
