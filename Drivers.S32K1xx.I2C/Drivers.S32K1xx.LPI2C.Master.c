/*
 * Drivers.S32K1xx.LPI2C.Master.c
 *
 *  Created on: 2020年7月21日
 *      Author: Master.HE
 */
#include "Error.h"
#include "Drivers.S32K1xx.LPI2C.Master.h"


int Drivers_S32K1xx_LPI2C_Master_Software_Reset(LPI2C_Type *P_LPI2C)
{
	if(P_LPI2C==Null)
	{
		return Error_Invalid_Parameter;
	}
	P_LPI2C->MCR.BIT.RST=1;
	P_LPI2C->MCR.BIT.RST=0;
	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_Reset_FIFO(LPI2C_Type *P_LPI2C,bool Transmit,bool Receive)
{
	if(P_LPI2C==Null || Transmit>=bool_End || Receive>=bool_End)
	{
		return Error_Invalid_Parameter;
	}
	P_LPI2C->MCR.BIT.RTF=Transmit;
	P_LPI2C->MCR.BIT.RRF=Receive;
	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_SET_Module_Enabled(LPI2C_Type *P_LPI2C,Enabled_Type Enabled)
{
	if(P_LPI2C==Null || Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}
	P_LPI2C->MCR.BIT.MEN=Enabled;
	if(P_LPI2C->MCR.BIT.MEN==Enabled)
	{
		return Error_OK;
	}
	else
	{
		return Error_Write_Register_Fault;
	}
}
int Drivers_S32K1xx_LPI2C_Master_GET_Module_Enabled(LPI2C_Type *P_LPI2C)
{
	if(P_LPI2C==Null)
	{
		return Error_Invalid_Parameter;
	}
	return P_LPI2C->MCR.BIT.MEN;
}
int Drivers_S32K1xx_LPI2C_Master_SET_Function_Enabled(
		LPI2C_Type *P_LPI2C,
		Drivers_S32K1xx_LPI2C_Master_Function_Type Function,
		Enabled_Type Enabled)
{
	if(P_LPI2C==Null
	|| (Function&(~(uint32_t)Drivers_S32K1xx_LPI2C_Master_Function_Mask))!=0
	|| Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}
	if((Function&Drivers_S32K1xx_LPI2C_Master_Function_Debug)!=0)
	{
		P_LPI2C->MCR.BIT.DBGEN=Enabled;
		if(P_LPI2C->MCR.BIT.DBGEN!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPI2C_Master_Function_Doze_Mode)!=0)
	{
		P_LPI2C->MCR.BIT.DOZEN=Enabled;
		if(P_LPI2C->MCR.BIT.DOZEN!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	if((Function&Drivers_S32K1xx_LPI2C_Master_Function_Receive_Data_DMA)!=0)
	{
		P_LPI2C->MDER.BIT.RDDE=Enabled;
		if(P_LPI2C->MDER.BIT.RDDE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPI2C_Master_Function_Transmit_Data_DMA)!=0)
	{
		P_LPI2C->MDER.BIT.TDDE=Enabled;
		if(P_LPI2C->MDER.BIT.TDDE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPI2C_Master_Function_Circular_FIFO)!=0)
	{
		P_LPI2C->MCFGR0.BIT.CIRFIFO=Enabled;
		if(P_LPI2C->MCFGR0.BIT.CIRFIFO!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPI2C_Master_Function_Host_Request)!=0)
	{
		P_LPI2C->MCFGR0.BIT.HREN=Enabled;
		if(P_LPI2C->MCFGR0.BIT.HREN!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_SET_Interrupt_Enabled(
		LPI2C_Type *P_LPI2C,
		Drivers_S32K1xx_LPI2C_Master_Interrupt_Type Interrupt,
		Enabled_Type Enabled)
{
	if(P_LPI2C==Null
	|| (Interrupt&(~(uint32_t)Drivers_S32K1xx_LPI2C_Master_Interrupt_SET_Mask))!=0
	|| Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}

	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_Data_Match)!=0)
	{
		P_LPI2C->MIER.BIT.DMIE=Enabled;
		if(P_LPI2C->MIER.BIT.DMIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_Pin_Low_Timeout)!=0)
	{
		P_LPI2C->MIER.BIT.PLTIE=Enabled;
		if(P_LPI2C->MIER.BIT.PLTIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_FIFO_Error)!=0)
	{
		P_LPI2C->MIER.BIT.FEIE=Enabled;
		if(P_LPI2C->MIER.BIT.FEIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_Arbitration_Lost)!=0)
	{
		P_LPI2C->MIER.BIT.ALIE=Enabled;
		if(P_LPI2C->MIER.BIT.ALIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_NACK_Detect)!=0)
	{
		P_LPI2C->MIER.BIT.NDIE=Enabled;
		if(P_LPI2C->MIER.BIT.NDIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_STOP_Detect)!=0)
	{
		P_LPI2C->MIER.BIT.SDIE=Enabled;
		if(P_LPI2C->MIER.BIT.SDIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_End_Packet)!=0)
	{
		P_LPI2C->MIER.BIT.EPIE=Enabled;
		if(P_LPI2C->MIER.BIT.EPIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_Receive_Data)!=0)
	{
		P_LPI2C->MIER.BIT.RDIE=Enabled;
		if(P_LPI2C->MIER.BIT.RDIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_Transmit_Data)!=0)
	{
		P_LPI2C->MIER.BIT.TDIE=Enabled;
		if(P_LPI2C->MIER.BIT.TDIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_GET_Interrupt_Flag(LPI2C_Type *P_LPI2C)
{
	if(P_LPI2C==Null)
	{
		return Error_Invalid_Parameter;
	}
	int Flag=0;

	LPI2C_MSR_Type MSR;
	MSR.DATA=P_LPI2C->MSR.DATA;

	if(MSR.BIT.DMF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPI2C_Master_Interrupt_Data_Match;
	}
	if(MSR.BIT.PLTF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPI2C_Master_Interrupt_Pin_Low_Timeout;
	}
	if(MSR.BIT.FEF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPI2C_Master_Interrupt_FIFO_Error;
	}
	if(MSR.BIT.ALF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPI2C_Master_Interrupt_Arbitration_Lost;
	}
	if(MSR.BIT.NDF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPI2C_Master_Interrupt_NACK_Detect;
	}
	if(MSR.BIT.SDF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPI2C_Master_Interrupt_STOP_Detect;
	}
	if(MSR.BIT.EPF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPI2C_Master_Interrupt_End_Packet;
	}
	if(MSR.BIT.RDF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPI2C_Master_Interrupt_Receive_Data;
	}
	if(MSR.BIT.TDF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPI2C_Master_Interrupt_Transmit_Data;
	}
	if(MSR.BIT.BBF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPI2C_Master_Interrupt_Bus_Busy;
	}
	if(MSR.BIT.MBF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPI2C_Master_Interrupt_Master_Busy;
	}
	return Flag;
}
int Drivers_S32K1xx_LPI2C_Master_Clear_Interrupt_Flag(
		LPI2C_Type *P_LPI2C,
		Drivers_S32K1xx_LPI2C_Master_Interrupt_Type Interrupt)
{
	if(P_LPI2C==Null
	|| (Interrupt&(~(uint32_t)Drivers_S32K1xx_LPI2C_Master_Interrupt_Clear_Mask))!=0)
	{
		return Error_Invalid_Parameter;
	}
	LPI2C_MSR_Type MSR={.DATA=0};

	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_Data_Match)!=0)
	{
		MSR.BIT.MBF=true;
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_Pin_Low_Timeout)!=0)
	{
		MSR.BIT.PLTF=true;
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_FIFO_Error)!=0)
	{
		MSR.BIT.FEF=true;
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_Arbitration_Lost)!=0)
	{
		MSR.BIT.ALF=true;
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_NACK_Detect)!=0)
	{
		MSR.BIT.NDF=true;
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_STOP_Detect)!=0)
	{
		MSR.BIT.SDF=true;
	}
	if((Interrupt&Drivers_S32K1xx_LPI2C_Master_Interrupt_End_Packet)!=0)
	{
		MSR.BIT.EPF=true;
	}
	P_LPI2C->MSR.DATA=MSR.DATA;
	if((P_LPI2C->MSR.DATA&MSR.DATA)!=0)
	{
		return Error_Clear_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_SET_Clock_Configuration_0(
		LPI2C_Type *P_LPI2C,
		uint8_t Data_Valid_Delay,
		uint8_t Setup_Hold_Delay,
		uint8_t Clock_High_Period,
		uint8_t Clock_Low_Period)
{
	if(P_LPI2C==Null
	|| Data_Valid_Delay>0x3F
	|| Setup_Hold_Delay>0x3F
	|| Clock_High_Period>0x3F
	|| Clock_Low_Period>0x3F)
	{
		return Error_Invalid_Parameter;
	}
	LPI2C_MCCR1_Type MCCR0={.DATA=0};

	MCCR0.BIT.DATAVD=Data_Valid_Delay;
	MCCR0.BIT.SETHOLD=Setup_Hold_Delay;
	MCCR0.BIT.CLKHI=Clock_High_Period;
	MCCR0.BIT.CLKLO=Clock_Low_Period;

	P_LPI2C->MCCR0.DATA=MCCR0.DATA;
	if(P_LPI2C->MCCR0.DATA!=MCCR0.DATA)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_SET_Clock_Configuration_1(
		LPI2C_Type *P_LPI2C,
		uint8_t Data_Valid_Delay,
		uint8_t Setup_Hold_Delay,
		uint8_t Clock_High_Period,
		uint8_t Clock_Low_Period)
{
	if(P_LPI2C==Null
	|| Data_Valid_Delay>0x3F
	|| Setup_Hold_Delay>0x3F
	|| Clock_High_Period>0x3F
	|| Clock_Low_Period>0x3F)
	{
		return Error_Invalid_Parameter;
	}
	LPI2C_MCCR1_Type MCCR1={.DATA=0};

	MCCR1.BIT.DATAVD=Data_Valid_Delay;
	MCCR1.BIT.SETHOLD=Setup_Hold_Delay;
	MCCR1.BIT.CLKHI=Clock_High_Period;
	MCCR1.BIT.CLKLO=Clock_Low_Period;

	P_LPI2C->MCCR1.DATA=MCCR1.DATA;
	if(P_LPI2C->MCCR1.DATA!=MCCR1.DATA)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_SET_FIFO_Watermark(LPI2C_Type *P_LPI2C,uint8_t Receive,uint8_t Transmit)
{
	if(P_LPI2C==Null || Receive>3 || Transmit>3)
	{
		return Error_Invalid_Parameter;
	}
	P_LPI2C->MFCR.BIT.RXWATER=Receive;
	if(P_LPI2C->MFCR.BIT.RXWATER!=Receive)
	{
		return Error_Write_Register_Fault;
	}

	P_LPI2C->MFCR.BIT.TXWATER=Transmit;
	if(P_LPI2C->MFCR.BIT.TXWATER!=Transmit)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_GET_FIFO_TX_COUNT(LPI2C_Type *P_LPI2C)
{
	if(P_LPI2C==Null)
	{
		return Error_Invalid_Parameter;
	}
	return P_LPI2C->MFSR.BIT.TXCOUNT;
}
int Drivers_S32K1xx_LPI2C_Master_GET_FIFO_RX_COUNT(LPI2C_Type *P_LPI2C)
{
	if(P_LPI2C==Null)
	{
		return Error_Invalid_Parameter;
	}
	return P_LPI2C->MFSR.BIT.RXCOUNT;
}
int Drivers_S32K1xx_LPI2C_Master_SET_DATA(
		LPI2C_Type *P_LPI2C,
		Drivers_S32K1xx_LPI2C_Master_Command_Data_Type Command_Data,
		uint8_t DATA)
{
	if(P_LPI2C==Null
	|| Command_Data>=Drivers_S32K1xx_LPI2C_Master_Command_Data_End)
	{
		return Error_Invalid_Parameter;
	}
	LPI2C_MTDR_Type MTDR={.DATA=0};
	MTDR.BIT.CMD=Command_Data;
	MTDR.BIT.DATA=DATA;
	P_LPI2C->MTDR.DATA=MTDR.DATA;

	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_GET_DATA(
		LPI2C_Type *P_LPI2C,
		bool *RX_Empty,
		uint8_t *DATA)
{
	if(P_LPI2C==Null || DATA==Null)
	{
		return Error_Invalid_Parameter;
	}
	uint32_t MRDR_DATA=P_LPI2C->MRDR.DATA;
	LPI2C_MRDR_Type *P_MRDR=(LPI2C_MRDR_Type *)&MRDR_DATA;

	if(RX_Empty!=Null)
	{
		*RX_Empty=(bool)P_MRDR->BIT.RXEMPTY;
	}
	*DATA=P_MRDR->BIT.DATA;

	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_SET_Pin_Low_Timeout(LPI2C_Type *P_LPI2C,uint16_t Timeout)
{
	if(P_LPI2C==Null || Timeout>0xFFF)
	{
		return Error_Invalid_Parameter;
	}
	P_LPI2C->MCFGR3.BIT.PINLOW=Timeout;
	if(P_LPI2C->MCFGR3.BIT.PINLOW!=Timeout)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_SET_Bus_Idle_Timeout(LPI2C_Type *P_LPI2C,uint16_t Timeout)
{
	if(P_LPI2C==Null || Timeout>0xFFF)
	{
		return Error_Invalid_Parameter;
	}
	P_LPI2C->MCFGR2.BIT.BUSIDLE=Timeout;
	if(P_LPI2C->MCFGR2.BIT.BUSIDLE!=Timeout)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_SET_Glitch_Filter(LPI2C_Type *P_LPI2C,uint8_t SCL,uint8_t SDA)
{
	if(P_LPI2C==Null || SCL>0xF || SDA>0xF)
	{
		return Error_Invalid_Parameter;
	}
	P_LPI2C->MCFGR2.BIT.FILTSCL=SCL;
	if(P_LPI2C->MCFGR2.BIT.FILTSCL!=SCL)
	{
		return Error_Write_Register_Fault;
	}
	P_LPI2C->MCFGR2.BIT.FILTSDA=SDA;
	if(P_LPI2C->MCFGR2.BIT.FILTSDA!=SDA)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_SET_PIN_Config(LPI2C_Type *P_LPI2C,Drivers_S32K1xx_LPI2C_Master_PIN_Config_Type Pin)
{
	if(P_LPI2C==Null || Pin>=Drivers_S32K1xx_LPI2C_Master_PIN_Config_End)
	{
		return Error_Invalid_Parameter;
	}
	P_LPI2C->MCFGR1.BIT.PINCFG=Pin;
	if(P_LPI2C->MCFGR1.BIT.PINCFG!=Pin)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}

int Drivers_S32K1xx_LPI2C_Master_SET_Prescaler(LPI2C_Type *P_LPI2C,Drivers_S32K1xx_LPI2C_Master_Prescaler_Type Prescaler)
{
	if(P_LPI2C==Null || Prescaler>=Drivers_S32K1xx_LPI2C_Master_Prescaler_End)
	{
		return Error_Invalid_Parameter;
	}
	P_LPI2C->MCFGR1.BIT.PRESCALE=Prescaler;
	if(P_LPI2C->MCFGR1.BIT.PRESCALE!=Prescaler)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_SET_Timeout_Config(LPI2C_Type *P_LPI2C,Drivers_S32K1xx_LPI2C_Master_Timeout_Config_Type Timeout_Config)
{
	if(P_LPI2C==Null || Timeout_Config>=Drivers_S32K1xx_LPI2C_Master_Timeout_Config_End)
	{
		return Error_Invalid_Parameter;
	}
	P_LPI2C->MCFGR1.BIT.TIMECFG=Timeout_Config;
	if(P_LPI2C->MCFGR1.BIT.TIMECFG!=Timeout_Config)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}

int Drivers_S32K1xx_LPI2C_Master_SET_IGNACK(LPI2C_Type *P_LPI2C,bool Ignored_NACK)
{
	if(P_LPI2C==Null || Ignored_NACK>=bool_End)
	{
		return Error_Invalid_Parameter;
	}
	P_LPI2C->MCFGR1.BIT.IGNACK=Ignored_NACK;
	if(P_LPI2C->MCFGR1.BIT.IGNACK!=Ignored_NACK)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPI2C_Master_SET_Automatic_STOP_Generation(LPI2C_Type *P_LPI2C,bool Auto_Stop)
{
	if(P_LPI2C==Null || Auto_Stop>=bool_End)
	{
		return Error_Invalid_Parameter;
	}
	P_LPI2C->MCFGR1.BIT.AUTOSTOP=Auto_Stop;
	if(P_LPI2C->MCFGR1.BIT.AUTOSTOP!=Auto_Stop)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}





