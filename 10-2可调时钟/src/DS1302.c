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
//写保护
#define DS1302_WP     0x8E
//年月日时分秒周
char DS1302_Time[] = {19,11,16,12,59,55,6};
void DS1302_WriteByte(unsigned char Command,Data);
unsigned char DS1302_DToB(unsigned char Data);
unsigned char DS1302_BToD(unsigned char Data);
/**
* @brief DS1302初始化
* @param 无
* @retval 无
*/
void DS1302_Init(void){
    DS1302_CE = 0;
    DS1302_SCLK = 0;
    DS1302_WriteByte(0x8E,0x00);
}
/**
* @brief DS1302写操作
* @param unsigned char Command 命令字
* @param unsigned char Data 要写入的数据
* @retval 无
*/
void DS1302_WriteByte(unsigned char Command,Data){
    unsigned char i = 0;
    DS1302_CE = 1;
    //写入命令字 告诉单片机接下来要进行的操作
    for(i = 0;i < 8;i++){
        DS1302_IO = Command&(0x01<<i);//取出第i位
        DS1302_SCLK = 1;//上升沿
        Delayus();
        DS1302_SCLK = 0;//下降沿
    }
    //写入数据
    for(i = 0;i < 8;i++){
        DS1302_IO = Data&(0x01<<i);//取出第i位
        DS1302_SCLK = 1;//上升沿
        DS1302_SCLK = 0;//下降沿
    }
    DS1302_CE = 0;//ce归0
}
/**
* @brief 读操作
* @param unsigned char Command 命令字
* @retval 无
*/
unsigned char DS1302_ReadByte(unsigned char Command){
    unsigned char i,Data = 0x00;
    //为了防止重复定义变量，直接使用写操作的地址，而读操作的末尾是0，
    //所以将读操作的命令字最后一位置1即可作为读操作的命令字
    Command |= 0x01;
    DS1302_CE = 1;
    //写入命令字
    for(i = 0;i < 8;i++){
        DS1302_IO = Command&(0x01<<i);//取出第i位
        DS1302_SCLK = 0;//下降沿
        DS1302_SCLK = 1;//上升沿
    }
    
    for(i = 0;i < 8;i++){
       DS1302_SCLK = 1;//上升沿 
       DS1302_SCLK = 0;//下降沿
        if(DS1302_IO){
            Data |= (0x01<<i);
        }
    }
    DS1302_CE = 0;
    DS1302_IO = 0;
    return Data;
}
/**
* @brief 设置时钟数据
* @param 无
* @retval 无
*/
void DS1302_SetTime(void){
    //关闭写保护
    DS1302_WriteByte(DS1302_WP,0x00);
    DS1302_WriteByte(DS1302_YEAR,DS1302_BToD(DS1302_Time[0]));
    DS1302_WriteByte(DS1302_MONTH,DS1302_BToD(DS1302_Time[1]));
    DS1302_WriteByte(DS1302_DATE,DS1302_BToD(DS1302_Time[2]));
    DS1302_WriteByte(DS1302_HOUR,DS1302_BToD(DS1302_Time[3]));
    DS1302_WriteByte(DS1302_MINUTE,DS1302_BToD(DS1302_Time[4]));
    DS1302_WriteByte(DS1302_SECOND,DS1302_BToD(DS1302_Time[5]));
    DS1302_WriteByte(DS1302_DAY,DS1302_BToD(DS1302_Time[6]));
    //打开写保护
    DS1302_WriteByte(DS1302_WP,0x80);
}
/**
* @brief 读取时钟数据
* @param 无
* @retval 无
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
* @brief 数据类型转换函数，将BDC码转换为DEC（十进制）
* @param unsigned char Data 要转换的数据
* @retval 无
*/
unsigned char DS1302_BToD(unsigned char Data){
    return Data/10*16+Data%10;
}
/**
* @brief 数据类型转换函数，将DEC（十进制）转换为BDC码
* @param unsigned char Data 要转换的数据
* @retval 无
*/
unsigned char DS1302_DToB(unsigned char Data){
    return Data/16*10+Data%16;
}