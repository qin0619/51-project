#include "REGX52.H"
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned int password = 0;
unsigned char k = 0;

void clean(){
    password = 0; k=0;LCD_ShowString(2,1,"          ");
}

void main(){

    LCD_Init();
    LCD_ShowString(1,1,"Password:");
    while (1)
    { 
        KeyNum = MatrixKey();
        if(KeyNum){ 
            if(KeyNum <= 10) {
                k++;
                if( k <= 4) 
                    {
                        password = password*10;
                        password += KeyNum; 
                        LCD_ShowNum(2,1,password,k);
                        }
                }
            if(KeyNum == 11)  
                if(password == 1111) LCD_ShowString(1,11,"right!");
                else {LCD_ShowString(1,11,"wrong!");clean();}
            }
            if(KeyNum == 12) clean();
    }
    

}