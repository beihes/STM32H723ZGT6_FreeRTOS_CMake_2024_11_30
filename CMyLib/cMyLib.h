#ifndef __CMYLIB_H
#define __CMYLIB_H

#ifdef __cplusplus
extern "C" {
#endif


#include "define.h"
#include "dts.h"
#include "usart.h"
#include "cJSON.h"
#include "ff.h"

typedef struct MyDrivers
{
    int8_t lcd;
    int8_t w25q64;
    int8_t fatfs;
    int8_t sdCard;
    int8_t jy61p;
}MyDrivers;

typedef struct CoreData
{
    char* name;
    int32_t temperature;
    uint32_t time;
    uint32_t memory;
    MyDrivers drivers;
}CoreData;

CoreData* CJSON_To_CoreData(cJSON* cJSONData);

cJSON* CoreData_To_CJSON(CoreData* coreData);

void CJSON_Test();

#ifdef __cplusplus
}
#endif

#endif //__CMYLIB_H
