#ifndef TWI_H
#define TWI_H

#include <stdint.h>

void twi_init();
void twi_start();
void twi_write_data(uint8_t data);
void twi_stop();
#endif
