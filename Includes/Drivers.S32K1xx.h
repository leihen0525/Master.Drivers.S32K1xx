/*
 * Drivers.S32K1xx.h
 *
 *  Created on: 2020年3月10日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_H_
#define DRIVERS_S32K1XX_H_


#include "Drivers.S32K1xx.GPIO.Define.h"
#include "Drivers.S32K1xx.GPIO.Enum.h"
#include "Drivers.S32K1xx.GPIO.Struct.h"

#include "Drivers.S32K1xx.UART.Enum.h"
#include "Drivers.S32K1xx.UART.Struct.h"

#include "Drivers.S32K1xx.SPI.Enum.h"
#include "Drivers.S32K1xx.SPI.Struct.h"

#if (defined (__Target_S32K148__))
#include "Drivers.S32K1xx.Ether.Enum.h"
#include "Drivers.S32K1xx.Ether.Struct.h"
#endif

#endif /* DRIVERS_S32K1XX_H_ */
