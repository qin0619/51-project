#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

/**
* @brief I2C开始
* @param 无
* @retval 无
*/
void I2C_Start(void){
    //起始条件：SCL高电平期间，SDA从高电平切换到低电平
    I2C_SDA = 1;//不确定SDA状态，为满足起始条件，故需要先将SDA拉高
    I2C_SCL = 1;
    I2C_SDA = 0;
    I2C_SCL = 0;
}

/**
* @brief I2C结束
* @param 无
* @retval 无
*/
void I2C_Stop(void){
    //终止条件：SCL高电平期间，SDA从低电平切换到高电平
    I2C_SDA = 0;
    I2C_SCL = 1;
    I2C_SDA = 1;
}

/**
* @brief I2C发送一个字节
* @param unsigned char Byte 要发送的数据
* @retval 无
*/
void I2C_SendByte(unsigned char Byte){
    unsigned char i;
    for ( i = 0; i < 8; i++)
    {
        I2C_SDA = Byte & (0x80 >> i);//将数据放到数据线上
        I2C_SCL = 1;//操作期间需要将scl电平拉高
        I2C_SCL = 0;//结束后再将电平拉回
    }
}

/**
* @brief I2C接收一个字节
* @param 无
* @retval unsigned char 接受到的数据
*/
unsigned char I2C_ReceiveByte(void){
    unsigned char Byte=0x00,i;
    I2C_SDA = 1;
    
    for ( i = 0; i < 8; i++)
    {
        I2C_SCL = 1;
        if(I2C_SDA) {
            Byte |= (0x80 >> i);
        }
        I2C_SCL = 0;
    }
    return Byte;
}
/**
* @brief I2C 发送应答
* @param unsigned char ACKBit 应答位，0为应答，1为非应答
* @retval 无
*/
void I2C_SendACK(unsigned char ACKBit){
    I2C_SDA = ACKBit;
    I2C_SCL = 1;
    I2C_SCL = 0;
}

/**
* @brief I2C 接受应答
* @param 无
* @retval unsigned char ACKBit 应答位，0为应答，1为非应答
*/
unsigned char I2C_ReceiveACK(void){
    unsigned char ACKBit=0;
    I2C_SDA = 1;
    I2C_SCL = 1;
    ACKBit = I2C_SDA;
    I2C_SCL = 0;   
    return ACKBit;
}