/*
 * spi.h
 *
 * Created: 4/28/2023 1:45:01 PM
 *  Author: Speed
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "../dio/dio.h"
#include "../registers.h"
#include "../../SERVICE/bit_math.h"

void SPI_initMaster(void);
void SPI_initSlave(void);
void SPI_sendByte(u8);
u8 SPI_receiveByte(void);

#endif /* SPI_H_ */