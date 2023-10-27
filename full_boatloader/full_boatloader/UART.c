/*
 * UART.c
 *
 * Created: 6/30/2023 3:52:48 AM
 *  Author: abdelrhman mattar
 */ 
#define  F_CPU 8000000UL
#include <avr/io.h>
#include "UART.h"
#include "std_macros.h"
#include <util/delay.h>
void UART_Vinit(unsigned int baudrate)
{
	CLR_BIT(DDRD,0);
	SET_BIT(DDRD,1);
	//SET VALUE OF UBRR REGISTER
	short int data=(F_CPU>>4)/baudrate;
	data--;
	UBRRH = (unsigned char)(data >> 8);
	UBRRL = (unsigned char) data;
	
	
	SET_BIT(UCSRB ,RXEN);
	SET_BIT(UCSRB,TXEN);
	//SET_BIT(UCSRB,RXCIE);
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
}


void UART_SEND_CHAR(unsigned char DATA)
{
	while(READ_BIT(UCSRA,UDRE) == 0);
	UDR = DATA;
}



void UART_SEND_STRING(unsigned char *DATA)
{
	while(*DATA != '\0')
	{
		UART_SEND_CHAR(*DATA);
		DATA++;
		_delay_ms(2);
	}
}


char UART_RECIEVE8()
{	
	while( READ_BIT(UCSRA ,RXC) ==0);
	return (char)UDR;
}


