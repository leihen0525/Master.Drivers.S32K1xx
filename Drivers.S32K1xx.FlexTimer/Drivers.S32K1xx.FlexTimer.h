/*
 * Drivers.S32K1xx.FlexTimer.h
 *
 *  Created on: 2020年7月19日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_FLEXTIMER_H_
#define DRIVERS_S32K1XX_FLEXTIMER_H_

int Drivers_S32K1xx_FlexTimer_Setup(void);
int Drivers_S32K1xx_FlexTimer_Open(void *Device_Args,int Mode);
int Drivers_S32K1xx_FlexTimer_Close(void *Device_Args);
int Drivers_S32K1xx_FlexTimer_Control(void *Device_Args,int Cmd, unsigned long Args);
int Drivers_S32K1xx_FlexTimer_GET_Count(void *Device_Args);

#endif /* DRIVERS_S32K1XX_FLEXTIMER_H_ */
