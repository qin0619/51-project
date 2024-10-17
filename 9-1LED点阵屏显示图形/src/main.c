#include "REGX52.H"
#include "Delay.h"

sbit RCK = P3^5; // RCLK 上升沿锁位 将寄存器的数据发出
sbit SCK = P3^6; //SRCLK 上升沿移位 将数据按位下移
sbit SER = P3^4; //SER 传输数据位，逐位添加信息

#define MATRIX_LED_PORT P0
/**
* @brief 74HC595写入一个字节的数据
* @param char Byte 要写入的数据
* @retval 无
*/
void _74HC595_WriteByte(unsigned char Byte){
    /*
    位对齐 16进制数赋给sbit时，满足非零即一
    所以当&0x80（1000 0000）时，
    当第一位为零，则SER = 0；
    当第一位为一，则SER = 1; 
    SER = Byte&0x80 
    SCK = 1;  赋高电平向下移位
    SCk = 0;  置0 为下一次的移位做准备
    */
   
    unsigned char i;
    for(i = 0;i<8;i++){
        SER = Byte&(0x80>>i); //逐位添加信息
        SCK = 1;//数据上移，并及时归零
        SCK = 0;
    }
    RCK = 1;//将数据发送到IO口上，及时置零
    RCK = 0;
}
/*
为防止串位，按如下流程执行
段选 位选 延时 位清零 段选 位选 延时 位清零.........
*/
/**
* @brief LED点阵屏显示一列数据
* @param char Colum 要选择的列（0~7）
* @param char Data 选择列显示的数据 高位在上，1为亮，0为灭
* @retval 无
*/
void MatrixLED_ShowColumn(unsigned char Colum,Data){
    _74HC595_WriteByte(Data);
    /*
    通过将Data中的数据写入到74HC595(串转并)模块来控制行
    由P0口控制列(对应的列为P00~P07)
    */
    MATRIX_LED_PORT = ~(0x80>>Colum);//低电平亮，高电平不亮 1000 0000 ~ 0111 1111
    Delayus();
    MATRIX_LED_PORT = 0xFF;
}
void main(){
    SCK = 0;
    RCK = 0;
    while(1){
        /*
        笑脸
    MatrixLED_ShowColumn(0,0x3c);
    MatrixLED_ShowColumn(1,0x42);
    MatrixLED_ShowColumn(2,0xa9);
    MatrixLED_ShowColumn(3,0x85);
    MatrixLED_ShowColumn(4,0x85);
    MatrixLED_ShowColumn(5,0xa9);
    MatrixLED_ShowColumn(6,0x42);
    MatrixLED_ShowColumn(7,0x3c);
        */
    //空心爱心
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