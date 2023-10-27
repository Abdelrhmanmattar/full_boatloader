/*
 * CONNECT.c
 *
 * Created: 9/6/2023 11:21:18 PM
 *  Author: abdelrhman mattar
 */ 

#include "CONNECT.h"
static uint8_t RX_LEN;
static uint8_t RxBuffer[255];

static uint8_t IS_REQUEST=False;
static uint8_t Req_len;
static uint8_t Req_ID;
static uint8_t *Req_Data;

#define  Response_positive() UART_SEND_CHAR(Req_ID+0x40)
#define  Response_negative() UART_SEND_CHAR(0x7f)

void APP_vidMoveIVT(uint8_t u8Section)
{
	/*Move IVt to Application [starting from 0]*/
	if(u8Section == APP_SECTION)
	{
		/* Enable change of interrupt vectors */
		GICR = (1<<IVCE);
		/* Move interrupts to Application section */
		CLR_BIT(GICR,IVSEL);
	}

	/*Move IVt to Bootloader [starting after end of app section]*/
	else
	{
		/* Enable change of interrupt vectors */
		GICR = (1<<IVCE);
		/* Move interrupts to boot Flash section */
		GICR = (1<<IVSEL);
	}
}



void Flash_MainTask(void)
{
	static uint8_t page_number=0;
	static uint16_t code_size=0 , recevied_code=0;
	uint8_t req_valid=False;
	if (IS_REQUEST==True)
	{
		switch (Req_ID)
		{
			case SESSION_CONTROL:
			{
				SET_BIT(PORTA,0);
				if (Req_Data[0]==PROGRAMMING_SESSION && Req_len==2 && download_state==waiting_ProgrammingSession)
				{
					Response_positive();
					download_state++;
				}
				else
				{
					download_state==waiting_ProgrammingSession;
					Response_negative();
				}
			}break;
			
			case DOWNLOAD_REQUEST:
			{
				SET_BIT(PORTA,1);
				if (download_state==waiting_DownloadRequest && Req_len==3 )
				{
					code_size=(Req_Data[0]<<8) | Req_Data[1];
					//if (code_size < MAX_CODE_SIZE )
					//{
						Response_positive();
						download_state=waiting_TransferData;
						req_valid=True;
					//}
				}
				if (req_valid==False)
				{
					download_state==waiting_ProgrammingSession;
					Response_negative();
				}
			}break;
			case TRANSFER_DATA:
			{
				SET_BIT(PORTA,2);
				if (download_state==waiting_TransferData && Req_len == PAGE_SIZE+1)
				{
					boot_program_page(page_number++,&Req_Data[0]);
					Response_positive();
					recevied_code+=PAGE_SIZE;
					if (recevied_code>=code_size)
						download_state=waiting_TransferExit;
				}
				else
				{
					download_state==waiting_ProgrammingSession;
					Response_negative();
					page_number=0;
				}
			}break;
			
			case TRANSFER_EXIT:
			{
				SET_BIT(PORTA,3);
				if (download_state==waiting_TransferExit && Req_len==1)
				{
					Response_positive();
					download_state=waiting_CheckCRC;
				}
				else
				{
					download_state==waiting_ProgrammingSession;
					Response_negative();
				}
				page_number=0;
				
			}break;
			
			case CHECK_CRC:
			{
				SET_BIT(PORTB,0);
				uint16_t recevied_CRC;
				uint8_t is_valid;
				if (download_state==waiting_CheckCRC && Req_len==3)
				{
					recevied_CRC=(Req_Data[0]<<8)|Req_Data[1];
					is_valid=CRC_CHECK_FLASH(0,code_size,recevied_CRC);
					if (is_valid)
					{
						Response_positive();
						EEPROM_write(Code_VALID_ADDRESS,1);						
						_delay_ms(100);
						asm("jmp 0");
					}
					else
					{
						Response_negative();
					}
				}
				else {Response_negative();}
				download_state=waiting_ProgrammingSession;
				page_number=0;
			}break;
			default:
			{
				Response_negative();
				download_state = waiting_ProgrammingSession;
				page_number=0;
			}break;
		}
	}
	
	IS_REQUEST=False;
}



void save_state(void)
{
	static unsigned short add_x=0;
	EEPROM_write(add_x,download_state);
}
void boot_program_page(uint16_t page , uint8_t *buf)
{
	uint16_t sreg = SREG;
	cli();
	uint32_t address;
	address=page*PAGE_SIZE;
	boot_page_erase_safe(address);
	uint16_t word;
	for (uint8_t i=0;i<PAGE_SIZE;i+=2)
	{
		word=*buf;
		buf++;
		word+= (*buf++)<<8;
		boot_page_fill_safe(address+i,word);
	}
	boot_page_write_safe(address);
	boot_rww_enable_safe();
	SREG=sreg;
}


uint8_t CRC_CHECK_FLASH(uint16_t start,uint16_t end_,uint16_t crc)
{
	uint16_t address , CRC_16=0XFFFF;uint8_t byte;
	for (address=start;address<end_;address++)
	{
		byte=pgm_read_byte(address);
		CRC_16=_crc16_update(CRC_16,byte);
	}
	if(crc == CRC_16)return 1;
	else return 0;
}


void RX_HANDLE(void)
{
	static uint8_t index=0;
	static uint8_t state =IDLE;
	//static unsigned short addr_x=10;
	uint8_t x = UART_RECIEVE8();
	//EEPROM_write(addr_x++,x);
	//EEPROM_write(addr_x++,download_state);
	if (state == IDLE)
	{
		RX_LEN=x;
		state=BUSY;
	}
	else
	{
		RxBuffer[index++]=x;
		if (index==RX_LEN)
		{
			index=0;
			state=IDLE;
			Req_Notification(RxBuffer,RX_LEN);
		}
	}
	CLR_BIT(UCSRA ,RXC);
}
void REQ_HANDLE(void)
{
	PORTB|=2;
	Req_ID=SESSION_CONTROL;
	Response_positive();
	download_state=waiting_DownloadRequest;
}
void Req_Notification(uint8_t * req , uint8_t len)
{
	//static unsigned short addr_x=0;
	IS_REQUEST=True;
	Req_ID=req[0];
	Req_len = len;
	Req_Data = &req[1];
	//EEPROM_write(addr_x++,Req_ID);
}