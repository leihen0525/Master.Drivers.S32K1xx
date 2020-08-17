/*
 * Drivers.S32K1xx.LPI2C.h
 *
 *  Created on: 2020年7月27日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_LPI2C_H_
#define DRIVERS_S32K1XX_LPI2C_H_

#include "Master.Stdint.h"
#include "S32K1xx.h"

#include "Drivers.S32K1xx.LPI2C.Enum.h"
#include "Drivers.S32K1xx.LPI2C.Master.h"
#include "Drivers.S32K1xx.LPI2C.Slave.h"

int Drivers_S32K1xx_LPI2C_SET_Clock_Source(
		LPI2C_Type *P_LPI2C,
		Drivers_S32K1xx_LPI2C_Clock_Source_Type Clock_Source,
		S32K1xx_Clock_Tree_Type *Tree);

int Drivers_S32K1xx_LPI2C_SET_Clock_Enabled(
		LPI2C_Type *P_LPI2C,
		Enabled_Type Enabled);
int Drivers_S32K1xx_LPI2C_GET_Clock_Enabled(LPI2C_Type *P_LPI2C);

#endif /* DRIVERS_S32K1XX_LPI2C_H_ */
