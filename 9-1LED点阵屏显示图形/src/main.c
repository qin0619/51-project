#include "REGX52.H"
#include "Delay.h"

sbit RCK = P3^5; // RCLK ��������λ ���Ĵ��������ݷ���
sbit SCK = P3^6; //SRCLK ��������λ �����ݰ�λ����
sbit SER = P3^4; //SER ��������λ����λ�����Ϣ

#define MATRIX_LED_PORT P0
/**
* @brief 74HC595д��һ���ֽڵ�����
* @param char Byte Ҫд�������
* @retval ��
*/
void _74HC595_WriteByte(unsigned char Byte){
    /*
    λ���� 16����������sbitʱ��������㼴һ
    ���Ե�&0x80��1000 0000��ʱ��
    ����һλΪ�㣬��SER = 0��
    ����һλΪһ����SER = 1; 
    SER = Byte&0x80 
    SCK = 1;  ���ߵ�ƽ������λ
    SCk = 0;  ��0 Ϊ��һ�ε���λ��׼��
    */
   
    unsigned char i;
    for(i = 0;i<8;i++){
        SER = Byte&(0x80>>i); //��λ�����Ϣ
        SCK = 1;//�������ƣ�����ʱ����
        SCK = 0;
    }
    RCK = 1;//�����ݷ��͵�IO���ϣ���ʱ����
    RCK = 0;
}
/*
Ϊ��ֹ��λ������������ִ��
��ѡ λѡ ��ʱ λ���� ��ѡ λѡ ��ʱ λ����.........
*/
/**
* @brief LED��������ʾһ������
* @param char Colum Ҫѡ����У�0~7��
* @param char Data ѡ������ʾ������ ��λ���ϣ�1Ϊ����0Ϊ��
* @retval ��
*/
void MatrixLED_ShowColumn(unsigned char Colum,Data){
    _74HC595_WriteByte(Data);
    /*
    ͨ����Data�е�����д�뵽74HC595(��ת��)ģ����������
    ��P0�ڿ�����(��Ӧ����ΪP00~P07)
    */
    MATRIX_LED_PORT = ~(0x80>>Colum);//�͵�ƽ�����ߵ�ƽ���� 1000 0000 ~ 0111 1111
    Delayus();
    MATRIX_LED_PORT = 0xFF;
}
void main(){
    SCK = 0;
    RCK = 0;
    while(1){
        /*
        Ц��
    MatrixLED_ShowColumn(0,0x3c);
    MatrixLED_ShowColumn(1,0x42);
    MatrixLED_ShowColumn(2,0xa9);
    MatrixLED_ShowColumn(3,0x85);
    MatrixLED_ShowColumn(4,0x85);
    MatrixLED_ShowColumn(5,0xa9);
    MatrixLED_ShowColumn(6,0x42);
    MatrixLED_ShowColumn(7,0x3c);
        */
    //���İ���
    MatrixLED_ShowColumn(0,0x30);
    MatrixLED_ShowColumn(1,0x48);
    MatrixLED_ShowColumn(2,0x44);
    MatrixLED_ShowColumn(3,0x22);
    MatrixLED_ShowColumn(4,0x22);
    MatrixLED_ShowColumn(5,0x44);
    MatrixLED_ShowColumn(6,0x48);
    MatrixLED_ShowColumn(7,0x30);
    }
}