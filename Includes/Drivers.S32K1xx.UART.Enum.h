/*
 * Drivers.S32K1xx.UART.Enum.h
 *
 *  Created on: 2020年7月10日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_UART_ENUM_H_
#define DRIVERS_S32K1XX_UART_ENUM_H_

typedef enum
{
	Drivers_S32K1xx_UART_Cmd_Mask									=0xFFFF0000,

	//Drivers_S32K1xx_UART_Cmd_Software_Reset							=1<<16,

	Drivers_S32K1xx_UART_Cmd_Init									=2<<16,

	Drivers_S32K1xx_UART_Cmd_SET_LIN_Break_Detection_Enabled		=3<<16,

	Drivers_S32K1xx_UART_Cmd_SET_Rx_Buff_Flush						=4<<16,




	Drivers_S32K1xx_UART_Cmd_GET_LIN_Break_Detection_Interrupt_Flag	=8<<16,


	//Drivers_S32K1xx_UART_Cmd_SET_Baud_Rate						=3<<16,

	//Drivers_S32K1xx_UART_Cmd_SET_Function_Enabled					=3<<16,

	//Drivers_S32K1xx_UART_Cmd_SET_Interrupt_Enabled				=4<<16,



	//Drivers_S32K1xx_UART_Cmd_GET_Interrupt_Flag					=10<<16,

}Drivers_S32K1xx_UART_Cmd_Type;

typedef enum
{
	Drivers_S32K1xx_UART_Open_Mode_Clock_Source_Mask					=0x0000FFFF,

	Drivers_S32K1xx_UART_Open_Mode_Clock_Source_SOSCDIV2_CLK			=1,
	Drivers_S32K1xx_UART_Open_Mode_Clock_Source_SIRCDIV2_CLK			=2,
	Drivers_S32K1xx_UART_Open_Mode_Clock_Source_FIRCDIV2_CLK			=3,

#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Drivers_S32K1xx_UART_Open_Mode_Clock_Source_SPLLDIV2_CLK			=6,
#endif


	Drivers_S32K1xx_UART_Open_Mode_Operate_Mask							=0x00010000,

	Drivers_S32K1xx_UART_Open_Mode_Operate_UART							=0<<16,
	Drivers_S32K1xx_UART_Open_Mode_Operate_LIN							=1<<16,

}Drivers_S32K1xx_UART_Open_Mode_Type;

/*
typedef enum
{
	Drivers_S32K1xx_UART_OffSet_Pos_8BIT					=0,
	Drivers_S32K1xx_UART_OffSet_Pos_16BIT,

	Drivers_S32K1xx_UART_OffSet_Pos_End,
}Drivers_S32K1xx_UART_OffSet_Pos_Type;
*/

typedef enum
{
	Drivers_S32K1xx_UART_Bit_Mode_Select_7BitTo9Bit			=0,
	Drivers_S32K1xx_UART_Bit_Mode_Select_10Bit,

	Drivers_S32K1xx_UART_Bit_Mode_Select_End,
}Drivers_S32K1xx_UART_Bit_Mode_Select_Type;

typedef enum
{
	Drivers_S32K1xx_UART_Stop_Bit_Select_OneStopBit			=0,
	Drivers_S32K1xx_UART_Stop_Bit_Select_TwoStopBit,

	Drivers_S32K1xx_UART_Stop_Bit_Select_End,
}Drivers_S32K1xx_UART_Stop_Bit_Select_Type;

#endif /* DRIVERS_S32K1XX_UART_ENUM_H_ */
