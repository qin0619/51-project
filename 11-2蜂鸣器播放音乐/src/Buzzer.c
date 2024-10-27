#include <REGX52.H>
#include <INTRINS.H>
#include "Delay.h"
sbit Buzzer = P2^5;

void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}
void Delay500us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 247;
	while (--i);
}

/**
* @brief 蜂鸣器响应
* @param  unsigned int ms 响应时长 单位us
* @retval 无
*/
void Buzzer_Time(unsigned int ms){
    unsigned int i;
     for(i=0;i<ms;i++){
                Buzzer = !Buzzer;
                Delay500us();
            }
}