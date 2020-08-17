/*
 * Drivers.S32K1xx.LPI2C.Master.Enum.h
 *
 *  Created on: 2020年7月28日
 *      Author: Master.HE
 */

#ifndef DRIVERS_S32K1XX_LPI2C_MASTER_ENUM_H_
#define DRIVERS_S32K1XX_LPI2C_MASTER_ENUM_H_

typedef enum
{
	Drivers_S32K1xx_LPI2C_Master_Function_Debug							=1<<0,
	Drivers_S32K1xx_LPI2C_Master_Function_Doze_Mode						=1<<1,
	Drivers_S32K1xx_LPI2C_Master_Function_Receive_Data_DMA				=1<<2,
	Drivers_S32K1xx_LPI2C_Master_Function_Transmit_Data_DMA				=1<<3,
	Drivers_S32K1xx_LPI2C_Master_Function_Circular_FIFO					=1<<4,
	Drivers_S32K1xx_LPI2C_Master_Function_Host_Request 					=1<<5,

	Drivers_S32K1xx_LPI2C_Master_Function_Mask							=0x3F,
}Drivers_S32K1xx_LPI2C_Master_Function_Type;


typedef enum
{
	Drivers_S32K1xx_LPI2C_Master_Interrupt_Data_Match					=1<<0,
	Drivers_S32K1xx_LPI2C_Master_Interrupt_Pin_Low_Timeout				=1<<1,
	Drivers_S32K1xx_LPI2C_Master_Interrupt_FIFO_Error					=1<<2,
	Drivers_S32K1xx_LPI2C_Master_Interrupt_Arbitration_Lost				=1<<3,
	Drivers_S32K1xx_LPI2C_Master_Interrupt_NACK_Detect					=1<<4,
	Drivers_S32K1xx_LPI2C_Master_Interrupt_STOP_Detect					=1<<5,
	Drivers_S32K1xx_LPI2C_Master_Interrupt_End_Packet					=1<<6,
	Drivers_S32K1xx_LPI2C_Master_Interrupt_Receive_Data					=1<<7,
	Drivers_S32K1xx_LPI2C_Master_Interrupt_Transmit_Data				=1<<8,
	Drivers_S32K1xx_LPI2C_Master_Interrupt_Bus_Busy						=1<<9,
	Drivers_S32K1xx_LPI2C_Master_Interrupt_Master_Busy					=1<<10,

	Drivers_S32K1xx_LPI2C_Master_Interrupt_SET_Mask						=0x1FF,
	Drivers_S32K1xx_LPI2C_Master_Interrupt_Clear_Mask					=0x7F,
}Drivers_S32K1xx_LPI2C_Master_Interrupt_Type;

typedef enum
{
	Drivers_S32K1xx_LPI2C_Master_Command_Data_Transmit_DATA				=0,
	Drivers_S32K1xx_LPI2C_Master_Command_Data_Receive_DATA_ACK,
	Drivers_S32K1xx_LPI2C_Master_Command_Data_Generate_STOP_Condition,
	Drivers_S32K1xx_LPI2C_Master_Command_Data_Receive_And_Discard_DATA_ACK,
	Drivers_S32K1xx_LPI2C_Master_Command_Data_Generate_START_And_Transmit_Address,
	Drivers_S32K1xx_LPI2C_Master_Command_Data_Generate_START_And_Transmit_Address_NACK,
	Drivers_S32K1xx_LPI2C_Master_Command_Data_High_Speed_Generate_START_And_Transmit_Address,
	Drivers_S32K1xx_LPI2C_Master_Command_Data_High_Speed_Generate_START_And_Transmit_Address_NACK,

	Drivers_S32K1xx_LPI2C_Master_Command_Data_End,
}Drivers_S32K1xx_LPI2C_Master_Command_Data_Type;


typedef enum
{
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_SCLSDA_OpenDrainMasterSlave_SCLSSDAS_NotUsed								=0,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_SCLSDA_OutputOnlyOpenDrainMasterSlave_SCLSSDAS_NotUsed						=1,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_SCLSDA_PushPullMasterSlave_SCLSSDAS_NotUsed									=2,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_SCLSDA_InputOnlyMasterSlave_SCLSSDAS_OutputOnlyPushPullMasterSlave			=3,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_SCLSDA_OpenDrainMaster_SCLSSDAS_OpenDrainSlave								=4,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_SCLSDA_OutputOnlyOpenDrainMaster_SCLSSDAS_OutputOnlyOpenDrainSlave			=5,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_SCLSDA_PushPullMaster_SCLSSDAS_PushPullSlave								=6,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_SCLSDA_InputOnlyMasterSlave_SCLSSDAS_InvertedOutputOnlyPushPullMasterSlave	=7,


	Drivers_S32K1xx_LPI2C_Master_PIN_Config_2PinOpenDrain					=0,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_2PinOutputOnly					=1,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_2PinPushPull					=2,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_4PinPushPull					=3,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_2PinOpenDrainSlave				=4,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_2PinOutputOnlySlave				=5,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_2PinPushPullSlave				=6,
	Drivers_S32K1xx_LPI2C_Master_PIN_Config_4PinPushPullInverted			=7,

	Drivers_S32K1xx_LPI2C_Master_PIN_Config_End								=8,
}Drivers_S32K1xx_LPI2C_Master_PIN_Config_Type;

typedef enum
{
	Drivers_S32K1xx_LPI2C_Master_Prescaler_Divide_By_1						=0,
	Drivers_S32K1xx_LPI2C_Master_Prescaler_Divide_By_2,
	Drivers_S32K1xx_LPI2C_Master_Prescaler_Divide_By_4,
	Drivers_S32K1xx_LPI2C_Master_Prescaler_Divide_By_8,
	Drivers_S32K1xx_LPI2C_Master_Prescaler_Divide_By_16,
	Drivers_S32K1xx_LPI2C_Master_Prescaler_Divide_By_32,
	Drivers_S32K1xx_LPI2C_Master_Prescaler_Divide_By_64,
	Drivers_S32K1xx_LPI2C_Master_Prescaler_Divide_By_128,

	Drivers_S32K1xx_LPI2C_Master_Prescaler_End,
}Drivers_S32K1xx_LPI2C_Master_Prescaler_Type;

typedef enum
{
	Drivers_S32K1xx_LPI2C_Master_Timeout_Config_SCL_Longer_Low				=0,
	Drivers_S32K1xx_LPI2C_Master_Timeout_Config_SCL_OR_SDA_Longer_Low,

	Drivers_S32K1xx_LPI2C_Master_Timeout_Config_End,
}Drivers_S32K1xx_LPI2C_Master_Timeout_Config_Type;

#endif /* DRIVERS_S32K1XX_LPI2C_MASTER_ENUM_H_ */
