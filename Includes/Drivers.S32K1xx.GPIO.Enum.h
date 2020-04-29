/*
 * Drivers.S32K1xx.GPIO.Enum.h
 *
 *  Created on: 2020年3月10日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_GPIO_ENUM_H_
#define DRIVERS_S32K1XX_GPIO_ENUM_H_

typedef enum
{
	Drivers_S32K1xx_GPIO_Option_Pull_None						= 0,	/*!< No pull up/down */
	Drivers_S32K1xx_GPIO_Option_Pull_Down						= 1,	/*!< Pull down */
	Drivers_S32K1xx_GPIO_Option_Pull_Up							= 2,	/*!< Pull up */
	Drivers_S32K1xx_GPIO_Option_Pull_End,
}Drivers_S32K1xx_GPIO_Option_Pull_Type;

typedef enum
{
	Drivers_S32K1xx_GPIO_Option_Interrupt_Config_Disabled								=0,
	Drivers_S32K1xx_GPIO_Option_Interrupt_Config_ISF_Flag_DMA_Request_On_Rising_Edge	=1,
	Drivers_S32K1xx_GPIO_Option_Interrupt_Config_ISF_Flag_DMA_Request_On_Falling_Edge	=2,
	Drivers_S32K1xx_GPIO_Option_Interrupt_Config_ISF_Flag_DMA_Request_On_Either_Edge	=3,

	Drivers_S32K1xx_GPIO_Option_Interrupt_Config_ISF_Flag_Interrupt_When_Logic_0		=8,
	Drivers_S32K1xx_GPIO_Option_Interrupt_Config_ISF_Flag_Interrupt_On_Rising_Edge		=9,
	Drivers_S32K1xx_GPIO_Option_Interrupt_Config_ISF_Flag_Interrupt_On_Falling_Edge		=10,
	Drivers_S32K1xx_GPIO_Option_Interrupt_Config_ISF_Flag_Interrupt_On_Either_Edge		=11,
	Drivers_S32K1xx_GPIO_Option_Interrupt_Config_ISF_Flag_Interrupt_when_Logic_1		=12,

}Drivers_S32K1xx_GPIO_Option_Interrupt_Config_Type;

typedef enum
{

	Drivers_S32K1xx_GPIO_Option_MUX_Control_Alternative_0_Pin_Disabled_Analog			=0,
	Drivers_S32K1xx_GPIO_Option_MUX_Control_Alternative_1_GPIO,
	Drivers_S32K1xx_GPIO_Option_MUX_Control_Alternative_2,
	Drivers_S32K1xx_GPIO_Option_MUX_Control_Alternative_3,
	Drivers_S32K1xx_GPIO_Option_MUX_Control_Alternative_4,
	Drivers_S32K1xx_GPIO_Option_MUX_Control_Alternative_5,
	Drivers_S32K1xx_GPIO_Option_MUX_Control_Alternative_6,
	Drivers_S32K1xx_GPIO_Option_MUX_Control_Alternative_7,

}Drivers_S32K1xx_GPIO_Option_MUX_Control_Type;

typedef enum
{
	Drivers_S32K1xx_GPIO_A							=0,
	Drivers_S32K1xx_GPIO_B,
	Drivers_S32K1xx_GPIO_C,
	Drivers_S32K1xx_GPIO_D,
	Drivers_S32K1xx_GPIO_E,

	Drivers_S32K1xx_GPIO_End,
}Drivers_S32K1xx_GPIO_Type;


typedef enum
{
	Drivers_S32K1xx_GPIO_Cmd_GPIO_Mask				=0xFFFF0000,

	Drivers_S32K1xx_GPIO_Cmd_SET_Clock_Enable		=1<<16,

	Drivers_S32K1xx_GPIO_Cmd_SET_Option				=2<<16,

	Drivers_S32K1xx_GPIO_Cmd_SET_DDR				=3<<16,

	Drivers_S32K1xx_GPIO_Cmd_SET_DDR_Set			=4<<16,

	Drivers_S32K1xx_GPIO_Cmd_SET_DDR_Clear			=5<<16,

	Drivers_S32K1xx_GPIO_Cmd_SET_OUT_DATA			=6<<16,

	Drivers_S32K1xx_GPIO_Cmd_SET_OUT_DATA_Set		=7<<16,

	Drivers_S32K1xx_GPIO_Cmd_SET_OUT_DATA_Clear		=8<<16,

	Drivers_S32K1xx_GPIO_Cmd_SET_OUT_DATA_Toggle	=9<<16,

	Drivers_S32K1xx_GPIO_Cmd_SET_Input_Disable		=10<<16,

	Drivers_S32K1xx_GPIO_Cmd_SET_Input_Disable_Set	=11<<16,

	Drivers_S32K1xx_GPIO_Cmd_SET_Input_Disable_Clear=12<<16,

	Drivers_S32K1xx_GPIO_Cmd_GET_DDR				=13<<16,

	Drivers_S32K1xx_GPIO_Cmd_GET_IN_DATA			=14<<16,

	Drivers_S32K1xx_GPIO_Cmd_GET_OUT_DATA			=15<<16,


}Drivers_S32K1xx_GPIO_Cmd_Type;

#endif /* DRIVERS_S32K1XX_GPIO_ENUM_H_ */
