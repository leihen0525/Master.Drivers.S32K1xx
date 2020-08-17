/*
 * Drivers.S32K1xx.I2C.Struct.h
 *
 *  Created on: 2020年7月27日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_I2C_STRUCT_H_
#define DRIVERS_S32K1XX_I2C_STRUCT_H_

#include "Master.Stdint.h"


typedef struct
{
	uint32_t Baud_Rate							:2;
	//uint32_t Pin_Config							:2;
	//uint32_t SCK_Divider						:8;
	//uint32_t Mode								:1;
}Drivers_S32K1xx_I2C_Master_Init_Type;


typedef struct
{
	uint32_t Slave_Address_10Bit				:1;
	uint32_t Slave_Address_1st					:7;

	uint32_t Slave_Address_2nd					:8;
	uint32_t Read								:1;

	uint32_t Size								:6;
	uint32_t RepeatedSize						:6;

	uint32_t RepeatedSTART						:1;
	uint32_t RepeatedRead						:1;

	uint8_t *DATA;
	uint8_t *RepeatedDATA;

	int32_t TimeOut;
}Drivers_S32K1xx_I2C_Master_Transmit_Cmd_Type;

#endif /* DRIVERS_S32K1XX_I2C_STRUCT_H_ */
