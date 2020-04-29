/*
 * Drivers.S32K1xx.Ether.c
 *
 *  Created on: 2020年3月10日
 *      Author: Master.HE
 */
#if (defined (__Target_S32K148__))

#include <string.h>

#include "Define.h"
#include "Error.h"

//#include "__Sys.Device.Enum.h"
#include "Device\__Sys.Device.h"

#include "Module\Module.h"

#include "__Sys.API.h"

#include "Drivers.S32K1xx.Ether.h"




const __Sys_Device_OPS_Type __Device_OPS_Ether=
{
	.Device_Name="Ether",
	.Device_Args=Null,
	.Open=Null,//Drivers_S32K1xxxx_Ether_Open,
	.Close=Null,
	.Read=Drivers_S32K1xx_Ether_Read,
	.Write=Drivers_S32K1xx_Ether_Write,
	.Control=Drivers_S32K1xx_Ether_Control,

	.Info="MCU:S32K148 Module:Ether Version:0.0.1 "__DATE__" "__TIME__,
};

int Drivers_S32K1xx_Ether_Setup(void)
{

	__Sys_Device_Register_Drivers(&__Device_OPS_Ether);



	return Error_OK;
}

int Drivers_S32K1xx_Ether_Open(void *Device_Args,int Mode)
{
	return Error_OK;
}
int Drivers_S32K1xx_Ether_Read(void *Device_Args,long OffSet_Pos, void *Buffer, unsigned long Size,int TimeOut)
{
	return Error_OK;
}
int Drivers_S32K1xx_Ether_Write(void *Device_Args,long OffSet_Pos, const void *Buffer, unsigned long Size,int TimeOut)
{
	return Error_OK;
}
int Drivers_S32K1xx_Ether_Control(void *Device_Args,int Cmd,unsigned long Args)
{
	return Error_OK;
}


















__Sys_Device_Module_Init_Export(Drivers_S32K1xx_Ether_Setup);
#endif
