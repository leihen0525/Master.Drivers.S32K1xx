/*
 * Drivers.S32K1xx.SPI.Struct.h
 *
 *  Created on: 2020年7月22日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_SPI_STRUCT_H_
#define DRIVERS_S32K1XX_SPI_STRUCT_H_

#include "Master.Stdint.h"

typedef struct
{
	//uint32_t Baud_Rate_Kbps						:14;
	uint32_t Pin_Config							:2;
	//uint32_t SCK_Divider						:8;
	uint32_t Mode								:1;
}Drivers_S32K1xx_SPI_Init_Type;

typedef struct
{
	uint32_t SCK_To_PCS_Delay					:8;
	uint32_t PCS_To_SCK_Delay					:8;
	uint32_t Between_Transfers_Delay			:8;
	uint32_t SCK_Divider						:8;
}Drivers_S32K1xx_SPI_Clock_Config_Type;

typedef struct
{
	uint32_t Baud_Rate_kbps						:12;

	uint32_t CPOL								:1;
	uint32_t CPHA								:1;
	uint32_t LSB_First							:1;

	uint32_t Size								:8;

	uint8_t *Tx_DATA;
	uint8_t *Rx_DATA;
	//uint8_t Tx_Size;
	//uint8_t Rx_Size;

	int32_t TimeOut;
}Drivers_S32K1xx_SPI_Transmit_Cmd_Type;

#endif /* DRIVERS_S32K1XX_SPI_STRUCT_H_ */
