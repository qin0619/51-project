#include "REGX52.H"
#include "Delay.h"
sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;
#define DS1302_SECOND 0x80
#define DS1302_MINUTE 0x82
#define DS1302_HOUR   0x84
#define DS1302_DATE   0x86
#define DS1302_MONTH  0x88
#define DS1302_DAY    0x8A
#define DS1302_YEAR   0x8C
//д����
#define DS1302_WP     0x8E
//������ʱ������
char DS1302_Time[] = {19,11,16,12,59,55,6};
void DS1302_WriteByte(unsigned char Command,Data);
unsigned char DS1302_DToB(unsigned char Data);
unsigned char DS1302_BToD(unsigned char Data);
/**
* @brief DS1302��ʼ��
* @param ��
* @retval ��
*/
void DS1302_Init(void){
    DS1302_CE = 0;
    DS1302_SCLK = 0;
    DS1302_WriteByte(0x8E,0x00);
}
/**
* @brief DS1302д����
* @param unsigned char Command ������
* @param unsigned char Data Ҫд�������
* @retval ��
*/
void DS1302_WriteByte(unsigned char Command,Data){
    unsigned char i = 0;
    DS1302_CE = 1;
    //д�������� ���ߵ�Ƭ��������Ҫ���еĲ���
    for(i = 0;i < 8;i++){
        DS1302_IO = Command&(0x01<<i);//ȡ����iλ
        DS1302_SCLK = 1;//������
        Delayus();
        DS1302_SCLK = 0;//�½���
    }
    //д������
    for(i = 0;i < 8;i++){
        DS1302_IO = Data&(0x01<<i);//ȡ����iλ
        DS1302_SCLK = 1;//������
        DS1302_SCLK = 0;//�½���
    }
    DS1302_CE = 0;//ce��0
}
/**
* @brief ������
* @param unsigned char Command ������
* @retval ��
*/
unsigned char DS1302_ReadByte(unsigned char Command){
    unsigned char i,Data = 0x00;
    //Ϊ�˷�ֹ�ظ����������ֱ��ʹ��д�����ĵ�ַ������������ĩβ��0��
    //���Խ������������������һλ��1������Ϊ��������������
    Command |= 0x01;
    DS1302_CE = 1;
    //д��������
    for(i = 0;i < 8;i++){
        DS1302_IO = Command&(0x01<<i);//ȡ����iλ
        DS1302_SCLK = 0;//�½���
        DS1302_SCLK = 1;//������
    }
    
    for(i = 0;i < 8;i++){
       DS1302_SCLK = 1;//������ 
       DS1302_SCLK = 0;//�½���
        if(DS1302_IO){
            Data |= (0x01<<i);
        }
    }
    DS1302_CE = 0;
    DS1302_IO = 0;
    return Data;
}
/**
* @brief ����ʱ������
* @param ��
* @retval ��
*/
void DS1302_SetTime(void){
    //�ر�д����
    DS1302_WriteByte(DS1302_WP,0x00);
    DS1302_WriteByte(DS1302_YEAR,DS1302_BToD(DS1302_Time[0]));
    DS1302_WriteByte(DS1302_MONTH,DS1302_BToD(DS1302_Time[1]));
    DS1302_WriteByte(DS1302_DATE,DS1302_BToD(DS1302_Time[2]));
    DS1302_WriteByte(DS1302_HOUR,DS1302_BToD(DS1302_Time[3]));
    DS1302_WriteByte(DS1302_MINUTE,DS1302_BToD(DS1302_Time[4]));
    DS1302_WriteByte(DS1302_SECOND,DS1302_BToD(DS1302_Time[5]));
    DS1302_WriteByte(DS1302_DAY,DS1302_BToD(DS1302_Time[6]));
    //��д����
    DS1302_WriteByte(DS1302_WP,0x80);
}
/**
* @brief ��ȡʱ������
* @param ��
* @retval ��
*/
void DS1302_ReadTime(void){
  
    DS1302_Time[0] = DS1302_DToB(DS1302_ReadByte(DS1302_YEAR));
    DS1302_Time[1] = DS1302_DToB(DS1302_ReadByte(DS1302_MONTH));
    DS1302_Time[2] = DS1302_DToB(DS1302_ReadByte(DS1302_DATE));
    DS1302_Time[3] = DS1302_DToB(DS1302_ReadByte(DS1302_HOUR));
    DS1302_Time[4] = DS1302_DToB(DS1302_ReadByte(DS1302_MINUTE));
    DS1302_Time[5] = DS1302_DToB(DS1302_ReadByte(DS1302_SECOND));
    DS1302_Time[6] = DS1302_DToB(DS1302_ReadByte(DS1302_DAY));

}
/**
* @brief ��������ת����������BDC��ת��ΪDEC��ʮ���ƣ�
* @param unsigned char Data Ҫת��������
* @retval ��
*/
unsigned char DS1302_BToD(unsigned char Data){
    return Data/10*16+Data%10;
}
/**
* @brief ��������ת����������DEC��ʮ���ƣ�ת��ΪBDC��
* @param unsigned char Data Ҫת��������
* @retval ��
*/
unsigned char DS1302_DToB(unsigned char Data){
    return Data/16*10+Data%16;
}