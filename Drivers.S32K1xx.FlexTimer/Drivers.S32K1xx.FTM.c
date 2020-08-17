/*
 * Drivers.S32K1xx.FTM.c
 *
 *  Created on: 2020年7月30日
 *      Author: Master.HE
 */
#include "Define.h"
#include "Error.h"
#include "Drivers.S32K1xx.FTM.h"


int Drivers_S32K1xx_FTM_SET_Clock_Source_Enabled(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Clock_Source_Type Clock_Source,
		Enabled_Type Enabled,
		S32K1xx_Clock_Tree_Type *Tree)
{
	int32_t FTM_Frequency_Hz=Error_OK;
	if(P_FTM==Null || Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}

	if(Enabled==Enable)
	{
		if(Tree==Null)
		{
			return Error_Invalid_Parameter;
		}
		//时钟源检查
		switch (Clock_Source)
		{
			case Drivers_S32K1xx_FTM_Clock_Source_SYS_CLK:
			{
				if(Tree->SYS_CLK_Hz==0)
				{
					return Error_Invalid_Parameter;
				}
				FTM_Frequency_Hz=Tree->SYS_CLK_Hz;
			}break;
			case Drivers_S32K1xx_FTM_Clock_Source_RTC_CLK:
			{
				if(Tree->RTC_CLK_Hz==0)
				{
					return Error_Invalid_Parameter;
				}
				FTM_Frequency_Hz=Tree->RTC_CLK_Hz;
			}break;

			case Drivers_S32K1xx_FTM_Clock_Source_TCLK0:
			{
				FTM_Frequency_Hz=0;
			}break;
			case Drivers_S32K1xx_FTM_Clock_Source_TCLK1:
			{
				FTM_Frequency_Hz=0;;
			}break;
			case Drivers_S32K1xx_FTM_Clock_Source_TCLK2:
			{
				FTM_Frequency_Hz=0;;
			}break;

			case Drivers_S32K1xx_FTM_Clock_Source_SOSCDIV1_CLK:
			{
				if(Tree->SOSCDIV1_CLK_Hz==0)
				{
					return Error_Invalid_Parameter;
				}
				FTM_Frequency_Hz=Tree->SOSCDIV1_CLK_Hz;
			}break;

			case Drivers_S32K1xx_FTM_Clock_Source_SIRCDIV1_CLK:
			{
				if(Tree->SIRCDIV1_CLK_Hz==0)
				{
					return Error_Invalid_Parameter;
				}
				FTM_Frequency_Hz=Tree->SIRCDIV1_CLK_Hz;
			}break;
			case Drivers_S32K1xx_FTM_Clock_Source_FIRCDIV1_CLK:
			{
				if(Tree->FIRCDIV1_CLK_Hz==0)
				{
					return Error_Invalid_Parameter;
				}
				FTM_Frequency_Hz=Tree->FIRCDIV1_CLK_Hz;
			}break;
	#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
			case Drivers_S32K1xx_FTM_Clock_Source_SPLLDIV1_CLK:
			{
				if(Tree->SPLLDIV1_CLK_Hz==0)
				{
					return Error_Invalid_Parameter;
				}
				FTM_Frequency_Hz=Tree->SPLLDIV1_CLK_Hz;
			}break;
	#endif
			default:
			{
				return Error_Invalid_Parameter;
			}break;
		}
	}
	switch ((uint32_t)P_FTM)
	{
		case FTM0_BASE:
		{
			if(Enabled==Enable)
			{
				SIM->FTMOPT0.BIT.FTM0CLKSEL=(Clock_Source&0x03);
				if(SIM->FTMOPT0.BIT.FTM0CLKSEL!=(Clock_Source&0x03))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM0_INDEX].PCS=((Clock_Source>>2)&0x07);
				if(PCC->PCCn_BIT[PCC_FTM0_INDEX].PCS!=((Clock_Source>>2)&0x07))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM0_INDEX].CGC=Enable;
				if(PCC->PCCn_BIT[PCC_FTM0_INDEX].CGC!=Enable)
				{
					return Error_Write_Register_Fault;
				}

				FTM0->SC.BIT.CLKS=((Clock_Source>>5)&0x03);
				if(FTM0->SC.BIT.CLKS!=((Clock_Source>>5)&0x03))
				{
					return Error_Write_Register_Fault;
				}
			}
			else//Disable
			{
				PCC->PCCn_BIT[PCC_FTM0_INDEX].CGC=Disable;
				if(PCC->PCCn_BIT[PCC_FTM0_INDEX].CGC!=Disable)
				{
					return Error_Write_Register_Fault;
				}
			}
			return FTM_Frequency_Hz;

		}break;
		case FTM1_BASE:
		{
			if(Enabled==Enable)
			{
				SIM->FTMOPT0.BIT.FTM1CLKSEL=(Clock_Source&0x03);
				if(SIM->FTMOPT0.BIT.FTM1CLKSEL!=(Clock_Source&0x03))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM1_INDEX].PCS=((Clock_Source>>2)&0x07);
				if(PCC->PCCn_BIT[PCC_FTM1_INDEX].PCS!=((Clock_Source>>2)&0x07))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM1_INDEX].CGC=Enable;
				if(PCC->PCCn_BIT[PCC_FTM1_INDEX].CGC!=Enable)
				{
					return Error_Write_Register_Fault;
				}

				FTM1->SC.BIT.CLKS=((Clock_Source>>5)&0x03);
				if(FTM1->SC.BIT.CLKS!=((Clock_Source>>5)&0x03))
				{
					return Error_Write_Register_Fault;
				}
			}
			else//Disable
			{
				PCC->PCCn_BIT[PCC_FTM1_INDEX].CGC=Disable;
				if(PCC->PCCn_BIT[PCC_FTM1_INDEX].CGC!=Disable)
				{
					return Error_Write_Register_Fault;
				}
			}
			return FTM_Frequency_Hz;

		}break;
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case FTM2_BASE:
		{
			if(Enabled==Enable)
			{
				SIM->FTMOPT0.BIT.FTM2CLKSEL=(Clock_Source&0x03);
				if(SIM->FTMOPT0.BIT.FTM2CLKSEL!=(Clock_Source&0x03))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM2_INDEX].PCS=((Clock_Source>>2)&0x07);
				if(PCC->PCCn_BIT[PCC_FTM2_INDEX].PCS!=((Clock_Source>>2)&0x07))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM2_INDEX].CGC=Enable;
				if(PCC->PCCn_BIT[PCC_FTM2_INDEX].CGC!=Enable)
				{
					return Error_Write_Register_Fault;
				}

				FTM2->SC.BIT.CLKS=((Clock_Source>>5)&0x03);
				if(FTM2->SC.BIT.CLKS!=((Clock_Source>>5)&0x03))
				{
					return Error_Write_Register_Fault;
				}
			}
			else//Disable
			{
				PCC->PCCn_BIT[PCC_FTM2_INDEX].CGC=Disable;
				if(PCC->PCCn_BIT[PCC_FTM2_INDEX].CGC!=Disable)
				{
					return Error_Write_Register_Fault;
				}
			}
			return FTM_Frequency_Hz;

		}break;
		case FTM3_BASE:
		{
			if(Enabled==Enable)
			{
				SIM->FTMOPT0.BIT.FTM3CLKSEL=(Clock_Source&0x03);
				if(SIM->FTMOPT0.BIT.FTM3CLKSEL!=(Clock_Source&0x03))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM3_INDEX].PCS=((Clock_Source>>2)&0x07);
				if(PCC->PCCn_BIT[PCC_FTM3_INDEX].PCS!=((Clock_Source>>2)&0x07))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM3_INDEX].CGC=Enable;
				if(PCC->PCCn_BIT[PCC_FTM3_INDEX].CGC!=Enable)
				{
					return Error_Write_Register_Fault;
				}

				FTM3->SC.BIT.CLKS=((Clock_Source>>5)&0x03);
				if(FTM3->SC.BIT.CLKS!=((Clock_Source>>5)&0x03))
				{
					return Error_Write_Register_Fault;
				}
			}
			else//Disable
			{
				PCC->PCCn_BIT[PCC_FTM3_INDEX].CGC=Disable;
				if(PCC->PCCn_BIT[PCC_FTM3_INDEX].CGC!=Disable)
				{
					return Error_Write_Register_Fault;
				}
			}
			return FTM_Frequency_Hz;

		}break;
#if (defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case FTM4_BASE:
		{
			if(Enabled==Enable)
			{
				SIM->FTMOPT0.BIT.FTM4CLKSEL=(Clock_Source&0x03);
				if(SIM->FTMOPT0.BIT.FTM4CLKSEL!=(Clock_Source&0x03))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM4_INDEX].PCS=((Clock_Source>>2)&0x07);
				if(PCC->PCCn_BIT[PCC_FTM4_INDEX].PCS!=((Clock_Source>>2)&0x07))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM4_INDEX].CGC=Enable;
				if(PCC->PCCn_BIT[PCC_FTM4_INDEX].CGC!=Enable)
				{
					return Error_Write_Register_Fault;
				}

				FTM4->SC.BIT.CLKS=((Clock_Source>>5)&0x03);
				if(FTM4->SC.BIT.CLKS!=((Clock_Source>>5)&0x03))
				{
					return Error_Write_Register_Fault;
				}
			}
			else//Disable
			{
				PCC->PCCn_BIT[PCC_FTM4_INDEX].CGC=Disable;
				if(PCC->PCCn_BIT[PCC_FTM4_INDEX].CGC!=Disable)
				{
					return Error_Write_Register_Fault;
				}
			}
			return FTM_Frequency_Hz;

		}break;
		case FTM5_BASE:
		{
			if(Enabled==Enable)
			{
				SIM->FTMOPT0.BIT.FTM5CLKSEL=(Clock_Source&0x03);
				if(SIM->FTMOPT0.BIT.FTM5CLKSEL!=(Clock_Source&0x03))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM5_INDEX].PCS=((Clock_Source>>2)&0x07);
				if(PCC->PCCn_BIT[PCC_FTM5_INDEX].PCS!=((Clock_Source>>2)&0x07))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM5_INDEX].CGC=Enable;
				if(PCC->PCCn_BIT[PCC_FTM5_INDEX].CGC!=Enable)
				{
					return Error_Write_Register_Fault;
				}

				FTM5->SC.BIT.CLKS=((Clock_Source>>5)&0x03);
				if(FTM5->SC.BIT.CLKS!=((Clock_Source>>5)&0x03))
				{
					return Error_Write_Register_Fault;
				}
			}
			else//Disable
			{
				PCC->PCCn_BIT[PCC_FTM5_INDEX].CGC=Disable;
				if(PCC->PCCn_BIT[PCC_FTM5_INDEX].CGC!=Disable)
				{
					return Error_Write_Register_Fault;
				}
			}
			return FTM_Frequency_Hz;

		}break;
#if (defined (__Target_S32K148__))
		case FTM6_BASE:
		{
			if(Enabled==Enable)
			{
				SIM->FTMOPT0.BIT.FTM6CLKSEL=(Clock_Source&0x03);
				if(SIM->FTMOPT0.BIT.FTM6CLKSEL!=(Clock_Source&0x03))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM6_INDEX].PCS=((Clock_Source>>2)&0x07);
				if(PCC->PCCn_BIT[PCC_FTM6_INDEX].PCS!=((Clock_Source>>2)&0x07))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM6_INDEX].CGC=Enable;
				if(PCC->PCCn_BIT[PCC_FTM6_INDEX].CGC!=Enable)
				{
					return Error_Write_Register_Fault;
				}

				FTM6->SC.BIT.CLKS=((Clock_Source>>5)&0x03);
				if(FTM6->SC.BIT.CLKS!=((Clock_Source>>5)&0x03))
				{
					return Error_Write_Register_Fault;
				}
			}
			else//Disable
			{
				PCC->PCCn_BIT[PCC_FTM6_INDEX].CGC=Disable;
				if(PCC->PCCn_BIT[PCC_FTM6_INDEX].CGC!=Disable)
				{
					return Error_Write_Register_Fault;
				}
			}
			return FTM_Frequency_Hz;

		}break;
		case FTM7_BASE:
		{
			if(Enabled==Enable)
			{
				SIM->FTMOPT0.BIT.FTM7CLKSEL=(Clock_Source&0x03);
				if(SIM->FTMOPT0.BIT.FTM7CLKSEL!=(Clock_Source&0x03))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM7_INDEX].PCS=((Clock_Source>>2)&0x07);
				if(PCC->PCCn_BIT[PCC_FTM7_INDEX].PCS!=((Clock_Source>>2)&0x07))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_FTM7_INDEX].CGC=Enable;
				if(PCC->PCCn_BIT[PCC_FTM7_INDEX].CGC!=Enable)
				{
					return Error_Write_Register_Fault;
				}

				FTM7->SC.BIT.CLKS=((Clock_Source>>5)&0x03);
				if(FTM7->SC.BIT.CLKS!=((Clock_Source>>5)&0x03))
				{
					return Error_Write_Register_Fault;
				}
			}
			else//Disable
			{
				PCC->PCCn_BIT[PCC_FTM7_INDEX].CGC=Disable;
				if(PCC->PCCn_BIT[PCC_FTM7_INDEX].CGC!=Disable)
				{
					return Error_Write_Register_Fault;
				}
			}
			return FTM_Frequency_Hz;

		}break;
#endif

#endif

#endif
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
}
int Drivers_S32K1xx_FTM_SET_Clock(FTM_Type *P_FTM,Drivers_S32K1xx_FTM_Clock_Type Clock)
{
	if(P_FTM==Null || Clock>=Drivers_S32K1xx_FTM_Clock_End)
	{
		return Error_Invalid_Parameter;
	}
	P_FTM->SC.BIT.CLKS=Clock;
	if(P_FTM->SC.BIT.CLKS!=Clock)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_FTM_GET_Clock(FTM_Type *P_FTM)
{
	if(P_FTM==Null)
	{
		return Error_Invalid_Parameter;
	}
	return P_FTM->SC.BIT.CLKS;
}
int Drivers_S32K1xx_FTM_GET_Clock_Enabled(FTM_Type *P_FTM)
{
	if(P_FTM==Null)
	{
		return Error_Invalid_Parameter;
	}
	switch ((uint32_t)P_FTM)
	{
		case FTM0_BASE:
		{
			return PCC->PCCn_BIT[PCC_FTM0_INDEX].CGC;
		}break;
		case FTM1_BASE:
		{
			return PCC->PCCn_BIT[PCC_FTM1_INDEX].CGC;
		}break;
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case FTM2_BASE:
		{
			return PCC->PCCn_BIT[PCC_FTM2_INDEX].CGC;
		}break;
		case FTM3_BASE:
		{
			return PCC->PCCn_BIT[PCC_FTM3_INDEX].CGC;
		}break;
#if (defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case FTM4_BASE:
		{
			return PCC->PCCn_BIT[PCC_FTM4_INDEX].CGC;
		}break;
		case FTM5_BASE:
		{
			return PCC->PCCn_BIT[PCC_FTM5_INDEX].CGC;
		}break;
#if (defined (__Target_S32K148__))
		case FTM6_BASE:
		{
			return PCC->PCCn_BIT[PCC_FTM6_INDEX].CGC;
		}break;
		case FTM7_BASE:
		{
			return PCC->PCCn_BIT[PCC_FTM7_INDEX].CGC;
		}break;
#endif

#endif

#endif
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
}
int Drivers_S32K1xx_FTM_SET_Module_Enabled(
		FTM_Type *P_FTM,
		Enabled_Type Enabled)
{
	if(P_FTM==Null || Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}
	P_FTM->MODE.BIT.FTMEN=Enabled;
	if(P_FTM->MODE.BIT.FTMEN!=Enabled)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_FTM_GET_Module_Enabled(FTM_Type *P_FTM)
{
	if(P_FTM==Null)
	{
		return Error_Invalid_Parameter;
	}
	return P_FTM->MODE.BIT.FTMEN;
}
int Drivers_S32K1xx_FTM_SET_Write_Protection_Enabled(
		FTM_Type *P_FTM,
		Enabled_Type Enabled)
{
	if(P_FTM==Null || Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}
	if(Enabled==Disable)
	{
		P_FTM->MODE.BIT.WPDIS=1;
		if(P_FTM->MODE.BIT.WPDIS!=1)
		{
			return Error_Write_Register_Fault;
		}
	}
	else//Enable
	{
		P_FTM->FMS.BIT.WPEN=1;
		if(P_FTM->FMS.BIT.WPEN!=1)
		{
			return Error_Write_Register_Fault;
		}
	}
	return Error_OK;
}
int Drivers_S32K1xx_FTM_GET_Write_Protection_Enabled(FTM_Type *P_FTM)
{
	if(P_FTM==Null)
	{
		return Error_Invalid_Parameter;
	}
	if(P_FTM->MODE.BIT.WPDIS==0)
	{
		return Enable;
	}
	else
	{
		return Disable;
	}
}
int Drivers_S32K1xx_FTM_SET_Channel_PWM_Enabled(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channel_Type CH,
		Enabled_Type Enabled)
{
	if(P_FTM==Null
	|| (CH&(~Drivers_S32K1xx_FTM_Channel_Mask))!=0
	|| CH==Drivers_S32K1xx_FTM_Channel_Null
	|| Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}

	if(Enabled==Enable)
	{
		P_FTM->SC.BIT.PWMENn|=CH;

		if((P_FTM->SC.BIT.PWMENn&CH)!=CH)
		{
			return Error_Write_Register_Fault;
		}

	}
	else
	{
		P_FTM->SC.BIT.PWMENn&=(~CH);

		if((P_FTM->SC.BIT.PWMENn&CH)!=0)
		{
			return Error_Write_Register_Fault;
		}
	}

	return Error_OK;
}

int Drivers_S32K1xx_FTM_SET_Prescale(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Prescale_Type Prescale)
{
	if(P_FTM==Null || Prescale>=Drivers_S32K1xx_FTM_Prescale_End)
	{
		return Error_Invalid_Parameter;
	}
	P_FTM->SC.BIT.PS=Prescale;
	if(P_FTM->SC.BIT.PS!=Prescale)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_FTM_SET_Channel_Control(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channel_Type CH,
		Enabled_Type Trigger_Mode,
		Enabled_Type Interrupt,
		uint8_t MSB_MSA,
		uint8_t ELSB_ELSA,
		Enabled_Type ICRST,//FTM counter reset by the selected input capture event
		Enabled_Type DMA)
{
	if(P_FTM==Null
	|| (CH&(~Drivers_S32K1xx_FTM_Channel_Mask))!=0
	|| CH==Drivers_S32K1xx_FTM_Channel_Null
	|| Trigger_Mode>=Enabled_End
	|| Interrupt>=Enabled_End
	|| MSB_MSA>0x03
	|| ELSB_ELSA>0x03
	|| ICRST>=Enabled_End
	|| DMA>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}
	for(int i=0;i<FTM_CONTROLS_COUNT;i++)
	{
		if((CH&(1<<i))==0)continue;

		P_FTM->CONTROLS[i].CnSC.BIT.TRIGMODE=Trigger_Mode;
		if(P_FTM->CONTROLS[i].CnSC.BIT.TRIGMODE!=Trigger_Mode)
		{
			return Error_Write_Register_Fault;
		}

		P_FTM->CONTROLS[i].CnSC.BIT.CHIE=Interrupt;
		if(P_FTM->CONTROLS[i].CnSC.BIT.CHIE!=Interrupt)
		{
			return Error_Write_Register_Fault;
		}

		P_FTM->CONTROLS[i].CnSC.BIT.MSB_MSA=MSB_MSA;
		if(P_FTM->CONTROLS[i].CnSC.BIT.MSB_MSA!=MSB_MSA)
		{
			return Error_Write_Register_Fault;
		}

		P_FTM->CONTROLS[i].CnSC.BIT.ELSB_ELSA=ELSB_ELSA;
		if(P_FTM->CONTROLS[i].CnSC.BIT.ELSB_ELSA!=ELSB_ELSA)
		{
			return Error_Write_Register_Fault;
		}

		P_FTM->CONTROLS[i].CnSC.BIT.ICRST=ICRST;
		if(P_FTM->CONTROLS[i].CnSC.BIT.ICRST!=ICRST)
		{
			return Error_Write_Register_Fault;
		}

		P_FTM->CONTROLS[i].CnSC.BIT.DMA=DMA;
		if(P_FTM->CONTROLS[i].CnSC.BIT.DMA!=DMA)
		{
			return Error_Write_Register_Fault;
		}
	}
	return Error_OK;
}
int Drivers_S32K1xx_FTM_SET_Channel_Control_Modes(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channel_Type CH,
		uint8_t MSB_MSA,
		uint8_t ELSB_ELSA)
{
	if(P_FTM==Null
	|| (CH&(~Drivers_S32K1xx_FTM_Channel_Mask))!=0
	|| CH==Drivers_S32K1xx_FTM_Channel_Null
	|| MSB_MSA>0x03
	|| ELSB_ELSA>0x03)
	{
		return Error_Invalid_Parameter;
	}
	for(int i=0;i<FTM_CONTROLS_COUNT;i++)
	{
		if((CH&(1<<i))==0)continue;


		P_FTM->CONTROLS[i].CnSC.BIT.MSB_MSA=MSB_MSA;
		if(P_FTM->CONTROLS[i].CnSC.BIT.MSB_MSA!=MSB_MSA)
		{
			return Error_Write_Register_Fault;
		}

		P_FTM->CONTROLS[i].CnSC.BIT.ELSB_ELSA=ELSB_ELSA;
		if(P_FTM->CONTROLS[i].CnSC.BIT.ELSB_ELSA!=ELSB_ELSA)
		{
			return Error_Write_Register_Fault;
		}

	}
	return Error_OK;
}
int Drivers_S32K1xx_FTM_SET_Channel_Value(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channel_Type CH,
		uint16_t VAL)
{
	if(P_FTM==Null || (CH&(~Drivers_S32K1xx_FTM_Channel_Mask))!=0 || CH==Drivers_S32K1xx_FTM_Channel_Null)
	{
		return Error_Invalid_Parameter;
	}
	for(int i=0;i<FTM_CONTROLS_COUNT;i++)
	{
		if((CH&(1<<i))==0)continue;

		P_FTM->CONTROLS[i].CnV.BIT.VAL=VAL;
		P_FTM->PWMLOAD.BIT.LDOK=1;
		if(P_FTM->CONTROLS[i].CnV.BIT.VAL!=VAL)
		{
			return Error_Write_Register_Fault;
		}
	}
	return Error_OK;
}
int Drivers_S32K1xx_FTM_SET_Channels_Function_ChannelModes(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channels_Type Channels,
		uint8_t DECAPEN,
		uint8_t MCOMBINE,
		uint8_t COMBINE)
{
	if(P_FTM==Null || Channels>=Drivers_S32K1xx_FTM_Channels_End || DECAPEN>0x01 || MCOMBINE>0x01 || COMBINE>0x01)
	{
		return Error_Invalid_Parameter;
	}

	P_FTM->COMBINE.BIT[Channels].DECAPEN=DECAPEN;
	if(P_FTM->COMBINE.BIT[Channels].DECAPEN!=DECAPEN)
	{
		return Error_Write_Register_Fault;
	}

	P_FTM->COMBINE.BIT[Channels].MCOMBINE=MCOMBINE;
	if(P_FTM->COMBINE.BIT[Channels].MCOMBINE!=MCOMBINE)
	{
		return Error_Write_Register_Fault;
	}

	P_FTM->COMBINE.BIT[Channels].COMBINE=COMBINE;
	if(P_FTM->COMBINE.BIT[Channels].COMBINE!=COMBINE)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_FTM_SET_Channels_Function_Synchronization_Enabled(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channels_Type Channels,
		Enabled_Type SYNCEN)
{
	if(P_FTM==Null || Channels>=Drivers_S32K1xx_FTM_Channels_End || SYNCEN>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}

	P_FTM->COMBINE.BIT[Channels].SYNCEN=SYNCEN;
	if(P_FTM->COMBINE.BIT[Channels].SYNCEN!=SYNCEN)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_FTM_SET_Center_Aligned_PWM(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Center_Aligned_PWM_Type CPWMS)
{
	if(P_FTM==Null || CPWMS>=Drivers_S32K1xx_FTM_Center_Aligned_PWM_End)
	{
		return Error_Invalid_Parameter;
	}
	P_FTM->SC.BIT.CPWMS=CPWMS;
	if(P_FTM->SC.BIT.CPWMS!=CPWMS)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}

int Drivers_S32K1xx_FTM_SET_Modulo(FTM_Type *P_FTM,uint16_t MOD)
{
	if(P_FTM==Null)
	{
		return Error_Invalid_Parameter;
	}
	P_FTM->CNTIN.DATA=0;
	P_FTM->CNT.DATA=0;
	P_FTM->MOD.DATA=MOD;
	//P_FTM->PWMLOAD.BIT.LDOK=1;
	if(P_FTM->MOD.DATA!=MOD)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}

int Drivers_S32K1xx_FTM_SET_Channel_Polarity(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channel_Type CH,
		Drivers_S32K1xx_FTM_Channel_Polarity_Type Polarity)
{
	if(P_FTM==Null
	|| (CH&(~Drivers_S32K1xx_FTM_Channel_Mask))!=0
	|| CH==Drivers_S32K1xx_FTM_Channel_Null
	|| Polarity>=Drivers_S32K1xx_FTM_Channel_Polarity_End)
	{
		return Error_Invalid_Parameter;
	}

	if(Polarity==Drivers_S32K1xx_FTM_Channel_Polarity_Active_Low)//1
	{
		P_FTM->POL.BIT.POLn|=CH;

		if((P_FTM->POL.BIT.POLn&CH)!=CH)
		{
			return Error_Write_Register_Fault;
		}

	}
	else
	{
		P_FTM->POL.BIT.POLn&=(~CH);

		if((P_FTM->POL.BIT.POLn&CH)!=0)
		{
			return Error_Write_Register_Fault;
		}
	}
	return Error_OK;
}
int Drivers_S32K1xx_FTM_SET_Channel_Modes(
		FTM_Type *P_FTM,
		Drivers_S32K1xx_FTM_Channel_Type CH,
		Drivers_S32K1xx_FTM_Channel_Modes_Type Channel_Modes,
		Enabled_Type Synchronization_Enabled)
{
	int Err;
	if(P_FTM==Null
	|| (CH&(~Drivers_S32K1xx_FTM_Channel_Mask))!=0
	|| CH==Drivers_S32K1xx_FTM_Channel_Null
	|| Synchronization_Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}
	for(int i=0;i<FTM_CONTROLS_COUNT;i++)
	{
		if((CH&(1<<i))!=0)
		{
			Drivers_S32K1xx_FTM_Channels_Type Channels;
			switch (i)
			{
				case 0:
				case 1:
				{
					Channels=Drivers_S32K1xx_FTM_Channels_CH01;
				}break;
				case 2:
				case 3:
				{
					Channels=Drivers_S32K1xx_FTM_Channels_CH23;
				}break;
				case 4:
				case 5:
				{
					Channels=Drivers_S32K1xx_FTM_Channels_CH45;
				}break;
				case 6:
				case 7:
				{
					Channels=Drivers_S32K1xx_FTM_Channels_CH67;
				}break;
				default:
					break;
			}
			Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Channels_Function_ChannelModes(
					P_FTM,
					Channels,
					(Channel_Modes>>7)&0x01,
					(Channel_Modes>>6)&0x01,
					(Channel_Modes>>5)&0x01));
			Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Channels_Function_Synchronization_Enabled(P_FTM,Channels,Synchronization_Enabled));

		}
	}
	Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Channel_Control_Modes(P_FTM,CH,(Channel_Modes>>2)&0x03,(Channel_Modes>>0)&0x03));

	return Error_OK;
}

/*

int Drivers_S32K1xx_FTM_SET_Demo(FTM_Type *P_FTM)
{
	if(P_FTM==Null)
	{
		return Error_Invalid_Parameter;
	}

	P_FTM->MODE.DATA |= FTM_MODE_WPDIS_MASK; //写保护禁 用
	P_FTM->MODE.DATA |= FTM_MODE_FTMEN_MASK; //FTM 使能

	P_FTM->SC.DATA = 0;//清除状态寄存器
	P_FTM->SC.DATA |= FTM_SC_PWMEN5_MASK | FTM_SC_PS(0);//CH5打开   分频因子选择 000b Divide by 1
	P_FTM->SC.DATA &= ~FTM_SC_TOF_MASK; //清除计数器溢出标志
	P_FTM->COMBINE.DATA = 0x00000000;// DECAPENx, MCOMBINEx, COMBINEx=0
	P_FTM->POL.DATA = 0x00000000; //设置通道输出的极性
	P_FTM->CNTIN.DATA = 0;//计数清零
	P_FTM->MOD.DATA = 100 -1;//设置周期 需要根据选择的时钟源
	// FTM1 Period = MOD-CNTIN+0x0001 ~= 2 ctr clks //


	P_FTM->CONTROLS[5].CnSC.DATA |= FTM_CnSC_MSA_MASK | FTM_CnSC_ELSA_MASK;//设置为输出比较
	P_FTM->CONTROLS[5].CnV.DATA = 20;//设置计算占空比

	P_FTM->SC.DATA |= FTM_SC_CLKS(1);  //时钟源选择
	P_FTM->SC.DATA |= (FTM_SC_PWMEN5_MASK);//打开通道，输出PWM


	return Error_OK;
}

*/


