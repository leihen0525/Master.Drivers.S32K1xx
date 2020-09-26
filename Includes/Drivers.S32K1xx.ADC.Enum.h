/*
 * Drivers.S32K1xx.ADC.Enum.h
 *
 *  Created on: 2020年8月5日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_ADC_ENUM_H_
#define DRIVERS_S32K1XX_ADC_ENUM_H_

typedef enum
{
	Drivers_S32K1xx_ADC_Open_Mode_Clock_Source_Mask						=0x0000FFFF,

	Drivers_S32K1xx_ADC_Open_Mode_Clock_Source_ALTCLK1_Disable			=(0<<3)|(0<<0),
	Drivers_S32K1xx_ADC_Open_Mode_Clock_Source_ALTCLK1_SOSCDIV2_CLK		=(0<<3)|(1<<0),
	Drivers_S32K1xx_ADC_Open_Mode_Clock_Source_ALTCLK1_SIRCDIV2_CLK		=(0<<3)|(2<<0),
	Drivers_S32K1xx_ADC_Open_Mode_Clock_Source_ALTCLK1_FIRCDIV2_CLK		=(0<<3)|(3<<0),
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Drivers_S32K1xx_ADC_Open_Mode__Clock_Source_ALTCLK1_SPLLDIV2_CLK	=(0<<3)|(6<<0),
#endif

	Drivers_S32K1xx_ADC_Open_Mode_Clock_Source_ALTCLK2					=(1<<3)|(0<<0),
	Drivers_S32K1xx_ADC_Open_Mode_Clock_Source_ALTCLK3					=(2<<3)|(0<<0),
	Drivers_S32K1xx_ADC_Open_Mode_Clock_Source_ALTCLK4					=(3<<3)|(0<<0),

	//Drivers_S32K1xx_ADC_Open_Mode_Operate_Mask							=0x00010000,


}Drivers_S32K1xx_ADC_Open_Mode_Type;

typedef enum
{
	Drivers_S32K1xx_ADC_Cmd_Mask										=0xFF00,
	Drivers_S32K1xx_ADC_Cmd_Read_Channel_DATA							=1<<8,


}Drivers_S32K1xx_ADC_Cmd_Type;

typedef enum
{
	Drivers_S32K1xx_ADC_Channel_External_0								=0x00,
	Drivers_S32K1xx_ADC_Channel_External_1,
	Drivers_S32K1xx_ADC_Channel_External_2,
	Drivers_S32K1xx_ADC_Channel_External_3,
	Drivers_S32K1xx_ADC_Channel_External_4,
	Drivers_S32K1xx_ADC_Channel_External_5,
	Drivers_S32K1xx_ADC_Channel_External_6,
	Drivers_S32K1xx_ADC_Channel_External_7,
	Drivers_S32K1xx_ADC_Channel_External_8,
	Drivers_S32K1xx_ADC_Channel_External_9,
	Drivers_S32K1xx_ADC_Channel_External_10,
	Drivers_S32K1xx_ADC_Channel_External_11,
	Drivers_S32K1xx_ADC_Channel_External_12,
	Drivers_S32K1xx_ADC_Channel_External_13,
	Drivers_S32K1xx_ADC_Channel_External_14,
	Drivers_S32K1xx_ADC_Channel_External_15,

	Drivers_S32K1xx_ADC_Channel_Internal_0								=0x15,
	Drivers_S32K1xx_ADC_Channel_Internal_1,
	Drivers_S32K1xx_ADC_Channel_Internal_2,

	Drivers_S32K1xx_ADC_Channel_Band_Gap								=0x1B,
	Drivers_S32K1xx_ADC_Channel_Internal_3,
	Drivers_S32K1xx_ADC_Channel_V_REFSH,
	Drivers_S32K1xx_ADC_Channel_V_REFSL,

	Drivers_S32K1xx_ADC_Channel_External_16								=0x20,
	Drivers_S32K1xx_ADC_Channel_External_17,
	Drivers_S32K1xx_ADC_Channel_External_18,
	Drivers_S32K1xx_ADC_Channel_External_19,
	Drivers_S32K1xx_ADC_Channel_External_20,
	Drivers_S32K1xx_ADC_Channel_External_21,
	Drivers_S32K1xx_ADC_Channel_External_22,
	Drivers_S32K1xx_ADC_Channel_External_23,
	Drivers_S32K1xx_ADC_Channel_External_24,
	Drivers_S32K1xx_ADC_Channel_External_25,
	Drivers_S32K1xx_ADC_Channel_External_26,
	Drivers_S32K1xx_ADC_Channel_External_27,
	Drivers_S32K1xx_ADC_Channel_External_28,
	Drivers_S32K1xx_ADC_Channel_External_29,
	Drivers_S32K1xx_ADC_Channel_External_30,
	Drivers_S32K1xx_ADC_Channel_External_31,

	Drivers_S32K1xx_ADC_Channel_Disabled								=0x3F,
}Drivers_S32K1xx_ADC_Channel_Type;

#endif /* DRIVERS_S32K1XX_ADC_ENUM_H_ */
