/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_gpio.h
 * �ļ���ʶ��
 * ����ժҪ�� GPIO������������ͷ�ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 21/11/10
 *
 *******************************************************************************/

#ifndef __snr8503x_GPIO_H
#define __snr8503x_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "snr8503x.h"
#include "basic.h"

typedef struct
{
   __IO uint32_t PIE;
   __IO uint32_t POE;
   __IO uint32_t PDI;
   __IO uint32_t PDO;
   __IO uint32_t PUE;
   __IO uint32_t null1;
   __IO uint32_t PODE;
   __IO uint32_t null2;
   __IO uint32_t F3210;
   __IO uint32_t F7654;
   __IO uint32_t FBA98;
   __IO uint32_t FFEDC;
   __IO uint32_t BSRR;
   __IO uint32_t BRR;
} GPIO_TypeDef;

typedef struct
{
   __IO uint32_t CR0;
   __IO uint32_t CR1;
   __IO uint32_t IE;
   __IO uint32_t IF;
   __IO uint32_t SEL;
} EXTI_TypeDef;

typedef enum
{
   EXTI_Trigger_None    = 0x00, // ������
   EXTI_Trigger_Negedge = 0x01, // �½��ش���
   EXTI_Trigger_Posedge = 0x02, // �����ش���
   EXTI_Trigger_Edge    = 0x03  // �����ء��½��ؾ�����
} EXTIMode_TypeDef;
typedef enum
{
   GPIO_Mode_IN  = 0x00, // GPIO����ģʽ
   GPIO_Mode_OUT = 0x01, // GPIO���ģʽ
   GPIO_Mode_ANA = 0x02  // GPIOģ���·
} GPIOMode_TypeDef;

typedef enum
{
   GPIO_PuPd_NOPULL = 0x00, // ����������������
   GPIO_PuPd_UP     = 0x01, // ����
   GPIO_PuPd_DOWN   = 0x02, // ����
} GPIOPuPd_TypeDef;

typedef enum
{
   Bit_RESET = 0,
   Bit_SET
} BitAction;

typedef struct
{
   uint32_t          GPIO_Pin;     // Ҫ���õ�Pad
   GPIOMode_TypeDef  GPIO_Mode;    // GPIOģʽ:���롢�����ģ��
   GPIOPuPd_TypeDef  GPIO_PuPd;    // ����OR����
   uint32_t          GPIO_PODEna;  // ��©
} GPIO_InitTypeDef;

// GPIO ���ù���
#define AF0_GPIO          0
#define AF1_CMP           1
#define AF2_HALL          2
#define AF3_MCPWM         3
#define AF4_UART          4
#define AF5_SPI           5
#define AF6_I2C           6
#define AF7_TIMER0        7
#define AF8_TIMER1        8
#define AF9_ADC_TRIGGER   9

// GPIO ���Ŷ���
#define GPIO_Pin_NONE     0
#define GPIO_Pin_0        BIT0
#define GPIO_Pin_1        BIT1
#define GPIO_Pin_2        BIT2
#define GPIO_Pin_3        BIT3
#define GPIO_Pin_4        BIT4
#define GPIO_Pin_5        BIT5
#define GPIO_Pin_6        BIT6
#define GPIO_Pin_7        BIT7
#define GPIO_Pin_8        BIT8
#define GPIO_Pin_9        BIT9
#define GPIO_Pin_10       BIT10
#define GPIO_Pin_11       BIT11
#define GPIO_Pin_12       BIT12
#define GPIO_Pin_13       BIT13
#define GPIO_Pin_14       BIT14
#define GPIO_Pin_15       BIT15
#define GPIO_Pin_ALL      (uint32_t)0xFFFF

// GPIO ��Ŷ���
#define GPIO_PinSource_0   0
#define GPIO_PinSource_1   1
#define GPIO_PinSource_2   2
#define GPIO_PinSource_3   3
#define GPIO_PinSource_4   4
#define GPIO_PinSource_5   5
#define GPIO_PinSource_6   6
#define GPIO_PinSource_7   7
#define GPIO_PinSource_8   8
#define GPIO_PinSource_9   9
#define GPIO_PinSource_10 10
#define GPIO_PinSource_11 11
#define GPIO_PinSource_12 12
#define GPIO_PinSource_13 13
#define GPIO_PinSource_14 14
#define GPIO_PinSource_15 15

// EXTI_IF �жϱ�־λ����
#define GPIO_P00_EXTI_IF  BIT0
#define GPIO_P02_EXTI_IF  BIT1
#define GPIO_P04_EXTI_IF  BIT2
#define GPIO_P05_EXTI_IF  BIT3
#define GPIO_P06_EXTI_IF  BIT4
#define GPIO_P07_EXTI_IF  BIT5
#define GPIO_P08_EXTI_IF  BIT6
#define GPIO_P09_EXTI_IF  BIT7
#define GPIO_P014_EXTI_IF BIT8
#define GPIO_P015_EXTI_IF BIT9
#define GPIO_P14_EXTI_IF  BIT10
#define GPIO_P15_EXTI_IF  BIT11
#define GPIO_P16_EXTI_IF  BIT12
#define GPIO_P17_EXTI_IF  BIT13
#define GPIO_P18_EXTI_IF  BIT14
#define GPIO_P19_EXTI_IF  BIT15

// CLKO_SEL ʱ���źŵ������ѡ��
#define CLKO_SEL_ADC BIT3   // 24MHz
#define CLKO_SEL_PLL BIT2   // 48MHz �޷���������
#define CLKO_SEL_HSI BIT1   // 4MHz
#define CLKO_SEL_LSI BIT0   // 64kHz

// GPIO��ʼ��
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct);

// GPIO ��
uint32_t GPIO_ReadInputData    (GPIO_TypeDef *GPIOx);
uint32_t GPIO_ReadOutputData   (GPIO_TypeDef *GPIOx);
uint8_t  GPIO_ReadInputDataBit (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t  GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
// GPIO д
void GPIO_Write     (GPIO_TypeDef *GPIOx, uint32_t Val);
void GPIO_SetBits   (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit  (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal);

// GPIO����ѡ��
void GPIO_PinAFConfig(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint32_t GPIO_AF);

// EXTI��� 
void EXTI_Trigger_Config(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint16_t EXTI_Trigger);

#endif /*__snr8503x_GPIO_H */

/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
