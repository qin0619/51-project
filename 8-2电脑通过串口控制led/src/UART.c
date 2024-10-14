#include "REGX52.H"

void UART_Init(){//4800bps@11.0592MHz
    SCON = 0X50;
    PCON &= 0x7F;		//波特率不倍速 01111111 0x80
    TMOD &= 0X0F;
    TMOD |= 0x20;
    /*
    串口通过统计定时器1的溢出率即波特率来与其他单位进行同步通信，即约束同等的波特率
    当单片机工作在12T模式时，定时器1的溢益出率=SYSclk/12/(256-TH1):F=1/T
    当单片机工作在6T模式时，定时器1的溢出率=SYSclk/6/(256-TH1)
    SYSclk为系统晶振频率
    256 -250 = 6s
    每1.085计一次数
    每隔6X1.085溢出一次
    溢出率：1/6.51=0.1536098310291859MHz
    SMOD = 1 不加倍
    波特率 = 溢出率/16/2=0.0048003072196621 @4800MHz
    */
    TL1 = 0xFA;		//设定定时初值 250 
	TH1 = 0xFA;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
    EA = 1;         //启动所有中断
    ES = 1;         //启动串口中断
}
void UART_SendByte(unsigned char Byte){
    SBUF = Byte;
    while(TI == 0);
    TI = 0;
}
/*
中断函数模板
void UART_Routine() interrupt 4{
    if(RI==1){
        P2 = ~SBUF;
        UART_SendByte(SBUF);
        RI = 0;
    }
}*/