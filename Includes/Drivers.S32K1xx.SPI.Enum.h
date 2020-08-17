/*
 * Drivers.S32K1xx.SPI.Enum.h
 *
 *  Created on: 2020年7月22日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_SPI_ENUM_H_
#define DRIVERS_S32K1XX_SPI_ENUM_H_

typedef enum
{
	Drivers_S32K1xx_SPI_Cmd_Mask									=0xFFFF0000,

	Drivers_S32K1xx_SPI_Cmd_Init									=2<<16,

	Drivers_S32K1xx_SPI_Cmd_Clock_Config							=3<<16,

	Drivers_S32K1xx_SPI_Cmd_Transmit_Cmd							=4<<16,

}Drivers_S32K1xx_SPI_Cmd_Type;


typedef enum
{
	Drivers_S32K1xx_SPI_Open_Mode_Clock_Source_Mask					=0x0000FFFF,

	Drivers_S32K1xx_SPI_Open_Mode_Clock_Source_SOSCDIV2_CLK			=1,
	Drivers_S32K1xx_SPI_Open_Mode_Clock_Source_SIRCDIV2_CLK			=2,
	Drivers_S32K1xx_SPI_Open_Mode_Clock_Source_FIRCDIV2_CLK			=3,

#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Drivers_S32K1xx_SPI_Open_Mode_Clock_Source_SPLLDIV2_CLK			=6,
#endif


	//Drivers_S32K1xx_SPI_Open_Mode_Operate_Mask							=0x00010000,


}Drivers_S32K1xx_SPI_Open_Mode_Type;

typedef enum
{
	Drivers_S32K1xx_SPI_Init_Mode_Slave								=0,
	Drivers_S32K1xx_SPI_Init_Mode_Master,

	Drivers_S32K1xx_SPI_Init_Mode_End,
}Drivers_S32K1xx_SPI_Init_Mode_Type;

typedef enum
{
	Drivers_S32K1xx_SPI_PIN_Config_SIN_Input_And_SOUT_Output		=0,
	Drivers_S32K1xx_SPI_PIN_Config_SIN_Both_InputOuput,
	Drivers_S32K1xx_SPI_PIN_Config_SOUT_Both_InputOuput,
	Drivers_S32K1xx_SPI_PIN_Config_SOUT_Input_And_SIN_Output,

	Drivers_S32K1xx_SPI_PIN_Config_End,
}Drivers_S32K1xx_SPI_PIN_Config_Type;

#endif /* DRIVERS_S32K1XX_SPI_ENUM_H_ */
