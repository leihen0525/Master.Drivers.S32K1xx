/*
 * Drivers.S32K1xx.LPSPI.Enum.h
 *
 *  Created on: 2020年7月22日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_LPSPI_ENUM_H_
#define DRIVERS_S32K1XX_LPSPI_ENUM_H_

typedef enum
{
	Drivers_S32K1xx_LPSPI_Clock_Source_Disable				=0,
	Drivers_S32K1xx_LPSPI_Clock_Source_SOSCDIV2_CLK			=1,
	Drivers_S32K1xx_LPSPI_Clock_Source_SIRCDIV2_CLK			=2,
	Drivers_S32K1xx_LPSPI_Clock_Source_FIRCDIV2_CLK			=3,



#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Drivers_S32K1xx_LPSPI_Clock_Source_SPLLDIV2_CLK			=6,
#endif

}Drivers_S32K1xx_LPSPI_Clock_Source_Type;

typedef enum
{
	Drivers_S32K1xx_LPSPI_Function_Debug					=1<<0,
	Drivers_S32K1xx_LPSPI_Function_Doze_Mode				=1<<1,
	Drivers_S32K1xx_LPSPI_Function_Receive_Data_DMA			=1<<2,
	Drivers_S32K1xx_LPSPI_Function_Transmit_Data_DMA		=1<<3,
	Drivers_S32K1xx_LPSPI_Function_Circular_FIFO			=1<<4,
	Drivers_S32K1xx_LPSPI_Function_Host_Request 			=1<<5,

	Drivers_S32K1xx_LPSPI_Function_Mask						=0x3F,
}Drivers_S32K1xx_LPSPI_Function_Type;

typedef enum
{
	Drivers_S32K1xx_LPSPI_Interrupt_Data_Match				=1<<0,
	Drivers_S32K1xx_LPSPI_Interrupt_Receive_Error			=1<<1,
	Drivers_S32K1xx_LPSPI_Interrupt_Transmit_Error			=1<<2,
	Drivers_S32K1xx_LPSPI_Interrupt_Transfer_Complete		=1<<3,
	Drivers_S32K1xx_LPSPI_Interrupt_Frame_Complete			=1<<4,
	Drivers_S32K1xx_LPSPI_Interrupt_Word_Complete 			=1<<5,
	Drivers_S32K1xx_LPSPI_Interrupt_Receive_Data			=1<<6,
	Drivers_S32K1xx_LPSPI_Interrupt_Transmit_Data 			=1<<7,
	Drivers_S32K1xx_LPSPI_Interrupt_Busy					=1<<8,

	Drivers_S32K1xx_LPSPI_Interrupt_SET_Mask				=0xFF,
	Drivers_S32K1xx_LPSPI_Interrupt_Clear_Mask				=0x3F,
}Drivers_S32K1xx_LPSPI_Interrupt_Type;

typedef enum
{
	Drivers_S32K1xx_LPSPI_Clock_Configuration_Delay_SCK_To_PCS				=0,
	Drivers_S32K1xx_LPSPI_Clock_Configuration_Delay_PCS_To_SCK,
	Drivers_S32K1xx_LPSPI_Clock_Configuration_Delay_Between_Transfers,

	Drivers_S32K1xx_LPSPI_Clock_Configuration_SCK_Divider,

	Drivers_S32K1xx_LPSPI_Clock_Configuration_End,
}Drivers_S32K1xx_LPSPI_Clock_Configuration_Type;

typedef enum
{
	Drivers_S32K1xx_LPSPI_PIN_Config_SIN_Input_And_SOUT_Output				=0,
	Drivers_S32K1xx_LPSPI_PIN_Config_SIN_Both_InputOuput,
	Drivers_S32K1xx_LPSPI_PIN_Config_SOUT_Both_InputOuput,
	Drivers_S32K1xx_LPSPI_PIN_Config_SOUT_Input_And_SIN_Output,

	Drivers_S32K1xx_LPSPI_PIN_Config_End,
}Drivers_S32K1xx_LPSPI_PIN_Config_Type;

#endif /* DRIVERS_S32K1XX_LPSPI_ENUM_H_ */
