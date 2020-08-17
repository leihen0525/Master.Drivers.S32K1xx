/*
 * Drivers.S32K1xx.FlexTimer.Struct.h
 *
 *  Created on: 2020年7月30日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_FLEXTIMER_STRUCT_H_
#define DRIVERS_S32K1XX_FLEXTIMER_STRUCT_H_

#include "Master.Stdint.h"

typedef struct
{
	uint32_t Frequency_Hz						:26;

	//uint32_t Prescale							:3;

	uint32_t									:3;

}Drivers_S32K1xx_FlexTimer_Init_Type;

typedef struct
{
	uint32_t Enabled							:1;


}Drivers_S32K1xx_FlexTimer_CH_Config_Type;

#endif /* DRIVERS_S32K1XX_FLEXTIMER_STRUCT_H_ */
