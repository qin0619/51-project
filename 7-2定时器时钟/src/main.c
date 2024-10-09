#include "REGX52.H"
#include "Timer0.h"
#include "Delay.h"
#include "LCD1602.h"
unsigned char sec=55,min=59,hour=23;
void Timer0_Routine() interrupt 1{
    static unsigned int T0_count;
    TH0 = 64535/256;//高位
    TL0 = 64535%256;//低位
    T0_count++;
    if(T0_count >= 1000){
        T0_count = 0;
        sec++; 
        if(sec>=60) 
        {
            sec = 0; min++;
            if(min >= 60){
                min = 0;
                hour++;
                if(hour >= 24){
                    hour = 0;
                }
            }
        }
    }
}
void main(){

    LCD_Init();
    Timer0Init();
    LCD_ShowString(1,1,"Clock:");
    LCD_ShowString(2,3,":");
    LCD_ShowString(2,6,":");
    while(1){
        LCD_ShowNum(2,1,hour,2);
        LCD_ShowNum(2,4,min,2);
        LCD_ShowNum(2,7,sec,2);
    }
}
