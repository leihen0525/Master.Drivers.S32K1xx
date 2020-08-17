/*
 * Drivers.S32K1xx.ADC.h
 *
 *  Created on: 2020年7月19日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_ADC_H_
#define DRIVERS_S32K1XX_ADC_H_


int Drivers_S32K1xx_ADC_Setup(void);
int Drivers_S32K1xx_ADC_Open(void *Device_Args,int Mode);
int Drivers_S32K1xx_ADC_Close(void *Device_Args);
int Drivers_S32K1xx_ADC_Control(void *Device_Args,int Cmd, unsigned long Args);
//----------------------------------------------------------------------------------------------------
int Drivers_S32K1xx_ADC_GET_Count(void *Device_Args);

#endif /* DRIVERS_S32K1XX_ADC_H_ */
