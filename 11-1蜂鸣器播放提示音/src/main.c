#include <REGX52.H>
#include "Key.h"
#include "NiXie.h"
#include "Delay.h"
#include "Buzzer.h"
sbit Buzzer = P2^5;

unsigned char KeyNum;
unsigned int i;
void main(){
    NiXie(1,0);
    while(1){
        KeyNum = Key();
        if(KeyNum){
            Buzzer_Time(500);
            NiXie(1,KeyNum);
        }
    }
}