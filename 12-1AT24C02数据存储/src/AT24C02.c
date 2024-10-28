#include "I2C.h"
#include "REGX52.H"

#define AT24C02_ADDRESS 0xA0
/**
* @brief AT24C02写入一个字节
* @param    WordAddress 要写入的地址，Data要写入的数据
* @retval 无
*/
void AT24C02_WriteByte(unsigned char WordAddress,Data){

    unsigned char ACK;
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS);
    ACK = I2C_ReceiveACK();
    if(ACK == 0 ) P2 = 0x00;
    I2C_SendByte(WordAddress);
    I2C_ReceiveACK();
    I2C_SendByte(Data);
    I2C_ReceiveACK();
    I2C_Stop();
}

/**
* @brief AT24C02读取一个字节
* @param WordAddress 要读取的地址
* @retval 读取到的数据
*/
unsigned char AT24C02_ReadByte(unsigned char WordAddress){
    unsigned char Data;
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS);
    I2C_ReceiveACK();
    I2C_SendByte(WordAddress);
    I2C_ReceiveACK();
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS | 0x01);
    I2C_ReceiveACK();
    Data = I2C_ReceiveByte();
    I2C_SendACK(1);
    I2C_Stop();
    return Data;
}