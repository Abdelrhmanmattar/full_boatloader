

#ifndef EEPROM_DRIVER_H_
#define EEPROM_DRIVER_H_

void EEPROM_write(unsigned short address, unsigned char data );
unsigned char EEPROM_read( unsigned short address );

#endif /* EEPROM_DRIVER_H_ */