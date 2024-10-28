#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

/**
* @brief I2C��ʼ
* @param ��
* @retval ��
*/
void I2C_Start(void){
    //��ʼ������SCL�ߵ�ƽ�ڼ䣬SDA�Ӹߵ�ƽ�л����͵�ƽ
    I2C_SDA = 1;//��ȷ��SDA״̬��Ϊ������ʼ����������Ҫ�Ƚ�SDA����
    I2C_SCL = 1;
    I2C_SDA = 0;
    I2C_SCL = 0;
}

/**
* @brief I2C����
* @param ��
* @retval ��
*/
void I2C_Stop(void){
    //��ֹ������SCL�ߵ�ƽ�ڼ䣬SDA�ӵ͵�ƽ�л����ߵ�ƽ
    I2C_SDA = 0;
    I2C_SCL = 1;
    I2C_SDA = 1;
}

/**
* @brief I2C����һ���ֽ�
* @param unsigned char Byte Ҫ���͵�����
* @retval ��
*/
void I2C_SendByte(unsigned char Byte){
    unsigned char i;
    for ( i = 0; i < 8; i++)
    {
        I2C_SDA = Byte & (0x80 >> i);//�����ݷŵ���������
        I2C_SCL = 1;//�����ڼ���Ҫ��scl��ƽ����
        I2C_SCL = 0;//�������ٽ���ƽ����
    }
}

/**
* @brief I2C����һ���ֽ�
* @param ��
* @retval unsigned char ���ܵ�������
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
* @brief I2C ����Ӧ��
* @param unsigned char ACKBit Ӧ��λ��0ΪӦ��1Ϊ��Ӧ��
* @retval ��
*/
void I2C_SendACK(unsigned char ACKBit){
    I2C_SDA = ACKBit;
    I2C_SCL = 1;
    I2C_SCL = 0;
}

/**
* @brief I2C ����Ӧ��
* @param ��
* @retval unsigned char ACKBit Ӧ��λ��0ΪӦ��1Ϊ��Ӧ��
*/
unsigned char I2C_ReceiveACK(void){
    unsigned char ACKBit=0;
    I2C_SDA = 1;
    I2C_SCL = 1;
    ACKBit = I2C_SDA;
    I2C_SCL = 0;   
    return ACKBit;
}