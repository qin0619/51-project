#include "REGX52.H"
/**
* @brief ��ʱ��0��ʼ����1����@11.0592MHz
* @param ��
* @retval ��
*/
void Timer0Init()		//1����@11.0592MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
      
    ET0 = 1;    //�ж�����
    EA = 1;
    PT0 = 1;
}

// �ж�ģ��
// void Timer0_Routine() interrupt 1{
//     static unsigned int T0count;
//     TH0 = 0xFC;//��λ
//     TL0 = 0x18;//��λ
//     T0count++;
//     if(T0count >= 500){T0count = 0;Timer0Init;}
// }

