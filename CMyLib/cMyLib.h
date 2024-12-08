#ifndef __CMYLIB_H
#define __CMYLIB_H

#ifdef __cplusplus
extern "C" {
#endif


#include "define.h"
#include "dts.h"
#include "usart.h"
#include "cJSON.h"

typedef struct CoreData
{
    char* name;
    int32_t temperature;
    uint32_t time;
    uint32_t memory;
}CoreData;

CoreData* CJSON_To_CoreData(cJSON* cJSONData);

cJSON* CoreData_To_CJSON(CoreData* coreData);

void CJSON_Test();

#ifdef __cplusplus
}
#endif

#endif //__CMYLIB_H
