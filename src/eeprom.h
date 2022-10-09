#ifndef __EEPROM_H
#define __EEPROM_H
#include "config.h"

void iap_eeprom_write(unsigned char addr, unsigned char *buf, unsigned char len) ;
void iap_eeprom_read(unsigned char addr, unsigned char *buf, unsigned char len) ;
#endif