/*
 * Drivers.S32K1xx.UART.c
 *
 *  Created on: 2020年6月19日
 *      Author: Master.HE
 */
#include "Error.h"
#include "Define.h"

#include "Device\__Sys.Device.h"

#include "Module\Module.h"

#include "__Sys.API.h"

#include "S32K1xx.h"

#include "Drivers.S32K1xx.LPUART.Enum.h"
#include "Drivers.S32K1xx.UART.Enum.h"

#include "Drivers.S32K1xx.UART.h"

#include "Drivers.S32K1xx.LPUART.h"

#include "Drivers.S32K1xx.UART.Struct.h"

#include "Library/Library.FIFO.h"

Drivers_S32K1xx_UART_DATA_Type Drivers_S32K1xx_UART_DATA;

const __Sys_Device_OPS_Type __Device_OPS_UART0=
{
	.Device_Name="UART0",
	.Device_Args=LPUART0,
	.Open=Drivers_S32K1xx_UART_Open,
	.Close=Drivers_S32K1xx_UART_Close,
	.Read=Drivers_S32K1xx_UART_Read,
	.Write=Drivers_S32K1xx_UART_Write,
	.Control=Drivers_S32K1xx_UART_Control,

	.Info="MCU:S32K1xx Module:UART0 Version:0.0.1 "__DATE__" "__TIME__,
};

const __Sys_Device_OPS_Type __Device_OPS_UART1=
{
	.Device_Name="UART1",
	.Device_Args=LPUART1,
	.Open=Drivers_S32K1xx_UART_Open,
	.Close=Drivers_S32K1xx_UART_Close,
	.Read=Drivers_S32K1xx_UART_Read,
	.Write=Drivers_S32K1xx_UART_Write,
	.Control=Drivers_S32K1xx_UART_Control,

	.Info="MCU:S32K1xx Module:UART1 Version:0.0.1 "__DATE__" "__TIME__,
};

#if (defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
const __Sys_Device_OPS_Type __Device_OPS_UART2=
{
	.Device_Name="UART2",
	.Device_Args=LPUART2,
	.Open=Drivers_S32K1xx_UART_Open,
	.Close=Drivers_S32K1xx_UART_Close,
	.Read=Drivers_S32K1xx_UART_Read,
	.Write=Drivers_S32K1xx_UART_Write,
	.Control=Drivers_S32K1xx_UART_Control,

	.Info="MCU:S32K1xx Module:UART2 Version:0.0.1 "__DATE__" "__TIME__,
};
#endif

//---------------------------------------------------------------------------------------------------------
int Drivers_S32K1xx_UART_Setup(void)
{
	int Err;
	for(int i=0;i<LPUART_INSTANCE_COUNT;i++)
	{
		//申请一个事件组
		Error_Args_Return(Drivers_S32K1xx_UART_DATA.UART[i].Interrupt_Flag_Event_Flag_Group,__Sys_Event_Flag_Group_Create_16bit(Null));

		Drivers_S32K1xx_UART_DATA.UART[i].Tx_Ing=false;

		Drivers_S32K1xx_UART_DATA.UART[i].Open=false;
		//Drivers_S32K1xx_UART_DATA.UART[i].Tx_Event_Flag=__Sys_Event_Flag_Create(Null,false);

		//初始化FIFO队列
		Error_NoArgs_Return(Err,Library_FIFO_2Byte_FIFO_Init(&Drivers_S32K1xx_UART_DATA.UART[i].TX_FIFO));
		Error_NoArgs_Return(Err,Library_FIFO_2Byte_FIFO_Init(&Drivers_S32K1xx_UART_DATA.UART[i].RX_FIFO));

	}

	//初始化中断函数和开启中断
	Error_Args_Return(Err,__Sys_IRQ_Register_Hook(LPUART0_RxTx_IRQn,Drivers_S32K1xx_UART_IRQ,__Device_OPS_UART0.Device_Args));
	Error_NoArgs_Return(Err,__Sys_IRQ_Enable(LPUART0_RxTx_IRQn));

	Error_Args_Return(Err,__Sys_IRQ_Register_Hook(LPUART1_RxTx_IRQn,Drivers_S32K1xx_UART_IRQ,__Device_OPS_UART1.Device_Args));
	Error_NoArgs_Return(Err,__Sys_IRQ_Enable(LPUART1_RxTx_IRQn));

	//注册当前设备的OPS
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_UART0));
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_UART1));

#if (defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Error_Args_Return(Err,__Sys_IRQ_Register_Hook(LPUART2_RxTx_IRQn,Drivers_S32K1xx_UART_IRQ,__Device_OPS_UART2.Device_Args));
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_UART2));
	Error_NoArgs_Return(Err,__Sys_IRQ_Enable(LPUART2_RxTx_IRQn));
#endif


	//获取MCU时钟树
	Error_NoArgs_Return(Err,__Sys_BSP_UpData_Clock_Tree((void **)&Drivers_S32K1xx_UART_DATA.Clock.Source,(void **)&Drivers_S32K1xx_UART_DATA.Clock.Tree));

	return Error_OK;
}
int Drivers_S32K1xx_UART_Open(void *Device_Args,int Mode)
{
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}

	int Err;
	int Index=Drivers_S32K1xx_UART_GET_Count(Device_Args);

	//设备是独占的 不允许 多次打开
	if(Drivers_S32K1xx_UART_DATA.UART[Index].Open==true)
	{
		return Error_Exist;
	}

	//Mode 作为时钟源参数
	//改变模块时钟之前确保时钟是关闭的
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPUART_SET_Clock_Enabled((LPUART_Type *)Device_Args,Disable));

	//设置模块时钟源
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPUART_SET_Clock_Source((LPUART_Type *)Device_Args,(Drivers_S32K1xx_LPUART_Clock_Source_Type)(Drivers_S32K1xx_UART_Open_Mode_Clock_Source_Mask&Mode),Drivers_S32K1xx_UART_DATA.Clock.Tree));

	//打开模块时钟
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPUART_SET_Clock_Enabled((LPUART_Type *)Device_Args,Enable));


	//设置当前操作模式UART OR LIN
	Drivers_S32K1xx_UART_DATA.UART[Index].Operate=Mode&Drivers_S32K1xx_UART_Open_Mode_Operate_Mask;



	//绑定事件组到当前任务的TCB中
	Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Open(Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group));

	Drivers_S32K1xx_UART_DATA.UART[Index].Open=true;
	return Error_OK;
}
int Drivers_S32K1xx_UART_Close(void *Device_Args)
{
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}
	int Err;
	int Index=Drivers_S32K1xx_UART_GET_Count(Device_Args);

	//复位当前设备寄存器
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPUART_Software_Reset((LPUART_Type *)Device_Args));

	//关闭模块时钟
	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPUART_SET_Clock_Enabled((LPUART_Type *)Device_Args,Disable));

	//清除当前任务的TCB中绑定的事件组
	Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Close(Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group));

	Drivers_S32K1xx_UART_DATA.UART[Index].Open=false;
	return Error_OK;
}

int Drivers_S32K1xx_UART_Read(void *Device_Args,long OffSet_Pos, void *Buffer, unsigned long Size,long TimeOut)
{
	int Err;
	if(Device_Args==Null)return Error_Unknown;

	int Index=Drivers_S32K1xx_UART_GET_Count(Device_Args);

	if(Buffer==Null || Size==0 /*|| OffSet_Pos>=Drivers_S32K1xx_UART_OffSet_Pos_End*/)
	{
		return Error_Invalid_Parameter;
	}
	uint16_t Interrupt_Flag=0;

	Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Wait_Or_16bit(
			Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group,
			Drivers_S32K1xx_LPUART_Interrupt_Receiver,
			Drivers_S32K1xx_LPUART_Interrupt_Receiver,
			&Interrupt_Flag,
			Event_Flag_Group_Clear_Any_Read_Result_OK_Clear_Dissatisfy_Retain,
			0,
			TimeOut));
/*
	Err=__Sys_Event_Flag_Group_Wait_Or_16bit(
				Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group,
				Drivers_S32K1xx_LPUART_Interrupt_Receiver,
				Drivers_S32K1xx_LPUART_Interrupt_Receiver,
				&Interrupt_Flag,
				Event_Flag_Group_Clear_Any_Read_Result_OK_Clear_Dissatisfy_Retain,
				0,
				TimeOut);
	if(Err!=Error_OK)
	{
		if(Err==Error_Dissatisfy)
		{
			return Err;
		}
		return Err;
	}
*/
	if((Interrupt_Flag&Drivers_S32K1xx_LPUART_Interrupt_Receiver)==0)
	{
		return Error_Unknown;
	}

	uint16_t Rx_DATA;
	uint8_t *P_DATA=(uint8_t *)Buffer;
	unsigned long i=0;
	for(;i<Size;i++)
	{
		Err=Library_FIFO_2Byte_FIFO_OUT(&Drivers_S32K1xx_UART_DATA.UART[Index].RX_FIFO,&Rx_DATA);
		if(Err==Error_OK)
		{
			P_DATA[i]=Rx_DATA;
		}
		else if(Err==Error_Empty)
		{
			if(i==0)
			{
				return Error_Unknown;
			}
			else
			{
				return i;
			}
		}
		else
		{
			return Err;
		}
	}

	return i;

}

int Drivers_S32K1xx_UART_Write(void *Device_Args,long OffSet_Pos, const void *Buffer, unsigned long Size,long TimeOut)
{
	int Err;
	if(Device_Args==Null)return Error_Unknown;

	int Index=Drivers_S32K1xx_UART_GET_Count(Device_Args);

	if(Buffer==Null || Size==0 /*|| OffSet_Pos>=Drivers_S32K1xx_UART_OffSet_Pos_End*/)
	{
		return Error_Invalid_Parameter;
	}

	uint16_t Interrupt_Flag=0;
/*
	Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Wait_Or_16bit(
			Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group,
			Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete,
			Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete,
			&Interrupt_Flag,
			Event_Flag_Group_Clear_Any_Read_Clear,
			0,
			Event_Time_Out_Query));
*/
	Err=__Sys_Event_Flag_Group_Wait_Or_16bit(
				Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group,
				Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete,
				Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete,
				&Interrupt_Flag,
				Event_Flag_Group_Clear_Any_Read_Clear,
				0,
				Event_Time_Out_Query);
	if(Err!=Error_OK && Err!=Error_Dissatisfy)
	{
		return Err;
	}

	uint8_t *P_DATA=(uint8_t *)Buffer;
	for(int i=0;i<Size;i++)
	{
		Error_NoArgs_Return(Err,Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_UART_DATA.UART[Index].TX_FIFO,P_DATA[i]));
	}

	Drivers_S32K1xx_UART_DATA.UART[Index].Tx_Ing=true;

	Error_NoArgs_Return(Err,Drivers_S32K1xx_LPUART_SET_Interrupt_Enabled(
			(LPUART_Type *)Device_Args,
			(Drivers_S32K1xx_LPUART_Interrupt_Type)Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete,
			Enable));

	Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Wait_Or_16bit(
			Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group,
			Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete,
			Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete,
			&Interrupt_Flag,
			Event_Flag_Group_Clear_Any_Read_Result_OK_Clear_Dissatisfy_Retain,
			0,
			TimeOut));

	return Error_OK;
/*
	if(Drivers_S32K1xx_UART_DATA.UART[Index].Operate==Drivers_S32K1xx_UART_Open_Mode_Operate_UART)
	{
		return Error_Undefined;
	}
	else if(Drivers_S32K1xx_UART_DATA.UART[Index].Operate==Drivers_S32K1xx_UART_Open_Mode_Operate_LIN)
	{
		//在LIN模式下 发送数据前 先将收发缓冲区清空 标志位清空
		Error_NoArgs_Return(Err,Drivers_S32K1xx_UART_FIFO_Init(&Drivers_S32K1xx_UART_DATA.UART[Index].TX_FIFO));
		Error_NoArgs_Return(Err,Drivers_S32K1xx_UART_FIFO_Init(&Drivers_S32K1xx_UART_DATA.UART[Index].RX_FIFO));

		uint16_t Interrupt_Flag=0;

		Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Wait_Or_16bit(
				Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group,
				Drivers_S32K1xx_LPUART_Interrupt_Receiver|Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete,
				Drivers_S32K1xx_LPUART_Interrupt_Receiver|Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete,
				&Interrupt_Flag,
				Event_Flag_Group_Clear_Any_Read_Clear,
				0,
				Event_Time_Out_Query));


	}
	else
	{
		return Error_Unknown;
	}
*/
	/*
	int Err;
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}
	if(Buffer==Null || Size==0 || OffSet_Pos>=Drivers_S32K1xx_UART_OffSet_Pos_End)
	{
		return Error_Invalid_Parameter;
	}
	int Index=Drivers_S32K1xx_UART_GET_Count(Device_Args);


	//uint16_t DATA=0;
	if(OffSet_Pos==Drivers_S32K1xx_UART_OffSet_Pos_8BIT)
	{
		uint8_t *P_DATA=(uint8_t *)Buffer;
		for(int i=0;i<Size;i++)
		{
			if((Err=Drivers_S32K1xx_UART_FIFO_IN())!=Error_OK)
			{
				return Err;
			}
		}
	}
	else if(OffSet_Pos==Drivers_S32K1xx_UART_OffSet_Pos_16BIT)
	{

	}
	else
	{
		while(1);//????
	}



	uint8_t *P_DATA=(uint8_t *)Buffer;
	return Drivers_S32K1xx_LPUART_SET_DATA((LPUART_Type *)Device_Args,false,P_DATA[0]);
	*/
}

int Drivers_S32K1xx_UART_Control(void *Device_Args,int Cmd, unsigned long Args)
{
	int Index=Drivers_S32K1xx_UART_GET_Count(Device_Args);
	int Err;

	switch (Cmd&Drivers_S32K1xx_UART_Cmd_Mask)
	{
	/*
		case Drivers_S32K1xx_UART_Cmd_Software_Reset:
		{
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPUART_Software_Reset((LPUART_Type *)Device_Args));

			return Error_OK;
		}break;
		*/
		case Drivers_S32K1xx_UART_Cmd_Init:
		{
			Drivers_S32K1xx_UART_Init_Type *P_UART_Init=(Drivers_S32K1xx_UART_Init_Type *)&Args;
			if(P_UART_Init==Null)
			{
				return Error_Invalid_Parameter;
			}


			//初始化FIFO队列
			Error_NoArgs_Return(Err,Library_FIFO_2Byte_FIFO_Init(&Drivers_S32K1xx_UART_DATA.UART[Index].TX_FIFO));
			Error_NoArgs_Return(Err,Library_FIFO_2Byte_FIFO_Init(&Drivers_S32K1xx_UART_DATA.UART[Index].RX_FIFO));

			//复位模块寄存器
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPUART_Software_Reset((LPUART_Type *)Device_Args));

			uint16_t Interrupt_Flag=0;
			/*
			Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Wait_Or_16bit(
					Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group,
					Drivers_S32K1xx_LPUART_Interrupt_Mask,
					Drivers_S32K1xx_LPUART_Interrupt_Mask,
					&Interrupt_Flag,
					Event_Flag_Group_Clear_Any_Read_Clear,
					0,
					Event_Time_Out_Query));
			 */
			Err=__Sys_Event_Flag_Group_Wait_Or_16bit(
								Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group,
								Drivers_S32K1xx_LPUART_Interrupt_Mask,
								Drivers_S32K1xx_LPUART_Interrupt_Mask,
								&Interrupt_Flag,
								Event_Flag_Group_Clear_Any_Read_Clear,
								0,
								Event_Time_Out_Query);
			if(Err!=Error_OK && Err!=Error_Dissatisfy)
			{
				return Err;
			}

			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPUART_SET_Baud_Rate(
										(LPUART_Type *)Device_Args,
										Drivers_S32K1xx_UART_DATA.Clock.Tree,
										Drivers_S32K1xx_LPUART_Oversampling_Ratio_16,
										P_UART_Init->Baud_Rate_bps));
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPUART_SET_Bit_Select(
										(LPUART_Type *)Device_Args,
										(Drivers_S32K1xx_LPUART_Bit_Mode_Select_Type)P_UART_Init->Bit_Mode_Select,
										(Drivers_S32K1xx_LPUART_Stop_Bit_Select_Type)P_UART_Init->Stop_Bit_Select));
			//根据不同模式开启相应功能
			if(Drivers_S32K1xx_UART_DATA.UART[Index].Operate==Drivers_S32K1xx_UART_Open_Mode_Operate_UART)
			{
				//Drivers_S32K1xx_LPUART_SET_Function_Enabled();
			}
			else if(Drivers_S32K1xx_UART_DATA.UART[Index].Operate==Drivers_S32K1xx_UART_Open_Mode_Operate_LIN)
			{
				Error_NoArgs_Return(Err,Drivers_S32K1xx_LPUART_SET_Function_Enabled(
						(LPUART_Type *)Device_Args,
						(Drivers_S32K1xx_LPUART_Function_Type)(/*Drivers_S32K1xx_LPUART_Function_LIN_Break_Detection|*/Drivers_S32K1xx_LPUART_Function_Transmitter|Drivers_S32K1xx_LPUART_Function_Receiver),
						Enable));
				Error_NoArgs_Return(Err,Drivers_S32K1xx_LPUART_SET_Interrupt_Enabled(
						(LPUART_Type *)Device_Args,
						(Drivers_S32K1xx_LPUART_Interrupt_Type)(Drivers_S32K1xx_LPUART_Interrupt_LIN_Break_Detect|Drivers_S32K1xx_LPUART_Interrupt_Receiver),
						Enable));

			}
			else
			{
				return Error_Invalid_Parameter;
			}

			return Error_OK;
		}break;
		case Drivers_S32K1xx_UART_Cmd_SET_LIN_Break_Detection_Enabled:
		{
			Error_NoArgs_Return(Err,Drivers_S32K1xx_LPUART_SET_Function_Enabled(
									(LPUART_Type *)Device_Args,
									Drivers_S32K1xx_LPUART_Function_LIN_Break_Detection,
									(Enabled_Type)Args));
			return Error_OK;
		}break;
		case Drivers_S32K1xx_UART_Cmd_SET_Rx_Buff_Flush:
		{
			Error_NoArgs_Return(Err,Library_FIFO_2Byte_FIFO_Init(&Drivers_S32K1xx_UART_DATA.UART[Index].RX_FIFO));

			uint16_t Interrupt_Flag=0;
/*
			Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Wait_Or_16bit(
					Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group,
					Drivers_S32K1xx_LPUART_Interrupt_Receiver,
					Drivers_S32K1xx_LPUART_Interrupt_Receiver,
					&Interrupt_Flag,
					Event_Flag_Group_Clear_Any_Read_Clear,
					0,
					Event_Time_Out_Query));
					*/
			Err=__Sys_Event_Flag_Group_Wait_Or_16bit(
								Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group,
								Drivers_S32K1xx_LPUART_Interrupt_Receiver,
								Drivers_S32K1xx_LPUART_Interrupt_Receiver,
								&Interrupt_Flag,
								Event_Flag_Group_Clear_Any_Read_Clear,
								0,
								Event_Time_Out_Query);
			if(Err!=Error_OK && Err!=Error_Dissatisfy)
			{
				return Err;
			}
			return Error_OK;
		}break;

		case Drivers_S32K1xx_UART_Cmd_GET_LIN_Break_Detection_Interrupt_Flag:
		{
			uint16_t Interrupt_Flag=0;
			int32_t *P_TimeOut=(int32_t *)&Args;
			Error_NoArgs_Return(Err,__Sys_Event_Flag_Group_Wait_Or_16bit(
					Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group,
					Drivers_S32K1xx_LPUART_Interrupt_LIN_Break_Detect,
					Drivers_S32K1xx_LPUART_Interrupt_LIN_Break_Detect,
					&Interrupt_Flag,
					Event_Flag_Group_Clear_Any_Read_Result_OK_Clear_Dissatisfy_Retain,
					0,
					*P_TimeOut));

			if((Interrupt_Flag&Drivers_S32K1xx_LPUART_Interrupt_LIN_Break_Detect)==0)
			{
				return Error_Unknown;
			}
			return Error_OK;
		}break;
		/*
		case Drivers_S32K1xx_UART_Cmd_SET_Baud_Rate:
		{
			return Drivers_S32K1xx_LPUART_SET_Baud_Rate(
							(LPUART_Type *)Device_Args,
							Drivers_S32K1xx_UART_DATA.Clock.Tree,
							Drivers_S32K1xx_LPUART_Oversampling_Ratio_16,
							Args);
		}break;
		*/
/*
		case Drivers_S32K1xx_UART_Cmd_SET_Function_Enabled:
		{
			return Drivers_S32K1xx_LPUART_SET_Function_Enabled(
										(LPUART_Type *)Device_Args,
										(Drivers_S32K1xx_LPUART_Function_Type)(Cmd&0xFFFF),
										(Enabled_Type)Args);
		}break;

		case Drivers_S32K1xx_UART_Cmd_SET_Interrupt_Enabled:
		{
			return Drivers_S32K1xx_LPUART_SET_Interrupt_Enabled(
							(LPUART_Type *)Device_Args,
							(Drivers_S32K1xx_LPUART_Interrupt_Type)(Cmd&0xFFFF),
							(Enabled_Type)Args);
		}break;


		case Drivers_S32K1xx_UART_Cmd_GET_Interrupt_Flag:
		{
			Drivers_S32K1xx_UART_GET_Interrupt_Flag_Type *Interrupt_Flag=(Drivers_S32K1xx_UART_GET_Interrupt_Flag_Type *)Args;
			if(Interrupt_Flag==Null)
			{
				return Error_Invalid_Parameter;
			}

			return __Sys_Event_Flag_Group_Wait_Or_16bit(
							Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group,
							Interrupt_Flag->Mask,
							Drivers_S32K1xx_LPUART_Interrupt_Mask,
							&Interrupt_Flag->Flag,
							Event_Flag_Group_Clear_Any_Read_Result_OK_Clear_Dissatisfy_Retain,
							Interrupt_Flag->Mask,
							Interrupt_Flag->Time_Out);

		}break;
*/
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}
}
//---------------------------------------------------------------------------------------------------------
int Drivers_S32K1xx_UART_GET_Count(void *Device_Args)
{
	switch ((uint32_t)Device_Args)
	{
		case LPUART0_BASE:
		{
			return 0;
		}break;
		case LPUART1_BASE:
		{
			return 1;
		}break;
#if (defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case LPUART2_BASE:
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
//---------------------------------------------------------------------------------------------------------
void Drivers_S32K1xx_UART_IRQ(void *Args,int IRQ_Index)
{
	//bool Tx_DATA_Complete=false;


	int Err;
	LPUART_Type *P_UART=(LPUART_Type *)Args;

	if(P_UART==Null)return ;
	int Index=Drivers_S32K1xx_UART_GET_Count(P_UART);
	int Flag=Drivers_S32K1xx_LPUART_GET_Interrupt_Flag(P_UART);
	int Flag_Clear=0;
	if(Flag<Error_OK)
	{
		return ;
	}

	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_LIN_Break_Detect)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPUART_Interrupt_LIN_Break_Detect;
	}
	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_RX_Input_Active_Edge)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPUART_Interrupt_RX_Input_Active_Edge;
	}
	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_Overrun)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPUART_Interrupt_Overrun;
	}
	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_Noise_Error)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPUART_Interrupt_Noise_Error;
	}
	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_Framing_Error)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPUART_Interrupt_Framing_Error;
	}
	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_Parity_Error)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPUART_Interrupt_Parity_Error;
	}
	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_Transmit)!=0)
	{

	}
	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete)!=0)
	{
		uint16_t Tx_DATA;
		Err=Library_FIFO_2Byte_FIFO_OUT(&Drivers_S32K1xx_UART_DATA.UART[Index].TX_FIFO,&Tx_DATA);
		if(Err==Error_OK)
		{
			Drivers_S32K1xx_LPUART_SET_DATA(P_UART,false,Tx_DATA);
		}
		else if(Err==Error_Empty)
		{
			if(Drivers_S32K1xx_UART_DATA.UART[Index].Tx_Ing==true)
			{
				Drivers_S32K1xx_LPUART_SET_Interrupt_Enabled(
						P_UART,
						(Drivers_S32K1xx_LPUART_Interrupt_Type)Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete,
						Disable);
			}
			Drivers_S32K1xx_UART_DATA.UART[Index].Tx_Ing=false;
		}
		else
		{
			//return Err;
		}

		if(Drivers_S32K1xx_UART_DATA.UART[Index].Tx_Ing==false)
		{
			;
		}
		else
		{
			Flag=Flag&(uint32_t)(~Drivers_S32K1xx_LPUART_Interrupt_Transmission_Complete);//在传输过程中则 取消发送完成事件
		}
	}
	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_Receiver)!=0)
	{
		uint16_t Rx_Temp_DATA;
		if(Drivers_S32K1xx_LPUART_GET_DATA(P_UART,Null,Null,Null,Null,Null,&Rx_Temp_DATA)==Error_OK)
		{
			Library_FIFO_2Byte_FIFO_IN(&Drivers_S32K1xx_UART_DATA.UART[Index].RX_FIFO,Rx_Temp_DATA);
		}

	}
	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_Idle_Line)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPUART_Interrupt_Idle_Line;
	}
	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_Match_1)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPUART_Interrupt_Match_1;
	}
	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_Match_2)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPUART_Interrupt_Match_2;
	}
	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_Transmit_FIFO_Overflow)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPUART_Interrupt_Transmit_FIFO_Overflow;
	}
	if((Flag&Drivers_S32K1xx_LPUART_Interrupt_Receive_FIFO_Underflow)!=0)
	{
		Flag_Clear=Flag_Clear|Drivers_S32K1xx_LPUART_Interrupt_Receive_FIFO_Underflow;
	}

	Drivers_S32K1xx_LPUART_Clear_Interrupt_Flag(P_UART,(Drivers_S32K1xx_LPUART_Interrupt_Type)Flag_Clear);

	__Sys_Event_Flag_Group_Set_16bit(
			Drivers_S32K1xx_UART_DATA.UART[Index].Interrupt_Flag_Event_Flag_Group,
			Drivers_S32K1xx_LPUART_Interrupt_Mask,Flag);

}

//---------------------------------------------------------------------------------------------------------

__Sys_Device_Module_Init_Export(Drivers_S32K1xx_UART_Setup);
