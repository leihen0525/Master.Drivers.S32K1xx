/*
 * Drivers.S32K1xx.LPUART.c
 *
 *  Created on: 2020年7月8日
 *      Author: Master.HE
 */
#include "Error.h"

#include "Drivers.S32K1xx.LPUART.h"

int Drivers_S32K1xx_LPUART_SET_Clock_Source(
		LPUART_Type *P_LPUART,
		Drivers_S32K1xx_LPUART_Clock_Source_Type Clock_Source,
		S32K1xx_Clock_Tree_Type *Tree)
{
	if(P_LPUART==Null || Tree==Null)
	{
		return Error_Invalid_Parameter;
	}
	//时钟源检查
	switch (Clock_Source)
	{
		case Drivers_S32K1xx_LPUART_Clock_Source_SOSCDIV2_CLK:
		{
			if(Tree->SOSCDIV2_CLK_Hz==0)
			{
				return Error_Invalid_Parameter;
			}
		}break;
		case Drivers_S32K1xx_LPUART_Clock_Source_SIRCDIV2_CLK:
		{
			if(Tree->SIRCDIV2_CLK_Hz==0)
			{
				return Error_Invalid_Parameter;
			}
		}break;
		case Drivers_S32K1xx_LPUART_Clock_Source_FIRCDIV2_CLK:
		{
			if(Tree->FIRCDIV2_CLK_Hz==0)
			{
				return Error_Invalid_Parameter;
			}
		}break;
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case Drivers_S32K1xx_LPUART_Clock_Source_SPLLDIV2_CLK:
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

	switch ((uint32_t)P_LPUART)
	{
		case LPUART0_BASE:
		{
			PCC->PCCn_BIT[PCC_LPUART0_INDEX].PCS=Clock_Source;
			if(PCC->PCCn_BIT[PCC_LPUART0_INDEX].PCS==Clock_Source)
			{
				return Error_OK;
			}
			else
			{
				return Error_Write_Register_Fault;
			}

		}break;
		case LPUART1_BASE:
		{
			PCC->PCCn_BIT[PCC_LPUART1_INDEX].PCS=Clock_Source;
			if(PCC->PCCn_BIT[PCC_LPUART1_INDEX].PCS==Clock_Source)
			{
				return Error_OK;
			}
			else
			{
				return Error_Write_Register_Fault;
			}
		}break;
#if (defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case LPUART2_BASE:
		{
			PCC->PCCn_BIT[PCC_LPUART2_INDEX].PCS=Clock_Source;
			if(PCC->PCCn_BIT[PCC_LPUART2_INDEX].PCS==Clock_Source)
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

int Drivers_S32K1xx_LPUART_SET_Clock_Enabled(
		LPUART_Type *P_LPUART,
		Enabled_Type Enabled)
{
	if(P_LPUART==Null || Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}
	switch ((uint32_t)P_LPUART)
	{
		case LPUART0_BASE:
		{
			PCC->PCCn_BIT[PCC_LPUART0_INDEX].CGC=Enabled;
			if(PCC->PCCn_BIT[PCC_LPUART0_INDEX].CGC==Enabled)
			{
				return Error_OK;
			}
			else
			{
				return Error_Write_Register_Fault;
			}

		}break;
		case LPUART1_BASE:
		{
			PCC->PCCn_BIT[PCC_LPUART1_INDEX].CGC=Enabled;
			if(PCC->PCCn_BIT[PCC_LPUART1_INDEX].CGC==Enabled)
			{
				return Error_OK;
			}
			else
			{
				return Error_Write_Register_Fault;
			}
		}break;
#if (defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case LPUART2_BASE:
		{
			PCC->PCCn_BIT[PCC_LPUART2_INDEX].CGC=Enabled;
			if(PCC->PCCn_BIT[PCC_LPUART2_INDEX].CGC==Enabled)
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
int Drivers_S32K1xx_LPUART_Software_Reset(LPUART_Type *P_LPUART)
{
	if(P_LPUART==Null)
	{
		return Error_Invalid_Parameter;
	}
	P_LPUART->GLOBAL.BIT.RST=1;
	P_LPUART->GLOBAL.BIT.RST=0;
	return Error_OK;
}
int Drivers_S32K1xx_LPUART_SET_Bit_Select(
		LPUART_Type *P_LPUART,
		Drivers_S32K1xx_LPUART_Bit_Mode_Select_Type Bit_Mode,
		Drivers_S32K1xx_LPUART_Stop_Bit_Select_Type Stop_Bit)
{
	if(P_LPUART==Null || Bit_Mode>=Drivers_S32K1xx_LPUART_Bit_Mode_Select_End || Stop_Bit>=Drivers_S32K1xx_LPUART_Stop_Bit_Select_End)
	{
		return Error_Invalid_Parameter;
	}
	P_LPUART->BAUD.BIT.M10=Bit_Mode;
	if(P_LPUART->BAUD.BIT.M10!=Bit_Mode)
	{
		return Error_Write_Register_Fault;
	}
	P_LPUART->BAUD.BIT.SBNS=Stop_Bit;
	if(P_LPUART->BAUD.BIT.SBNS!=Stop_Bit)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_LPUART_SET_Baud_Rate(
		LPUART_Type *P_LPUART,
		S32K1xx_Clock_Tree_Type *Tree,
		Drivers_S32K1xx_LPUART_Oversampling_Ratio_Type Oversampling_Ratio,
		uint32_t bps)
{
	if(P_LPUART==Null
	|| Tree==Null
	|| Oversampling_Ratio==Drivers_S32K1xx_LPUART_Oversampling_Ratio_Reserved1
	|| Oversampling_Ratio==Drivers_S32K1xx_LPUART_Oversampling_Ratio_Reserved2
	|| Oversampling_Ratio>=Drivers_S32K1xx_LPUART_Oversampling_Ratio_End
	|| bps==0)
	{
		return Error_Invalid_Parameter;
	}
	int Index=0;
	switch ((uint32_t)P_LPUART)
	{
		case LPUART0_BASE:
		{
			Index=PCC_LPUART0_INDEX;

		}break;
		case LPUART1_BASE:
		{
			Index=PCC_LPUART1_INDEX;
		}break;
#if (defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case LPUART2_BASE:
		{
			Index=PCC_LPUART2_INDEX;
		}break;
#endif
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
	uint32_t Module_Clock=0;
	switch (PCC->PCCn_BIT[Index].PCS)
	{
		case Drivers_S32K1xx_LPUART_Clock_Source_SOSCDIV2_CLK:
		{
			Module_Clock=Tree->SOSCDIV2_CLK_Hz;
		}break;
		case Drivers_S32K1xx_LPUART_Clock_Source_SIRCDIV2_CLK:
		{
			Module_Clock=Tree->SIRCDIV2_CLK_Hz;
		}break;
		case Drivers_S32K1xx_LPUART_Clock_Source_FIRCDIV2_CLK:
		{
			Module_Clock=Tree->FIRCDIV2_CLK_Hz;
		}break;
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case Drivers_S32K1xx_LPUART_Clock_Source_SPLLDIV2_CLK:
		{
			Module_Clock=Tree->SPLLDIV2_CLK_Hz==0)
		}break;
#endif
		default:
		{
			return Error_Clock_Fault;
		}break;
	}
	if(Module_Clock==0)
	{
		return Error_Clock_Fault;
	}
	uint32_t OSR=0;
	if(Oversampling_Ratio==Drivers_S32K1xx_LPUART_Oversampling_Ratio_Default_16)
	{
		OSR=16;
	}
	else
	{
		OSR=Oversampling_Ratio+1;
	}
	uint32_t SBR=0;
	SBR=Module_Clock/bps/OSR;

	if(SBR==0 || SBR>=0x1000)
	{
		return Error_Invalid_Parameter;
	}
	P_LPUART->BAUD.BIT.SBR=SBR;
	P_LPUART->BAUD.BIT.OSR=Oversampling_Ratio;

	if(P_LPUART->BAUD.BIT.SBR==SBR && P_LPUART->BAUD.BIT.OSR==Oversampling_Ratio)
	{
		return Error_OK;
	}
	else
	{
		return Error_Write_Register_Fault;
	}

}
int Drivers_S32K1xx_LPUART_SET_Function_Enabled(
		LPUART_Type *P_LPUART,
		Drivers_S32K1xx_LPUART_Function_Type Function,
		Enabled_Type Enabled)
{
	if(P_LPUART==Null
	|| (Function&(~(uint32_t)Drivers_S32K1xx_LPUART_Function_Mask))!=0
	|| Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}
	if((Function&Drivers_S32K1xx_LPUART_Function_Match_1)!=0)
	{
		P_LPUART->BAUD.BIT.MAEN1=Enabled;
		if(P_LPUART->BAUD.BIT.MAEN1!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPUART_Function_Match_2)!=0)
	{
		P_LPUART->BAUD.BIT.MAEN2=Enabled;
		if(P_LPUART->BAUD.BIT.MAEN2!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPUART_Function_Transmitter_DMA)!=0)
	{
		P_LPUART->BAUD.BIT.TDMAE=Enabled;
		if(P_LPUART->BAUD.BIT.TDMAE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPUART_Function_Receiver_Full_DMA)!=0)
	{
		P_LPUART->BAUD.BIT.RDMAE=Enabled;
		if(P_LPUART->BAUD.BIT.RDMAE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	if((Function&Drivers_S32K1xx_LPUART_Function_LIN_Break_Detection)!=0)
	{
		uint32_t Mask_Reserve=(LPUART_STAT_LBKDE_MASK|LPUART_STAT_BRK13_MASK|LPUART_STAT_RWUID_MASK|LPUART_STAT_RXINV_MASK|LPUART_STAT_MSBF_MASK);
		LPUART_STAT_Type STAT;
		STAT.DATA=P_LPUART->STAT.DATA;
		STAT.DATA=STAT.DATA&Mask_Reserve;

		STAT.BIT.LBKDE=Enabled;

		P_LPUART->STAT.DATA=STAT.DATA;
		if((P_LPUART->STAT.DATA&Mask_Reserve)!=STAT.DATA)
		{
			return Error_Clear_Register_Fault;
		}
	}

	if((Function&Drivers_S32K1xx_LPUART_Function_Transmitter)!=0)
	{
		P_LPUART->CTRL.BIT.TE=Enabled;
		if(P_LPUART->CTRL.BIT.TE!=Enabled)
		{
			return Error_Clear_Register_Fault;
		}
	}

	if((Function&Drivers_S32K1xx_LPUART_Function_Receiver)!=0)
	{
		P_LPUART->CTRL.BIT.RE=Enabled;
		if(P_LPUART->CTRL.BIT.RE!=Enabled)
		{
			return Error_Clear_Register_Fault;
		}
	}

	if((Function&Drivers_S32K1xx_LPUART_Function_Doze)!=0)
	{
		P_LPUART->CTRL.BIT.DOZEEN=Enabled;
		if(P_LPUART->CTRL.BIT.DOZEEN!=Enabled)
		{
			return Error_Clear_Register_Fault;
		}
	}

	if((Function&Drivers_S32K1xx_LPUART_Function_Parity)!=0)
	{
		P_LPUART->CTRL.BIT.PE=Enabled;
		if(P_LPUART->CTRL.BIT.PE!=Enabled)
		{
			return Error_Clear_Register_Fault;
		}
	}

	if((Function&Drivers_S32K1xx_LPUART_Function_Infrared)!=0)
	{
		P_LPUART->MODIR.BIT.IREN=Enabled;
		if(P_LPUART->MODIR.BIT.IREN!=Enabled)
		{
			return Error_Clear_Register_Fault;
		}
	}

	if((Function&Drivers_S32K1xx_LPUART_Function_Receiver_Request_To_Send)!=0)
	{
		P_LPUART->MODIR.BIT.RXRTSE=Enabled;
		if(P_LPUART->MODIR.BIT.RXRTSE!=Enabled)
		{
			return Error_Clear_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPUART_Function_Transmitter_Request_To_Send)!=0)
	{
		P_LPUART->MODIR.BIT.TXRTSE=Enabled;
		if(P_LPUART->MODIR.BIT.TXRTSE!=Enabled)
		{
			return Error_Clear_Register_Fault;
		}
	}
	if((Function&Drivers_S32K1xx_LPUART_Function_Transmitter_Clear_To_Send)!=0)
	{
		P_LPUART->MODIR.BIT.TXCTSE=Enabled;
		if(P_LPUART->MODIR.BIT.TXCTSE!=Enabled)
		{
			return Error_Clear_Register_Fault;
		}
	}

	uint32_t Mask_FIFO=~(uint32_t)(LPUART_FIFO_TXOF_MASK|LPUART_FIFO_RXUF_MASK);
	LPUART_FIFO_Type FIFO;
	FIFO.DATA=P_LPUART->FIFO.DATA&Mask_FIFO&(~(uint32_t)(LPUART_FIFO_TXFLUSH_MASK|LPUART_FIFO_RXFLUSH_MASK));
	if((Function&Drivers_S32K1xx_LPUART_Function_Transmit_FIFO)!=0)
	{
		FIFO.BIT.TXFE=Enabled;
	}

	if((Function&Drivers_S32K1xx_LPUART_Function_Receive_FIFO)!=0)
	{
		FIFO.BIT.RXFE=Enabled;
	}
	P_LPUART->FIFO.DATA=FIFO.DATA;
	if((P_LPUART->FIFO.DATA&Mask_FIFO)!=FIFO.DATA)
	{
		return Error_Write_Register_Fault;
	}

	return Error_OK;
}


int Drivers_S32K1xx_LPUART_SET_DATA(
		LPUART_Type *P_LPUART,
		bool Transmit_Special_Character,
		uint16_t DATA)
{
	if(P_LPUART==Null || Transmit_Special_Character>=bool_End || DATA>=0x400)
	{
		return Error_Invalid_Parameter;
	}
	LPUART_DATA_Type LPUART_DATA={.DATA=0};

	LPUART_DATA.BIT.FRETSC=Transmit_Special_Character;
	LPUART_DATA.BIT.DATA_10BIT=DATA;

	P_LPUART->DATA.DATA=LPUART_DATA.DATA;

	return Error_OK;

}

int Drivers_S32K1xx_LPUART_GET_DATA(
		LPUART_Type *P_LPUART,
		bool *NOISY,
		bool *PARITYE,
		bool *Frame_Error,
		bool *Receive_Buffer_Empty,
		bool *Idle_Line,
		uint16_t *DATA)
{
	if(P_LPUART==Null)
	{
		return Error_Invalid_Parameter;
	}
	LPUART_DATA_Type LPUART_DATA={.DATA=0};
	LPUART_DATA.DATA=P_LPUART->DATA.DATA;

	if(NOISY!=Null)
	{
		*NOISY=(bool)LPUART_DATA.BIT.NOISY;
	}
	if(PARITYE!=Null)
	{
		*PARITYE=(bool)LPUART_DATA.BIT.PARITYE;
	}
	if(Frame_Error!=Null)
	{
		*Frame_Error=(bool)LPUART_DATA.BIT.FRETSC;
	}
	if(Receive_Buffer_Empty!=Null)
	{
		*Receive_Buffer_Empty=(bool)LPUART_DATA.BIT.RXEMPT;
	}
	if(Idle_Line!=Null)
	{
		*Idle_Line=(bool)LPUART_DATA.BIT.IDLINE;
	}
	if(DATA!=Null)
	{
		*DATA=LPUART_DATA.BIT.DATA_10BIT;
	}
	return Error_OK;
}

int Drivers_S32K1xx_LPUART_SET_Interrupt_Enabled(
		LPUART_Type *P_LPUART,
		Drivers_S32K1xx_LPUART_Interrupt_Type Interrupt,
		Enabled_Type Enabled)
{
	if(P_LPUART==Null
	|| (Interrupt&(~(uint32_t)Drivers_S32K1xx_LPUART_Interrupt_Mask))!=0
	|| Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_LIN_Break_Detect)!=0)
	{
		P_LPUART->BAUD.BIT.LBKDIE=Enabled;
		if(P_LPUART->BAUD.BIT.LBKDIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_RX_Input_Active_Edge)!=0)
	{
		P_LPUART->BAUD.BIT.RXEDGIE=Enabled;
		if(P_LPUART->BAUD.BIT.RXEDGIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Overrun)!=0)
	{
		P_LPUART->CTRL.BIT.ORIE=Enabled;
		if(P_LPUART->CTRL.BIT.ORIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Noise_Error)!=0)
	{
		P_LPUART->CTRL.BIT.NEIE=Enabled;
		if(P_LPUART->CTRL.BIT.NEIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Framing_Error)!=0)
	{
		P_LPUART->CTRL.BIT.FEIE=Enabled;
		if(P_LPUART->CTRL.BIT.FEIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Parity_Error)!=0)
	{
		P_LPUART->CTRL.BIT.PEIE=Enabled;
		if(P_LPUART->CTRL.BIT.PEIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Transmit)!=0)
	{
		P_LPUART->CTRL.BIT.TIE=Enabled;
		if(P_LPUART->CTRL.BIT.TIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete)!=0)
	{
		P_LPUART->CTRL.BIT.TCIE=Enabled;
		if(P_LPUART->CTRL.BIT.TCIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Receiver)!=0)
	{
		P_LPUART->CTRL.BIT.RIE=Enabled;
		if(P_LPUART->CTRL.BIT.RIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Idle_Line)!=0)
	{
		P_LPUART->CTRL.BIT.ILIE=Enabled;
		if(P_LPUART->CTRL.BIT.ILIE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Match_1)!=0)
	{
		P_LPUART->CTRL.BIT.MA1IE=Enabled;
		if(P_LPUART->CTRL.BIT.MA1IE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Match_2)!=0)
	{
		P_LPUART->CTRL.BIT.MA2IE=Enabled;
		if(P_LPUART->CTRL.BIT.MA2IE!=Enabled)
		{
			return Error_Write_Register_Fault;
		}
	}

	uint32_t Mask_FIFO=~(uint32_t)(LPUART_FIFO_TXOF_MASK|LPUART_FIFO_RXUF_MASK);
	LPUART_FIFO_Type FIFO;
	FIFO.DATA=P_LPUART->FIFO.DATA&Mask_FIFO&(~(uint32_t)(LPUART_FIFO_TXFLUSH_MASK|LPUART_FIFO_RXFLUSH_MASK));

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Transmit_FIFO_Overflow)!=0)
	{
		FIFO.BIT.TXOFE=Enabled;
	}
	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Receive_FIFO_Underflow)!=0)
	{
		FIFO.BIT.RXUFE=Enabled;
	}

	P_LPUART->FIFO.DATA=FIFO.DATA;
	if((P_LPUART->FIFO.DATA&Mask_FIFO)!=FIFO.DATA)
	{
		return Error_Write_Register_Fault;
	}

	return Error_OK;
}
int Drivers_S32K1xx_LPUART_GET_Interrupt_Flag(LPUART_Type *P_LPUART)
{
	if(P_LPUART==Null)
	{
		return Error_Invalid_Parameter;
	}
	int Flag=0;

	LPUART_STAT_Type STAT;
	STAT.DATA=P_LPUART->STAT.DATA;

	if(STAT.BIT.LBKDIF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_LIN_Break_Detect;
	}

	if(STAT.BIT.RXEDGIF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_RX_Input_Active_Edge;
	}

	if(STAT.BIT.OR==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_Overrun;
	}

	if(STAT.BIT.NF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_Noise_Error;
	}

	if(STAT.BIT.FE==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_Framing_Error;
	}

	if(STAT.BIT.PF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_Parity_Error;
	}

	if(STAT.BIT.TDRE==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_Transmit;
	}

	if(STAT.BIT.TC==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete;
	}

	if(STAT.BIT.RDRF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_Receiver;
	}

	if(STAT.BIT.IDLE==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_Idle_Line;
	}

	if(STAT.BIT.MA1F==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_Match_1;
	}

	if(STAT.BIT.MA2F==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_Match_2;
	}

	LPUART_FIFO_Type FIFO;
	FIFO.DATA=P_LPUART->FIFO.DATA;

	if(FIFO.BIT.TXOF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_Transmit_FIFO_Overflow;
	}

	if(FIFO.BIT.RXUF==true)
	{
		Flag=Flag|Drivers_S32K1xx_LPUART_Interrupt_Receive_FIFO_Underflow;
	}

	return Flag;
}
int Drivers_S32K1xx_LPUART_Clear_Interrupt_Flag(
		LPUART_Type *P_LPUART,
		Drivers_S32K1xx_LPUART_Interrupt_Type Interrupt)
{
	if(P_LPUART==Null
	|| (Interrupt&(~(uint32_t)Drivers_S32K1xx_LPUART_Interrupt_Mask))!=0)
	{
		return Error_Invalid_Parameter;
	}
	uint32_t Mask_Reserve=(LPUART_STAT_LBKDE_MASK|LPUART_STAT_BRK13_MASK|LPUART_STAT_RWUID_MASK|LPUART_STAT_RXINV_MASK|LPUART_STAT_MSBF_MASK);
	LPUART_STAT_Type STAT;
	STAT.DATA=P_LPUART->STAT.DATA;
	STAT.DATA=STAT.DATA&Mask_Reserve;

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_LIN_Break_Detect)!=0)
	{
		STAT.BIT.LBKDIF=true;
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_RX_Input_Active_Edge)!=0)
	{
		STAT.BIT.RXEDGIF=true;
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Overrun)!=0)
	{
		STAT.BIT.OR=true;
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Noise_Error)!=0)
	{
		STAT.BIT.NF=true;
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Framing_Error)!=0)
	{
		STAT.BIT.FE=true;
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Parity_Error)!=0)
	{
		STAT.BIT.PF=true;
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Transmit)!=0)
	{
		//STAT.BIT.TDRE=true;
		return Error_Invalid_Parameter;
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete)!=0)
	{
		//STAT.BIT.TC=true;
		return Error_Invalid_Parameter;
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Receiver)!=0)
	{
		//STAT.BIT.RDRF=true;
		return Error_Invalid_Parameter;
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Idle_Line)!=0)
	{
		STAT.BIT.IDLE=true;
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Match_1)!=0)
	{
		STAT.BIT.MA1F=true;
	}

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Match_2)!=0)
	{
		STAT.BIT.MA2F=true;
	}



	uint32_t Mask_FIFO=~(uint32_t)(LPUART_FIFO_TXOF_MASK|LPUART_FIFO_RXUF_MASK);
	LPUART_FIFO_Type FIFO;
	FIFO.DATA=P_LPUART->FIFO.DATA&Mask_FIFO&(~(uint32_t)(LPUART_FIFO_TXFLUSH_MASK|LPUART_FIFO_RXFLUSH_MASK));

	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Transmit_FIFO_Overflow)!=0)
	{
		FIFO.BIT.TXOF=true;
	}
	if((Interrupt&Drivers_S32K1xx_LPUART_Interrupt_Receive_FIFO_Underflow)!=0)
	{
		FIFO.BIT.RXUF=true;
	}


	P_LPUART->STAT.DATA=STAT.DATA;
	if((P_LPUART->STAT.DATA&(STAT.DATA&(~Mask_Reserve)))!=0)
	{
		return Error_Clear_Register_Fault;
	}

	P_LPUART->FIFO.DATA=FIFO.DATA;
	if((P_LPUART->FIFO.DATA&(FIFO.DATA&(~Mask_FIFO)))!=0)
	{
		return Error_Clear_Register_Fault;
	}

	return Error_OK;
}
