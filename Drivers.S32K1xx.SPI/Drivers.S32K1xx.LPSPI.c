/*
 * Drivers.S32K1xx.LPSPI.c
 *
 *  Created on: 2020年7月21日
 *      Author: Master.HE
 */
#include "Error.h"

#include "Drivers.S32K1xx.LPSPI.h"

int Drivers_S32K1xx_LPSPI_SET_Clock_Source(
		LPSPI_Type *P_LPSPI,
		Drivers_S32K1xx_LPSPI_Clock_Source_Type Clock_Source,
		S32K1xx_Clock_Tree_Type *Tree)
{
	if(P_LPSPI==Null || Tree==Null)
	{
		return Error_Invalid_Parameter;
	}
	//时钟源检查
	switch (Clock_Source)
	{
		case Drivers_S32K1xx_LPSPI_Clock_Source_SOSCDIV2_CLK:
		{
			if(Tree->SOSCDIV2_CLK_Hz==0)
			{
				return Error_Invalid_Parameter;
			}
		}break;
		case Drivers_S32K1xx_LPSPI_Clock_Source_SIRCDIV2_CLK:
		{
			if(Tree->SIRCDIV2_CLK_Hz==0)
			{
				return Error_Invalid_Parameter;
			}
		}break;
		case Drivers_S32K1xx_LPSPI_Clock_Source_FIRCDIV2_CLK:
		{
			if(Tree->FIRCDIV2_CLK_Hz==0)
			{
				return Error_Invalid_Parameter;
			}
		}break;
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case Drivers_S32K1xx_LPSPI_Clock_Source_SPLLDIV2_CLK:
		{
			if(Tree->SPLLDIV2_CLK_Hz==0)
			{
				return Error_Invalid_Parameter;
			}
		}break;
#endif
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}

	switch ((uint32_t)P_LPSPI)
	{
		case LPSPI0_BASE:
		{
			PCC->PCCn_BIT[PCC_LPSPI0_INDEX].PCS=Clock_Source;
			if(PCC->PCCn_BIT[PCC_LPSPI0_INDEX].PCS==Clock_Source)
			{
				return Error_OK;
			}
			else
			{
				return Error_Write_Register_Fault;
			}

		}break;
#if (defined (__Target_S32K118__) || defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case LPSPI1_BASE:
		{
			PCC->PCCn_BIT[PCC_LPSPI1_INDEX].PCS=Clock_Source;
			if(PCC->PCCn_BIT[PCC_LPSPI1_INDEX].PCS==Clock_Source)
			{
				return Error_OK;
			}
			else
			{
				return Error_Write_Register_Fault;
			}
		}break;
#endif
#if (defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case LPSPI2_BASE:
		{
			PCC->PCCn_BIT[PCC_LPSPI2_INDEX].PCS=Clock_Source;
			if(PCC->PCCn_BIT[PCC_LPSPI2_INDEX].PCS==Clock_Source)
			{
				return Error_OK;
			}
			else
			{
				return Error_Write_Register_Fault;
			}
		}break;
#endif
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
}

int Drivers_S32K1xx_LPSPI_SET_Clock_Enabled(
		LPSPI_Type *P_LPSPI,
		Enabled_Type Enabled)
{
	if(P_LPSPI==Null || Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}
	switch ((uint32_t)P_LPSPI)
	{
		case LPSPI0_BASE:
		{
			PCC->PCCn_BIT[PCC_LPSPI0_INDEX].CGC=Enabled;
			if(PCC->PCCn_BIT[PCC_LPSPI0_INDEX].CGC==Enabled)
			{
				return Error_OK;
			}
			else
			{
				return Error_Write_Register_Fault;
			}

		}break;
#if (defined (__Target_S32K118__) || defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case LPSPI1_BASE:
		{
			PCC->PCCn_BIT[PCC_LPSPI1_INDEX].CGC=Enabled;
			if(PCC->PCCn_BIT[PCC_LPSPI1_INDEX].CGC==Enabled)
			{
				return Error_OK;
			}
			else
			{
				return Error_Write_Register_Fault;
			}
		}break;
#endif
#if (defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case LPSPI2_BASE:
		{
			PCC->PCCn_BIT[PCC_LPSPI2_INDEX].CGC=Enabled;
			if(PCC->PCCn_BIT[PCC_LPSPI2_INDEX].CGC==Enabled)
			{
				return Error_OK;
			}
			else
			{
				return Error_Write_Register_Fault;
			}
		}break;
#endif
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
}
int Drivers_S32K1xx_LPSPI_GET_Clock_Enabled(LPSPI_Type *P_LPSPI)
{
	if(P_LPSPI==Null)
	{
		return Error_Invalid_Parameter;
	}
	switch ((uint32_t)P_LPSPI)
	{
		case LPSPI0_BASE:
		{
			return PCC->PCCn_BIT[PCC_LPSPI0_INDEX].CGC;
		}break;
#if (defined (__Target_S32K118__) || defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case LPSPI1_BASE:
		{
			return PCC->PCCn_BIT[PCC_LPSPI1_INDEX].CGC;
		}break;
#endif
#if (defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case LPSPI2_BASE:
		{
			return PCC->PCCn_BIT[PCC_LPSPI2_INDEX].CGC;
		}break;
#endif
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
}
int Drivers_S32K1xx_LPSPI_Software_Reset(LPSPI_Type *P_LPSPI)
{
	if(P_LPSPI==Null)
	{
		return Error_Invalid_Parameter;
	}
	P_LPSPI->CR.BIT.RST=1;
	P_LPSPI->CR.BIT.RST=0;
	return Error_OK;
}
int Drivers_S32K1xx_LPSPI_Reset_FIFO(LPSPI_Type *P_LPSPI,bool Transmit,bool Receive)
{
	if(P_LPSPI==Null || Transmit>=bool_End || Receive>=bool_End)
	{
		return Error_Invalid_Parameter;
	}
	P_LPSPI->CR.BIT.RTF=Transmit;
	P_LPSPI->CR.BIT.RRF=Receive;
	return Error_OK;
}
int Drivers_S32K1xx_LPSPI_SET_Module_Enabled(LPSPI_Type *P_LPSPI,Enabled_Type Enabled)
{
	if(P_LPSPI==Null || Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}
	P_LPSPI->CR.BIT.MEN=Enabled;
	if(P_LPSPI->CR.BIT.MEN==Enabled)
	{
		return Error_OK;
	}
	else
	{
		return Error_Write_Register_Fault;
	}
}
int Drivers_S32K1xx_LPSPI_GET_Module_Enabled(LPSPI_Type *P_LPSPI)
{
	if(P_LPSPI==Null)
	{
		return Error_Invalid_Parameter;
	}
	return P_LPSPI->CR.BIT.MEN;
}
int Drivers_S32K1xx_LPSPI_SET_Function_Enabled(
		LPSPI_Type *P_LPSPI,
		Drivers_S32K1xx_LPSPI_Function_Type Function,
		Enabled_Type Enabled)
{
	if(P_LPSPI==Null
	|| (Function&(~(uint32_t)Drivers_S32K1xx_LPSPI_Function_Mask))!=0
	|| Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}
	if((Function&Drivers_S32K1xx_LPSPI_Function_Debug)!=0)
	{
		P_LPSPI->CR.BIT.DBGEN=Enabled;
		if(P_LPSPI->CR.BIT.DBGEN!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPSPI_Function_Doze_Mode)!=0)
	{
		P_LPSPI->CR.BIT.DOZEN=Enabled;
		if(P_LPSPI->CR.BIT.DOZEN!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPSPI_Function_Receive_Data_DMA)!=0)
	{
		P_LPSPI->DER.BIT.RDDE=Enabled;
		if(P_LPSPI->DER.BIT.RDDE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPSPI_Function_Transmit_Data_DMA)!=0)
	{
		P_LPSPI->DER.BIT.TDDE=Enabled;
		if(P_LPSPI->DER.BIT.TDDE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPSPI_Function_Circular_FIFO)!=0)
	{
		P_LPSPI->CFGR0.BIT.CIRFIFO=Enabled;
		if(P_LPSPI->CFGR0.BIT.CIRFIFO!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPSPI_Function_Host_Request)!=0)
	{
		P_LPSPI->CFGR0.BIT.HREN=Enabled;
		if(P_LPSPI->CFGR0.BIT.HREN!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	return Error_OK;
}

int Drivers_S32K1xx_LPSPI_SET_Interrupt_Enabled(
		LPSPI_Type *P_LPSPI,
		Drivers_S32K1xx_LPSPI_Interrupt_Type Interrupt,
		Enabled_Type Enabled)
{
	if(P_LPSPI==Null
	|| (Interrupt&(~(uint32_t)Drivers_S32K1xx_LPSPI_Interrupt_SET_Mask))!=0
	|| Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}

	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Data_Match)!=0)
	{
		P_LPSPI->IER.BIT.DMIE=Enabled;
		if(P_LPSPI->IER.BIT.DMIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Receive_Error)!=0)
	{
		P_LPSPI->IER.BIT.REIE=Enabled;
		if(P_LPSPI->IER.BIT.REIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Transmit_Error)!=0)
	{
		P_LPSPI->IER.BIT.TEIE=Enabled;
		if(P_LPSPI->IER.BIT.TEIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Transfer_Complete)!=0)
	{
		P_LPSPI->IER.BIT.TCIE=Enabled;
		if(P_LPSPI->IER.BIT.TCIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Frame_Complete)!=0)
	{
		P_LPSPI->IER.BIT.FCIE=Enabled;
		if(P_LPSPI->IER.BIT.FCIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Word_Complete)!=0)
	{
		P_LPSPI->IER.BIT.WCIE=Enabled;
		if(P_LPSPI->IER.BIT.WCIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Receive_Data)!=0)
	{
		P_LPSPI->IER.BIT.RDIE=Enabled;
		if(P_LPSPI->IER.BIT.RDIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Transmit_Data)!=0)
	{
		P_LPSPI->IER.BIT.TDIE=Enabled;
		if(P_LPSPI->IER.BIT.TDIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPSPI_GET_Interrupt_Flag(LPSPI_Type *P_LPSPI)
{
	if(P_LPSPI==Null)
	{
		return Error_Invalid_Parameter;
	}
	int Flag=0;

	LPSPI_SR_Type SR;
	SR.DATA=P_LPSPI->SR.DATA;

	if(SR.BIT.DMF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPSPI_Interrupt_Data_Match;
	}
	if(SR.BIT.REF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPSPI_Interrupt_Receive_Error;
	}
	if(SR.BIT.TEF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPSPI_Interrupt_Transmit_Error;
	}
	if(SR.BIT.TCF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPSPI_Interrupt_Transfer_Complete;
	}
	if(SR.BIT.FCF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPSPI_Interrupt_Frame_Complete;
	}
	if(SR.BIT.WCF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPSPI_Interrupt_Word_Complete;
	}
	if(SR.BIT.RDF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPSPI_Interrupt_Receive_Data;
	}
	if(SR.BIT.TDF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPSPI_Interrupt_Transmit_Data;
	}
	if(SR.BIT.MBF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPSPI_Interrupt_Busy;
	}
	return Flag;
}
int Drivers_S32K1xx_LPSPI_Clear_Interrupt_Flag(
		LPSPI_Type *P_LPSPI,
		Drivers_S32K1xx_LPSPI_Interrupt_Type Interrupt)
{
	if(P_LPSPI==Null
	|| (Interrupt&(~(uint32_t)Drivers_S32K1xx_LPSPI_Interrupt_Clear_Mask))!=0)
	{
		return Error_Invalid_Parameter;
	}
	LPSPI_SR_Type SR={.DATA=0};

	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Data_Match)!=0)
	{
		SR.BIT.MBF=true;
	}
	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Receive_Error)!=0)
	{
		SR.BIT.REF=true;
	}
	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Transmit_Error)!=0)
	{
		SR.BIT.TEF=true;
	}
	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Transfer_Complete)!=0)
	{
		SR.BIT.TCF=true;
	}
	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Frame_Complete)!=0)
	{
		SR.BIT.FCF=true;
	}
	if((Interrupt&Drivers_S32K1xx_LPSPI_Interrupt_Word_Complete)!=0)
	{
		SR.BIT.WCF=true;
	}
	P_LPSPI->SR.DATA=SR.DATA;
	if((P_LPSPI->SR.DATA&SR.DATA)!=0)
	{
		return Error_Clear_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPSPI_SET_Clock_Configuration_Sub(
		LPSPI_Type *P_LPSPI,
		Drivers_S32K1xx_LPSPI_Clock_Configuration_Type Type,
		uint8_t DATA)
{
	if(P_LPSPI==Null)
	{
		return Error_Invalid_Parameter;
	}
	switch (Type)
	{
		case Drivers_S32K1xx_LPSPI_Clock_Configuration_Delay_SCK_To_PCS:
		{
			P_LPSPI->CCR.BIT.SCKPCS=DATA;
			if(P_LPSPI->CCR.BIT.SCKPCS!=DATA)
			{
				return Error_Write_Register_Fault;
			}
		}break;
		case Drivers_S32K1xx_LPSPI_Clock_Configuration_Delay_PCS_To_SCK:
		{
			P_LPSPI->CCR.BIT.PCSSCK=DATA;
			if(P_LPSPI->CCR.BIT.PCSSCK!=DATA)
			{
				return Error_Write_Register_Fault;
			}
		}break;
		case Drivers_S32K1xx_LPSPI_Clock_Configuration_Delay_Between_Transfers:
		{
			P_LPSPI->CCR.BIT.DBT=DATA;
			if(P_LPSPI->CCR.BIT.DBT!=DATA)
			{
				return Error_Write_Register_Fault;
			}
		}break;
		case Drivers_S32K1xx_LPSPI_Clock_Configuration_SCK_Divider:
		{
			P_LPSPI->CCR.BIT.SCKDIV=DATA;
			if(P_LPSPI->CCR.BIT.SCKDIV!=DATA)
			{
				return Error_Write_Register_Fault;
			}
		}break;
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPSPI_SET_Clock_Configuration(
		LPSPI_Type *P_LPSPI,
		uint8_t SCK_To_PCS_Delay,
		uint8_t PCS_To_SCK_Delay,
		uint8_t Between_Transfers_Delay,
		uint8_t SCK_Divider)
{
	if(P_LPSPI==Null)
	{
		return Error_Invalid_Parameter;
	}
	LPSPI_CCR_Type CCR={
						.BIT.SCKDIV=SCK_Divider,
						.BIT.DBT=Between_Transfers_Delay,
						.BIT.PCSSCK=PCS_To_SCK_Delay,
						.BIT.SCKPCS=SCK_To_PCS_Delay
						};
	P_LPSPI->CCR.DATA=CCR.DATA;
	if(P_LPSPI->CCR.DATA!=CCR.DATA)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPSPI_SET_PIN_Config(LPSPI_Type *P_LPSPI,Drivers_S32K1xx_LPSPI_PIN_Config_Type Pin)
{
	if(P_LPSPI==Null || Pin>=Drivers_S32K1xx_LPSPI_PIN_Config_End)
	{
		return Error_Invalid_Parameter;
	}
	P_LPSPI->CFGR1.BIT.PINCFG=Pin;
	if(P_LPSPI->CFGR1.BIT.PINCFG!=Pin)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
