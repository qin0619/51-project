#include "REGX52.H"
#include "Delay.h"
#include "LCD1602.h"
#include "Key.h"
#include "I2C.h"
#include "AT24C02.h"

unsigned char Data,KeyNum;
unsigned int num = 0;
void main()
{     
    LCD_Init();
    num = AT24C02_ReadByte(0);
    num |= AT24C02_ReadByte(1) << 8;
    LCD_ShowNum(1,1,num,5);
    // LCD_ShowString(1,1,"hello");
    // SAT24C02_WriteByte(1,66);
    // Delay(5);
    // Data = AT24C02_ReadByte(1);
    // LCD_ShowNum(2,1,Data,3);
    while (1)
    {
        
        KeyNum = Key();
        switch (KeyNum)
        {
        case 1:
            num++;
            LCD_ShowNum(1,1,num,5);
            break;
        case 2:
            num--;
            LCD_ShowNum(1,1,num,5);
            break;
        case 3:
            AT24C02_WriteByte(0,num%256);
            Delay(5);
            AT24C02_WriteByte(1,num/256);
            Delay(5);
            LCD_ShowString(2,1,"write ok");
            Delay(1000);
            LCD_ShowString(2,1,"         ");
            break;
        case 4:
            num = AT24C02_ReadByte(0);
            num |= AT24C02_ReadByte(1) << 8;
            LCD_ShowNum(1,1,num,5);
            LCD_ShowString(2,1,"read ok");
            LCD_ShowString(2,1,"         ");
        default:
            break;
        }
    }
    
}
