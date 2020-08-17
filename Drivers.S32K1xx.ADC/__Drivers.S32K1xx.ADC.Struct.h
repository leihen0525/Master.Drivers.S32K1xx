/*
 * __Drivers.S32K1xx.ADC.Struct.h
 *
 *  Created on: 2020年8月5日
 *      Author: Master.HE
 */

#ifndef __DRIVERS_S32K1XX_ADC_STRUCT_H_
#define __DRIVERS_S32K1XX_ADC_STRUCT_H_

#include "Master.Stdint.h"

#include "S32K1xx.h"


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

	}ADC[ADC_INSTANCE_COUNT];

}Drivers_S32K1xx_ADC_DATA_Type;

#endif /* __DRIVERS_S32K1XX_ADC_STRUCT_H_ */
