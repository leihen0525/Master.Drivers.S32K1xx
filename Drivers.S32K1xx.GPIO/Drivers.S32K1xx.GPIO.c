/*
 * Drivers.S32K1xx.GPIO.c
 *
 *  Created on: 2019年12月4日
 *      Author: Master.HE
 */
#include "Error.h"

#include "Device\__Sys.Device.h"

#include "Module\Module.h"

#include "S32K1xx.h"

#include "Drivers.S32K1xx.GPIO.h"
#include "Drivers.S32K1xx.GPIO.Define.h"
#include "Drivers.S32K1xx.GPIO.Enum.h"
#include "Drivers.S32K1xx.GPIO.Struct.h"


const __Sys_Device_OPS_Type __Device_OPS_GPIO=
{
	.Device_Name="GPIO",
	.Device_Args=Null,
	.Open=Null,//Drivers_S32K1xx_GPIO_Open,
	.Close=Null,//Drivers_S32K1xx_GPIO_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_GPIO_Control,

	.Info="MCU:S32K1xx Module:GPIO Version:0.0.1 "__DATE__" "__TIME__,
};

int Drivers_S32K1xx_GPIO_Setup(void)
{
	PCC->PCCn_BIT[PCC_PORTA_INDEX].CGC=true;
	PCC->PCCn_BIT[PCC_PORTB_INDEX].CGC=true;
	PCC->PCCn_BIT[PCC_PORTC_INDEX].CGC=true;
	PCC->PCCn_BIT[PCC_PORTD_INDEX].CGC=true;
	PCC->PCCn_BIT[PCC_PORTE_INDEX].CGC=true;

	if(PCC->PCCn_BIT[PCC_PORTA_INDEX].CGC!=true
	|| PCC->PCCn_BIT[PCC_PORTB_INDEX].CGC!=true
	|| PCC->PCCn_BIT[PCC_PORTC_INDEX].CGC!=true
	|| PCC->PCCn_BIT[PCC_PORTD_INDEX].CGC!=true
	|| PCC->PCCn_BIT[PCC_PORTE_INDEX].CGC!=true)
	{
		return Error_Write_Register_Fault;
	}

	__Sys_Device_Register_Drivers(&__Device_OPS_GPIO);

	return Error_OK;
}
/*
int Drivers_S32K1xx_GPIO_Open(void *Device_Args,int Mode)
{
	PCC->PCCn_BIT[PCC_PORTA_INDEX].CGC=1;
	PCC->PCCn_BIT[PCC_PORTB_INDEX].CGC=1;
	PCC->PCCn_BIT[PCC_PORTC_INDEX].CGC=1;
	PCC->PCCn_BIT[PCC_PORTD_INDEX].CGC=1;
	PCC->PCCn_BIT[PCC_PORTE_INDEX].CGC=1;

	if(PCC->PCCn_BIT[PCC_PORTA_INDEX].CGC!=1
	|| PCC->PCCn_BIT[PCC_PORTB_INDEX].CGC!=1
	|| PCC->PCCn_BIT[PCC_PORTC_INDEX].CGC!=1
	|| PCC->PCCn_BIT[PCC_PORTD_INDEX].CGC!=1
	|| PCC->PCCn_BIT[PCC_PORTE_INDEX].CGC!=1)
	{
		return Error_Operation_Failed;
	}
	else
	{
		return Error_OK;
	}
}
int Drivers_S32K1xx_GPIO_Close(void *Device_Args)
{
	PCC->PCCn_BIT[PCC_PORTA_INDEX].CGC=0;
	PCC->PCCn_BIT[PCC_PORTB_INDEX].CGC=0;
	PCC->PCCn_BIT[PCC_PORTC_INDEX].CGC=0;
	PCC->PCCn_BIT[PCC_PORTD_INDEX].CGC=0;
	PCC->PCCn_BIT[PCC_PORTE_INDEX].CGC=0;

	if(PCC->PCCn_BIT[PCC_PORTA_INDEX].CGC!=0
	|| PCC->PCCn_BIT[PCC_PORTB_INDEX].CGC!=0
	|| PCC->PCCn_BIT[PCC_PORTC_INDEX].CGC!=0
	|| PCC->PCCn_BIT[PCC_PORTD_INDEX].CGC!=0
	|| PCC->PCCn_BIT[PCC_PORTE_INDEX].CGC!=0)
	{
		return Error_Operation_Failed;
	}
	else
	{
		return Error_OK;
	}
}
*/
int Drivers_S32K1xx_GPIO_Control(void *Device_Args,int Cmd, unsigned long Args)
{
	switch (Cmd&Drivers_S32K1xx_GPIO_Cmd_GPIO_Mask)
	{
	/*
		case Drivers_S32K1xx_GPIO_Cmd_SET_Clock_Enable:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}

			if(Args==Enable)
			{
				PCC->PCCn_BIT[PCC_PORTA_INDEX+GPIOx].CGC=1;
			}
			else if(Args==Disable)
			{
				PCC->PCCn_BIT[PCC_PORTA_INDEX+GPIOx].CGC=0;
			}
			else
			{
				return Error_Invalid_Parameter;
			}
			return Error_OK;
		}break;
*/
		case Drivers_S32K1xx_GPIO_Cmd_SET_Option:
		{
			Drivers_S32K1xx_GPIO_Cmd_Option_Type *P_Option=(Drivers_S32K1xx_GPIO_Cmd_Option_Type *)&Args;

			uint16_t GPIOx=(Cmd>>8)&0xFF;
			uint16_t CHn=(Cmd)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End || CHn>=Drivers_S32K1xx_GPIOx_CHn_Max)
			{
				return Error_Invalid_Parameter;
			}

			if(P_Option->Pull==Drivers_S32K1xx_GPIO_Option_Pull_None)
			{
				PORT->Index[GPIOx].PCR[CHn].Bit.PE=0;
			}
			else if(P_Option->Pull==Drivers_S32K1xx_GPIO_Option_Pull_Down)
			{
				PORT->Index[GPIOx].PCR[CHn].Bit.PE=1;
				PORT->Index[GPIOx].PCR[CHn].Bit.PS=0;
			}
			else if(P_Option->Pull==Drivers_S32K1xx_GPIO_Option_Pull_Up)
			{
				PORT->Index[GPIOx].PCR[CHn].Bit.PE=1;
				PORT->Index[GPIOx].PCR[CHn].Bit.PS=1;
			}
			else
			{
				return Error_Invalid_Parameter;
			}

			PORT->Index[GPIOx].PCR[CHn].Bit.PFE=P_Option->Passive_Filter_Enable;
			PORT->Index[GPIOx].PCR[CHn].Bit.DSE=P_Option->Drive_Strength_Enable;

			PORT->Index[GPIOx].PCR[CHn].Bit.MUX=P_Option->MUX_Control;

			PORT->Index[GPIOx].PCR[CHn].Bit.LK=P_Option->Lock_Register_Enable;

			PORT->Index[GPIOx].PCR[CHn].Bit.IRQC=P_Option->Interrupt_Config;

			PORT->Index[GPIOx].PCR[CHn].DATA=PORT->Index[GPIOx].PCR[CHn].DATA|PORT_PCR_ISF_MASK;

			return Error_OK;

		}break;

		case Drivers_S32K1xx_GPIO_Cmd_SET_DDR:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}

			GPIO->Index[GPIOx].PDDR.DATA=Args;

			return Error_OK;
		}break;

		case Drivers_S32K1xx_GPIO_Cmd_SET_DDR_Set:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}

			GPIO->Index[GPIOx].PDDR.DATA=GPIO->Index[GPIOx].PDDR.DATA|Args;

			return Error_OK;

		}break;

		case Drivers_S32K1xx_GPIO_Cmd_SET_DDR_Clear:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}

			GPIO->Index[GPIOx].PDDR.DATA=GPIO->Index[GPIOx].PDDR.DATA&(~Args);

			return Error_OK;
		}break;

		case Drivers_S32K1xx_GPIO_Cmd_SET_OUT_DATA:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}

			GPIO->Index[GPIOx].PDOR.DATA=Args;

			return Error_OK;
		}break;

		case Drivers_S32K1xx_GPIO_Cmd_SET_OUT_DATA_Set:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}

			GPIO->Index[GPIOx].PSOR.DATA=Args;

			return Error_OK;
		}break;

		case Drivers_S32K1xx_GPIO_Cmd_SET_OUT_DATA_Clear:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}

			GPIO->Index[GPIOx].PCOR.DATA=Args;

			return Error_OK;
		}break;

		case Drivers_S32K1xx_GPIO_Cmd_SET_OUT_DATA_Toggle:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}

			GPIO->Index[GPIOx].PTOR.DATA=Args;

			return Error_OK;
		}break;

		case Drivers_S32K1xx_GPIO_Cmd_SET_Input_Disable:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}

			GPIO->Index[GPIOx].PIDR.DATA=Args;

			return Error_OK;
		}break;
		case Drivers_S32K1xx_GPIO_Cmd_SET_Input_Disable_Set:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}

			GPIO->Index[GPIOx].PIDR.DATA=GPIO->Index[GPIOx].PIDR.DATA|Args;

			return Error_OK;
		}break;

		case Drivers_S32K1xx_GPIO_Cmd_SET_Input_Disable_Clear:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}

			GPIO->Index[GPIOx].PIDR.DATA=GPIO->Index[GPIOx].PIDR.DATA&(~Args);

			return Error_OK;
		}break;

		case Drivers_S32K1xx_GPIO_Cmd_GET_DDR:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}
			uint32_t *P_DATA=(uint32_t *)Args;
			if(P_DATA==Null)
			{
				return Error_Invalid_Parameter;
			}

			*P_DATA=GPIO->Index[GPIOx].PDDR.DATA;

			return Error_OK;
		}break;

		case Drivers_S32K1xx_GPIO_Cmd_GET_IN_DATA:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}
			uint32_t *P_DATA=(uint32_t *)Args;
			if(P_DATA==Null)
			{
				return Error_Invalid_Parameter;
			}

			*P_DATA=GPIO->Index[GPIOx].PDIR.DATA;

			return Error_OK;
		}break;

		case Drivers_S32K1xx_GPIO_Cmd_GET_OUT_DATA:
		{
			uint16_t GPIOx=(Cmd>>8)&0xFF;

			if(GPIOx>=Drivers_S32K1xx_GPIO_End)
			{
				return Error_Invalid_Parameter;
			}
			uint32_t *P_DATA=(uint32_t *)Args;
			if(P_DATA==Null)
			{
				return Error_Invalid_Parameter;
			}

			*P_DATA=GPIO->Index[GPIOx].PDOR.DATA;

			return Error_OK;
		}break;

		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
}




__Sys_Device_Module_Init_Export(Drivers_S32K1xx_GPIO_Setup);
