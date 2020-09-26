/*
 * __Drivers.S32K1xx.ADC.c
 *
 *  Created on: 2020年8月5日
 *      Author: Master.HE
 */
#include "Define.h"
#include "Error.h"
#include "__Drivers.S32K1xx.ADC.h"


int Drivers_S32K1xx_ADC_SET_Clock_Source_Enabled(
		ADC_Type *P_ADC,
		Drivers_S32K1xx_ADC_Clock_Source_Type Clock_Source,
		Enabled_Type Enabled,
		S32K1xx_Clock_Tree_Type *Tree)
{
	if(P_ADC==Null || Enabled>=Enabled_End)
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

			case Drivers_S32K1xx_ADC_Clock_Source_ALTCLK1_SOSCDIV2_CLK:
			{
				if(Tree->SOSCDIV2_CLK_Hz==0)
				{
					return Error_Invalid_Parameter;
				}
			}break;

			case Drivers_S32K1xx_ADC_Clock_Source_ALTCLK1_SIRCDIV2_CLK:
			{
				if(Tree->SIRCDIV2_CLK_Hz==0)
				{
					return Error_Invalid_Parameter;
				}
			}break;
			case Drivers_S32K1xx_ADC_Clock_Source_ALTCLK1_FIRCDIV2_CLK:
			{
				if(Tree->FIRCDIV2_CLK_Hz==0)
				{
					return Error_Invalid_Parameter;
				}
			}break;
	#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
			case Drivers_S32K1xx_ADC_Clock_Source_ALTCLK1_SPLLDIV2_CLK:
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
	}
	switch ((uint32_t)P_ADC)
	{
		case ADC0_BASE:
		{
			if(Enabled==Enable)
			{

				PCC->PCCn_BIT[PCC_ADC0_INDEX].PCS=((Clock_Source>>0)&0x07);
				if(PCC->PCCn_BIT[PCC_ADC0_INDEX].PCS!=((Clock_Source>>0)&0x07))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_ADC0_INDEX].CGC=Enable;
				if(PCC->PCCn_BIT[PCC_ADC0_INDEX].CGC!=Enable)
				{
					return Error_Write_Register_Fault;
				}

				ADC0->CFG1.BIT.ADICLK=((Clock_Source>>3)&0x03);
				if(ADC0->CFG1.BIT.ADICLK!=((Clock_Source>>3)&0x03))
				{
					return Error_Write_Register_Fault;
				}
			}
			else//Disable
			{
				PCC->PCCn_BIT[PCC_ADC0_INDEX].CGC=Disable;
				if(PCC->PCCn_BIT[PCC_ADC0_INDEX].CGC!=Disable)
				{
					return Error_Write_Register_Fault;
				}
			}
			return Error_OK;

		}break;
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case ADC1_BASE:
		{
			if(Enabled==Enable)
			{

				PCC->PCCn_BIT[PCC_ADC1_INDEX].PCS=((Clock_Source>>0)&0x07);
				if(PCC->PCCn_BIT[PCC_ADC1_INDEX].PCS!=((Clock_Source>>0)&0x07))
				{
					return Error_Write_Register_Fault;
				}

				PCC->PCCn_BIT[PCC_ADC1_INDEX].CGC=Enable;
				if(PCC->PCCn_BIT[PCC_ADC1_INDEX].CGC!=Enable)
				{
					return Error_Write_Register_Fault;
				}

				ADC1->CFG1.BIT.ADICLK=((Clock_Source>>3)&0x03);
				if(ADC1->CFG1.BIT.ADICLK!=((Clock_Source>>3)&0x03))
				{
					return Error_Write_Register_Fault;
				}
			}
			else//Disable
			{
				PCC->PCCn_BIT[PCC_ADC1_INDEX].CGC=Disable;
				if(PCC->PCCn_BIT[PCC_ADC1_INDEX].CGC!=Disable)
				{
					return Error_Write_Register_Fault;
				}
			}
			return Error_OK;

		}break;
#endif
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
}

int Drivers_S32K1xx_ADC_SET_AutoCalibration(ADC_Type *P_ADC)
{
	if(P_ADC==Null)
	{
		return Error_Invalid_Parameter;
	}
	ADC_SC3_Type SC3={.DATA=0};

	SC3.BIT.CAL=1;
	SC3.BIT.AVGE=1;
	SC3.BIT.AVGS=3;

	P_ADC->SC3.DATA=SC3.DATA;
	if(P_ADC->SC3.DATA!=SC3.DATA)
	{
		return Error_Write_Register_Fault;
	}
	uint16_t Timeout=0xFFFF;

	while(P_ADC->SC1[0].BIT.COCO==0)
	{
		Timeout--;
		if(Timeout==0)
		{
			return Error_Time_Out;
		}
	}
	return Error_OK;

}
int Drivers_S32K1xx_ADC_Init(ADC_Type *P_ADC)
{
	if(P_ADC==Null)
	{
		return Error_Invalid_Parameter;
	}
	ADC_SC1_Type SC1={.DATA=0};
	SC1.BIT.ADCH=ADC_SC1_ADCH_MASK;

	P_ADC->SC1[0].DATA=SC1.DATA;
	if(P_ADC->SC1[0].DATA!=SC1.DATA)
	{
		return Error_Write_Register_Fault;
	}

	ADC_CFG1_Type CFG1={.DATA=0};
	CFG1.BIT.ADIV=0;
	CFG1.BIT.MODE=1;
	P_ADC->CFG1.DATA=CFG1.DATA;
	if(P_ADC->CFG1.DATA!=CFG1.DATA)
	{
		return Error_Write_Register_Fault;
	}

	ADC_CFG2_Type CFG2={.DATA=0};
	CFG2.BIT.SMPLTS=12;
	P_ADC->CFG2.DATA=CFG2.DATA;
	if(P_ADC->CFG2.DATA!=CFG2.DATA)
	{
		return Error_Write_Register_Fault;
	}

	ADC_SC2_Type SC2={.DATA=0};
	SC2.BIT.ADTRG=0;
	P_ADC->SC2.DATA=SC2.DATA;
	if(P_ADC->SC2.DATA!=SC2.DATA)
	{
		return Error_Write_Register_Fault;
	}

	ADC_SC3_Type SC3={.DATA=0};
	P_ADC->SC3.DATA=SC3.DATA;
	if((P_ADC->SC3.DATA&ADC_SC3_MASK)!=SC3.DATA)
	{
		return Error_Write_Register_Fault;
	}
	return Error_OK;
}
int Drivers_S32K1xx_ADC_GET_Channel_DATA(ADC_Type *P_ADC,uint8_t Channel,uint32_t *DATA)
{
	if(P_ADC==Null || Channel>0x3F || DATA==Null)
	{
		return Error_Invalid_Parameter;
	}
	P_ADC->SC1[0].DATA=Channel;

	uint16_t Timeout=0xFFFF;

	while(P_ADC->SC1[0].BIT.COCO==0)
	{
		Timeout--;
		if(Timeout==0)
		{
			return Error_Time_Out;
		}
	}
	*DATA=P_ADC->R[0].DATA;
	return Error_OK;

}
