#include "REGX52.H"

void UART_Init(){//4800bps@11.0592MHz
    SCON = 0X40;
    PCON &= 0x80;		//波特率不倍速
    TMOD &= 0X0F;
    TMOD |= 0x20;
    TL1 = 0xFA;		//设定定时初值
	TH1 = 0xFA;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}
void UART_SendByte(unsigned char Byte){
    SBUF = Byte;
    while(TI == 0);
    TI = 0;
}