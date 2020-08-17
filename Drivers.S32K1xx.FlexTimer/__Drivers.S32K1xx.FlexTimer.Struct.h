/*
 * __Drivers.S32K1xx.FlexTimer.Struct.h
 *
 *  Created on: 2020年7月30日
 *      Author: Master.HE
 */

#ifndef __DRIVERS_S32K1XX_FLEXTIMER_STRUCT_H_
#define __DRIVERS_S32K1XX_FLEXTIMER_STRUCT_H_

#include "Master.Stdint.h"

#include "S32K1xx.h"

//#include "Library/Library.FIFO.Struct.h"

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
		int32_t FTM_Frequency_Hz;
		uint32_t MOD;
		//int Operate;
		//int Semaphore;

		//int Event_Flag;

		//Library_FIFO_1Byte_DATA_Type TX_FIFO;
		//Library_FIFO_1Byte_DATA_Type RX_FIFO;

		//uint8_t Tx_FIFO_Size;
		//uint8_t Rx_FIFO_Size;

	}FlexTimer[FTM_INSTANCE_COUNT];

}Drivers_S32K1xx_FlexTimer_DATA_Type;

#endif /* __DRIVERS_S32K1XX_FLEXTIMER_STRUCT_H_ */
