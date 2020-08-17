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
