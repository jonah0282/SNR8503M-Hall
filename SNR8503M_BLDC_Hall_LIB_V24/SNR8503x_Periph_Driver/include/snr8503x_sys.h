/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_sys.h
 * �ļ���ʶ��
 * ����ժҪ�� SYS��������ͷ�ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 2021��11��09��
 *
 *******************************************************************************/
 
#ifndef __snr8503x_SYS_H
#define __snr8503x_SYS_H


/* Includes ------------------------------------------------------------------*/
#include "snr8503x.h"
#include "basic.h"
#include "snr8503x_gpio.h"

typedef struct
{
	uint32_t PLL_SrcSel;                      /*PLL�ź�����Դѡ��RCʱ�ӻ��ⲿ����*/
	uint32_t PLL_DivSel;                      /*ѡ��8��ʱ�������У��ĸ��������ʱ��*/
	uint32_t PLL_ReDiv;                       /*PLL�ٷ�Ƶ��1��Ƶ��4��Ƶ*/

	uint32_t Clk_DivI2C;                      /*SPI I2Cʱ�ӷ�Ƶ*/
	uint32_t Clk_DivUART;                     /*UARTʱ�ӷ�Ƶ*/
	uint32_t Clk_FEN;                         /*ģ��ʱ��ʹ��*/

}SYS_InitTypeDef;

/*PLL�ź�����Դѡ��*/
#define SYS_PLLSRSEL_RCH        0x00          /*ʹ��4MHz RCʱ��*/
#define SYS_PLLSRSEL_CRYSTAL    0x01          /*ʹ�þ���ʱ��*/

/*PLL�ٷ�Ƶ����*/
#define SYS_PLLREDIV_4			0x00          /*��PLL��Ƶ��������/4*/
#define SYS_PLLREDIV_1			0x01          /*��PLL��Ƶ�����ϲ��ٷ�Ƶ*/

/*SPIʱ�ӷ�Ƶ*/
#define SYS_Clk_SPIDiv1          0
#define SYS_Clk_SPIDiv2          1
#define SYS_Clk_SPIDiv4          2
#define SYS_Clk_SPIDiv8          3

/*UARTʱ�ӷ�Ƶ*/
#define SYS_Clk_UARTDiv1         0
#define SYS_Clk_UARTDiv2         1
#define SYS_Clk_UARTDiv4         2
#define SYS_Clk_UARTDiv8         3

/*����ģ��λ����*/
#define SYS_Module_I2C          BIT0   //I2C
#define SYS_Module_HALL         BIT1   //HALL
#define SYS_Module_UART         BIT2   //UART
#define SYS_Module_CMP          BIT3   //CMP
#define SYS_Module_MCPWM        BIT4   //MCPWM
#define SYS_Module_TIMER0       BIT5   //TIMER0
#define SYS_Module_TIMER1       BIT6   //TIMER1
#define SYS_Module_GPIO         BIT7   //GPIO
#define SYS_Module_DIV          BIT8   //DIV
#define SYS_Module_ADC          BIT9   //ADC
#define SYS_Module_SPI          BIT10  //SPI
#define SYS_Module_DMA          BIT11  //DMA

/*ģ��ģ�鶨��*/
#define SYS_AnalogModule_ADC    BIT8   // ADC
#define SYS_AnalogModule_OPA    BIT9   // OPA
#define SYS_AnalogModule_BGP    BIT10  // BGP
#define SYS_AnalogModule_DAC    BIT11  // DAC
#define SYS_AnalogModule_TMP    BIT12  // TMP
#define SYS_AnalogModule_CMP0   BIT13  // CMP0
#define SYS_AnalogModule_CMP1   BIT14  // CMP1
#define SYS_AnalogModule_PLL    BIT15  // PLL

/*���Ź���ʱʱ��*/
#define SYS_WD_TimeOut2s  0         /*2s��λ*/
#define SYS_WD_TimeOut4s  1         /*4s��λ*/
#define SYS_WD_TimeOut8s 2         /*8s��λ*/
#define SYS_WD_TimeOut64s 3         /*64s��λ*/

/*��λ�ź�Դ����*/
#define SYS_RstSrc_LPOR        0x01
#define SYS_RstSrc_HPOR        0x02
#define SYS_RstSrc_KEYBOARD    0x04     /*������λ*/
#define SYS_RstSrc_WDT         0x08     /*WDT��λ*/

/*���߻��Ѽ��ʱ��*/
#define SYS_WakeInterval_025s  0x00     /*0.25s*/    
#define SYS_WakeInterval_05s   0x01     /*0.5s*/
#define SYS_WakeInterval_1s    0x02     /*1s*/
#define SYS_WakeInterval_2s    0x03     /*2s*/
#define SYS_WakeInterval_4s    0x04     /*4s*/
#define SYS_WakeInterval_8s    0x05     /*8s*/
#define SYS_WakeInterval_16s   0x06     /*16s*/
#define SYS_WakeInterval_32s   0x07     /*32s*/


void SYS_Init(SYS_InitTypeDef* SYS_InitStruct);         // sysģ���ʼ��
void SYS_StructInit(SYS_InitTypeDef* SYS_InitStruct);   // SYS�ṹ���ʼ��
void SYS_ClearRst(void);                                // SYS�����λ��־
void SYS_ModuleClockCmd(uint32_t,FuncState);            // ����ģ��ʱ��ʹ�ܺ�ֹͣ
void SYS_AnalogModuleClockCmd(uint32_t, FuncState);     // ģ��ģ��ʹ�ܺ�ֹͣ
void SYS_SoftResetModule(uint32_t nModule);             // ģ����λ

u32 SYS_GetRstSource(void);                             // ���SYS��λԴ�ź�

#endif /*__snr8503x_SYS_H */

/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
