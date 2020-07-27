/*
 * Drivers.S32K1xx.UART.h
 *
 *  Created on: 2020年6月19日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_UART_H_
#define DRIVERS_S32K1XX_UART_H_

#include "__Drivers.S32K1xx.UART.Struct.h"

int Drivers_S32K1xx_UART_Setup(void);

int Drivers_S32K1xx_UART_Open(void *Device_Args,int Mode);
int Drivers_S32K1xx_UART_Close(void *Device_Args);
int Drivers_S32K1xx_UART_Read(void *Device_Args,long OffSet_Pos, void *Buffer, unsigned long Size,long TimeOut);
int Drivers_S32K1xx_UART_Write(void *Device_Args,long OffSet_Pos, const void *Buffer, unsigned long Size,long TimeOut);
int Drivers_S32K1xx_UART_Control(void *Device_Args,int Cmd, unsigned long Args);

int Drivers_S32K1xx_UART_GET_Count(void *Device_Args);
void Drivers_S32K1xx_UART_IRQ(void *Args,int IRQ_Index);

//---------------------------------------------------------------------------------------------------------


#endif /* DRIVERS_S32K1XX_UART_H_ */
