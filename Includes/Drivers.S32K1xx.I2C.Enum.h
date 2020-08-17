/*
 * Drivers.S32K1xx.I2C.Enum.h
 *
 *  Created on: 2020年7月27日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_I2C_ENUM_H_
#define DRIVERS_S32K1XX_I2C_ENUM_H_

typedef enum
{
	Drivers_S32K1xx_I2C_Cmd_Mask									=0xFFFF0000,

	Drivers_S32K1xx_I2C_Cmd_Master_Init								=2<<16,

	Drivers_S32K1xx_I2C_Cmd_Master_Transmit_Cmd						=3<<16,


	//Drivers_S32K1xx_I2C_Cmd_Clock_Config							=3<<16,

	//Drivers_S32K1xx_I2C_Cmd_Transmit_Cmd							=4<<16,

}Drivers_S32K1xx_I2C_Cmd_Type;

typedef enum
{
	Drivers_S32K1xx_I2C_Open_Mode_Clock_Source_Mask					=0x0000FFFF,

	Drivers_S32K1xx_I2C_Open_Mode_Clock_Source_SOSCDIV2_CLK			=1,
	Drivers_S32K1xx_I2C_Open_Mode_Clock_Source_SIRCDIV2_CLK			=2,
	Drivers_S32K1xx_I2C_Open_Mode_Clock_Source_FIRCDIV2_CLK			=3,

#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Drivers_S32K1xx_I2C_Open_Mode_Clock_Source_SPLLDIV2_CLK			=6,
#endif


	//Drivers_S32K1xx_I2C_Open_Mode_Operate_Mask							=0x00010000,


}Drivers_S32K1xx_I2C_Open_Mode_Type;

typedef enum
{
	Drivers_S32K1xx_I2C_Baud_Rate_400Kbps								=0,
	Drivers_S32K1xx_I2C_Baud_Rate_1000Kbps,
	Drivers_S32K1xx_I2C_Baud_Rate_3200Kbps,

	Drivers_S32K1xx_I2C_Baud_Rate_End,
}Drivers_S32K1xx_I2C_Baud_Rate_Type;


#endif /* DRIVERS_S32K1XX_I2C_ENUM_H_ */
