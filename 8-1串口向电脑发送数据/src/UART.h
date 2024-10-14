#ifndef __UART_H__
#define __UART_H__
/**
* @brief 串口初始化
* @param 无
* @retval 无
*/
void UART_Init();
/**
* @brief 发送数据
* @param  Byte ：char,接受发送内容
* @retval 无
*/
void UART_SendByte(unsigned char Byte);
#endif