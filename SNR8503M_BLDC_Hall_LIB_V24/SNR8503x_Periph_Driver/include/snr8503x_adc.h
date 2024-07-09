/*******************************************************************************
 * ��Ȩ���� (C)2021, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_adc.h
 * �ļ���ʶ��
 * ����ժҪ�� ADC������������ͷ�ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ�   Li
 * ������ڣ� 2021��10��14��
 *
 *******************************************************************************/

#ifndef _CONNIE_ADC_H_
#define _CONNIE_ADC_H_

/* Includes ------------------------------------------------------------------*/
#include "snr8503x.h"
#include "basic.h"

typedef struct
{
    __IO uint32_t DAT0;
    __IO uint32_t DAT1;
    __IO uint32_t DAT2;
    __IO uint32_t DAT3;
    __IO uint32_t DAT4;
    __IO uint32_t DAT5;
    __IO uint32_t DAT6;
    __IO uint32_t DAT7;
    __IO uint32_t DAT8;
    __IO uint32_t DAT9;
    __IO uint32_t null0;
    __IO uint32_t null1;
    __IO uint32_t LTH;
    __IO uint32_t HTH;
    __IO uint32_t GEN;
    __IO uint32_t null2;
    __IO uint32_t CHN0;
    __IO uint32_t CHN1;
    __IO uint32_t CHN2;
    __IO uint32_t null3;

    __IO uint32_t CHNT0;

    __IO uint32_t CFG;
    __IO uint32_t SWT;

    __IO uint32_t null;

    __IO uint32_t DC;
    __IO uint32_t AMC;

    __IO uint32_t IE;
    __IO uint32_t IF;

} ADC_TypeDef;

typedef struct
{
	  uint16_t ADC_SAMP_CLK; /* ADC ����ʱ��ѡ��*/
    uint16_t IE;           /* Configures ADC_IRQ */
    uint16_t Align;        /* Configures ADC Result Align */
    uint16_t Con_Sample;   /* ��������ģʽ */
    uint16_t Trigger_Cnt;  /* ����ģʽ�´�����һ�β�������Ĵ����¼��� */
    uint16_t FirSeg_Ch;    /* ��һ�β�������ͨ���� */
    uint16_t SecSeg_Ch;    /* �ڶ��β�������ͨ���� */
    uint16_t ThrSeg_Ch;    /* �����β�������ͨ���� */
    uint16_t FouSeg_Ch;    /* ���Ķβ�������ͨ���� */
    uint16_t Trigger_Mode; /* ADC trigger mode */
    uint16_t Trigger_En;   /* TADC����ADC����ʹ���ź� */
    uint16_t SEL_En;       /* TADC������Դѡ��0:MCPWM��1:UTimer */
    uint16_t AMC0;
    uint16_t AMC1;
    uint16_t ADC_GEN_En;  /* ADCģ�⿴�Ź� */
    uint16_t ADC_GEN_HTH; /* ADCģ�⿴�Ź�����ֵ */
    uint16_t ADC_GEN_LTH; /* ADCģ�⿴�Ź�����ֵ */
	  uint16_t REFOUT_EN;   /* ADC REF���ʹ��*/
} ADC_InitTypeDef;

#define ADC_1_TIMES_SAMPLE ((u8)1) /* ADC����ͨ����1�β��� */
#define ADC_2_TIMES_SAMPLE ((u8)2) /* ADC����ͨ����2�β��� */
#define ADC_3_TIMES_SAMPLE ((u8)3) /* ADC����ͨ����3�β��� */
#define ADC_4_TIMES_SAMPLE ((u8)4)
#define ADC_5_TIMES_SAMPLE ((u8)5)
#define ADC_6_TIMES_SAMPLE ((u8)6)
#define ADC_7_TIMES_SAMPLE ((u8)7)
#define ADC_8_TIMES_SAMPLE ((u8)8)
#define ADC_9_TIMES_SAMPLE ((u8)9) /* ADC����ͨ����9�β��� */


#define ADC_GEN_DAT0 ((uint16_t)0x01)  /* DAT0���Ź����ʹ�� */
#define ADC_GEN_DAT1 ((uint16_t)0x02)  /* DAT1���Ź����ʹ�� */
#define ADC_GEN_DAT2 ((uint16_t)0x04)  /* DAT2���Ź����ʹ�� */
#define ADC_GEN_DAT3 ((uint16_t)0x08)  /* DAT3���Ź����ʹ�� */
#define ADC_GEN_DAT4 ((uint16_t)0x10)  /* DAT4���Ź����ʹ�� */
#define ADC_GEN_DAT5 ((uint16_t)0x20)  /* DAT5���Ź����ʹ�� */
#define ADC_GEN_DAT6 ((uint16_t)0x40)  /* DAT6���Ź����ʹ�� */
#define ADC_GEN_DAT7 ((uint16_t)0x80)  /* DAT7���Ź����ʹ�� */
#define ADC_GEN_DAT8 ((uint16_t)0x100) /* DAT8���Ź����ʹ�� */
#define ADC_GEN_DAT9 ((uint16_t)0x200) /* DAT9���Ź����ʹ�� */

#define ADC_EOS0_IRQ_EN ((uint16_t)0x01)     /* ��һ��ɨ������ж� */
#define ADC_EOS1_IRQ_EN ((uint16_t)0x02)     /* �ڶ���ɨ������ж� */
#define ADC_EOS2_IRQ_EN ((uint16_t)0x04)     /* ������ɨ������ж� */
#define ADC_EOS3_IRQ_EN ((uint16_t)0x08)     /* ���Ķ�ɨ������ж� */
#define ADC_CONFLICT_IRQ_EN ((uint16_t)0x10) /* ���������ͻ */
#define ADC_HERR_IRQ_EN ((uint16_t)0x20)     /* Ӳ��������ͻ */
#define ADC_DAT0_OV_IRQ_EN ((uint16_t)0x40)  /* ����ֵ�ж� */

#define ADC_EOS0_DMA_EN ((uint16_t)0x100)      /* ��һ��ɨ�����DMA����ʹ�� */
#define ADC_EOS1_DMA_EN ((uint16_t)0x200)      /* �ڶ���ɨ�����DMA����ʹ�� */
#define ADC_EOS2_DMA_EN ((uint16_t)0x400)      /* ������ɨ�����DMA����ʹ�� */
#define ADC_EOS3_DMA_EN ((uint16_t)0x800)      /* ���Ķ�ɨ�����DMA����ʹ�� */
#define ADC_CONFLICT_DMA_EN ((uint16_t)0x1000) /* ���������ͻDMA����ʹ�� */
#define ADC_HERR_DMA_EN ((uint16_t)0x2000)     /* Ӳ��������ͻDMA����ʹ�� */
#define ADC_DAT0_OV_DMA_EN ((uint16_t)0x4000)  /* ����ֵDMA����ʹ�� */

#define ADC_DAT0_OV_IRQ_IF ((uint16_t)0x40)  /* ����ֵ�ж� */
#define ADC_CONFLICT_IRQ_IF ((uint16_t)0x20) /* Ӳ��������ͻ��־ */
#define ADC_HERR_IRQ_IF ((uint16_t)0x10)     /* ���������ͻ��־ */
#define ADC_EOS3_IRQ_IF ((uint16_t)0x08)     /* ���Ķ�ɨ������жϱ�־ */
#define ADC_EOS2_IRQ_IF ((uint16_t)0x04)     /* ������ɨ������жϱ�־*/
#define ADC_EOS1_IRQ_IF ((uint16_t)0x02)     /* �ڶ���ɨ������жϱ�־ */
#define ADC_EOS0_IRQ_IF ((uint16_t)0x01)     /* ��һ��ɨ������жϱ�־ */

#define ADC_LEFT_ALIGN ((uint16_t)0x0000)  /* ADC������������ */
#define ADC_RIGHT_ALIGN ((uint16_t)0x0001) /* ADC��������Ҷ��� */

#define ADC_DAT0_HTH ((uint16_t)0x0001) /* ADC_DAT0_TH��Ϊ����ֵ */
#define ADC_DAT0_LTH ((uint16_t)0x0000) /* ADC_DAT0_TH��Ϊ����ֵ */

#define ADC_MCPWM_SEL ((uint16_t)0x0000)  /* MCPWM ����ADC���� */
#define ADC_UTIMER_SEL ((uint16_t)0x0001) /* UTIMER����ADC���� */

#define ADC_1SEG_TRG ((uint16_t)0x00) /* ADC���õ���ģʽ */
#define ADC_2SEG_TRG ((uint16_t)0x01) /* ADC����2��ģʽ */
#define ADC_4SEG_TRG ((uint16_t)0x03) /* ADC����4��ģʽ */

#define ADC_CHANNEL_0 ((uint16_t)0x00)  /* ADCͨ��0  OPA0_OUT*/
#define ADC_CHANNEL_1 ((uint16_t)0x01)  /* ADCͨ��1  ADC_CH1*/
#define ADC_CHANNEL_2 ((uint16_t)0x02)  /* ADCͨ��2  ADC_CH2*/
#define ADC_CHANNEL_3 ((uint16_t)0x03)  /* ADCͨ��3  ADC_CH3*/
#define ADC_CHANNEL_4 ((uint16_t)0x04)  /* ADCͨ��4  ADC_CH4*/
#define ADC_CHANNEL_5 ((uint16_t)0x05)  /* ADCͨ��5  ADC_CH5*/
#define ADC_CHANNEL_6 ((uint16_t)0x06)  /* ADCͨ��6  ADC_CH6*/
#define ADC_CHANNEL_7 ((uint16_t)0x07)  /* ADCͨ��7  ADC_CH7*/
#define ADC_CHANNEL_8 ((uint16_t)0x08)  /* ADCͨ��8  ADC_CH8/OPA1_OUT*/
#define ADC_CHANNEL_9 ((uint16_t)0x09)  /* ADCͨ��9  ADC_CH9*/
#define ADC_CHANNEL_10 ((uint16_t)0x0a) /* ADCͨ��10 ADC_CH10*/
#define ADC_CHANNEL_11 ((uint16_t)0x0b) /* ADCͨ��11 �¶ȴ�����*/
#define ADC_CHANNEL_12 ((uint16_t)0x0c) /* ADCͨ��12 �ڲ���*/
#define ADC_CHANNEL_13 ((uint16_t)0x0d) /* ADCͨ��13 2.4V��׼Դ*/

#define ADC_HARDWARE_T0_TRG ((uint16_t)0x01) /* ADC����Ӳ��T0�¼����� */
#define ADC_HARDWARE_T1_TRG ((uint16_t)0x02) /* ADC����Ӳ��T1�¼����� */
#define ADC_HARDWARE_T2_TRG ((uint16_t)0x04) /* ADC����Ӳ��T2�¼����� */
#define ADC_HARDWARE_T3_TRG ((uint16_t)0x08) /* ADC����Ӳ��T3�¼����� */

void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct);

#endif /*_CONNIE_ADC_H_ */

/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
