/*
 * Drivers.S32K1xx.SPI.h
 *
 *  Created on: 2020年7月19日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_SPI_H_
#define DRIVERS_S32K1XX_SPI_H_

int Drivers_S32K1xx_SPI_Setup(void);
int Drivers_S32K1xx_SPI_Open(void *Device_Args,int Mode);
int Drivers_S32K1xx_SPI_Close(void *Device_Args);
int Drivers_S32K1xx_SPI_Control(void *Device_Args,int Cmd, unsigned long Args);

int Drivers_S32K1xx_SPI_GET_Count(void *Device_Args);
void Drivers_S32K1xx_SPI_IRQ(void *Args,int IRQ_Index);

#endif /* DRIVERS_S32K1XX_SPI_H_ */
