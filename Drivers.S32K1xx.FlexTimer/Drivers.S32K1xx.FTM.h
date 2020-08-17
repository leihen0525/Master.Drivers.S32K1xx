/*
 * Drivers.S32K1xx.FTM.h
 *
 *  Created on: 2020年7月30日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_FTM_H_
#define DRIVERS_S32K1XX_FTM_H_

#include "Master.Stdint.h"
#include "S32K1xx.h"

#include "Drivers.S32K1xx.FTM.Enum.h"

int Drivers_S32K1xx_FTM_SET_Clock_Source_Enabled(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Clock_Source_Type Clock_Source,
		Enabled_Type Enabled,
		S32K1xx_Clock_Tree_Type *Tree);
int Drivers_S32K1xx_FTM_SET_Clock(FTM_Type *P_FTM,Drivers_S32K1xx_FTM_Clock_Type Clock);
int Drivers_S32K1xx_FTM_GET_Clock(FTM_Type *P_FTM);
int Drivers_S32K1xx_FTM_GET_Clock_Enabled(FTM_Type *P_FTM);
int Drivers_S32K1xx_FTM_SET_Module_Enabled(
		FTM_Type *P_FTM,
		Enabled_Type Enabled);
int Drivers_S32K1xx_FTM_GET_Module_Enabled(FTM_Type *P_FTM);
int Drivers_S32K1xx_FTM_SET_Write_Protection_Enabled(
		FTM_Type *P_FTM,
		Enabled_Type Enabled);
int Drivers_S32K1xx_FTM_GET_Write_Protection_Enabled(FTM_Type *P_FTM);
int Drivers_S32K1xx_FTM_SET_Channel_PWM_Enabled(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channel_Type CH,
		Enabled_Type Enabled);
int Drivers_S32K1xx_FTM_SET_Prescale(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Prescale_Type Prescale);
int Drivers_S32K1xx_FTM_SET_Channel_Control(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channel_Type CH,
		Enabled_Type Trigger_Mode,
		Enabled_Type Interrupt,
		uint8_t MSB_MSA,
		uint8_t ELSB_ELSA,
		Enabled_Type ICRST,//FTM counter reset by the selected input capture event
		Enabled_Type DMA);
int Drivers_S32K1xx_FTM_SET_Channel_Control_Modes(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channel_Type CH,
		uint8_t MSB_MSA,
		uint8_t ELSB_ELSA);
int Drivers_S32K1xx_FTM_SET_Channel_Value(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channel_Type CH,
		uint16_t VAL);
int Drivers_S32K1xx_FTM_SET_Channels_Function_ChannelModes(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channels_Type Channels,
		uint8_t DECAPEN,
		uint8_t MCOMBINE,
		uint8_t COMBINE);
int Drivers_S32K1xx_FTM_SET_Channels_Function_Synchronization_Enabled(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channels_Type Channels,
		Enabled_Type SYNCEN);
int Drivers_S32K1xx_FTM_SET_Center_Aligned_PWM(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Center_Aligned_PWM_Type CPWMS);
int Drivers_S32K1xx_FTM_SET_Modulo(FTM_Type *P_FTM,uint16_t MOD);
int Drivers_S32K1xx_FTM_SET_Channel_Polarity(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channel_Type CH,
		Drivers_S32K1xx_FTM_Channel_Polarity_Type Polarity);
int Drivers_S32K1xx_FTM_SET_Channel_Modes(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channel_Type CH,
		Drivers_S32K1xx_FTM_Channel_Modes_Type Channel_Modes,
		Enabled_Type Synchronization_Enabled);
//int Drivers_S32K1xx_FTM_SET_Demo(FTM_Type *P_FTM);

#endif /* DRIVERS_S32K1XX_FTM_H_ */
