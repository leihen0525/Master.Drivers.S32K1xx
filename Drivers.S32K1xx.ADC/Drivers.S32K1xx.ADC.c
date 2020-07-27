/*
 * Drivers.S32K1xx.ADC.c
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

#include "Drivers.S32K1xx.ADC.h"

const __Sys_Device_OPS_Type __Device_OPS_ADC0=
{
	.Device_Name="ADC0",
	.Device_Args=ADC0,
	.Open=Null,
	.Close=Null,
	.Read=Null,
	.Write=Null,
	.Control=Null,

	.Info="MCU:S32K1xx Module:ADC0 Version:0.0.1 "__DATE__" "__TIME__,
};

#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
const __Sys_Device_OPS_Type __Device_OPS_ADC1=
{
	.Device_Name="ADC1",
	.Device_Args=ADC1,
	.Open=Null,
	.Close=Null,
	.Read=Null,
	.Write=Null,
	.Control=Null,

	.Info="MCU:S32K1xx Module:ADC1 Version:0.0.1 "__DATE__" "__TIME__,
};
#endif

int Drivers_S32K1xx_ADC_Setup(void)
{
	int Err;

	//注册当前设备的OPS
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_ADC0));
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_ADC1));
#endif

	return Error_OK;
}


__Sys_Device_Module_Init_Export(Drivers_S32K1xx_ADC_Setup);
