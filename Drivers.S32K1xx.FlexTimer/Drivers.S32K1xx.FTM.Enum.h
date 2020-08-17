/*
 * Drivers.S32K1xx.FTM.Enum.h
 *
 *  Created on: 2020年7月30日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_FTM_ENUM_H_
#define DRIVERS_S32K1XX_FTM_ENUM_H_

typedef enum
{
															//FTMn_SC[CLKS]|PCC_FLEXTMRn[PCS]|SIM_FTMOPT0[FTMnCLKSEL]
	Drivers_S32K1xx_FTM_Clock_Source_Disable0				=(0<<5)|(0<<2)|(0<<0),
	Drivers_S32K1xx_FTM_Clock_Source_SYS_CLK				=(1<<5)|(0<<2)|(0<<0),
	Drivers_S32K1xx_FTM_Clock_Source_RTC_CLK				=(2<<5)|(0<<2)|(0<<0),
	Drivers_S32K1xx_FTM_Clock_Source_TCLK0					=(3<<5)|(0<<2)|(0<<0),
	Drivers_S32K1xx_FTM_Clock_Source_TCLK1					=(3<<5)|(0<<2)|(1<<0),
	Drivers_S32K1xx_FTM_Clock_Source_TCLK2					=(3<<5)|(0<<2)|(2<<0),
	Drivers_S32K1xx_FTM_Clock_Source_Disable1				=(3<<5)|(0<<2)|(3<<0),
	Drivers_S32K1xx_FTM_Clock_Source_SOSCDIV1_CLK			=(3<<5)|(1<<2)|(0<<0),
	Drivers_S32K1xx_FTM_Clock_Source_SIRCDIV1_CLK			=(3<<5)|(2<<2)|(0<<0),
	Drivers_S32K1xx_FTM_Clock_Source_FIRCDIV1_CLK			=(3<<5)|(3<<2)|(0<<0),

#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Drivers_S32K1xx_FTM_Clock_Source_SPLLDIV1_CLK			=(3<<5)|(6<<2)|(0<<0),
#endif

}Drivers_S32K1xx_FTM_Clock_Source_Type;

typedef enum
{
	Drivers_S32K1xx_FTM_Clock_Disable						=0,
	Drivers_S32K1xx_FTM_Clock_FTM_System_Clock,
	Drivers_S32K1xx_FTM_Clock_Fixed_Frequency_Clock,
	Drivers_S32K1xx_FTM_Clock_External_Clock,

	Drivers_S32K1xx_FTM_Clock_End,
}Drivers_S32K1xx_FTM_Clock_Type;

typedef enum
{
	Drivers_S32K1xx_FTM_Channel_Null						=0,
	Drivers_S32K1xx_FTM_Channel_CH0							=(1<<0),
	Drivers_S32K1xx_FTM_Channel_CH1							=(1<<1),
	Drivers_S32K1xx_FTM_Channel_CH2							=(1<<2),
	Drivers_S32K1xx_FTM_Channel_CH3							=(1<<3),
	Drivers_S32K1xx_FTM_Channel_CH4							=(1<<4),
	Drivers_S32K1xx_FTM_Channel_CH5							=(1<<5),
	Drivers_S32K1xx_FTM_Channel_CH6							=(1<<6),
	Drivers_S32K1xx_FTM_Channel_CH7							=(1<<7),

	Drivers_S32K1xx_FTM_Channel_Mask						=0xFF,
}Drivers_S32K1xx_FTM_Channel_Type;

typedef enum
{
	Drivers_S32K1xx_FTM_Prescale_Divide_By_1				=0,
	Drivers_S32K1xx_FTM_Prescale_Divide_By_2,
	Drivers_S32K1xx_FTM_Prescale_Divide_By_4,
	Drivers_S32K1xx_FTM_Prescale_Divide_By_8,
	Drivers_S32K1xx_FTM_Prescale_Divide_By_16,
	Drivers_S32K1xx_FTM_Prescale_Divide_By_32,
	Drivers_S32K1xx_FTM_Prescale_Divide_By_64,
	Drivers_S32K1xx_FTM_Prescale_Divide_By_128,

	Drivers_S32K1xx_FTM_Prescale_End,
}Drivers_S32K1xx_FTM_Prescale_Type;

typedef enum
{
	Drivers_S32K1xx_FTM_Channels_CH01							=0,
	Drivers_S32K1xx_FTM_Channels_CH23,
	Drivers_S32K1xx_FTM_Channels_CH45,
	Drivers_S32K1xx_FTM_Channels_CH67,

	Drivers_S32K1xx_FTM_Channels_End,
}Drivers_S32K1xx_FTM_Channels_Type;

typedef enum
{
	Drivers_S32K1xx_FTM_Center_Aligned_PWM_Counter_In_Up_Counting_Mode		=0,
	Drivers_S32K1xx_FTM_Center_Aligned_PWM_Counter_In_UpDown_Counting_Mode,

	Drivers_S32K1xx_FTM_Center_Aligned_PWM_End,
}Drivers_S32K1xx_FTM_Center_Aligned_PWM_Type;

typedef enum
{
	Drivers_S32K1xx_FTM_Channel_Polarity_Active_High				=0,
	Drivers_S32K1xx_FTM_Channel_Polarity_Active_Low,

	Drivers_S32K1xx_FTM_Channel_Polarity_End,
}Drivers_S32K1xx_FTM_Channel_Polarity_Type;

typedef enum
{
																					//DECAPEN		MCOMBINE		COMBINE			CPWMS			MSB:MSA			ELSB:ELSA
	Drivers_S32K1xx_FTM_Channel_Modes_Null											=((0<<7)/*X*/	|(0<<6)/*X*/	|(0<<5)/*X*/	|(0<<4)/*X*/	|(0<<2)/*XX*/	|(0<<0)),

	Drivers_S32K1xx_FTM_Channel_Modes_InputCapture_RisingEdge_Only					=((0<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(0<<2)			|(1<<0)),
	Drivers_S32K1xx_FTM_Channel_Modes_InputCapture_FallingEdge_Only					=((0<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(0<<2)			|(2<<0)),
	Drivers_S32K1xx_FTM_Channel_Modes_InputCapture_RisingFallingEdge				=((0<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(0<<2)			|(3<<0)),

	Drivers_S32K1xx_FTM_Channel_Modes_OutputCompare_Match_Toggle					=((0<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(1<<2)			|(1<<0)),
	Drivers_S32K1xx_FTM_Channel_Modes_OutputCompare_Match_Clear						=((0<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(1<<2)			|(2<<0)),
	Drivers_S32K1xx_FTM_Channel_Modes_OutputCompare_Match_Set						=((0<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(1<<2)			|(3<<0)),

	Drivers_S32K1xx_FTM_Channel_Modes_PWM_Edge_Aligned_LowPulses					=((0<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(2<<2)/*1X*/	|(1<<0)),/*X1*/
	Drivers_S32K1xx_FTM_Channel_Modes_PWM_Edge_Aligned_HighPulses					=((0<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(2<<2)/*1X*/	|(2<<0)),

	Drivers_S32K1xx_FTM_Channel_Modes_PWM_Center_Aligned_LowPulses					=((0<<7)		|(0<<6)			|(0<<5)			|(1<<4)			|(0<<2)/*XX*/	|(1<<0)),/*X1*/
	Drivers_S32K1xx_FTM_Channel_Modes_PWM_Center_Aligned_HighPulses					=((0<<7)		|(0<<6)			|(0<<5)			|(1<<4)			|(0<<2)/*XX*/	|(2<<0)),

	Drivers_S32K1xx_FTM_Channel_Modes_PWM_Combine_LowPulses							=((0<<7)		|(0<<6)			|(1<<5)			|(0<<4)			|(0<<2)/*XX*/	|(1<<0)),/*X1*/
	Drivers_S32K1xx_FTM_Channel_Modes_PWM_Combine_HighPulses						=((0<<7)		|(0<<6)			|(1<<5)			|(0<<4)			|(0<<2)/*XX*/	|(2<<0)),

	Drivers_S32K1xx_FTM_Channel_Modes_PWM_Modified_Combine_LowPulses				=((0<<7)		|(1<<6)			|(1<<5)			|(0<<4)			|(0<<2)/*XX*/	|(1<<0)),/*X1*/
	Drivers_S32K1xx_FTM_Channel_Modes_PWM_Modified_Combine_HighPulses				=((0<<7)		|(1<<6)			|(1<<5)			|(0<<4)			|(0<<2)/*XX*/	|(2<<0)),

	Drivers_S32K1xx_FTM_Channel_Modes_Dual_Edge_Capture_OneShot_NoEdge				=((1<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(0<<2)/*X0*/	|(0<<0)),
	Drivers_S32K1xx_FTM_Channel_Modes_Dual_Edge_Capture_OneShot_RisingEdge			=((1<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(0<<2)/*X0*/	|(1<<0)),
	Drivers_S32K1xx_FTM_Channel_Modes_Dual_Edge_Capture_OneShot_FallingEdge			=((1<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(0<<2)/*X0*/	|(2<<0)),
	Drivers_S32K1xx_FTM_Channel_Modes_Dual_Edge_Capture_OneShot_RisingFallingEdge	=((1<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(0<<2)/*X0*/	|(3<<0)),


	Drivers_S32K1xx_FTM_Channel_Modes_Dual_Edge_Capture_Continuous_NoEdge			=((1<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(1<<2)/*X1*/	|(0<<0)),
	Drivers_S32K1xx_FTM_Channel_Modes_Dual_Edge_Capture_Continuous_RisingEdge		=((1<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(1<<2)/*X1*/	|(1<<0)),
	Drivers_S32K1xx_FTM_Channel_Modes_Dual_Edge_Capture_Continuous_FallingEdge		=((1<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(1<<2)/*X1*/	|(2<<0)),
	Drivers_S32K1xx_FTM_Channel_Modes_Dual_Edge_Capture_Continuous_RisingFallingEdge=((1<<7)		|(0<<6)			|(0<<5)			|(0<<4)			|(1<<2)/*X1*/	|(3<<0)),

}Drivers_S32K1xx_FTM_Channel_Modes_Type;

#endif /* DRIVERS_S32K1XX_FTM_ENUM_H_ */
