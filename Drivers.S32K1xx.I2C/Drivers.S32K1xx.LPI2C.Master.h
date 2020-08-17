/*
 * Drivers.S32K1xx.LPI2C.Master.h
 *
 *  Created on: 2020年7月21日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_LPI2C_MASTER_H_
#define DRIVERS_S32K1XX_LPI2C_MASTER_H_

#include "Master.Stdint.h"
#include "S32K1xx.h"
#include "Drivers.S32K1xx.LPI2C.Master.Enum.h"

int Drivers_S32K1xx_LPI2C_Master_Software_Reset(LPI2C_Type *P_LPI2C);
int Drivers_S32K1xx_LPI2C_Master_Reset_FIFO(LPI2C_Type *P_LPI2C,bool Transmit,bool Receive);
int Drivers_S32K1xx_LPI2C_Master_SET_Module_Enabled(LPI2C_Type *P_LPI2C,Enabled_Type Enabled);
int Drivers_S32K1xx_LPI2C_Master_GET_Module_Enabled(LPI2C_Type *P_LPI2C);
int Drivers_S32K1xx_LPI2C_Master_SET_Function_Enabled(
		LPI2C_Type *P_LPI2C,
		Drivers_S32K1xx_LPI2C_Master_Function_Type Function,
		Enabled_Type Enabled);
int Drivers_S32K1xx_LPI2C_Master_SET_Interrupt_Enabled(
		LPI2C_Type *P_LPI2C,
		Drivers_S32K1xx_LPI2C_Master_Interrupt_Type Interrupt,
		Enabled_Type Enabled);
int Drivers_S32K1xx_LPI2C_Master_GET_Interrupt_Flag(LPI2C_Type *P_LPI2C);
int Drivers_S32K1xx_LPI2C_Master_Clear_Interrupt_Flag(
		LPI2C_Type *P_LPI2C,
		Drivers_S32K1xx_LPI2C_Master_Interrupt_Type Interrupt);
int Drivers_S32K1xx_LPI2C_Master_SET_Clock_Configuration_0(
		LPI2C_Type *P_LPI2C,
		uint8_t Data_Valid_Delay,
		uint8_t Setup_Hold_Delay,
		uint8_t Clock_High_Period,
		uint8_t Clock_Low_Period);
int Drivers_S32K1xx_LPI2C_Master_SET_Clock_Configuration_1(
		LPI2C_Type *P_LPI2C,
		uint8_t Data_Valid_Delay,
		uint8_t Setup_Hold_Delay,
		uint8_t Clock_High_Period,
		uint8_t Clock_Low_Period);
int Drivers_S32K1xx_LPI2C_Master_SET_FIFO_Watermark(LPI2C_Type *P_LPI2C,uint8_t Receive,uint8_t Transmit);
int Drivers_S32K1xx_LPI2C_Master_GET_FIFO_TX_COUNT(LPI2C_Type *P_LPI2C);
int Drivers_S32K1xx_LPI2C_Master_GET_FIFO_RX_COUNT(LPI2C_Type *P_LPI2C);
int Drivers_S32K1xx_LPI2C_Master_SET_DATA(
		LPI2C_Type *P_LPI2C,
		Drivers_S32K1xx_LPI2C_Master_Command_Data_Type Command_Data,
		uint8_t DATA);
int Drivers_S32K1xx_LPI2C_Master_GET_DATA(
		LPI2C_Type *P_LPI2C,
		bool *RX_Empty,
		uint8_t *DATA);
int Drivers_S32K1xx_LPI2C_Master_SET_Pin_Low_Timeout(LPI2C_Type *P_LPI2C,uint16_t Timeout);
int Drivers_S32K1xx_LPI2C_Master_SET_Bus_Idle_Timeout(LPI2C_Type *P_LPI2C,uint16_t Timeout);
int Drivers_S32K1xx_LPI2C_Master_SET_Glitch_Filter(LPI2C_Type *P_LPI2C,uint8_t SCL,uint8_t SDA);
int Drivers_S32K1xx_LPI2C_Master_SET_PIN_Config(LPI2C_Type *P_LPI2C,Drivers_S32K1xx_LPI2C_Master_PIN_Config_Type Pin);
int Drivers_S32K1xx_LPI2C_Master_SET_Prescaler(LPI2C_Type *P_LPI2C,Drivers_S32K1xx_LPI2C_Master_Prescaler_Type Prescaler);
int Drivers_S32K1xx_LPI2C_Master_SET_Timeout_Config(LPI2C_Type *P_LPI2C,Drivers_S32K1xx_LPI2C_Master_Timeout_Config_Type Timeout_Config);
int Drivers_S32K1xx_LPI2C_Master_SET_IGNACK(LPI2C_Type *P_LPI2C,bool Ignored_NACK);
int Drivers_S32K1xx_LPI2C_Master_SET_Automatic_STOP_Generation(LPI2C_Type *P_LPI2C,bool Auto_Stop);


#endif /* DRIVERS_S32K1XX_LPI2C_MASTER_H_ */
