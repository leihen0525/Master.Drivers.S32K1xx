/*
 * Drivers.S32K1xx.LPUART.h
 *
 *  Created on: 2020年7月8日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_LPUART_H_
#define DRIVERS_S32K1XX_LPUART_H_

#include "Master.Stdint.h"
#include "S32K1xx.h"
#include "Drivers.S32K1xx.LPUART.Enum.h"

int Drivers_S32K1xx_LPUART_SET_Clock_Source(LPUART_Type *P_LPUART,Drivers_S32K1xx_LPUART_Clock_Source_Type Clock_Source,S32K1xx_Clock_Tree_Type *Tree);
int Drivers_S32K1xx_LPUART_SET_Clock_Enabled(LPUART_Type *P_LPUART,Enabled_Type Enabled);

int Drivers_S32K1xx_LPUART_Software_Reset(LPUART_Type *P_LPUART);

int Drivers_S32K1xx_LPUART_SET_Bit_Select(
		LPUART_Type *P_LPUART,
		Drivers_S32K1xx_LPUART_Bit_Mode_Select_Type Bit_Mode,
		Drivers_S32K1xx_LPUART_Stop_Bit_Select_Type Stop_Bit);

int Drivers_S32K1xx_LPUART_SET_Baud_Rate(
		LPUART_Type *P_LPUART,
		S32K1xx_Clock_Tree_Type *Tree,
		Drivers_S32K1xx_LPUART_Oversampling_Ratio_Type Oversampling_Ratio,
		uint32_t bps);

int Drivers_S32K1xx_LPUART_SET_Function_Enabled(
		LPUART_Type *P_LPUART,
		Drivers_S32K1xx_LPUART_Function_Type Function,
		Enabled_Type Enabled);

int Drivers_S32K1xx_LPUART_SET_DATA(
		LPUART_Type *P_LPUART,
		bool Transmit_Special_Character,
		uint16_t DATA);
int Drivers_S32K1xx_LPUART_GET_DATA(
		LPUART_Type *P_LPUART,
		bool *NOISY,
		bool *PARITYE,
		bool *Frame_Error,
		bool *Receive_Buffer_Empty,
		bool *Idle_Line,
		uint16_t *DATA);

int Drivers_S32K1xx_LPUART_SET_Interrupt_Enabled(
		LPUART_Type *P_LPUART,
		Drivers_S32K1xx_LPUART_Interrupt_Type Interrupt,
		Enabled_Type Enabled);
int Drivers_S32K1xx_LPUART_GET_Interrupt_Flag(LPUART_Type *P_LPUART);
int Drivers_S32K1xx_LPUART_Clear_Interrupt_Flag(
		LPUART_Type *P_LPUART,
		Drivers_S32K1xx_LPUART_Interrupt_Type Interrupt);



#endif /* DRIVERS_S32K1XX_LPUART_H_ */
