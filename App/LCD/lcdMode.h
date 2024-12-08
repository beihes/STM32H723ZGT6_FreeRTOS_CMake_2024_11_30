#ifndef __LCDMODE_H
#define __LCDMODE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lcd_spi_154.h"

    // LCD测试函数，函数定义在底部
    void LCD_Test_Clear(void);     // 清屏测试
    void LCD_Test_Text(void);      // 文本测试
    void LCD_Test_Variable(void);  // 变量显示，包括整数和小数
    void LCD_Test_Color(void);     // 矩形填充测试
    void LCD_Test_Grahic(void);    // 2D图形绘制
    void LCD_Test_Image(void);     // 图片显示
    void LCD_Test_Direction(void); // 更换显示方向

    void LCD_Line(void);             // 画线
    void LCD_Rectangle(void);        // 矩形
    void LCD_RouRectangle(void);     // 圆角矩形
    void LCD_Ellipse(void);          // 椭圆
    void LCD_Circle(void);           // 圆
    void LCD_Triangle(void);         // 三角形
    void LCD_Picture(void);          // 图片
    void LCD_Arc(void);              // 圆弧
    void LCD_Polygon(void);          // 多边形
    void LCD_Clock(void);            // 时钟
    void Clock_Needle(int t, int l); // 时钟、分钟移动轨迹
    void Clock_Sec(int t, int l);    // 秒针移动轨迹和表盘
    //l为秒针长度，依次为l，l/4*3，1/2
    void Show_Clock(int l, uint32_t time);
    void User_Image(uint16_t x,uint16_t y, const char* user,uint16_t* image);

#ifdef __cplusplus
}
#endif

#endif // __LCDMODE_H