/*
 * flash.h
 *
 * Created: 9/7/2023 5:50:04 PM
 *  Author: abdelrhman mattar
 */ 


#ifndef FLASH_H_
#define FLASH_H_


#define IDLE 0
#define BUSY 1
#define False 0
#define True 1
#define F_CPU 8000000ul
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/boot.h>
#include <avr/pgmspace.h>
#include <util/crc16.h>
#include <util/delay.h>

#include "std_macros.h"
#include "EEPROM_driver.h"
#include "UART.h"

#define APP_SECTION	0
#define BLD_SECTION	1

#define Code_VALID_ADDRESS 0X01
#define Req_VALID_ADDRESS 0X02

typedef enum connect_state
{
	waiting_ProgrammingSession=0,
	waiting_DownloadRequest=1,
	waiting_TransferData=2,
	waiting_TransferExit=3,
	waiting_CheckCRC=4
}connect_state;
static connect_state download_state;



#define SREG *(uint8_t *)(0x005f)
#define SESSION_CONTROL			(0X10)
#define PROGRAMMING_SESSION	    (0x03)
#define DOWNLOAD_REQUEST		(0X34)
#define TRANSFER_DATA			(0X36)
#define TRANSFER_EXIT			(0X37)
#define CHECK_CRC				(0X31)
#define MAX_CODE_SIZE			(0X1C00)
#define PAGE_SIZE				(128) /*64 word*/




uint8_t CRC_CHECK_FLASH(uint16_t start,uint16_t end_,uint16_t crc);
void boot_program_page(uint16_t page , uint8_t *buf);
void RX_HANDLE(void);
void REQ_HANDLE(void);
void Req_Notification(uint8_t * req , uint8_t len);
void Flash_MainTask(void);
void save_state(void);
void APP_vidMoveIVT(uint8_t u8Section);


#endif /* FLASH_H_ */