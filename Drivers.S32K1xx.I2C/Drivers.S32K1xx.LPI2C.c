/*
 * Drivers.S32K1xx.LPI2C.c
 *
 *  Created on: 2020年7月27日
 *      Author: Master.HE
 */
#include "Error.h"
#include "Drivers.S32K1xx.LPI2C.h"


int Drivers_S32K1xx_LPI2C_SET_Clock_Source(
		LPI2C_Type *P_LPI2C,
		Drivers_S32K1xx_LPI2C_Clock_Source_Type Clock_Source,
		S32K1xx_Clock_Tree_Type *Tree)
{
	uint32_t Frequency=0;
	if(P_LPI2C==Null || Tree==Null)
	{
		return Error_Invalid_Parameter;
	}
	//时钟源检查
	switch (Clock_Source)
	{
		case Drivers_S32K1xx_LPI2C_Clock_Source_SOSCDIV2_CLK:
		{
			if(Tree->SOSCDIV2_CLK_Hz==0)
			{
				return Error_Invalid_Parameter;
			}
			Frequency=Tree->SOSCDIV2_CLK_Hz;
		}break;
		case Drivers_S32K1xx_LPI2C_Clock_Source_SIRCDIV2_CLK:
		{
			if(Tree->SIRCDIV2_CLK_Hz==0)
			{
				return Error_Invalid_Parameter;
			}
			Frequency=Tree->SIRCDIV2_CLK_Hz;
		}break;
		case Drivers_S32K1xx_LPI2C_Clock_Source_FIRCDIV2_CLK:
		{
			if(Tree->FIRCDIV2_CLK_Hz==0)
			{
				return Error_Invalid_Parameter;
			}
			Frequency=Tree->FIRCDIV2_CLK_Hz;
		}break;
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case Drivers_S32K1xx_LPI2C_Clock_Source_SPLLDIV2_CLK:
		{
			if(Tree->SPLLDIV2_CLK_Hz==0)
			{
				return Error_Invalid_Parameter;
			}
			Frequency=Tree->SPLLDIV2_CLK_Hz;
		}break;
#endif
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}

	switch ((uint32_t)P_LPI2C)
	{
		case LPI2C0_BASE:
		{
			PCC->PCCn_BIT[PCC_LPI2C0_INDEX].PCS=Clock_Source;
			if(PCC->PCCn_BIT[PCC_LPI2C0_INDEX].PCS!=Clock_Source)
			{
				return Error_Write_Register_Fault;
			}

		}break;
#if (defined (__Target_S32K148__))
		case LPI2C1_BASE:
		{
			PCC->PCCn_BIT[PCC_LPI2C1_INDEX].PCS=Clock_Source;
			if(PCC->PCCn_BIT[PCC_LPI2C1_INDEX].PCS!=Clock_Source)
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

	return Frequency;
}

int Drivers_S32K1xx_LPI2C_SET_Clock_Enabled(
		LPI2C_Type *P_LPI2C,
		Enabled_Type Enabled)
{
	if(P_LPI2C==Null || Enabled>=Enabled_End)
	{
		return Error_Invalid_Parameter;
	}
	switch ((uint32_t)P_LPI2C)
	{
		case LPI2C0_BASE:
		{
			PCC->PCCn_BIT[PCC_LPI2C0_INDEX].CGC=Enabled;
			if(PCC->PCCn_BIT[PCC_LPI2C0_INDEX].CGC==Enabled)
			{
				return Error_OK;
			}
			else
			{
				return Error_Write_Register_Fault;
			}

		}break;
#if (defined (__Target_S32K148__))
		case LPI2C1_BASE:
		{
			PCC->PCCn_BIT[PCC_LPI2C1_INDEX].CGC=Enabled;
			if(PCC->PCCn_BIT[PCC_LPI2C1_INDEX].CGC==Enabled)
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
int Drivers_S32K1xx_LPI2C_GET_Clock_Enabled(LPI2C_Type *P_LPI2C)
{
	if(P_LPI2C==Null)
	{
		return Error_Invalid_Parameter;
	}
	switch ((uint32_t)P_LPI2C)
	{
		case LPI2C0_BASE:
		{
			return PCC->PCCn_BIT[PCC_LPI2C0_INDEX].CGC;
		}break;
#if (defined (__Target_S32K148__))
		case LPI2C1_BASE:
		{
			return PCC->PCCn_BIT[PCC_LPI2C1_INDEX].CGC;
		}break;
#endif
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
}
