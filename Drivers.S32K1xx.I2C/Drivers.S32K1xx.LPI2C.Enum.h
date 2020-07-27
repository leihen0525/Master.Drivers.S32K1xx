/*
 * Drivers.S32K1xx.LPI2C.Enum.h
 *
 *  Created on: 2020年7月22日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_LPI2C_ENUM_H_
#define DRIVERS_S32K1XX_LPI2C_ENUM_H_

typedef enum
{
	Drivers_S32K1xx_LPI2C_Clock_Source_Disable				=0,
	Drivers_S32K1xx_LPI2C_Clock_Source_SOSCDIV2_CLK			=1,
	Drivers_S32K1xx_LPI2C_Clock_Source_SIRCDIV2_CLK			=2,
	Drivers_S32K1xx_LPI2C_Clock_Source_FIRCDIV2_CLK			=3,

#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Drivers_S32K1xx_LPI2C_Clock_Source_SPLLDIV2_CLK			=6,
#endif

}Drivers_S32K1xx_LPSPI_Clock_Source_Type;

#endif /* DRIVERS_S32K1XX_LPI2C_ENUM_H_ */
