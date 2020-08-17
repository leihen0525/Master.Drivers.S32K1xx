/*
 * Drivers.S32K1xx.FlexTimer.c
 *
 *  Created on: 2020年7月19日
 *      Author: Master.HE
 */
#include "Error.h"
#include "Define.h"

#include "Device\__Sys.Device.h"

#include "Module\Module.h"

#include "__Sys.API.h"

#include "S32K1xx.h"

#include "Drivers.S32K1xx.FlexTimer.Enum.h"
#include "__Drivers.S32K1xx.FlexTimer.Struct.h"
#include "Drivers.S32K1xx.FlexTimer.Struct.h"
#include "Drivers.S32K1xx.FlexTimer.h"

#include "Drivers.S32K1xx.FTM.h"

Drivers_S32K1xx_FlexTimer_DATA_Type Drivers_S32K1xx_FlexTimer_DATA;

const __Sys_Device_OPS_Type __Device_OPS_FlexTimer0=
{
	.Device_Name="FlexTimer0",
	.Device_Args=FTM0,
	.Open=Drivers_S32K1xx_FlexTimer_Open,
	.Close=Drivers_S32K1xx_FlexTimer_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_FlexTimer_Control,

	.Info="MCU:S32K1xx Module:FlexTimer0 Version:0.0.1 "__DATE__" "__TIME__,
};
const __Sys_Device_OPS_Type __Device_OPS_FlexTimer1=
{
	.Device_Name="FlexTimer1",
	.Device_Args=FTM1,
	.Open=Drivers_S32K1xx_FlexTimer_Open,
	.Close=Drivers_S32K1xx_FlexTimer_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_FlexTimer_Control,

	.Info="MCU:S32K1xx Module:FlexTimer1 Version:0.0.1 "__DATE__" "__TIME__,
};
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
const __Sys_Device_OPS_Type __Device_OPS_FlexTimer2=
{
	.Device_Name="FlexTimer2",
	.Device_Args=FTM2,
	.Open=Drivers_S32K1xx_FlexTimer_Open,
	.Close=Drivers_S32K1xx_FlexTimer_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_FlexTimer_Control,

	.Info="MCU:S32K1xx Module:FlexTimer2 Version:0.0.1 "__DATE__" "__TIME__,
};
const __Sys_Device_OPS_Type __Device_OPS_FlexTimer3=
{
	.Device_Name="FlexTimer3",
	.Device_Args=FTM3,
	.Open=Drivers_S32K1xx_FlexTimer_Open,
	.Close=Drivers_S32K1xx_FlexTimer_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_FlexTimer_Control,

	.Info="MCU:S32K1xx Module:FlexTimer3 Version:0.0.1 "__DATE__" "__TIME__,
};
#if (defined (__Target_S32K146__) || defined (__Target_S32K148__))
const __Sys_Device_OPS_Type __Device_OPS_FlexTimer4=
{
	.Device_Name="FlexTimer4",
	.Device_Args=FTM4,
	.Open=Drivers_S32K1xx_FlexTimer_Open,
	.Close=Drivers_S32K1xx_FlexTimer_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_FlexTimer_Control,

	.Info="MCU:S32K1xx Module:FlexTimer4 Version:0.0.1 "__DATE__" "__TIME__,
};
const __Sys_Device_OPS_Type __Device_OPS_FlexTimer5=
{
	.Device_Name="FlexTimer5",
	.Device_Args=FTM5,
	.Open=Drivers_S32K1xx_FlexTimer_Open,
	.Close=Drivers_S32K1xx_FlexTimer_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_FlexTimer_Control,

	.Info="MCU:S32K1xx Module:FlexTimer5 Version:0.0.1 "__DATE__" "__TIME__,
};
#if (defined (__Target_S32K148__))
const __Sys_Device_OPS_Type __Device_OPS_FlexTimer6=
{
	.Device_Name="FlexTimer6",
	.Device_Args=FTM6,
	.Open=Drivers_S32K1xx_FlexTimer_Open,
	.Close=Drivers_S32K1xx_FlexTimer_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_FlexTimer_Control,

	.Info="MCU:S32K1xx Module:FlexTimer6 Version:0.0.1 "__DATE__" "__TIME__,
};
const __Sys_Device_OPS_Type __Device_OPS_FlexTimer7=
{
	.Device_Name="FlexTimer7",
	.Device_Args=FTM7,
	.Open=Drivers_S32K1xx_FlexTimer_Open,
	.Close=Drivers_S32K1xx_FlexTimer_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_FlexTimer_Control,

	.Info="MCU:S32K1xx Module:FlexTimer7 Version:0.0.1 "__DATE__" "__TIME__,
};
#endif

#endif

#endif

int Drivers_S32K1xx_FlexTimer_Setup(void)
{
	int Err;

	for(int i=0;i<FTM_INSTANCE_COUNT;i++)
	{
		Drivers_S32K1xx_FlexTimer_DATA.FlexTimer[i].Open=false;
		Drivers_S32K1xx_FlexTimer_DATA.FlexTimer[i].MOD=0;

	}

	//注册当前设备的OPS
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_FlexTimer0));
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_FlexTimer1));
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_FlexTimer2));
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_FlexTimer3));
#if (defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_FlexTimer4));
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_FlexTimer5));
#if (defined (__Target_S32K148__))
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_FlexTimer6));
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_FlexTimer7));
#endif

#endif

#endif
	//获取MCU时钟树
	Error_NoArgs_Return(Err,__Sys_BSP_UpData_Clock_Tree((void **)&Drivers_S32K1xx_FlexTimer_DATA.Clock.Source,(void **)&Drivers_S32K1xx_FlexTimer_DATA.Clock.Tree));
	return Error_OK;
}
int Drivers_S32K1xx_FlexTimer_Open(void *Device_Args,int Mode)
{
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}

	int Err;
	int Index=Drivers_S32K1xx_FlexTimer_GET_Count(Device_Args);

	//设备是独占的 不允许 多次打开
	if(Drivers_S32K1xx_FlexTimer_DATA.FlexTimer[Index].Open==true)
	{
		return Error_Exist;
	}

	//Mode 作为时钟源参数
	//改变模块时钟之前确保时钟是关闭的
	Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Clock_Source_Enabled((FTM_Type *)Device_Args,Drivers_S32K1xx_FTM_Clock_Source_Disable0,Disable,Null));

	//设置模块时钟源
	//打开模块时钟
	Error_Args_Return(Drivers_S32K1xx_FlexTimer_DATA.FlexTimer[Index].FTM_Frequency_Hz,Drivers_S32K1xx_FTM_SET_Clock_Source_Enabled((FTM_Type *)Device_Args,(Drivers_S32K1xx_FTM_Clock_Source_Type)(Drivers_S32K1xx_FlexTimer_Open_Mode_Clock_Source_Mask&Mode),Enable,Drivers_S32K1xx_FlexTimer_DATA.Clock.Tree));


	//Drivers_S32K1xx_FTM_SET_Demo((FTM_Type *)Device_Args);

	//绑定事件组到当前任务的TCB中
	//Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Open(Drivers_S32K1xx_FlexTimer_DATA.FlexTimer[Index].Interrupt_Flag_Event_Flag_Group));

	Drivers_S32K1xx_FlexTimer_DATA.FlexTimer[Index].Open=true;
	return Error_OK;
}
int Drivers_S32K1xx_FlexTimer_Close(void *Device_Args)
{
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}
	int Err;
	int Index=Drivers_S32K1xx_FlexTimer_GET_Count(Device_Args);

	//关闭所有通道
	Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Channel_PWM_Enabled((FTM_Type *)Device_Args,Drivers_S32K1xx_FTM_Channel_Mask,Disable));
	//关闭模块
	Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Module_Enabled((FTM_Type *)Device_Args,Disable));

	//关闭模块时钟
	Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Clock_Source_Enabled((FTM_Type *)Device_Args,Drivers_S32K1xx_FTM_Clock_Source_Disable0,Disable,Null));

	//清除当前任务的TCB中绑定的事件组
	//Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Close(Drivers_S32K1xx_FlexTimer_DATA.FlexTimer[Index].Interrupt_Flag_Event_Flag_Group));

	Drivers_S32K1xx_FlexTimer_DATA.FlexTimer[Index].Open=false;
	return Error_OK;
}
int Drivers_S32K1xx_FlexTimer_Control(void *Device_Args,int Cmd, unsigned long Args)
{
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}
	int Index=Drivers_S32K1xx_FlexTimer_GET_Count(Device_Args);
	int Err;

	switch (Cmd&Drivers_S32K1xx_FlexTimer_Cmd_Mask)
	{
		case Drivers_S32K1xx_FlexTimer_Cmd_Init:
		{
			Drivers_S32K1xx_FlexTimer_Init_Type *P_Init=(Drivers_S32K1xx_FlexTimer_Init_Type *)&Args;
			if(P_Init==Null)return Error_Invalid_Parameter;
			if(P_Init->Frequency_Hz==0)return Error_Invalid_Parameter;
			int Clock;

			Error_Args_Return(Clock,Drivers_S32K1xx_FTM_GET_Clock((FTM_Type *)Device_Args));

			Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Write_Protection_Enabled((FTM_Type *)Device_Args,Disable));

			Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Clock((FTM_Type *)Device_Args,Drivers_S32K1xx_FTM_Clock_Disable));

			Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Prescale((FTM_Type *)Device_Args,Drivers_S32K1xx_FTM_Prescale_Divide_By_1));

			uint32_t Temp_FTM_Frequency_Hz=0;
			Temp_FTM_Frequency_Hz=Drivers_S32K1xx_FlexTimer_DATA.FlexTimer[Index].FTM_Frequency_Hz/(P_Init->Frequency_Hz);

			if(Temp_FTM_Frequency_Hz>0xFFFF || Temp_FTM_Frequency_Hz==0)
			{
				return Error_Invalid_Parameter;
			}
			Drivers_S32K1xx_FlexTimer_DATA.FlexTimer[Index].MOD=Temp_FTM_Frequency_Hz;

			Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Modulo((FTM_Type *)Device_Args,Temp_FTM_Frequency_Hz-1));

			Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Center_Aligned_PWM((FTM_Type *)Device_Args,Drivers_S32K1xx_FTM_Center_Aligned_PWM_Counter_In_Up_Counting_Mode));

			Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Clock((FTM_Type *)Device_Args,(Drivers_S32K1xx_FTM_Clock_Type)Clock));
			//打开模块
			Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Module_Enabled((FTM_Type *)Device_Args,Enable));

			return Error_OK;
		}break;
		case Drivers_S32K1xx_FlexTimer_Cmd_SET_CH_Config:
		{
			Drivers_S32K1xx_FlexTimer_CH_Config_Type *P_CH_Config=(Drivers_S32K1xx_FlexTimer_CH_Config_Type *)&Args;
			if(P_CH_Config==Null)return Error_Invalid_Parameter;


			Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Channel_Modes((FTM_Type *)Device_Args,(Drivers_S32K1xx_FTM_Channel_Type)(Cmd&0xFFFF),Drivers_S32K1xx_FTM_Channel_Modes_PWM_Edge_Aligned_HighPulses,Enable));

			Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Channel_PWM_Enabled((FTM_Type *)Device_Args,(Drivers_S32K1xx_FTM_Channel_Type)(Cmd&0xFFFF),(Enabled_Type)P_CH_Config->Enabled));
			return Error_OK;
		}break;
		case Drivers_S32K1xx_FlexTimer_Cmd_SET_CH_Duty:
		{
			if(Args>100)return Error_Invalid_Parameter;
			uint32_t Value=0;
			Value=(Drivers_S32K1xx_FlexTimer_DATA.FlexTimer[Index].MOD*Args)/100;
			if(Value>Drivers_S32K1xx_FlexTimer_DATA.FlexTimer[Index].MOD)
			{
				return Error_Unknown;
			}
			Error_NoArgs_Return(Err,Drivers_S32K1xx_FTM_SET_Channel_Value((FTM_Type *)Device_Args,(Drivers_S32K1xx_FTM_Channel_Type)(Cmd&0xFFFF),Value));

			return Error_OK;
		}break;
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
}
//----------------------------------------------------------------------------------------------------
int Drivers_S32K1xx_FlexTimer_GET_Count(void *Device_Args)
{
	switch ((uint32_t)Device_Args)
	{
		case FTM0_BASE:
		{
			return 0;
		}break;
		case FTM1_BASE:
		{
			return 1;
		}break;
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case FTM2_BASE:
		{
			return 2;
		}break;
		case FTM3_BASE:
		{
			return 3;
		}break;
#if (defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case FTM4_BASE:
		{
			return 4;
		}break;
		case FTM5_BASE:
		{
			return 5;
		}break;
#if (defined (__Target_S32K148__))
		case FTM6_BASE:
		{
			return 6;
		}break;
		case FTM7_BASE:
		{
			return 7;
		}break;
#endif

#endif

#endif
		default:
		{
			while(1);//绝对不能出现
		}break;
	}
}
//----------------------------------------------------------------------------------------------------

__Sys_Device_Module_Init_Export(Drivers_S32K1xx_FlexTimer_Setup);

