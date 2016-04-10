
#include "delay.h"

/**********************************************
 * 函数功能: 微秒级精确延时
 * 参数范围: 1us~65535us(0.001ms~65.535ms)
 * 运行环境: STC12@32.000MHz
 * 最大误差: 0.00%
 * 作者日期: 电器开发部 - (2015-2-23)
**********************************************/
# pragma optimize(4, SPEED)
void delay_us(unsigned int n)
{
    extern void _nop_(void);
    register unsigned char i = n, j = (n>>8);
    _nop_(); _nop_(); _nop_();
    if ((--i) | j)
    {
        do
        {
            _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
            if (0xFF == (i--)) j--; else {_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();};
        } while (i | j);
    }
}

/* 毫秒延时函数 */
void delay_ms(unsigned int n) {while (n--) delay_us(1000);}
