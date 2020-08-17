/*
 * __Drivers.S32K1xx.I2C.Enum.h
 *
 *  Created on: 2020年8月10日
 *      Author: Master.HE
 */

#ifndef __DRIVERS_S32K1XX_I2C_ENUM_H_
#define __DRIVERS_S32K1XX_I2C_ENUM_H_

typedef enum
{
	Drivers_S32K1xx_I2C_Error_OK						=0,
	Drivers_S32K1xx_I2C_Error_NACK,
	Drivers_S32K1xx_I2C_Error_Arbitration_Lost,

}Drivers_S32K1xx_I2C_Error_Type;

#endif /* __DRIVERS_S32K1XX_I2C_ENUM_H_ */
