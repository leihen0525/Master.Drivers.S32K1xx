/*
 * Drivers.S32K1xx.Ether.h
 *
 *  Created on: 2020年3月10日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_ETHER_H_
#define DRIVERS_S32K1XX_ETHER_H_

#if (defined (__Target_S32K148__))

int Drivers_S32K1xx_Ether_Setup(void);

int Drivers_S32K1xx_Ether_Open(void *Device_Args,int Mode);
int Drivers_S32K1xx_Ether_Read(void *Device_Args,long OffSet_Pos, void *Buffer, unsigned long Size,int TimeOut);
int Drivers_S32K1xx_Ether_Write(void *Device_Args,long OffSet_Pos, const void *Buffer, unsigned long Size,int TimeOut);
int Drivers_S32K1xx_Ether_Control(void *Device_Args,int Cmd,unsigned long Args);


#endif

#endif /* DRIVERS_S32K1XX_ETHER_H_ */
