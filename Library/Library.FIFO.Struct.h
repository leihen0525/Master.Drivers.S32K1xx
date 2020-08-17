/*
 * Library.FIFO.Struct.h
 *
 *  Created on: 2020年7月27日
 *      Author: Master.HE
 */

#ifndef LIBRARY_FIFO_STRUCT_H_
#define LIBRARY_FIFO_STRUCT_H_

#include "Master.Stdint.h"

typedef struct
{
	uint16_t FIFO_IN				:6;			//队列的进标号
	uint16_t FIFO_OUT				:6;			//队列的出标号

	uint8_t DATA[0x40];

}Library_FIFO_1Byte_DATA_Type;

typedef struct
{
	uint16_t FIFO_IN				:6;			//队列的进标号
	uint16_t FIFO_OUT				:6;			//队列的出标号

	uint16_t DATA[0x40];

}Library_FIFO_2Byte_DATA_Type;

#endif /* LIBRARY_FIFO_STRUCT_H_ */
