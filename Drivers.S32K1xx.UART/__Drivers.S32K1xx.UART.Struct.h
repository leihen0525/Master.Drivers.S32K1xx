/*
 * __Drivers.S32K1xx.UART.Struct.h
 *
 *  Created on: 2020年7月9日
 *      Author: Master.HE
 */

#ifndef __DRIVERS_S32K1XX_UART_STRUCT_H_
#define __DRIVERS_S32K1XX_UART_STRUCT_H_

#include "Master.Stdint.h"

#include "S32K1xx.h"

#include "Drivers.S32K1xx.UART.Define.h"

#include "Library/Library.FIFO.Struct.h"


typedef struct
{
	struct
	{
		S32K1xx_Clock_Source_Type *Source;
		S32K1xx_Clock_Tree_Type *Tree;
	}Clock;

	struct
	{
		bool Open;
		int Operate;

		int Interrupt_Flag_Event_Flag_Group;

		//int Tx_Event_Flag;

		Library_FIFO_2Byte_DATA_Type TX_FIFO;
		Library_FIFO_2Byte_DATA_Type RX_FIFO;

		//uint16_t Temp_Tx_DATA;
		bool Tx_Ing;

	}UART[LPUART_INSTANCE_COUNT];

}Drivers_S32K1xx_UART_DATA_Type;

#endif /* __DRIVERS_S32K1XX_UART_STRUCT_H_ */
