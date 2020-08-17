/*
 * Drivers.S32K1xx.FlexTimer.Enum.h
 *
 *  Created on: 2020年7月30日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_FLEXTIMER_ENUM_H_
#define DRIVERS_S32K1XX_FLEXTIMER_ENUM_H_

typedef enum
{
	Drivers_S32K1xx_FlexTimer_Cmd_Mask								=0xFFFF0000,

	Drivers_S32K1xx_FlexTimer_Cmd_Init								=2<<16,

	Drivers_S32K1xx_FlexTimer_Cmd_SET_CH_Config						=3<<16,

	Drivers_S32K1xx_FlexTimer_Cmd_SET_CH_Duty						=4<<16,

}Drivers_S32K1xx_FlexTimer_Cmd_Type;

typedef enum
{
	Drivers_S32K1xx_FlexTimer_Open_Mode_Clock_Source_Mask			=0x0000FFFF,

	Drivers_S32K1xx_FlexTimer_Open_Mode_Clock_Source_Disable0		=(0<<5)|(0<<2)|(0<<0),
	Drivers_S32K1xx_FlexTimer_Open_Mode_Clock_Source_SYS_CLK		=(1<<5)|(0<<2)|(0<<0),
	Drivers_S32K1xx_FlexTimer_Open_Mode_Clock_Source_RTC_CLK		=(2<<5)|(0<<2)|(0<<0),
	Drivers_S32K1xx_FlexTimer_Open_Mode_Clock_Source_TCLK0			=(3<<5)|(0<<2)|(0<<0),
	Drivers_S32K1xx_FlexTimer_Open_Mode_Clock_Source_TCLK1			=(3<<5)|(0<<2)|(1<<0),
	Drivers_S32K1xx_FlexTimer_Open_Mode_Clock_Source_TCLK2			=(3<<5)|(0<<2)|(2<<0),
	Drivers_S32K1xx_FlexTimer_Open_Mode_Clock_Source_Disable1		=(3<<5)|(0<<2)|(3<<0),
	Drivers_S32K1xx_FlexTimer_Open_Mode_Clock_Source_SOSCDIV1_CLK	=(3<<5)|(1<<2)|(0<<0),
	Drivers_S32K1xx_FlexTimer_Open_Mode_Clock_Source_SIRCDIV1_CLK	=(3<<5)|(2<<2)|(0<<0),
	Drivers_S32K1xx_FlexTimer_Open_Mode_Clock_Source_FIRCDIV1_CLK	=(3<<5)|(3<<2)|(0<<0),

#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Drivers_S32K1xx_FlexTimer_Open_Mode_Clock_Source_SPLLDIV1_CLK	=(3<<5)|(6<<2)|(0<<0),
#endif


	//Drivers_S32K1xx_FlexTimer_Open_Mode_Operate_Mask							=0x00010000,


}Drivers_S32K1xx_FlexTimer_Open_Mode_Type;

/*
typedef enum
{
	Drivers_S32K1xx_FlexTimer_Prescale_Divide_By_1				=0,
	Drivers_S32K1xx_FlexTimer_Prescale_Divide_By_2,
	Drivers_S32K1xx_FlexTimer_Prescale_Divide_By_4,
	Drivers_S32K1xx_FlexTimer_Prescale_Divide_By_8,
	Drivers_S32K1xx_FlexTimer_Prescale_Divide_By_16,
	Drivers_S32K1xx_FlexTimer_Prescale_Divide_By_32,
	Drivers_S32K1xx_FlexTimer_Prescale_Divide_By_64,
	Drivers_S32K1xx_FlexTimer_Prescale_Divide_By_128,

	Drivers_S32K1xx_FlexTimer_Prescale_End,
}Drivers_S32K1xx_FlexTimer_Prescale_Type;
*/
#endif /* DRIVERS_S32K1XX_FLEXTIMER_ENUM_H_ */
