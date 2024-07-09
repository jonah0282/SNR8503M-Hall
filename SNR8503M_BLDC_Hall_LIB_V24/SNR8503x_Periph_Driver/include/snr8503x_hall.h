/*******************************************************************************
 * ��Ȩ���� (C)2021, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_hall.h
 * �ļ���ʶ��
 * ����ժҪ�� HALL����ͷ�ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ�   Li
 * ������ڣ� 2021��10��14��
 *
 *******************************************************************************/
#ifndef __snr8503x_HALL_H
#define __snr8503x_HALL_H

/* Includes ------------------------------------------------------------------*/
#include "snr8503x.h"
#include "basic.h"

typedef struct
{
   __IO uint32_t CFG;
   __IO uint32_t INFO;
   __IO uint32_t WIDTH;
   __IO uint32_t TH;
   __IO uint32_t CNT;

} HALL_TypeDef;

typedef struct
{
   uint16_t FilterLen;       /*�˲�����,0��Ӧ����1,1023��Ӧ����1024�˲�����*/
   uint8_t ClockDivision;    /*��Ƶ 0~3:/1 /2 /4 /8*/
   uint8_t Filter75_Ena;     /*ʹ�ܵ�һ��7/5�˲�,�ߵ�ƽ��Ч*/
   uint8_t HALL_Ena;         /*ʹ��HALL,�ߵ�ƽ��Ч*/
   uint8_t HALL_CHGDMA_Ena;  /*HALL�źű仯DMA����ʹ��,�ߵ�ƽ��Ч*/
   uint8_t HALL_OVDMA_Ena;   /*HALL���������DMA����ʹ��,�ߵ�ƽ��Ч*/
   uint8_t Capture_IRQ_Ena;  /*HALL�źű仯�ж�ʹ��,�ߵ�ƽ��Ч*/
   uint8_t OverFlow_IRQ_Ena; /*HALL����������ж�ʹ��,�ߵ�ƽ��Ч*/
   uint32_t CountTH;         /*HALL����������ֵ*/
   uint8_t softIE;           /* ����ж�ʹ�� */
} HALL_InitTypeDef;

#define HALL_CLK_DIV1 ((uint32_t)0x00)
#define HALL_CLK_DIV2 ((uint32_t)0x01)
#define HALL_CLK_DIV4 ((uint32_t)0x02)
#define HALL_CLK_DIV8 ((uint32_t)0x03)

#define HALL_CAPTURE_EVENT ((uint32_t)0x00010000)
#define HALL_OVERFLOW_EVENT ((uint32_t)0x00020000)

void HALL_Init(HALL_InitTypeDef *HALL_InitStruct);
void HALL_StructInit(HALL_InitTypeDef *HALL_InitStruct);

uint32_t HALL_GetFilterValue(void);
uint32_t HALL_GetCaptureValue(void);
uint32_t HALL_WIDCount(void);
uint32_t HALL_GetCount(void);

uint32_t HALL_IsCaptureEvent(void);
uint32_t HALL_IsOverFlowEvent(void);

void HALL_Clear_IRQ(void);

uint32_t HALL_GetIRQFlag(uint32_t tempFlag);
void HALL_ClearIRQFlag(uint32_t tempFlag);


#endif /*__snr8503x_HALL_H */

/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
