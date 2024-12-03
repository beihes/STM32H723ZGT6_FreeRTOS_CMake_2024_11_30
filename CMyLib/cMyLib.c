#include "cMyLib.h"

void CJSON_Test()
{
    char json_data[] = "{\"name\":\"刘德华\",\"age\":40}";
    cJSON *json_list = cJSON_Parse(json_data);
    if (!json_list)
    {
        puts(cJSON_GetErrorPtr());
    }
    else
    {
        puts(cJSON_Print(json_list));
    }
    cJSON *json_name = cJSON_GetObjectItem(json_list, "name");
    if (json_name->type == cJSON_String)
    {
        printf("name:%s\n", json_name->valuestring);
    }
    cJSON *json_age = cJSON_GetObjectItem(json_list, "age");
    if (json_age->type == cJSON_Number)
    {
        printf("age:%d\n", json_age->valueint);
    }
    cJSON_Delete(json_list);
}