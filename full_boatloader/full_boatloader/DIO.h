/*
 * DIO.h
 *
 * Created: 1/28/2023 3:20:22 PM
 *  Author: abdelrhman mattar
 */ 


#ifndef DIO_H_
#define DIO_H_
#include <stdio.h>
void dio_setpin(char pin,int8_t num,int8_t value);
void dio_writepin(char pin,int8_t num,int8_t value);
void dio_toglepin(char pin,int8_t num);
unsigned char dio_readpin(char pin,int8_t num);
void dio_setport(char port,int8_t value);
void dio_writeport(char port,int8_t value);
unsigned char dio_readport(char port);
void dio_togleport(char pin);

void DIO_vconnectpullup(char portname ,char pinnumber, char connect_pullup);
void write_low_nibble(unsigned char portname,unsigned char value);
void write_high_nibble(unsigned char portname,unsigned char value);

#endif /* DIO_H_ */