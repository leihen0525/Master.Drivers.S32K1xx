/*
 * Library.FIFO.c
 *
 *  Created on: 2020年7月27日
 *      Author: Master.HE
 */
#include "Error.h"
#include "Library.FIFO.h"


int Library_FIFO_1Byte_FIFO_Init(Library_FIFO_1Byte_DATA_Type *P_FIFO)
{
	if(P_FIFO==Null)
	{
		return Error_Invalid_Parameter;
	}
	P_FIFO->FIFO_IN=0;
	P_FIFO->FIFO_OUT=0;

	return Error_OK;
}
int Library_FIFO_1Byte_FIFO_IN(
		Library_FIFO_1Byte_DATA_Type *P_FIFO,
		uint8_t DATA)
{
	if(P_FIFO==Null)
	{
		return Error_Invalid_Parameter;
	}
	P_FIFO->DATA[P_FIFO->FIFO_IN++]=DATA;
	if(P_FIFO->FIFO_IN==P_FIFO->FIFO_OUT)
	{
		P_FIFO->FIFO_OUT++;
		return Error_OverFlow;
	}
	return Error_OK;
}
int Library_FIFO_1Byte_FIFO_OUT(
		Library_FIFO_1Byte_DATA_Type *P_FIFO,
		uint8_t *DATA)
{
	if(P_FIFO==Null || DATA==Null)
	{
		return Error_Invalid_Parameter;
	}
	if(P_FIFO->FIFO_IN==P_FIFO->FIFO_OUT)
	{
		return Error_Empty;
	}
	else
	{
		*DATA=P_FIFO->DATA[P_FIFO->FIFO_OUT++];
	}
	return Error_OK;
}
//---------------------------------------------------------------------------------------------------------
int Library_FIFO_2Byte_FIFO_Init(Library_FIFO_2Byte_DATA_Type *P_FIFO)
{
	if(P_FIFO==Null)
	{
		return Error_Invalid_Parameter;
	}
	P_FIFO->FIFO_IN=0;
	P_FIFO->FIFO_OUT=0;

	return Error_OK;
}
int Library_FIFO_2Byte_FIFO_IN(
		Library_FIFO_2Byte_DATA_Type *P_FIFO,
		uint16_t DATA)
{
	if(P_FIFO==Null)
	{
		return Error_Invalid_Parameter;
	}
	P_FIFO->DATA[P_FIFO->FIFO_IN++]=DATA;
	if(P_FIFO->FIFO_IN==P_FIFO->FIFO_OUT)
	{
		P_FIFO->FIFO_OUT++;
		return Error_OverFlow;
	}
	return Error_OK;
}
int Library_FIFO_2Byte_FIFO_OUT(
		Library_FIFO_2Byte_DATA_Type *P_FIFO,
		uint16_t *DATA)
{
	if(P_FIFO==Null || DATA==Null)
	{
		return Error_Invalid_Parameter;
	}
	if(P_FIFO->FIFO_IN==P_FIFO->FIFO_OUT)
	{
		return Error_Empty;
	}
	else
	{
		*DATA=P_FIFO->DATA[P_FIFO->FIFO_OUT++];
	}
	return Error_OK;
}
