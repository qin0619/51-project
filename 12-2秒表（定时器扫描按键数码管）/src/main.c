#include "REGX52.H"
#include "Key.h"
#include "NiXie.h"
#include "Delay.h"
#include "Timer0.h"
#include "AT24C02.h"

unsigned char KeyNum,Temp,Min,Sec,MinSec,RunFlag;
void main(){
    Timer0Init();
    while(1){
        KeyNum = Key();
        if(KeyNum == 1) RunFlag = !RunFlag; 
        if(KeyNum == 2) {
            Min = 0;
            Sec = 0;
            MinSec = 0;
        }
        if(KeyNum == 3) {
            AT24C02_WriteByte(0,Min);
            Delay(5);
            AT24C02_WriteByte(1,Sec);
            Delay(5);
            AT24C02_WriteByte(2,MinSec);
            Delay(5);
        }
        if(KeyNum == 4) {
            Min = AT24C02_ReadByte(0);
            Sec = AT24C02_ReadByte(1);
            MinSec = AT24C02_ReadByte(2);
        }
        Nixie_SetBuf(1,Min/10);
        Nixie_SetBuf(2,Min%10);
        Nixie_SetBuf(3,17);
        Nixie_SetBuf(4,Sec/10);
        Nixie_SetBuf(5,Sec%10);
        Nixie_SetBuf(6,17);  
        Nixie_SetBuf(7,MinSec/10);
        Nixie_SetBuf(8,MinSec%10);
            
    }
}
void Sec_Loop(void){
    if(RunFlag){
        MinSec++;
    if(MinSec >= 100){
        MinSec = 0;
        Sec++;
        if(Sec > 60){
            Sec = 0;
            Min++;
            if(Min >= 60) Min = 0;
        }
    }
    }
    
}
void Timer0_Routine() interrupt 1{
    static unsigned int T0count1,T0count2,T0count3;
    TH0 = 0xFC;//¸ßÎ»
    TL0 = 0x18;//µÍÎ» 
    T0count1++;
    if(T0count1 >= 20){T0count1 = 0;Key_Loop();}
    T0count2++;
    if(T0count2 >= 2){T0count2 = 0;Nixie_Loop();}
    T0count3++;
    if(T0count3 >= 10){T0count3 = 0;Sec_Loop();}
}