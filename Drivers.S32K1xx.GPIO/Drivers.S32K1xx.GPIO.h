/*
 * Drivers.S32K1xx.GPIO.h
 *
 *  Created on: 2019年12月4日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_GPIO_H_
#define DRIVERS_S32K1XX_GPIO_H_

int Drivers_S32K1xx_GPIO_Setup(void);

int Drivers_S32K1xx_GPIO_Control(void *Device_Args,int Cmd, unsigned long Args);

#endif /* DRIVERS_S32K1XX_GPIO_H_ */
