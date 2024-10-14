#include "REGX52.H"

void UART_Init(){//4800bps@11.0592MHz
    SCON = 0X40;
    PCON &= 0x80;		//�����ʲ�����
    TMOD &= 0X0F;
    TMOD |= 0x20;
    TL1 = 0xFA;		//�趨��ʱ��ֵ
	TH1 = 0xFA;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
}
void UART_SendByte(unsigned char Byte){
    SBUF = Byte;
    while(TI == 0);
    TI = 0;
}