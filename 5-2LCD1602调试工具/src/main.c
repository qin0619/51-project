#include "REG52.H"
#include "LCD1602.h"
#include "Delay.h"

unsigned int result = 0;
void main(){
    LCD_Init();
    // LCD_ShowChar(1,1,'A');
    // LCD_ShowString(1,4,"hello world");
    // LCD_ShowNum(2,1,123,3);
    // LCD_ShowSignedNum(2,4,-11,2);
    // LCD_ShowHexNum(2,7,0xEF,2);
    // LCD_ShowBinNum(2,9,0xAA,8);

    while(1){
        Delay(50);
        result++;
        LCD_ShowNum(1,1,result,2);
    }
}  

