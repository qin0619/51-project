#include "REGX52.H"
#include "Timer0.h"
#include "Delay.h"

sbit Buzzer = P2^5;

unsigned int FreqSelect;

unsigned int FreqTable[] = {
63777,
63778,
63779,
63780,
63781,
63782,
63783,
63784,
63785,
63786,
63787,
63788,
63789,
63790,
63791,
63792,
63793,
63794,
63795,
63796,
63797,
63798,
63799,
63800,
63801,
63802,
63803,
63804,
63805,
63806,
63807,
63808,
63809,
63810,
63811,
63812
};
void main(){
    Timer0Init();
    while (1)
    {
        FreqSelect++;
        Delayus();
    }
    
}

void Timer0_Routine() interrupt 1{
   
    // TH0 = 0xFC;//¸ßÎ»
    // TL0 = 0x18;//µÍÎ»
   
        TL0 = FreqTable[FreqSelect]%256;
        TH0 = FreqTable[FreqSelect]/256;
        Buzzer = !Buzzer;
}