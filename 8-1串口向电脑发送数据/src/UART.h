#ifndef __UART_H__
#define __UART_H__
/**
* @brief ���ڳ�ʼ��
* @param ��
* @retval ��
*/
void UART_Init();
/**
* @brief ��������
* @param  Byte ��char,���ܷ�������
* @retval ��
*/
void UART_SendByte(unsigned char Byte);
#endif