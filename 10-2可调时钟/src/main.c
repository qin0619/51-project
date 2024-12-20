#include "REGX52.H"
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"
#include "Key.h"
#include "Timer0.h"

unsigned char keynum,mode,TimeSetFlashFlag,TimeSetSelect=0;

void TimeShow(void){
      DS1302_ReadTime();
      LCD_ShowNum(1,1,DS1302_Time[0],2);
      LCD_ShowString(1,3,":");
      LCD_ShowNum(1,4,DS1302_Time[1],2);
      LCD_ShowNum(1,7,DS1302_Time[2],2);
      LCD_ShowNum(2,1,DS1302_Time[3],2);
      LCD_ShowNum(2,4,DS1302_Time[4],2);
      LCD_ShowNum(2,7,DS1302_Time[5],2);
} 

void TimeSet(void){
   if(keynum == 2){
      TimeSetSelect++;
      TimeSetSelect %= 6;
   }
   if(keynum == 3){
      DS1302_Time[TimeSetSelect]++;
      
      if(DS1302_Time[0]>99){DS1302_Time[0] = 0;}
      
      if(DS1302_Time[1]>12){DS1302_Time[1] = 1;}
      
     if(DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time == 5 ||
         DS1302_Time[1] == 7 || DS1302_Time[1] == 8 || DS1302_Time == 10 ||
         DS1302_Time[1] == 12)
         {if(DS1302_Time[2] >31){DS1302_Time[2] = 1;}}
      else if(DS1302_Time[1] == 4 || DS1302_Time[1] == 6 || DS1302_Time == 9 ||
         DS1302_Time[1] == 11 )
         {if(DS1302_Time[2] >30) {DS1302_Time[2] = 1;}}
      else if (DS1302_Time[1] == 2)
      {
         if(DS1302_Time[0] % 4 ==0){
            if(DS1302_Time[2] > 29) {DS1302_Time[2] = 1;}
         }else{
            if(DS1302_Time[2] > 28) {DS1302_Time[2] = 1;}
         }
      }

      if(DS1302_Time[3] > 23) {DS1302_Time[3] = 0;}
      if(DS1302_Time[4] > 59) {DS1302_Time[4] = 0;}
      if(DS1302_Time[5] > 59) {DS1302_Time[5] = 0;}
   }
   if(keynum == 4){
      DS1302_Time[TimeSetSelect]--;

      if(DS1302_Time[0] < 0){DS1302_Time[0] = 0;}
      
      if(DS1302_Time[1] < 1){DS1302_Time[1] = 12;}
      
      if(DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time == 5 ||
         DS1302_Time[1] == 7 || DS1302_Time[1] == 8 || DS1302_Time == 10 ||
         DS1302_Time[1] == 12)
         {
            if(DS1302_Time[2] < 1){DS1302_Time[2] = 31;}
            if(DS1302_Time[2] >31){DS1302_Time[2] = 1;}
         }
      else if(DS1302_Time[1] == 4 || DS1302_Time[1] == 6 || DS1302_Time == 9 || DS1302_Time[1] == 11 )
         {
            if(DS1302_Time[2] < 1) {DS1302_Time[2] = 30;}
            if(DS1302_Time[2] >30) {DS1302_Time[2] = 1;}
            }
      else if (DS1302_Time[1] == 2)
      {
         if(DS1302_Time[0] % 4 ==0){
            if(DS1302_Time[2]< 1) {DS1302_Time[2] = 29;}
            if(DS1302_Time[2] > 29) {DS1302_Time[2] = 1;}
         }
         else{
            if(DS1302_Time[2] < 1) {DS1302_Time[2] = 28;}
            if(DS1302_Time[2] > 28) {DS1302_Time[2] = 1;}
         }
      }
      
      if(DS1302_Time[3] < 0) {DS1302_Time[3] = 23;}
      if(DS1302_Time[4] < 0) {DS1302_Time[4] = 59;}
      if(DS1302_Time[5] < 0) {DS1302_Time[5] = 59;}
   }
   if(TimeSetSelect == 0 && TimeSetFlashFlag == 1){
      LCD_ShowString(1,1,"  ");
   }else{
      LCD_ShowNum(1,1,DS1302_Time[0],2);
   }

   if(TimeSetSelect == 1 && TimeSetFlashFlag == 1){
      LCD_ShowString(1,4,"  ");
   }else{
      LCD_ShowNum(1,4,DS1302_Time[1],2);
   }

   if(TimeSetSelect == 2 && TimeSetFlashFlag == 1){
      LCD_ShowString(1,7,"  ");
   }else{
      LCD_ShowNum(1,7,DS1302_Time[2],2);
   }

   if(TimeSetSelect == 3 && TimeSetFlashFlag == 1){
      LCD_ShowString(2,1,"  ");
   }else{
      LCD_ShowNum(2,1,DS1302_Time[3],2);
   }
   
   if(TimeSetSelect == 4 && TimeSetFlashFlag == 1){
      LCD_ShowString(2,4,"  ");
   }else{
      LCD_ShowNum(2,4,DS1302_Time[4],2);
   }
   
   if(TimeSetSelect == 5 && TimeSetFlashFlag == 1){
      LCD_ShowString(2,7,"  ");
   }else{
      LCD_ShowNum(2,7,DS1302_Time[5],2);
   }

   if(TimeSetSelect == 5 && TimeSetFlashFlag == 1){
      LCD_ShowString(2,7,"  ");
   }else{
      LCD_ShowNum(2,7,DS1302_Time[5],2);
   }

   LCD_ShowNum(2,10,TimeSetSelect,2);
   LCD_ShowNum(2,13,TimeSetFlashFlag,2);
}
void main(){
   LCD_Init();
   DS1302_Init();
   Timer0Init();
   DS1302_SetTime();
   LCD_ShowString(1,3,":");
   LCD_ShowString(1,6,":");
   LCD_ShowString(2,3,":");
   LCD_ShowString(2,6,":");
    while(1){
      keynum = Key();
      if(keynum==1){
         if(mode==0){mode = 1;}
         else {mode = 0;DS1302_SetTime();}
      }
      switch (mode)
      {
      case 0:
         TimeShow();break;
      case 1:
         TimeSet();break;
      default:
         break;
      }
    } 
      
    }

void Timer0_Routine() interrupt 1{
    static unsigned int T0count;
    TL0 = 0x66;		//设置定时初值
	 TH0 = 0xFC;		//设置定时初值
    T0count++;
    if(T0count >= 500){T0count = 0;TimeSetFlashFlag=!TimeSetFlashFlag;}
}