/*
 * Drivers.S32K1xx.I2C.h
 *
 *  Created on: 2020年7月19日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_I2C_H_
#define DRIVERS_S32K1XX_I2C_H_

int Drivers_S32K1xx_I2C_Setup(void);
int Drivers_S32K1xx_I2C_Open(void *Device_Args,int Mode);
int Drivers_S32K1xx_I2C_Close(void *Device_Args);
int Drivers_S32K1xx_I2C_Control(void *Device_Args,int Cmd, unsigned long Args);
int Drivers_S32K1xx_I2C_GET_Count(void *Device_Args);
void Drivers_S32K1xx_I2C_Master_Slave_IRQ(void *Args,int IRQ_Index);
void Drivers_S32K1xx_I2C_Master_IRQ(void *Args,int IRQ_Index);
void Drivers_S32K1xx_I2C_Slave_IRQ(void *Args,int IRQ_Index);

#endif /* DRIVERS_S32K1XX_I2C_H_ */
