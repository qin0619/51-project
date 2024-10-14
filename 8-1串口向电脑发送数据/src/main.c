#include "REGX52.H"
#include "Delay.h"
#include "UART.h"
unsigned int sec;
void main(){
    UART_Init();
    
    while(1){
    sec++;
    UART_SendByte(sec);
    Delay(1);
    }
}