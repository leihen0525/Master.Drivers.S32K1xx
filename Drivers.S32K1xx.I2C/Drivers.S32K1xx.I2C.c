/*
 * Drivers.S32K1xx.I2C.c
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

#include "Drivers.S32K1xx.I2C.Struct.h"
#include "__Drivers.S32K1xx.I2C.Struct.h"

#include "Drivers.S32K1xx.I2C.Enum.h"
#include "Drivers.S32K1xx.I2C.h"

#include "Drivers.S32K1xx.LPI2C.h"

#include "Library/Library.FIFO.h"

Drivers_S32K1xx_I2C_DATA_Type Drivers_S32K1xx_I2C_DATA;

const __Sys_Device_OPS_Type __Device_OPS_I2C0=
{
	.Device_Name="I2C0",
	.Device_Args=LPI2C0,
	.Open=Drivers_S32K1xx_I2C_Open,
	.Close=Drivers_S32K1xx_I2C_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_I2C_Control,

	.Info="MCU:S32K1xx Module:I2C0 Version:0.0.1 "__DATE__" "__TIME__,
};

#if (defined (__Target_S32K148__))
const __Sys_Device_OPS_Type __Device_OPS_I2C1=
{
	.Device_Name="I2C1",
	.Device_Args=LPI2C1,
	.Open=Drivers_S32K1xx_I2C_Open,
	.Close=Drivers_S32K1xx_I2C_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_I2C_Control,

	.Info="MCU:S32K1xx Module:I2C1 Version:0.0.1 "__DATE__" "__TIME__,
};
#endif

int Drivers_S32K1xx_I2C_Setup(void)
{
	int Err;

	for(int i=0;i<LPI2C_INSTANCE_COUNT;i++)
	{
		Drivers_S32K1xx_I2C_DATA.I2C[i].Error=Drivers_S32K1xx_I2C_Error_OK;

		Drivers_S32K1xx_I2C_DATA.I2C[i].Open=false;

		Error_Args_Return(Drivers_S32K1xx_I2C_DATA.I2C[i].Semaphore,__Sys_Semaphore_Create(Null,1,1,Event_Queue_Option_FIFO));

		//初始化FIFO队列
		Error_NoArgs_Return(Err,Library_FIFO_2Byte_FIFO_Init(&Drivers_S32K1xx_I2C_DATA.I2C[i].TX_FIFO));
		Error_NoArgs_Return(Err,Library_FIFO_1Byte_FIFO_Init(&Drivers_S32K1xx_I2C_DATA.I2C[i].RX_FIFO));

		Drivers_S32K1xx_I2C_DATA.I2C[i].Tx_FIFO_Size=0;
		Drivers_S32K1xx_I2C_DATA.I2C[i].Rx_FIFO_Size=0;

		Error_Args_Return(Drivers_S32K1xx_I2C_DATA.I2C[i].Event_Flag,__Sys_Event_Flag_Create(Null,false));

	}

	//初始化中断函数和开启中断
#if (defined (__Target_S32K116__) || defined (__Target_S32K118__))
	Error_Args_Return(Err,__Sys_IRQ_Register_Hook(LPI2C0_Master_Slave_IRQn,Drivers_S32K1xx_I2C_Master_Slave_IRQ,__Device_OPS_I2C0.Device_Args));
	Error_NoArgs_Return(Err,__Sys_IRQ_Enable(LPI2C0_Master_Slave_IRQn));
#elif (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Error_Args_Return(Err,__Sys_IRQ_Register_Hook(LPI2C0_Master_IRQn,Drivers_S32K1xx_I2C_Master_IRQ,__Device_OPS_I2C0.Device_Args));
	Error_NoArgs_Return(Err,__Sys_IRQ_Enable(LPI2C0_Master_IRQn));

	Error_Args_Return(Err,__Sys_IRQ_Register_Hook(LPI2C0_Slave_IRQn,Drivers_S32K1xx_I2C_Slave_IRQ,__Device_OPS_I2C0.Device_Args));
	Error_NoArgs_Return(Err,__Sys_IRQ_Enable(LPI2C0_Slave_IRQn));
#endif
	//注册当前设备的OPS
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_I2C0));

#if (defined (__Target_S32K148__))
	Error_Args_Return(Err,__Sys_IRQ_Register_Hook(LPI2C1_Master_IRQn,Drivers_S32K1xx_I2C_Master_IRQ,__Device_OPS_I2C1.Device_Args));
	Error_NoArgs_Return(Err,__Sys_IRQ_Enable(LPI2C1_Master_IRQn));

	Error_Args_Return(Err,__Sys_IRQ_Register_Hook(LPI2C1_Slave_IRQn,Drivers_S32K1xx_I2C_Slave_IRQ,__Device_OPS_I2C1.Device_Args));
	Error_NoArgs_Return(Err,__Sys_IRQ_Enable(LPI2C1_Slave_IRQn));

	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_I2C1));
#endif

	//获取MCU时钟树
	Error_NoArgs_Return(Err,__Sys_BSP_UpData_Clock_Tree((void **)&Drivers_S32K1xx_I2C_DATA.Clock.Source,(void **)&Drivers_S32K1xx_I2C_DATA.Clock.Tree));
	return Error_OK;
}
int Drivers_S32K1xx_I2C_Open(void *Device_Args,int Mode)
{
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}
	int Frequency=0;
	int Err;
	int Index=Drivers_S32K1xx_I2C_GET_Count(Device_Args);

	//设备是独占的 不允许 多次打开
	if(Drivers_S32K1xx_I2C_DATA.I2C[Index].Open==true)
	{
		return Error_Exist;
	}

	//Mode 作为时钟源参数
	//改变模块时钟之前确保时钟是关闭的
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_SET_Clock_Enabled((LPI2C_Type *)Device_Args,Disable));

	//设置模块时钟源
	Error_Args_Return(Frequency,Drivers_S32K1xx_LPI2C_SET_Clock_Source((LPI2C_Type *)Device_Args,(Drivers_S32K1xx_LPI2C_Clock_Source_Type)(Drivers_S32K1xx_I2C_Open_Mode_Clock_Source_Mask&Mode),Drivers_S32K1xx_I2C_DATA.Clock.Tree));

	//TODO 暂时只支持48M频率
	if(Frequency!=48000000)
	{
		return Error_Invalid_Parameter;
	}

	//打开模块时钟
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_SET_Clock_Enabled((LPI2C_Type *)Device_Args,Enable));



	//绑定事件组到当前任务的TCB中
	//Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Open(Drivers_S32K1xx_I2C_DATA.I2C[Index].Interrupt_Flag_Event_Flag_Group));

	Drivers_S32K1xx_I2C_DATA.I2C[Index].Open=true;
	return Error_OK;
}
int Drivers_S32K1xx_I2C_Close(void *Device_Args)
{
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}
	int Err;
	int Index=Drivers_S32K1xx_I2C_GET_Count(Device_Args);

	//复位当前设备寄存器
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_Software_Reset((LPI2C_Type *)Device_Args));

	//关闭模块时钟
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_SET_Clock_Enabled((LPI2C_Type *)Device_Args,Disable));

	//清除当前任务的TCB中绑定的事件组
	//Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Close(Drivers_S32K1xx_I2C_DATA.I2C[Index].Interrupt_Flag_Event_Flag_Group));

	Drivers_S32K1xx_I2C_DATA.I2C[Index].Open=false;
	return Error_OK;
}
int Drivers_S32K1xx_I2C_Control(void *Device_Args,int Cmd, unsigned long Args)
{
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}
	int Index=Drivers_S32K1xx_I2C_GET_Count(Device_Args);
	int Err;

	switch (Cmd&Drivers_S32K1xx_I2C_Cmd_Mask)
	{
		case Drivers_S32K1xx_I2C_Cmd_Master_Init:
		{
			Drivers_S32K1xx_I2C_Master_Init_Type *P_Init=(Drivers_S32K1xx_I2C_Master_Init_Type *)&Args;
			if(P_Init==Null)return Error_Invalid_Parameter;

			//复位模块寄存器
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_Software_Reset((LPI2C_Type *)Device_Args));

			//复位FIFO
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_Reset_FIFO((LPI2C_Type *)Device_Args,true,true));


			//设置PIN功能
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_SET_PIN_Config((LPI2C_Type *)Device_Args,Drivers_S32K1xx_LPI2C_Master_PIN_Config_2PinOpenDrain));

			//开启设备功能
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_SET_Function_Enabled((LPI2C_Type *)Device_Args,Drivers_S32K1xx_LPI2C_Master_Function_Debug,Enable));

			//开启设备中断
			//Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_SET_Interrupt_Enabled((LPI2C_Type *)Device_Args,Drivers_S32K1xx_LPI2C_Master_Interrupt_Frame_Complete,Enable));

			//48M Clock Frequency
			switch (P_Init->Baud_Rate)
			{
				case Drivers_S32K1xx_I2C_Baud_Rate_400Kbps:
				{
					//PRESCALE=0x00
					Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_SET_Prescaler((LPI2C_Type *)Device_Args,Drivers_S32K1xx_LPI2C_Master_Prescaler_Divide_By_1));

					//FILTSCL=0x01 FILTSDA=0x01
					Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_SET_Glitch_Filter((LPI2C_Type *)Device_Args,0x01,0x01));

					//DATAVD=0x0F SETHOLD=0x1D CLKHI=0x35 CLKLO=0x3E
					Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_SET_Clock_Configuration_0((LPI2C_Type *)Device_Args,0x0F,0x1D,0x35,0x3E));
				}break;
				case Drivers_S32K1xx_I2C_Baud_Rate_1000Kbps:
				{
					//PRESCALE=0x02
					Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_SET_Prescaler((LPI2C_Type *)Device_Args,Drivers_S32K1xx_LPI2C_Master_Prescaler_Divide_By_4));

					//FILTSCL=0x01 FILTSDA=0x01
					Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_SET_Glitch_Filter((LPI2C_Type *)Device_Args,0x01,0x01));

					//DATAVD=0x04 SETHOLD=0x03 CLKHI=0x04 CLKLO=0x06
					Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_SET_Clock_Configuration_0((LPI2C_Type *)Device_Args,0x04,0x03,0x04,0x06));
				}break;
				case Drivers_S32K1xx_I2C_Baud_Rate_3200Kbps:
				{
					//PRESCALE=0x00
					Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_SET_Prescaler((LPI2C_Type *)Device_Args,Drivers_S32K1xx_LPI2C_Master_Prescaler_Divide_By_1));

					//FILTSCL=0x00 FILTSDA=0x00
					Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_SET_Glitch_Filter((LPI2C_Type *)Device_Args,0x00,0x00));

					//DATAVD=0x01 SETHOLD=0x07 CLKHI=0x03 CLKLO=0x08
					Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_SET_Clock_Configuration_0((LPI2C_Type *)Device_Args,0x01,0x07,0x03,0x08));
				}break;

				default:
				{
					return Error_Invalid_Parameter;
				}break;
			}

			//打开模块
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPI2C_Master_SET_Module_Enabled((LPI2C_Type *)Device_Args,Enable));
			return Error_OK;

		}break;

		case Drivers_S32K1xx_I2C_Cmd_Master_Transmit_Cmd:
		{
			Err=Error_OK;
			int Temp_Err;

			Drivers_S32K1xx_I2C_Master_Transmit_Cmd_Type *P_Transmit_Cmd=(Drivers_S32K1xx_I2C_Master_Transmit_Cmd_Type *)Args;
			if(P_Transmit_Cmd==Null)return Error_Invalid_Parameter;

			//参数检查
			if((P_Transmit_Cmd->DATA==Null && P_Transmit_Cmd->Size!=0)
			|| (P_Transmit_Cmd->RepeatedDATA==Null && P_Transmit_Cmd->RepeatedSize!=0)
			|| (P_Transmit_Cmd->Slave_Address_10Bit==false && (P_Transmit_Cmd->DATA==Null || P_Transmit_Cmd->Size==0))
			|| (P_Transmit_Cmd->RepeatedSTART==true && (P_Transmit_Cmd->RepeatedDATA==Null || P_Transmit_Cmd->RepeatedSize==0))
			|| (P_Transmit_Cmd->Slave_Address_10Bit==true && P_Transmit_Cmd->Read==true))//这个地方？规范是这么写的 我还没有研究
			{
				return Error_Invalid_Parameter;
			}

			Error_NoArgs_Return(Err,__Sys_Semaphore_Wait(Drivers_S32K1xx_I2C_DATA.I2C[Index].Semaphore,P_Transmit_Cmd->TimeOut));

			//Check Busy
			Error_Args(Err,Drivers_S32K1xx_LPI2C_Master_GET_Interrupt_Flag((LPI2C_Type *)Device_Args))
			{
				goto Exit_I2C_Transmit_Cmd;
			}
			//检查总线忙 或者 I2C模块忙
			if((Err&Drivers_S32K1xx_LPI2C_Master_Interrupt_Bus_Busy)!=0 || (Err&Drivers_S32K1xx_LPI2C_Master_Interrupt_Master_Busy)!=0)
			{
				Err=Error_Busy;
				goto Exit_I2C_Transmit_Cmd;
			}

			//复位FIFO
			Error_NoArgs(Err,Drivers_S32K1xx_LPI2C_Master_Reset_FIFO((LPI2C_Type *)Device_Args,true,true))
			{
				goto Exit_I2C_Transmit_Cmd;
			}
			//初始化FIFO队列
			Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_Init(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO))
			{
				goto Exit_I2C_Transmit_Cmd;
			}
			Error_NoArgs(Err,Library_FIFO_1Byte_FIFO_Init(&Drivers_S32K1xx_I2C_DATA.I2C[Index].RX_FIFO))
			{
				goto Exit_I2C_Transmit_Cmd;
			}

			Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size=0;
			Drivers_S32K1xx_I2C_DATA.I2C[Index].Rx_FIFO_Size=0;
			//准备数据
			uint16_t Temp_DATA;
			if(P_Transmit_Cmd->Slave_Address_10Bit==true)
			{
				//Slave_Address_1st
				Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Generate_START_And_Transmit_Address<<8)|(P_Transmit_Cmd->Slave_Address_1st<<1)|P_Transmit_Cmd->Read;
				Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
				{
					goto Exit_I2C_Transmit_Cmd;
				}
				Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;

				//Slave_Address_2nd
				Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Transmit_DATA<<8)|P_Transmit_Cmd->Slave_Address_2nd;
				Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
				{
					goto Exit_I2C_Transmit_Cmd;
				}
				Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;

				//DATA// 这个地方只能是发送数据 不能是接收数据 为什么 我是按照I2C协议来的。。。。。。
				for(int i=0;i<P_Transmit_Cmd->Size;i++)
				{
					Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Transmit_DATA<<8)|P_Transmit_Cmd->DATA[i];
					Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
					{
						goto Exit_I2C_Transmit_Cmd;
					}
					Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;
				}

				//RepeatedSTART
				if(P_Transmit_Cmd->RepeatedSTART==true)
				{
					//Slave_Address_1st
					Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Generate_START_And_Transmit_Address<<8)|(P_Transmit_Cmd->Slave_Address_1st<<1)|P_Transmit_Cmd->RepeatedRead;
					Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
					{
						goto Exit_I2C_Transmit_Cmd;
					}
					Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;

					if(P_Transmit_Cmd->RepeatedRead==true)
					{
						//RepeatedDATA
						for(int i=0;i<P_Transmit_Cmd->RepeatedSize;i++)
						{
							Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Receive_DATA_ACK<<8);
							Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
							{
								goto Exit_I2C_Transmit_Cmd;
							}
							Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;
							Drivers_S32K1xx_I2C_DATA.I2C[Index].Rx_FIFO_Size++;
						}
					}
					else
					{
						//Slave_Address_2nd
						Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Transmit_DATA<<8)|P_Transmit_Cmd->Slave_Address_2nd;
						Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
						{
							goto Exit_I2C_Transmit_Cmd;
						}
						Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;

						//RepeatedDATA
						for(int i=0;i<P_Transmit_Cmd->RepeatedSize;i++)
						{
							Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Transmit_DATA<<8)|P_Transmit_Cmd->RepeatedDATA[i];
							Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
							{
								goto Exit_I2C_Transmit_Cmd;
							}
							Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;
						}
					}
				}
			}
			else
			{
				//Slave_Address_1st
				Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Generate_START_And_Transmit_Address<<8)|(P_Transmit_Cmd->Slave_Address_1st<<1)|P_Transmit_Cmd->Read;
				Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
				{
					goto Exit_I2C_Transmit_Cmd;
				}
				Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;

				if(P_Transmit_Cmd->Read==true)
				{
					//DATA
					for(int i=0;i<P_Transmit_Cmd->Size;i++)
					{
						Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Receive_DATA_ACK<<8);
						Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
						{
							goto Exit_I2C_Transmit_Cmd;
						}
						Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;
						Drivers_S32K1xx_I2C_DATA.I2C[Index].Rx_FIFO_Size++;
					}
				}
				else
				{
					//DATA
					for(int i=0;i<P_Transmit_Cmd->Size;i++)
					{
						Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Transmit_DATA<<8)|P_Transmit_Cmd->DATA[i];
						Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
						{
							goto Exit_I2C_Transmit_Cmd;
						}
						Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;
					}
				}

				//RepeatedSTART
				if(P_Transmit_Cmd->RepeatedSTART==true)
				{
					//Slave_Address_1st
					Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Generate_START_And_Transmit_Address<<8)|(P_Transmit_Cmd->Slave_Address_1st<<1)|P_Transmit_Cmd->RepeatedRead;
					Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
					{
						goto Exit_I2C_Transmit_Cmd;
					}
					Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;

					if(P_Transmit_Cmd->RepeatedRead==true)
					{
						//RepeatedDATA
						for(int i=0;i<P_Transmit_Cmd->RepeatedSize;i++)
						{
							Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Receive_DATA_ACK<<8);
							Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
							{
								goto Exit_I2C_Transmit_Cmd;
							}
							Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;
							Drivers_S32K1xx_I2C_DATA.I2C[Index].Rx_FIFO_Size++;
						}
					}
					else
					{
						//RepeatedDATA
						for(int i=0;i<P_Transmit_Cmd->RepeatedSize;i++)
						{
							Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Transmit_DATA<<8)|P_Transmit_Cmd->RepeatedDATA[i];
							Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
							{
								goto Exit_I2C_Transmit_Cmd;
							}
							Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;
						}
					}
				}
			}
			//STOP
			Temp_DATA=(Drivers_S32K1xx_LPI2C_Master_Command_Data_Generate_STOP_Condition<<8);
			Error_NoArgs(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,Temp_DATA))
			{
				goto Exit_I2C_Transmit_Cmd;
			}
			Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size++;

			Drivers_S32K1xx_I2C_DATA.I2C[Index].Error=Drivers_S32K1xx_I2C_Error_OK;

			Error_NoArgs(Err,Drivers_S32K1xx_LPI2C_Master_SET_FIFO_Watermark((LPI2C_Type *)Device_Args,0,2))
			{
				goto Exit_I2C_Transmit_Cmd;
			}

			Error_NoArgs(Err,__Sys_Event_Flag_Clear(Drivers_S32K1xx_I2C_DATA.I2C[Index].Event_Flag))
			{
				goto Exit_I2C_Transmit_Cmd;
			}

			//打开发送数据中断
			Error_NoArgs(Err,Drivers_S32K1xx_LPI2C_Master_SET_Interrupt_Enabled(
					(LPI2C_Type *)Device_Args,
					Drivers_S32K1xx_LPI2C_Master_Interrupt_Transmit_Data|Drivers_S32K1xx_LPI2C_Master_Interrupt_Arbitration_Lost|Drivers_S32K1xx_LPI2C_Master_Interrupt_NACK_Detect|Drivers_S32K1xx_LPI2C_Master_Interrupt_STOP_Detect,
					Enable))
			{
				goto Exit_I2C_Transmit_Cmd;
			}
			//等待数据发送完成
			Error_NoArgs(Err,__Sys_Event_Flag_Wait(Drivers_S32K1xx_I2C_DATA.I2C[Index].Event_Flag,P_Transmit_Cmd->TimeOut))
			{
				goto Exit_I2C_Transmit_Cmd;
			}

			//
			if(Drivers_S32K1xx_I2C_DATA.I2C[Index].Error==Drivers_S32K1xx_I2C_Error_OK)
			{

			}
			else if(Drivers_S32K1xx_I2C_DATA.I2C[Index].Error==Drivers_S32K1xx_I2C_Error_Arbitration_Lost)
			{
				Err=Error_Busy;
				goto Exit_I2C_Transmit_Cmd;
			}
			else if(Drivers_S32K1xx_I2C_DATA.I2C[Index].Error==Drivers_S32K1xx_I2C_Error_NACK)
			{
				Err=Error_Not_Responding;
				goto Exit_I2C_Transmit_Cmd;
			}
			else
			{
				Err=Error_Unknown;
				goto Exit_I2C_Transmit_Cmd;
			}

			//
			if(Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size!=0 || Drivers_S32K1xx_I2C_DATA.I2C[Index].Rx_FIFO_Size!=0)
			{
				Err=Error_Unknown;
				goto Exit_I2C_Transmit_Cmd;
			}

			uint8_t Rx_DATA;
			if(P_Transmit_Cmd->Read==true)
			{

				int i=0;
				for(;i<P_Transmit_Cmd->Size;i++)
				{
					Err=Library_FIFO_1Byte_FIFO_OUT(&Drivers_S32K1xx_I2C_DATA.I2C[Index].RX_FIFO,&Rx_DATA);
					if(Err==Error_OK)
					{
						P_Transmit_Cmd->DATA[i]=Rx_DATA;
					}
					else if(Err==Error_Empty)
					{
						Err=Error_Unknown;
						goto Exit_I2C_Transmit_Cmd;
					}
					else
					{
						Err=Error_Unknown;
						goto Exit_I2C_Transmit_Cmd;
					}
				}
			}
			if(P_Transmit_Cmd->RepeatedRead==true)
			{
				int i=0;
				for(;i<P_Transmit_Cmd->RepeatedSize;i++)
				{
					Err=Library_FIFO_1Byte_FIFO_OUT(&Drivers_S32K1xx_I2C_DATA.I2C[Index].RX_FIFO,&Rx_DATA);
					if(Err==Error_OK)
					{
						P_Transmit_Cmd->RepeatedDATA[i]=Rx_DATA;
					}
					else if(Err==Error_Empty)
					{
						Err=Error_Unknown;
						goto Exit_I2C_Transmit_Cmd;
					}
					else
					{
						Err=Error_Unknown;
						goto Exit_I2C_Transmit_Cmd;
					}
				}
			}

			Err=Error_OK;

Exit_I2C_Transmit_Cmd:

			Error_NoArgs_Return(Temp_Err,__Sys_Semaphore_Release(Drivers_S32K1xx_I2C_DATA.I2C[Index].Semaphore,1,Null));

			return Err;
		}break;

		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
}
//---------------------------------------------------------------------------------------------------------
int Drivers_S32K1xx_I2C_GET_Count(void *Device_Args)
{
	switch ((uint32_t)Device_Args)
	{
		case LPI2C0_BASE:
		{
			return 0;
		}break;
#if (defined (__Target_S32K148__))
		case LPI2C1_BASE:
		{
			return 1;
		}break;
#endif
		default:
		{
			while(1);//绝对不能出现
		}break;
	}
}
//----------------------------------------------------------------------------------------------------

void Drivers_S32K1xx_I2C_Master_Slave_IRQ(void *Args,int IRQ_Index)
{
	/*
	int Err;
	LPI2C_Type *P_I2C=(LPI2C_Type *)Args;
	*/
	Drivers_S32K1xx_I2C_Master_IRQ(Args,IRQ_Index);
	Drivers_S32K1xx_I2C_Slave_IRQ(Args,IRQ_Index);

}
void Drivers_S32K1xx_I2C_Master_IRQ(void *Args,int IRQ_Index)
{
	int Err;
	LPI2C_Type *P_I2C=(LPI2C_Type *)Args;

	Drivers_S32K1xx_I2C_Error_Type I2C_Error=Drivers_S32K1xx_I2C_Error_OK;

	if(P_I2C==Null)return ;
	int Index=Drivers_S32K1xx_I2C_GET_Count(P_I2C);
	int Flag=Drivers_S32K1xx_LPI2C_Master_GET_Interrupt_Flag(P_I2C);
	int Flag_Clear=0;
	if(Flag<Error_OK)
	{
		return ;
	}

	if((Flag&Drivers_S32K1xx_LPI2C_Master_Interrupt_Data_Match)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPI2C_Master_Interrupt_Data_Match;
	}
	if((Flag&Drivers_S32K1xx_LPI2C_Master_Interrupt_Pin_Low_Timeout)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPI2C_Master_Interrupt_Pin_Low_Timeout;
	}
	if((Flag&Drivers_S32K1xx_LPI2C_Master_Interrupt_FIFO_Error)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPI2C_Master_Interrupt_FIFO_Error;
	}
	if((Flag&Drivers_S32K1xx_LPI2C_Master_Interrupt_Arbitration_Lost)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPI2C_Master_Interrupt_Arbitration_Lost;

		I2C_Error=Drivers_S32K1xx_I2C_Error_Arbitration_Lost;
	}
	if((Flag&Drivers_S32K1xx_LPI2C_Master_Interrupt_NACK_Detect)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPI2C_Master_Interrupt_NACK_Detect;

		I2C_Error=Drivers_S32K1xx_I2C_Error_NACK;
	}
	if((Flag&Drivers_S32K1xx_LPI2C_Master_Interrupt_STOP_Detect)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPI2C_Master_Interrupt_STOP_Detect;
	}
	if((Flag&Drivers_S32K1xx_LPI2C_Master_Interrupt_End_Packet)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPI2C_Master_Interrupt_End_Packet;
	}
	if((Flag&Drivers_S32K1xx_LPI2C_Master_Interrupt_Receive_Data)!=0)
	{
		uint8_t Temp_Rx_DATA=0x00;
		bool RX_Empty;
		if(Drivers_S32K1xx_LPI2C_Master_GET_DATA(P_I2C,&RX_Empty,&Temp_Rx_DATA)==Error_OK)
		{
			if(Drivers_S32K1xx_I2C_DATA.I2C[Index].Rx_FIFO_Size!=0)
			{
				if(Library_FIFO_1Byte_FIFO_IN(&Drivers_S32K1xx_I2C_DATA.I2C[Index].RX_FIFO,Temp_Rx_DATA)==Error_OK)
				{

				}

				Drivers_S32K1xx_I2C_DATA.I2C[Index].Rx_FIFO_Size--;
			}
		}
	}
	if((Flag&Drivers_S32K1xx_LPI2C_Master_Interrupt_Transmit_Data)!=0)
	{
		if(Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size!=0)
		{
			uint16_t Temp_Tx_DATA=0x00;
			Err=Library_FIFO_2Byte_FIFO_OUT(&Drivers_S32K1xx_I2C_DATA.I2C[Index].TX_FIFO,&Temp_Tx_DATA);
			if(Err==Error_OK)
			{

			}
			else if(Err==Error_Empty)
			{

			}
			else
			{

			}
			Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size--;

			if(Drivers_S32K1xx_LPI2C_Master_SET_DATA(P_I2C,(Drivers_S32K1xx_LPI2C_Master_Command_Data_Type)((Temp_Tx_DATA>>8)&0xFF),Temp_Tx_DATA&0xFF)==Error_OK)
			{

			}
			else
			{

			}

			if(Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size==0)
			{
				Drivers_S32K1xx_LPI2C_Master_SET_Interrupt_Enabled(P_I2C,Drivers_S32K1xx_LPI2C_Master_Interrupt_Transmit_Data,Disable);
			}

			Drivers_S32K1xx_LPI2C_Master_SET_Interrupt_Enabled(P_I2C,Drivers_S32K1xx_LPI2C_Master_Interrupt_Receive_Data,Enable);
		}


	}
	if((Flag&Drivers_S32K1xx_LPI2C_Master_Interrupt_Bus_Busy)!=0)
	{

	}
	if((Flag&Drivers_S32K1xx_LPI2C_Master_Interrupt_Master_Busy)!=0)
	{

	}
	if(Drivers_S32K1xx_I2C_DATA.I2C[Index].Rx_FIFO_Size==0)
	{
		Drivers_S32K1xx_LPI2C_Master_SET_Interrupt_Enabled(P_I2C,Drivers_S32K1xx_LPI2C_Master_Interrupt_Receive_Data,Disable);
	}

	Drivers_S32K1xx_LPI2C_Master_Clear_Interrupt_Flag(P_I2C,(Drivers_S32K1xx_LPI2C_Master_Interrupt_Type)Flag_Clear);

	if((Drivers_S32K1xx_I2C_DATA.I2C[Index].Rx_FIFO_Size==0 && Drivers_S32K1xx_I2C_DATA.I2C[Index].Tx_FIFO_Size==0 && (Flag&Drivers_S32K1xx_LPI2C_Master_Interrupt_STOP_Detect)!=0)
	|| I2C_Error==Drivers_S32K1xx_I2C_Error_Arbitration_Lost
	|| I2C_Error==Drivers_S32K1xx_I2C_Error_NACK)
	{
		Drivers_S32K1xx_I2C_DATA.I2C[Index].Error=I2C_Error;

		__Sys_Event_Flag_Set(Drivers_S32K1xx_I2C_DATA.I2C[Index].Event_Flag);
	}
}
void Drivers_S32K1xx_I2C_Slave_IRQ(void *Args,int IRQ_Index)
{
	int Err;
	LPI2C_Type *P_I2C=(LPI2C_Type *)Args;

}
__Sys_Device_Module_Init_Export(Drivers_S32K1xx_I2C_Setup);
