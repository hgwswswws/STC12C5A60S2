
#include "delay.h"

/**********************************************
 * ��������: ΢�뼶��ȷ��ʱ
 * ������Χ: 1us~65535us(0.001ms~65.535ms)
 * ���л���: STC12@32.000MHz
 * ������: 0.00%
 * ��������: ���������� - (2015-2-23)
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

/* ������ʱ���� */
void delay_ms(unsigned int n) {while (n--) delay_us(1000);}
