/*
 * Drivers.S32K1xx.ADC.c
 *
 *  Created on: 2020年7月19日
 *      Author: Master.HE
 */
#include "Error.h"
#include "Define.h"

#include "Device\__Sys.Device.h"

#include "Module\Module.h"

#include "__Sys.API.h"

#include "S32K1xx.h"

#include "__Drivers.S32K1xx.ADC.Struct.h"
#include "__Drivers.S32K1xx.ADC.h"

#include "Drivers.S32K1xx.ADC.Enum.h"

#include "Drivers.S32K1xx.ADC.h"

Drivers_S32K1xx_ADC_DATA_Type Drivers_S32K1xx_ADC_DATA;


const __Sys_Device_OPS_Type __Device_OPS_ADC0=
{
	.Device_Name="ADC0",
	.Device_Args=ADC0,
	.Open=Drivers_S32K1xx_ADC_Open,
	.Close=Drivers_S32K1xx_ADC_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_ADC_Control,

	.Info="MCU:S32K1xx Module:ADC0 Version:0.0.1 "__DATE__" "__TIME__,
};

#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
const __Sys_Device_OPS_Type __Device_OPS_ADC1=
{
	.Device_Name="ADC1",
	.Device_Args=ADC1,
	.Open=Drivers_S32K1xx_ADC_Open,
	.Close=Drivers_S32K1xx_ADC_Close,
	.Read=Null,
	.Write=Null,
	.Control=Drivers_S32K1xx_ADC_Control,

	.Info="MCU:S32K1xx Module:ADC1 Version:0.0.1 "__DATE__" "__TIME__,
};
#endif

/*
#pragma data_alignment=32
static uint32_t result[ADC_SC1_COUNT];

void PDB_Init(void);
void PDB_Init(void)
{
	PCC->PCCn[PCC_PDB0_INDEX] |= PCC_PCCn_CGC_MASK;  // Enable bus clock in PDB0 //

	PDB0->SC |= PDB_SC_TRGSEL(0xF)  |   // b1111: Software trigger is selected //
			PDB_SC_PRESCALER(8) |   // Prescaler:  010 = sysclck/(2*MULT) = 80 / (2*1) = 40MHz //
			PDB_SC_MULT(2)      |   // 00: Multiplication factor is 1. //
			PDB_SC_PDBEN_MASK;      // 1: PDB enabled //

	PDB0->CH[0].C1 |= PDB_C1_BB(0x00)   | // DLY[0]   : pre-trigger from PDB DLY //
			// DLY[3:1] : back-to-back enabled     //
			PDB_C1_TOS(0x00) | // Pretrigger Output Select: 0=bypassed , 1=enabled//
			PDB_C1_EN(0xFF);   // PDB channel's [3:0] pre-trigger enabled //

	PDB0->CH[1].C1 |= PDB_C1_BB(0x00)   | // DLY[0]   : pre-trigger from PDB DLY //
			// DLY[3:1] : back-to-back enabled     //
			PDB_C1_TOS(0x00) | // Pretrigger Output Select: 0=bypassed , 1=enabled//
			PDB_C1_EN(0xFf);   // PDB channel's [3:0] pre-trigger enabled //

	 //PDB0->MOD = 2200;
	 //PDB0->IDLY = 2200;
	 //PDB0->CH[0].DLY[0] = 100;   // Pretrigger 0 : 100 * 25e-9 =  2.5e-6 //

	PDB0->IDLY = 10000;
	PDB0->MOD = PDB_MOD_MOD(14400);


	PDB0->SC |= PDB_SC_LDOK_MASK;
}
void ADC_Init(void);
void ADC_Init(void)
{

  PCC->PCCn[PCC_ADC0_INDEX] &= ~PCC_PCCn_CGC_MASK;  // Disable clock to change PCS //
  PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_PCS(3);    // PCS=3: Select SPLL //
  PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_CGC_MASK;  // Enable bus clock in ADC //

  ADC0->CFG1.DATA |= ADC_CFG1_ADICLK(0) |     // Only ALTCLK1 is available //
		  	  	ADC_CFG1_ADIV(2) |		 // the clock rate is (input clock)/4 //
                ADC_CFG1_MODE(1);        // 0b00: 8-bit, 0b01: 12-bit, 0b10: 10-bit //
  ADC0->SC2.DATA |= ADC_SC2_ADTRG(1) |          // Conversion Trigger:  0b0= SW , 0b1 = HW //
  	  	  	  ADC_SC2_DMAEN(1);			  // enable DMA trigger //

  ADC0->SC1[0].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[1].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[2].DATA = ADC_SC1_ADCH(3);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[3].DATA = ADC_SC1_ADCH(3);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[4].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[5].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[6].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[7].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[8].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[9].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[10].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[11].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[12].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[13].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[14].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
  ADC0->SC1[15].DATA = ADC_SC1_ADCH(29);       // Select AD12 (ADC0_SE12) @PTC14 //
}
void DMA_init(void);
void DMA_init(void)
{
	SIM->PLATCGC|=SIM_PLATCGC_CGCDMA_MASK;

  //PCC->PCCn[PCC_DMA0_INDEX] |= PCC_PCCn_CGC_MASK;          	// CGC=1: Clock enabled for DMA0

  eDMA->TCD[0].CSR &= 0xFFFFFFFF ^ DMA_TCD_CSR_DONE_MASK;  					// Clear Channel Done flag
  eDMA->TCD[0].SADDR = DMA_TCD_SADDR_SADDR(&(ADC0->R[0].DATA));  				// Source Address
  eDMA->TCD[0].SOFF = DMA_TCD_SOFF_SOFF(4);                					// Source Offset
  eDMA->TCD[0].ATTR = DMA_TCD_ATTR_SMOD(0)  |              					// Source address modulo feature is disabled
                    DMA_TCD_ATTR_SSIZE(2) |              					// Source data transfer size: 1: 16-bit, 2=32-bit
                    DMA_TCD_ATTR_DMOD(0)  |              					// Destination address modulo feature: 0=disabled, x= x power of 2 buffer[DMOD=4->buffer of 16bytes]
                    DMA_TCD_ATTR_DSIZE(2);               					// Destination data transfer size: 1: 16-bit, 2=32-bit
  eDMA->TCD[0].NBYTES.MLOFFNO = DMA_TCD_NBYTES_MLNO_NBYTES(4); 				// Minor Byte Transfer Count is 4-bytes
  eDMA->TCD[0].SLAST = DMA_TCD_SLAST_SLAST(-64);             					// Last Source Address Adjustment is -16
  eDMA->TCD[0].DADDR = DMA_TCD_DADDR_DADDR(&(result[0]));     			// Destination Address of Buffer
  eDMA->TCD[0].DOFF = DMA_TCD_DOFF_DOFF(4);                					// Destination Address Signed Offset is 4
  eDMA->TCD[0].CITER.ELINKNO = DMA_TCD_CITER_ELINKNO_CITER(ADC_SC1_COUNT)  				// Current Major Iteration Count is 4
                                     | DMA_TCD_CITER_ELINKNO_ELINK(0);  	// The channel-to-channel linking is disabled
  eDMA->TCD[0].DLASTSGA = DMA_TCD_DLASTSGA_DLASTSGA(-64);    					// Destination last address adjustment is -16
  eDMA->TCD[0].BITER.ELINKNO = DMA_TCD_BITER_ELINKNO_BITER(ADC_SC1_COUNT) | 				// Starting major iteration count is 4
                                       DMA_TCD_BITER_ELINKNO_ELINK(0);  	// The minor channel-to-channel linking is disabled
  eDMA->TCD[0].CSR = DMA_TCD_CSR_BWC(0)         |         					// BWC=0: No eDMA engine stalls - full bandwidth
                    DMA_TCD_CSR_MAJORELINK(0)  |        					// The channel-to-channel linking is disabled
                    DMA_TCD_CSR_MAJORLINKCH(0) |       						// channel 1 will be called from ch0
                    DMA_TCD_CSR_ESG(0)         |         					// The current channel�fs TCD is normal format - No scatter/gather
                    DMA_TCD_CSR_DREQ(0)        |         					// The channel's ERQ bit is not affected
                    DMA_TCD_CSR_INTHALF(0)     |         					// The half-point interrupt is disabled
                    DMA_TCD_CSR_INTMAJOR(1)    |         					// The end-of-major loop interrupt is enabled
                    DMA_TCD_CSR_START(0);                					// The channel is not explicitly started

  eDMA->SERQ = 0;	// enable DMA channel 0 HW trigger
}
void DMAMUX_Init (void);
void DMAMUX_Init (void)
{
	PCC->PCCn[PCC_DMAMUX_INDEX] |= PCC_PCCn_CGC_MASK;    // CGC=1: Clock enabled for DMAMUX0

	DMAMUX->CHCFG[0] &= ~ DMAMUX_CHCFG_ENBL(1);         // Disabling the DMA channel
	DMAMUX->CHCFG[0] |= DMAMUX_CHCFG_SOURCE(42);        // ADC0 COCO is the source of the DMA0 channel
	DMAMUX->CHCFG[0] |= DMAMUX_CHCFG_ENBL(1);           // Enabling the DMA channel
}
void DMA0_IRQHandler(void *Args,int IRQ_Index);
void DMA0_IRQHandler(void *Args,int IRQ_Index)
{

	PDB0->SC |= PDB_SC_SWTRIG_MASK;    // restart PDB counter //

	eDMA->CINT = 0; // clear DMA channel 0 interrupt flag
}
*/

int Drivers_S32K1xx_ADC_Setup(void)
{
	int Err;

	for(int i=0;i<ADC_INSTANCE_COUNT;i++)
	{
		Drivers_S32K1xx_ADC_DATA.ADC[i].Open=false;

	}

	//Error_Args_Return(Err,__Sys_IRQ_Register_Hook(DMA0_IRQn,DMA0_IRQHandler,Null));
	//Error_NoArgs_Return(Err,__Sys_IRQ_Enable(DMA0_IRQn));


	//注册当前设备的OPS
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_ADC0));
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
	Error_NoArgs_Return(Err,__Sys_Device_Register_Drivers(&__Device_OPS_ADC1));
#endif


    //ADC_Init();
    //PDB_Init();
    //DMA_init();
    //DMAMUX_Init();

    //PDB0->SC |= PDB_SC_SWTRIG_MASK;    // restart PDB counter //

	//获取MCU时钟树
	Error_NoArgs_Return(Err,__Sys_BSP_UpData_Clock_Tree((void **)&Drivers_S32K1xx_ADC_DATA.Clock.Source,(void **)&Drivers_S32K1xx_ADC_DATA.Clock.Tree));
	return Error_OK;
}

int Drivers_S32K1xx_ADC_Open(void *Device_Args,int Mode)
{
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}

	int Err;
	int Index=Drivers_S32K1xx_ADC_GET_Count(Device_Args);

	//设备是独占的 不允许 多次打开
	if(Drivers_S32K1xx_ADC_DATA.ADC[Index].Open==true)
	{
		return Error_Exist;
	}

	//Mode 作为时钟源参数
	//改变模块时钟之前确保时钟是关闭的
	Error_NoArgs_Return(Err,Drivers_S32K1xx_ADC_SET_Clock_Source_Enabled((ADC_Type *)Device_Args,Drivers_S32K1xx_ADC_Clock_Source_ALTCLK1_Disable,Disable,Null));

	//设置模块时钟源
	//打开模块时钟
	Error_Args_Return(Err,Drivers_S32K1xx_ADC_SET_Clock_Source_Enabled((ADC_Type *)Device_Args,(Drivers_S32K1xx_ADC_Clock_Source_Type)(Drivers_S32K1xx_ADC_Open_Mode_Clock_Source_Mask&Mode),Enable,Drivers_S32K1xx_ADC_DATA.Clock.Tree));

	//校准
	Error_Args_Return(Err,Drivers_S32K1xx_ADC_SET_AutoCalibration((ADC_Type *)Device_Args));

	Error_Args_Return(Err,Drivers_S32K1xx_ADC_Init((ADC_Type *)Device_Args));

	Drivers_S32K1xx_ADC_DATA.ADC[Index].Open=true;
	return Error_OK;
}
int Drivers_S32K1xx_ADC_Close(void *Device_Args)
{
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}
	int Err;
	int Index=Drivers_S32K1xx_ADC_GET_Count(Device_Args);


	//关闭模块时钟
	Error_NoArgs_Return(Err,Drivers_S32K1xx_ADC_SET_Clock_Source_Enabled((ADC_Type *)Device_Args,Drivers_S32K1xx_ADC_Clock_Source_ALTCLK1_Disable,Disable,Null));


	Drivers_S32K1xx_ADC_DATA.ADC[Index].Open=false;
	return Error_OK;
}
int Drivers_S32K1xx_ADC_Control(void *Device_Args,int Cmd, unsigned long Args)
{
	int Err;
	if(Device_Args==Null)
	{
		return Error_Unknown;
	}
	switch (Cmd&Drivers_S32K1xx_ADC_Cmd_Mask)
	{
		case Drivers_S32K1xx_ADC_Cmd_Read_Channel_DATA:
		{
			uint8_t *P_DATA=(uint8_t *)Args;
			uint32_t DATA=0;
			Error_NoArgs_Return(Err,Drivers_S32K1xx_ADC_GET_Channel_DATA((ADC_Type *)Device_Args,Cmd&0xFF,&DATA));

			*P_DATA=DATA>>4;

			return Error_OK;
		}break;
		default:
		{
			return Error_Invalid_Parameter;
		}break;
	}

	//return Error_OK;
}
//----------------------------------------------------------------------------------------------------












//----------------------------------------------------------------------------------------------------
int Drivers_S32K1xx_ADC_GET_Count(void *Device_Args)
{
	switch ((uint32_t)Device_Args)
	{
		case ADC0_BASE:
		{
			return 0;
		}break;
#if (defined (__Target_S32K142__) || defined (__Target_S32K144__) || defined (__Target_S32K146__) || defined (__Target_S32K148__))
		case ADC1_BASE:
		{
			return 1;
		}break;
#endif
		default:
		{
			while(1);//绝对不能出现
		}break;
	}
}

__Sys_Device_Module_Init_Export(Drivers_S32K1xx_ADC_Setup);
