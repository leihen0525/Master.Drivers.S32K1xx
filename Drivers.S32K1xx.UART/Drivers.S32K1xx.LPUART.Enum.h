/*
 * Drivers.S32K1xx.LPUART.Enum.h
 *
 *  Created on: 2020年7月8日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_LPUART_ENUM_H_
#define DRIVERS_S32K1XX_LPUART_ENUM_H_

typedef enum
{
	Drivers_S32K1xx_LPUART_Clock_Source_Disable					=0,
	Drivers_S32K1xx_LPUART_Clock_Source_SOSCDIV2_CLK			=1,
	Drivers_S32K1xx_LPUART_Clock_Source_SIRCDIV2_CLK			=2,
	Drivers_S32K1xx_LPUART_Clock_Source_FIRCDIV2_CLK			=3,



#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Drivers_S32K1xx_LPUART_Clock_Source_SPLLDIV2_CLK			=6,
#endif

}Drivers_S32K1xx_LPUART_Clock_Source_Type;

typedef enum
{
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_Default_16		=0,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_Reserved1,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_Reserved2,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_4,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_5,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_6,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_7,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_8,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_9,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_10,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_11,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_12,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_13,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_14,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_15,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_16,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_17,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_18,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_19,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_20,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_21,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_22,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_23,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_24,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_25,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_26,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_27,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_28,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_29,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_30,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_31,
	Drivers_S32K1xx_LPUART_Oversampling_Ratio_32,

	Drivers_S32K1xx_LPUART_Oversampling_Ratio_End,
}Drivers_S32K1xx_LPUART_Oversampling_Ratio_Type;

typedef enum
{
	Drivers_S32K1xx_LPUART_Function_Match_1						=1<<0,
	Drivers_S32K1xx_LPUART_Function_Match_2						=1<<1,
	Drivers_S32K1xx_LPUART_Function_Transmitter_DMA				=1<<2,
	Drivers_S32K1xx_LPUART_Function_Receiver_Full_DMA			=1<<3,
	Drivers_S32K1xx_LPUART_Function_LIN_Break_Detection			=1<<4,
	Drivers_S32K1xx_LPUART_Function_Transmitter					=1<<5,
	Drivers_S32K1xx_LPUART_Function_Receiver					=1<<6,
	Drivers_S32K1xx_LPUART_Function_Doze						=1<<7,
	Drivers_S32K1xx_LPUART_Function_Parity						=1<<8,
	Drivers_S32K1xx_LPUART_Function_Infrared					=1<<9,
	Drivers_S32K1xx_LPUART_Function_Receiver_Request_To_Send	=1<<10,
	Drivers_S32K1xx_LPUART_Function_Transmitter_Request_To_Send	=1<<11,
	Drivers_S32K1xx_LPUART_Function_Transmitter_Clear_To_Send	=1<<12,
	Drivers_S32K1xx_LPUART_Function_Transmit_FIFO				=1<<13,
	Drivers_S32K1xx_LPUART_Function_Receive_FIFO				=1<<14,

	Drivers_S32K1xx_LPUART_Function_Mask						=0x7FFF,
}Drivers_S32K1xx_LPUART_Function_Type;


typedef enum
{
	Drivers_S32K1xx_LPUART_Interrupt_LIN_Break_Detect			=1<<0,
	Drivers_S32K1xx_LPUART_Interrupt_RX_Input_Active_Edge		=1<<1,
	Drivers_S32K1xx_LPUART_Interrupt_Overrun					=1<<2,
	Drivers_S32K1xx_LPUART_Interrupt_Noise_Error				=1<<3,
	Drivers_S32K1xx_LPUART_Interrupt_Framing_Error				=1<<4,
	Drivers_S32K1xx_LPUART_Interrupt_Parity_Error				=1<<5,
	Drivers_S32K1xx_LPUART_Interrupt_Transmit					=1<<6,
	Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete		=1<<7,
	Drivers_S32K1xx_LPUART_Interrupt_Receiver					=1<<8,
	Drivers_S32K1xx_LPUART_Interrupt_Idle_Line					=1<<9,
	Drivers_S32K1xx_LPUART_Interrupt_Match_1					=1<<10,
	Drivers_S32K1xx_LPUART_Interrupt_Match_2					=1<<11,
	Drivers_S32K1xx_LPUART_Interrupt_Transmit_FIFO_Overflow		=1<<12,
	Drivers_S32K1xx_LPUART_Interrupt_Receive_FIFO_Underflow		=1<<13,

	Drivers_S32K1xx_LPUART_Interrupt_Mask						=0x3FFF,
}Drivers_S32K1xx_LPUART_Interrupt_Type;

typedef enum
{
	Drivers_S32K1xx_LPUART_Bit_Mode_Select_7BitTo9Bit			=0,
	Drivers_S32K1xx_LPUART_Bit_Mode_Select_10Bit,

	Drivers_S32K1xx_LPUART_Bit_Mode_Select_End,
}Drivers_S32K1xx_LPUART_Bit_Mode_Select_Type;

typedef enum
{
	Drivers_S32K1xx_LPUART_Stop_Bit_Select_OneStopBit			=0,
	Drivers_S32K1xx_LPUART_Stop_Bit_Select_TwoStopBit,

	Drivers_S32K1xx_LPUART_Stop_Bit_Select_End,
}Drivers_S32K1xx_LPUART_Stop_Bit_Select_Type;

#endif /* DRIVERS_S32K1XX_LPUART_ENUM_H_ */
