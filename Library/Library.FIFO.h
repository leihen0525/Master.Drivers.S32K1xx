/*
 * Library.FIFO.h
 *
 *  Created on: 2020年7月27日
 *      Author: Master.HE
 */

#ifndef LIBRARY_FIFO_H_
#define LIBRARY_FIFO_H_

#include "Master.Stdint.h"
#include "Library.FIFO.Struct.h"

int Library_FIFO_1Byte_FIFO_Init(Library_FIFO_1Byte_DATA_Type *P_FIFO);
int Library_FIFO_1Byte_FIFO_IN(
		Library_FIFO_1Byte_DATA_Type *P_FIFO,
		uint8_t DATA);
int Library_FIFO_1Byte_FIFO_OUT(
		Library_FIFO_1Byte_DATA_Type *P_FIFO,
		uint8_t *DATA);
//---------------------------------------------------------------------------------------------------------
int Library_FIFO_2Byte_FIFO_Init(Library_FIFO_2Byte_DATA_Type *P_FIFO);
int Library_FIFO_2Byte_FIFO_IN(
		Library_FIFO_2Byte_DATA_Type *P_FIFO,
		uint16_t DATA);
int Library_FIFO_2Byte_FIFO_OUT(
		Library_FIFO_2Byte_DATA_Type *P_FIFO,
		uint16_t *DATA);
//---------------------------------------------------------------------------------------------------------


#endif /* LIBRARY_FIFO_H_ */
