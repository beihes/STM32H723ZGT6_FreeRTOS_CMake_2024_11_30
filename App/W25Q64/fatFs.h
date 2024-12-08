#ifndef __FATFAS_H
#define __FATFAS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "cMyLib.h"

    // 判断FatFs是否挂载成功，若没有创建FatFs则格式化SD卡
    void FatFs_Check(void);

    // 计算设备容量
    void FatFs_GetVolume(void);

    // 文件创建和写入测试
    int8_t FatFs_FileTest(void);

#ifdef __cplusplus
}
#endif

#endif //__FATFAS_H