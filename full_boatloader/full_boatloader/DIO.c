/*
 * DIO.c
 *
 * Created: 1/28/2023 3:19:24 PM
 * Author : abdelrhman mattar
 */ 
#include "DIO.h"
#include "std_macros.h"
#include <avr/io.h>

void dio_setpin(char pin,int8_t num,int8_t value)
{
	switch(pin)
	{
		case 'A':
		case 'a':
			if (value)
			{
				SET_BIT(DDRA,num);
			}
			else
				CLR_BIT(DDRA,num);
				
		break;
		case 'B':
		case 'b':
		if (value)
		{
			SET_BIT(DDRB,num);
		}
		else
		CLR_BIT(DDRB,num);
		break;
		case 'C':
		case 'c':
		if (value)
		{
			SET_BIT(DDRC,num);
		}
		else
		CLR_BIT(DDRC,num);
		break;
		case 'D':
		case 'd':
		if (value)
		{
			SET_BIT(DDRD,num);
		}
		else
		CLR_BIT(DDRD,num);
		break;
		default:
			printf("error in dio_setpin");
	}
}
	
	
	
	
	
	
	
void dio_writepin(char pin,int8_t num,int8_t value)
{
	switch(pin)
	{
		case 'A':
		case 'a':
		if (value)
		{
			SET_BIT(PORTA,num);
		}
		else
		CLR_BIT(PORTA,num);
		
		break;
		case 'B':
		case 'b':
		if (value)
		{
			SET_BIT(PORTB,num);
		}
		else
		CLR_BIT(PORTB,num);
		break;
		case 'C':
		case 'c':
		if (value)
		{
			SET_BIT(PORTC,num);
		}
		else
		CLR_BIT(PORTC,num);
		break;
		case 'D':
		case 'd':
		if (value)
		{
			SET_BIT(PORTD,num);
		}
		else
		CLR_BIT(PORTD,num);
		break;
		default:
		printf("error in dio_setpin");
	}
	
}



void dio_toglepin(char pin,int8_t num)
{
	switch(pin)
	{
		case 'A':
		case 'a':
		TOG_BIT(PORTA,num);
		break;
		case 'B':
		case 'b':
		TOG_BIT(PORTB,num);
		break;
		case 'C':
		case 'c':
		TOG_BIT(PORTC,num);
		break;
		case 'D':
		case 'd':
		TOG_BIT(PORTD,num);
		break;
		default:
		printf("error in dio_setpin");
	}
	
}


unsigned char dio_readpin(char pin,int8_t num)
{
	unsigned char x;
	switch(pin)
	{
		case 'A':
		case 'a':
		x=READ_BIT(PINA,num);
		return x;
		break;
		case 'B':
		case 'b':
		x=READ_BIT(PINB,num);
		return x;
		break;
		case 'C':
		case 'c':
		x=READ_BIT(PINC,num);
		return x;
		break;
		case 'D':
		case 'd':
		x=READ_BIT(PINC,num);
		return x;
		break;
	}
}

void dio_setport(char port,int8_t value)
{
	switch(port)
	{
		case 'A':
		case 'a':
		DDRA=value;
		break;
		case 'B':
		case 'b':
		DDRB=value;
		break;
		case 'C':
		case 'c':
		DDRC=value;
		break;
		case 'D':
		case 'd':
		DDRD=value;
		break;
		default:
		printf("error in dio_setpin");
	}	
	
}

void dio_writeport(char port,int8_t value)
{
	switch(port)
	{
		case 'A':
		case 'a':
		PORTA=value;
		break;
		case 'B':
		case 'b':
		PORTB=value;
		break;
		case 'C':
		case 'c':
		PORTC=value;
		break;
		case 'D':
		case 'd':
		PORTD=value;
		break;
		default:
		printf("error in dio_setpin");
	}
	
}



unsigned char dio_readport(char port)
{
	
	unsigned char x;
	switch(port)
	{
		case 'A':
		case 'a':
		x=PINA;
		return x;
		break;
		case 'B':
		case 'b':
		x=PINB;
		return x;
		break;
		case 'C':
		case 'c':
		x=PINC;
		return x;
		break;
		case 'D':
		case 'd':
		x=PIND;
		return x;
		break;
	}
}




void dio_togleport(char pin)
{
	switch(pin)
	{
		case 'A':
		case 'a':
		PORTA^=0xff;
		break;
		case 'B':
		case 'b':
		PORTB^=0xff;
		break;
		case 'C':
		case 'c':
		PORTC^=0xff;
		break;
		case 'D':
		case 'd':
		PORTD^=0xff;
		break;
		default:
		printf("error in dio_setpin");
	}
	
}

void DIO_vconnectpullup(char portname ,char pinnumber, char connect_pullup)
{
	switch(portname)
	{
		case 'A':
		if(connect_pullup==1)
		{
			SET_BIT(PORTA,pinnumber);
		}
		else
		{
			CLR_BIT(PORTA,pinnumber);
		}
		break;
		case 'B':
		if(connect_pullup==1)
		{
			SET_BIT(PORTB,pinnumber);
		}
		else
		{
			CLR_BIT(PORTB,pinnumber);
		}
		break;
		case 'C':
		if(connect_pullup==1)
		{
			SET_BIT(PORTC,pinnumber);
			
		}
		else
		{
			CLR_BIT(PORTC,pinnumber);
		}
		break;
		case 'D':
		if(connect_pullup==1)
		{
			SET_BIT(PORTD,pinnumber);
			
		}
		else
		{
			CLR_BIT(PORTD,pinnumber);
		}
		break;
		
	}
}

void write_low_nibble(unsigned char portname,unsigned char value)
{
	value&=0x0f;
	switch(portname)
	{
		case 'A':
		PORTA&=0xf0;
		PORTA|=value;
		case 'B':
		PORTB&=0xf0;
		PORTB|=value;
		case 'C':
		PORTC&=0xf0;
		PORTC|=value;
		case 'D':
		PORTD&=0xf0;
		PORTD|=value;
	}
}

void write_high_nibble(unsigned char portname,unsigned char value)
{
	value<<=4;
	switch(portname)
	{
		case 'A':
		PORTA&=0x0f;
		PORTA|=value;
		case 'B':
		PORTB&=0x0f;
		PORTB|=value;
		case 'C':
		PORTC&=0x0f;
		PORTC|=value;
		case 'D':
		PORTD&=0x0f;
		PORTD|=value;
	}
}

