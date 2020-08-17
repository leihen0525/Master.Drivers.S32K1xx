/*
 * Drivers.S32K1xx.LPSPI.h
 *
 *  Created on: 2020年7月21日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_LPSPI_H_
#define DRIVERS_S32K1XX_LPSPI_H_

#include "Master.Stdint.h"
#include "S32K1xx.h"
#include "Drivers.S32K1xx.LPSPI.Enum.h"

int Drivers_S32K1xx_LPSPI_SET_Clock_Source(
		LPSPI_Type *P_LPSPI,
		Drivers_S32K1xx_LPSPI_Clock_Source_Type Clock_Source,
		S32K1xx_Clock_Tree_Type *Tree);

int Drivers_S32K1xx_LPSPI_SET_Clock_Enabled(
		LPSPI_Type *P_LPSPI,
		Enabled_Type Enabled);
int Drivers_S32K1xx_LPSPI_GET_Clock_Enabled(LPSPI_Type *P_LPSPI);

int Drivers_S32K1xx_LPSPI_Software_Reset(LPSPI_Type *P_LPSPI);

int Drivers_S32K1xx_LPSPI_Reset_FIFO(LPSPI_Type *P_LPSPI,bool Transmit,bool Receive);

int Drivers_S32K1xx_LPSPI_SET_Module_Enabled(LPSPI_Type *P_LPSPI,Enabled_Type Enabled);

int Drivers_S32K1xx_LPSPI_GET_Module_Enabled(LPSPI_Type *P_LPSPI);

int Drivers_S32K1xx_LPSPI_SET_Mode(LPSPI_Type *P_LPSPI,Drivers_S32K1xx_LPSPI_Mode_Type Mode);

int Drivers_S32K1xx_LPSPI_SET_Function_Enabled(
		LPSPI_Type *P_LPSPI,
		Drivers_S32K1xx_LPSPI_Function_Type Function,
		Enabled_Type Enabled);

int Drivers_S32K1xx_LPSPI_SET_Interrupt_Enabled(
		LPSPI_Type *P_LPSPI,
		Drivers_S32K1xx_LPSPI_Interrupt_Type Interrupt,
		Enabled_Type Enabled);

int Drivers_S32K1xx_LPSPI_GET_Interrupt_Flag(LPSPI_Type *P_LPSPI);

int Drivers_S32K1xx_LPSPI_Clear_Interrupt_Flag(
		LPSPI_Type *P_LPSPI,
		Drivers_S32K1xx_LPSPI_Interrupt_Type Interrupt);

int Drivers_S32K1xx_LPSPI_SET_Clock_Configuration_Sub(
		LPSPI_Type *P_LPSPI,
		Drivers_S32K1xx_LPSPI_Clock_Configuration_Type Type,
		uint8_t DATA);

int Drivers_S32K1xx_LPSPI_SET_Clock_Configuration(
		LPSPI_Type *P_LPSPI,
		uint8_t SCK_To_PCS_Delay,
		uint8_t PCS_To_SCK_Delay,
		uint8_t Between_Transfers_Delay,
		uint8_t SCK_Divider);

int Drivers_S32K1xx_LPSPI_SET_PIN_Config(LPSPI_Type *P_LPSPI,Drivers_S32K1xx_LPSPI_PIN_Config_Type Pin);

int Drivers_S32K1xx_LPSPI_SET_FIFO_Watermark(LPSPI_Type *P_LPSPI,uint8_t Receive,uint8_t Transmit);

int Drivers_S32K1xx_LPSPI_SET_Transmit_Command(
		LPSPI_Type *P_LPSPI,
		bool CPOL,
		bool CPHA,
		uint8_t Prescaler,
		Drivers_S32K1xx_LPSPI_Peripheral_Chip_Select_Type Peripheral_Chip_Select,
		bool LSB_First,
		bool Byte_Swap,
		Enabled_Type Continuous_Transfer,
		bool Continuing_Command,
		bool Receive_Mask,
		bool Transmit_Mask,
		Drivers_S32K1xx_LPSPI_Transfer_Width_Type Transfer_Width,
		uint16_t Frame_Size);

int Drivers_S32K1xx_LPSPI_SET_DATA(LPSPI_Type *P_LPSPI,uint32_t DATA);

int Drivers_S32K1xx_LPSPI_GET_DATA(LPSPI_Type *P_LPSPI,uint32_t *DATA);

int Drivers_S32K1xx_LPSPI_GET_FIFO_TX_COUNT(LPSPI_Type *P_LPSPI);
int Drivers_S32K1xx_LPSPI_GET_FIFO_RX_COUNT(LPSPI_Type *P_LPSPI);


#endif /* DRIVERS_S32K1XX_LPSPI_H_ */
