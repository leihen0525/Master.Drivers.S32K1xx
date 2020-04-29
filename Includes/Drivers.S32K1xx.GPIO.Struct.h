/*
 * Drivers.S32K1xx.GPIO.Struct.h
 *
 *  Created on: 2020年3月10日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_GPIO_STRUCT_H_
#define DRIVERS_S32K1XX_GPIO_STRUCT_H_

#include "Master.Stdint.h"

typedef union
{
	uint32_t DATA;
	struct
	{
		uint32_t Pull						:2;//PS/PE
		uint32_t Passive_Filter_Enable		:1;//PFE
		uint32_t Drive_Strength_Enable		:1;//DSE
		uint32_t MUX_Control				:3;//MUX
		uint32_t Lock_Register_Enable		:1;//LK
		uint32_t Interrupt_Config			:4;//IRQC
	};

}Drivers_S32K1xx_GPIO_Cmd_Option_Type;

#endif /* DRIVERS_S32K1XX_GPIO_STRUCT_H_ */
