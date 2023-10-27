/*
 * UART.h
 *
 * Created: 6/30/2023 3:53:01 AM
 *  Author: abdelrhman mattar
 */ 


#ifndef UART_H_
#define UART_H_
void UART_Vinit(unsigned int baudrate);
void UART_SEND_CHAR(unsigned char DATA);
void UART_SEND_STRING(unsigned char *DATA);
char UART_RECIEVE8();
#endif /* UART_H_ */