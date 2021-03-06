/*
 * __Drivers.S32K1xx.ADC.Enum.h
 *
 *  Created on: 2020年8月5日
 *      Author: Master.HE
 */

#ifndef __DRIVERS_S32K1XX_ADC_ENUM_H_
#define __DRIVERS_S32K1XX_ADC_ENUM_H_

typedef enum
{
															//ADC_CFG1[ADICLK] PCC_ADCn[PCS]
	Drivers_S32K1xx_ADC_Clock_Source_ALTCLK1_Disable		=(0<<3)|(0<<0),
	Drivers_S32K1xx_ADC_Clock_Source_ALTCLK1_SOSCDIV2_CLK	=(0<<3)|(1<<0),
	Drivers_S32K1xx_ADC_Clock_Source_ALTCLK1_SIRCDIV2_CLK	=(0<<3)|(2<<0),
	Drivers_S32K1xx_ADC_Clock_Source_ALTCLK1_FIRCDIV2_CLK	=(0<<3)|(3<<0),
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Drivers_S32K1xx_ADC_Clock_Source_ALTCLK1_SPLLDIV2_CLK	=(0<<3)|(6<<0),
#endif

	Drivers_S32K1xx_ADC_Clock_Source_ALTCLK2				=(1<<3)|(0<<0),
	Drivers_S32K1xx_ADC_Clock_Source_ALTCLK3				=(2<<3)|(0<<0),
	Drivers_S32K1xx_ADC_Clock_Source_ALTCLK4				=(3<<3)|(0<<0),

}Drivers_S32K1xx_ADC_Clock_Source_Type;

#endif /* __DRIVERS_S32K1XX_ADC_ENUM_H_ */
