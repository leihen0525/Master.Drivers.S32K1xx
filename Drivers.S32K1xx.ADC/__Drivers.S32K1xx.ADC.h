/*
 * __Drivers.S32K1xx.ADC.h
 *
 *  Created on: 2020年8月5日
 *      Author: Master.HE
 */

#ifndef __DRIVERS_S32K1XX_ADC_H_
#define __DRIVERS_S32K1XX_ADC_H_

#include "Master.Stdint.h"
#include "S32K1xx.h"

#include "__Drivers.S32K1xx.ADC.Enum.h"

int Drivers_S32K1xx_ADC_SET_Clock_Source_Enabled(
		ADC_Type *P_ADC,
		Drivers_S32K1xx_ADC_Clock_Source_Type Clock_Source,
		Enabled_Type Enabled,
		S32K1xx_Clock_Tree_Type *Tree);

#endif /* __DRIVERS_S32K1XX_ADC_H_ */
