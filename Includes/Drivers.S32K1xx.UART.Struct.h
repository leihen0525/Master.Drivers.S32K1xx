/*
 * Drivers.S32K1xx.UART.Struct.h
 *
 *  Created on: 2020年7月15日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_UART_STRUCT_H_
#define DRIVERS_S32K1XX_UART_STRUCT_H_

#include "Master.Stdint.h"

/*
typedef struct
{
	uint16_t Mask;
	uint16_t Flag;
	int32_t Time_Out;
}Drivers_S32K1xx_UART_GET_Interrupt_Flag_Type;
*/

typedef struct
{
	uint32_t Baud_Rate_bps						:24;

	uint32_t Bit_Mode_Select					:1;
	uint32_t Stop_Bit_Select					:1;

}Drivers_S32K1xx_UART_Init_Type;

#endif /* DRIVERS_S32K1XX_UART_STRUCT_H_ */
