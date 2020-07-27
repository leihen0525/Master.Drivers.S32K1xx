/*
 * Drivers.S32K1xx.SPI.c
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

#include "Drivers.S32K1xx.SPI.Enum.h"

#include "Drivers.S32K1xx.SPI.h"

#include "__Drivers.S32K1xx.SPI.Struct.h"
#include "Drivers.S32K1xx.SPI.Struct.h"

#include "Drivers.S32K1xx.LPSPI.h"

#include "Library/Library.FIFO.h"

Drivers_S32K1xx_SPI_DATA_Type Drivers_S32K1xx_SPI_DATA;

const __Sys_Device_OPS_Type __Device_OPS_SPI0=
{
	.Device_Name="SPI0",
	.Device_Args=LPSPI0,
	.Open=Drivers_S32K1xx_SPI_Open,
	.Close=Drivers_S32K1xx_SPI_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_SPI_Control,

	.Info="MCU:S32K1xx Module:SPI0 Version:0.0.1 "__DATE__" "__TIME__,
};

#if (defined (__Target_S32K118__) || defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
const __Sys_Device_OPS_Type __Device_OPS_SPI1=
{
	.Device_Name="SPI1",
	.Device_Args=LPSPI1,
	.Open=Drivers_S32K1xx_SPI_Open,
	.Close=Drivers_S32K1xx_SPI_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_SPI_Control,

	.Info="MCU:S32K1xx Module:SPI1 Version:0.0.1 "__DATE__" "__TIME__,
};
#endif

#if (defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
const __Sys_Device_OPS_Type __Device_OPS_SPI2=
{
	.Device_Name="SPI2",
	.Device_Args=LPSPI2,
	.Open=Drivers_S32K1xx_SPI_Open,
	.Close=Drivers_S32K1xx_SPI_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_SPI_Control,

	.Info="MCU:S32K1xx Module:SPI2 Version:0.0.1 "__DATE__" "__TIME__,
};
#endif
int Drivers_S32K1xx_SPI_Setup(void)
{
	int Err;

	for(int i=0;i<LPSPI_INSTANCE_COUNT;i++)
	{
		Drivers_S32K1xx_SPI_DATA.SPI[i].Open=false;

		Error_Args_Return(Drivers_S32K1xx_SPI_DATA.SPI[i].Semaphore,__Sys_Semaphore_Create(Null,1,1,Event_Queue_Option_FIFO));

		//初始化FIFO队列
		Error_NoArgs_Return(Err,Library_FIFO_1Byte_FIFO_Init(&Drivers_S32K1xx_SPI_DATA.SPI[i].TX_FIFO));
		Error_NoArgs_Return(Err,Library_FIFO_1Byte_FIFO_Init(&Drivers_S32K1xx_SPI_DATA.SPI[i].RX_FIFO));

		Drivers_S32K1xx_SPI_DATA.SPI[i].Tx_FIFO_Size=0;
		Drivers_S32K1xx_SPI_DATA.SPI[i].Rx_FIFO_Size=0;

		Error_Args_Return(Drivers_S32K1xx_SPI_DATA.SPI[i].Event_Flag,__Sys_Event_Flag_Create(Null,false));
	}

	//初始化中断函数和开启中断
	Error_Args_Return(Err,__Sys_IRQ_Register_Hook(LPSPI0_IRQn,Drivers_S32K1xx_SPI_IRQ,__Device_OPS_SPI0.Device_Args));
	Error_NoArgs_Return(Err,__Sys_IRQ_Enable(LPSPI0_IRQn));
	//注册当前设备的OPS
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_SPI0));

#if (defined (__Target_S32K118__) || defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Error_Args_Return(Err,__Sys_IRQ_Register_Hook(LPSPI1_IRQn,Drivers_S32K1xx_SPI_IRQ,__Device_OPS_SPI1.Device_Args));
	Error_NoArgs_Return(Err,__Sys_IRQ_Enable(LPSPI1_IRQn));
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_SPI1));
#endif
#if (defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Error_Args_Return(Err,__Sys_IRQ_Register_Hook(LPSPI2_IRQn,Drivers_S32K1xx_SPI_IRQ,__Device_OPS_SPI2.Device_Args));
	Error_NoArgs_Return(Err,__Sys_IRQ_Enable(LPSPI2_IRQn));
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_SPI2));
#endif

	//获取MCU时钟树
	Error_NoArgs_Return(Err,__Sys_BSP_UpData_Clock_Tree((void **)&Drivers_S32K1xx_SPI_DATA.Clock.Source,(void **)&Drivers_S32K1xx_SPI_DATA.Clock.Tree));
	return Error_OK;
}
int Drivers_S32K1xx_SPI_Open(void *Device_Args,int Mode)
{
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}

	int Err;
	int Index=Drivers_S32K1xx_SPI_GET_Count(Device_Args);

	//设备是独占的 不允许 多次打开
	if(Drivers_S32K1xx_SPI_DATA.SPI[Index].Open==true)
	{
		return Error_Exist;
	}

	//Mode 作为时钟源参数
	//改变模块时钟之前确保时钟是关闭的
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_SET_Clock_Enabled((LPSPI_Type *)Device_Args,Disable));

	//设置模块时钟源
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_SET_Clock_Source((LPSPI_Type *)Device_Args,(Drivers_S32K1xx_LPSPI_Clock_Source_Type)(Drivers_S32K1xx_SPI_Open_Mode_Clock_Source_Mask&Mode),Drivers_S32K1xx_SPI_DATA.Clock.Tree));

	//打开模块时钟
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_SET_Clock_Enabled((LPSPI_Type *)Device_Args,Enable));



	//绑定事件组到当前任务的TCB中
	//Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Open(Drivers_S32K1xx_SPI_DATA.SPI[Index].Interrupt_Flag_Event_Flag_Group));

	Drivers_S32K1xx_SPI_DATA.SPI[Index].Open=true;
	return Error_OK;
}
int Drivers_S32K1xx_SPI_Close(void *Device_Args)
{
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}
	int Err;
	int Index=Drivers_S32K1xx_SPI_GET_Count(Device_Args);

	//复位当前设备寄存器
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_Software_Reset((LPSPI_Type *)Device_Args));

	//关闭模块时钟
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_SET_Clock_Enabled((LPSPI_Type *)Device_Args,Disable));

	//清除当前任务的TCB中绑定的事件组
	//Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Close(Drivers_S32K1xx_SPI_DATA.SPI[Index].Interrupt_Flag_Event_Flag_Group));

	Drivers_S32K1xx_SPI_DATA.SPI[Index].Open=false;
	return Error_OK;
}
int Drivers_S32K1xx_SPI_Control(void *Device_Args,int Cmd, unsigned long Args)
{
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}
	int Index=Drivers_S32K1xx_SPI_GET_Count(Device_Args);
	int Err;

	switch (Cmd&Drivers_S32K1xx_SPI_Cmd_Mask)
	{
		case Drivers_S32K1xx_SPI_Cmd_Init:
		{
			Drivers_S32K1xx_SPI_Init_Type *P_SPI_Init=(Drivers_S32K1xx_SPI_Init_Type *)&Args;

			if(P_SPI_Init==Null)return Error_Invalid_Parameter;

			//复位模块寄存器
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_Software_Reset((LPSPI_Type *)Device_Args));

			//复位FIFO
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_Reset_FIFO((LPSPI_Type *)Device_Args,true,true));


			//设置PIN功能
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_SET_PIN_Config((LPSPI_Type *)Device_Args,(Drivers_S32K1xx_LPSPI_PIN_Config_Type)P_SPI_Init->Pin_Config));

			//开启设备功能
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_SET_Function_Enabled((LPSPI_Type *)Device_Args,Drivers_S32K1xx_LPSPI_Function_Debug,Enable));

			//开启设备中断
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_SET_Interrupt_Enabled((LPSPI_Type *)Device_Args,Drivers_S32K1xx_LPSPI_Interrupt_Frame_Complete,Enable));

			//打开模块
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_SET_Module_Enabled((LPSPI_Type *)Device_Args,Enable));
			return Error_OK;

		}break;

		case Drivers_S32K1xx_SPI_Cmd_Clock_Config:
		{
			Drivers_S32K1xx_SPI_Clock_Config_Type *P_Clock_Config=(Drivers_S32K1xx_SPI_Clock_Config_Type *)&Args;
			if(P_Clock_Config==Null)return Error_Invalid_Parameter;

			//检查模块时钟
			Error_Args_Return(Err,Drivers_S32K1xx_LPSPI_GET_Clock_Enabled((LPSPI_Type *)Device_Args));
			if(Err==Disable)return Error_No_Clock_Config;

			//读取模块状态
			int Enabled;
			Error_Args_Return(Enabled,Drivers_S32K1xx_LPSPI_GET_Module_Enabled((LPSPI_Type *)Device_Args));


			//先关闭模块
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_SET_Module_Enabled((LPSPI_Type *)Device_Args,Disable));

			//设置参数
			int Temp_Err;
			Error_NoArgs(Temp_Err,Drivers_S32K1xx_LPSPI_SET_Clock_Configuration(
												(LPSPI_Type *)Device_Args,
												P_Clock_Config->SCK_To_PCS_Delay,
												P_Clock_Config->PCS_To_SCK_Delay,
												P_Clock_Config->Between_Transfers_Delay,
												P_Clock_Config->SCK_Divider))
			{
				Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_SET_Module_Enabled((LPSPI_Type *)Device_Args,(Enabled_Type)Enabled));
				return Temp_Err;
			}
			//恢复模块
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPSPI_SET_Module_Enabled((LPSPI_Type *)Device_Args,(Enabled_Type)Enabled));

			return Error_OK;

		}break;

		case Drivers_S32K1xx_SPI_Cmd_Transmit_Cmd:
		{
			Err=Error_OK;
			int Temp_Err;

			Drivers_S32K1xx_SPI_Transmit_Cmd_Type *P_Transmit_Cmd=(Drivers_S32K1xx_SPI_Transmit_Cmd_Type *)Args;
			if(P_Transmit_Cmd==Null)return Error_Invalid_Parameter;

			if(P_Transmit_Cmd->Baud_Rate_kbps==0 || P_Transmit_Cmd->Tx_DATA==Null || P_Transmit_Cmd->Size==0)
			{
				return Error_Invalid_Parameter;
			}

			//
			Error_NoArgs_Return(Err,__Sys_Semaphore_Wait(Drivers_S32K1xx_SPI_DATA.SPI[Index].Semaphore,P_Transmit_Cmd->TimeOut));

			//Check Busy
			Error_Args(Err,Drivers_S32K1xx_LPSPI_GET_Interrupt_Flag((LPSPI_Type *)Device_Args))
			{
				goto Exit_Transmit_Cmd;
			}
			if((Err&Drivers_S32K1xx_LPSPI_Interrupt_Busy)!=0)
			{
				Err=Error_Busy;
				goto Exit_Transmit_Cmd;
			}


			//复位FIFO
			Error_NoArgs(Err,Drivers_S32K1xx_LPSPI_Reset_FIFO((LPSPI_Type *)Device_Args,true,true))
			{
				goto Exit_Transmit_Cmd;
			}
/*
			//The second flush command is used to avoid the case when one word is still in shifter
			Error_NoArgs(Err,Drivers_S32K1xx_LPSPI_Reset_FIFO((LPSPI_Type *)Device_Args,true,true))
			{
				goto Exit_Transmit_Cmd;
			}
*/


			Error_NoArgs(Err,__Sys_Event_Flag_Clear(Drivers_S32K1xx_SPI_DATA.SPI[Index].Event_Flag))
			{
				goto Exit_Transmit_Cmd;
			}


			Error_NoArgs(Err,__Sys_Event_Flag_Wait(Drivers_S32K1xx_SPI_DATA.SPI[Index].Event_Flag,P_Transmit_Cmd->TimeOut))
			{
				goto Exit_Transmit_Cmd;
			}




Exit_Transmit_Cmd:

			Error_NoArgs_Return(Temp_Err,__Sys_Semaphore_Release(Drivers_S32K1xx_SPI_DATA.SPI[Index].Semaphore,1,Null));

			return Err;
		}break;

		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
}
//---------------------------------------------------------------------------------------------------------
int Drivers_S32K1xx_SPI_GET_Count(void *Device_Args)
{
	switch ((uint32_t)Device_Args)
	{
		case LPSPI0_BASE:
		{
			return 0;
		}break;
#if (defined (__Target_S32K118__) || defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case LPSPI1_BASE:
		{
			return 1;
		}break;
#endif
#if (defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case LPSPI2_BASE:
		{
			return 2;
		}break;
#endif
		default:
		{
			while(1);//绝对不能出现
		}break;
	}
}
//----------------------------------------------------------------------------------------------------
void Drivers_S32K1xx_SPI_IRQ(void *Args,int IRQ_Index)
{
	int Err;
	LPSPI_Type *P_SPI=(LPSPI_Type *)Args;

	if(P_SPI==Null)return ;
	int Index=Drivers_S32K1xx_SPI_GET_Count(P_SPI);
	int Flag=Drivers_S32K1xx_LPSPI_GET_Interrupt_Flag(P_SPI);
	int Flag_Clear=0;
	if(Flag<Error_OK)
	{
		return ;
	}

	if((Flag&Drivers_S32K1xx_LPSPI_Interrupt_Data_Match)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPSPI_Interrupt_Data_Match;
	}

	if((Flag&Drivers_S32K1xx_LPSPI_Interrupt_Receive_Error)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPSPI_Interrupt_Receive_Error;
	}

	if((Flag&Drivers_S32K1xx_LPSPI_Interrupt_Transmit_Error)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPSPI_Interrupt_Transmit_Error;
	}

	if((Flag&Drivers_S32K1xx_LPSPI_Interrupt_Transfer_Complete)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPSPI_Interrupt_Transfer_Complete;
	}

	if((Flag&Drivers_S32K1xx_LPSPI_Interrupt_Frame_Complete)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPSPI_Interrupt_Frame_Complete;
	}

	if((Flag&Drivers_S32K1xx_LPSPI_Interrupt_Word_Complete)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPSPI_Interrupt_Word_Complete;
	}

	if((Flag&Drivers_S32K1xx_LPSPI_Interrupt_Receive_Data)!=0)
	{

	}

	if((Flag&Drivers_S32K1xx_LPSPI_Interrupt_Transmit_Data)!=0)
	{

	}

	if((Flag&Drivers_S32K1xx_LPSPI_Interrupt_Busy)!=0)
	{

	}
	Drivers_S32K1xx_LPSPI_Clear_Interrupt_Flag(P_SPI,(Drivers_S32K1xx_LPSPI_Interrupt_Type)Flag_Clear);

}
__Sys_Device_Module_Init_Export(Drivers_S32K1xx_SPI_Setup);

