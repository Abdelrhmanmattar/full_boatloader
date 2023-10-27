/*
 * full_boatloader.c
 *
 * Created: 9/6/2023 10:24:19 PM
 * Author : abdelrhman mattar
 */ 

#include <avr/io.h>
//#include <avr/interrupt.h>
#define F_CPU 8000000ul
#include "CONNECT.h"

//static uint8_t RX_LEN;
//static uint8_t RxBuffer[255];

int main(void)
{
    /* Replace with your application code */
	int8_t valid_app,valid_req;
	DDRA=0XFF;DDRB=0xff;
	valid_app=(int8_t)EEPROM_read(Code_VALID_ADDRESS);
	valid_req=(int8_t)EEPROM_read(Req_VALID_ADDRESS);
	
	if ( (valid_app!=1) || (valid_req==1) )
	{
		UART_Vinit(9600);	
		if(valid_req==1)
		{
			EEPROM_write(Req_VALID_ADDRESS,0);
			REQ_HANDLE();
		}
		while(1)
		{
			RX_HANDLE();
			Flash_MainTask();
		}
	}
	else asm("jmp 0");
}

/*
ISR(USART_RXC_vect)
{
	static uint8_t index=0;
	static uint8_t state =IDLE;
	if (state == IDLE)
	{
		RX_LEN=UDR;
		state=BUSY;
	}
	else
	{
		RxBuffer[index++]=UDR;
		if (index==RX_LEN)
		{
			index=0;
			state=IDLE;
			Req_Notification(RxBuffer,RX_LEN);
		}
	}
}*/