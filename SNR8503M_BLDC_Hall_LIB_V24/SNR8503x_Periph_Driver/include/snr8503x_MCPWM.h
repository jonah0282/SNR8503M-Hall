/*******************************************************************************
 * ��Ȩ���� (C)2021, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_MCPWM.h
 * �ļ���ʶ�� 
 * ����ժҪ�� MCPWM������������ͷ�ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 2021��10��14��
 *
 *
 *******************************************************************************/

#ifndef __SNR8503X_PWM_H
#define __SNR8503X_PWM_H

/* Includes ------------------------------------------------------------------*/
#include "snr8503x.h"
#include "basic.h"

typedef struct
{
  __IO u32 PWM_TH00; /* MCPWM CH0_P �Ƚ�����ֵ�Ĵ��� 0x00*/
  __IO u32 PWM_TH01; /* MCPWM CH0_N �Ƚ�����ֵ�Ĵ���*/
  __IO u32 PWM_TH10;
  __IO u32 PWM_TH11;
  __IO u32 PWM_TH20;
  __IO u32 PWM_TH21;
  __IO u32 PWM_TH30;
  __IO u32 PWM_TH31;
  __IO u32 PWM_TMR0; /* ADC ������ʱ���Ƚ����� 0 �Ĵ��� */
  __IO u32 PWM_TMR1;
  __IO u32 PWM_TMR2;
  __IO u32 PWM_TMR3;
  __IO u32 PWM_TH0; /* MCPWM ʱ�� 0 ����ֵ�Ĵ��� */
  __IO u32 PWM_TH1;
  __IO u32 PWM_CNT0; /* MCPWM ʱ�� 0 �������Ĵ��� 0x38 */
  __IO u32 PWM_CNT1;
  __IO u32 PWM_UPDATE; /* MCPWM �ֶ����ؿ��ƼĴ��� */
  __IO u32 PWM_FCNT;   /* MCPWM FAIL ʱ�� CNT ֵ */
  __IO u32 PWM_EVT0;   /* MCPWM ʱ�� 0 �ⲿ���� */
  __IO u32 PWM_EVT1;
  __IO u32 PWM_DTH0; /* MCPWM CH0123 Nͨ��������ȿ��ƼĴ��� */
  __IO u32 PWM_DTH1; /* MCPWM CH0123 Pͨ��������ȿ��ƼĴ��� */
  __IO u32 null0;
  __IO u32 null1;
  __IO u32 null2;
  __IO u32 null3;
  __IO u32 null4;
  __IO u32 null5;
  __IO u32 PWM_FLT;   /* MCPWM �˲�ʱ�ӷ�Ƶ�Ĵ��� 0x70 */
  __IO u32 PWM_SDCFG; /* MCPWM �������üĴ��� */
  __IO u32 PWM_AUEN;  /* MCPWM �Զ�����ʹ�ܼĴ��� */
  __IO u32 PWM_TCLK;  /* MCPWM ʱ�ӷ�Ƶ���ƼĴ��� */
  __IO u32 PWM_IE0;   /* MCPWM ʱ�� 0 �жϿ��ƼĴ��� */
  __IO u32 PWM_IF0;   /* MCPWM ʱ�� 0 �жϱ�־λ�Ĵ��� */
  __IO u32 PWM_IE1;
  __IO u32 PWM_IF1;
  __IO u32 PWM_EIE; /* MCPWM �쳣�жϿ��ƼĴ��� 0x90*/
  __IO u32 PWM_EIF;
  __IO u32 PWM_RE;   /* MCPWM DMA ������ƼĴ��� */
  __IO u32 PWM_PP;   /* MCPWM ����ģʽʹ�ܼĴ��� */
  __IO u32 PWM_IO01; /* MCPWM CH0 CH1 IO ���ƼĴ��� */
  __IO u32 PWM_IO23;
  __IO u32 PWM_FAIL012; /* MCPWM CH0 CH1 CH2 ��·���ƼĴ��� */
  __IO u32 PWM_FAIL3;   /* MCPWM CH3 ��·���ƼĴ��� */
  __IO u32 PWM_PRT;     /* MCPWM �����Ĵ��� */
  __IO u32 PWM_CHMSK;   /* MCPWM ͨ������λ�Ĵ��� */
} MCPWM_REG_TypeDef;

typedef struct
{
  u16 TimeBase0_PERIOD; /* ʱ��0��������*/
  u16 TimeBase1_PERIOD; /* ʱ��1��������*/
  u8 CLK_DIV;           /* MCPWM ��Ƶϵ�� */
  u8 MCLK_EN;           /* MCPWM ʱ��ʹ�ܿ��� */
  u8 MCPWM_Cnt0_EN;     /* MCPWM ʱ��0��������ʹ�ܿ��� */
  u8 MCPWM_Cnt1_EN;     /* MCPWM ʱ��1��������ʹ�ܿ��� */
  u8 GPIO_BKIN_Filter;  /* GPIO�����˲�ʱ������1-256 */
  u8 CMP_BKIN_Filter;   /* �Ƚ���CMP�����˲�ʱ������1-256 */

  u8 TMR2_TimeBase_Sel; /* TMR2 �Ƚ����޼Ĵ��� ʱ��ѡ�� 0:ʱ��0 | 1:ʱ��1 */
  u8 TMR3_TimeBase_Sel; /* TMR3 �Ƚ����޼Ĵ��� ʱ��ѡ�� 1:ʱ��0 | 1:ʱ��1 */

  u8 TimeBase0_Trig_Enable; /* ʱ��0 �ⲿ����ʹ�� */
  u8 TimeBase1_Trig_Enable; /* ʱ��1 �ⲿ����ʹ��*/

  u16 TimeBase_TrigEvt0; /* ʱ��0 �ⲿ�����¼�ѡ�� */
  u16 TimeBase_TrigEvt1; /* ʱ��1 �ⲿ�����¼�ѡ�� */

  s16 TimeBase0Init_CNT; /* ʱ��0 ��������ʼֵ */
  s16 TimeBase1Init_CNT; /* ʱ��1 ��������ʼֵ */

  u16 MCPWM_WorkModeCH0; /* MCPWM CH0����ģʽ�����ض���/���Ķ��� */
  u16 MCPWM_WorkModeCH1; /* MCPWM CH0����ģʽ�����ض���/���Ķ��� */
  u16 MCPWM_WorkModeCH2; /* MCPWM CH0����ģʽ�����ض���/���Ķ��� */
  u16 MCPWM_WorkModeCH3; /* MCPWM CH0����ģʽ�����ض���/���Ķ��� */

  u16 TriggerPoint0; /* PWM����ADC�¼�0��ʱ������� */
  u16 TriggerPoint1; /* PWM����ADC�¼�1��ʱ������� */
  u16 TriggerPoint2; /* PWM����ADC�¼�2��ʱ������� */
  u16 TriggerPoint3; /* PWM����ADC�¼�3��ʱ������� */

  u16 DeadTimeCH0123N; /* CH0123N����ʱ�����á�*/
  u16 DeadTimeCH0123P; /* CH0123P����ʱ�����á�*/

  u8 CH0N_Polarity_INV; /* CH0N�������ȡ����0:���������1:ȡ����� */
  u8 CH0P_Polarity_INV; /* CH0P�������ȡ����0:���������1:ȡ����� */
  u8 CH1N_Polarity_INV; /* CH1N�������ȡ����0:���������1:ȡ����� */
  u8 CH1P_Polarity_INV; /* CH1P�������ȡ����0:���������1:ȡ����� */
  u8 CH2N_Polarity_INV; /* CH2N�������ȡ����0:���������1:ȡ����� */
  u8 CH2P_Polarity_INV; /* CH2P�������ȡ����0:���������1:ȡ����� */
  u8 CH3N_Polarity_INV; /* CH3N�������ȡ����0:���������1:ȡ����� */
  u8 CH3P_Polarity_INV; /* CH3P�������ȡ����0:���������1:ȡ����� */

  u8 Switch_CH0N_CH0P; /* ����CH0N, CH0P�ź����ʹ�ܿ��� */
  u8 Switch_CH1N_CH1P; /* ����CH1N, CH1P�ź����ʹ�ܿ��� */
  u8 Switch_CH2N_CH2P; /* ����CH2N, CH2P�ź����ʹ�ܿ��� */
  u8 Switch_CH3N_CH3P; /* ����CH3N, CH3P�ź����ʹ�ܿ��� */

  u8 MCPWM_UpdateT0Interval; /* MCPWM T0�¼����¼�� */
  u8 MCPWM_UpdateT1Interval; /* MCPWM T1�¼����¼�� */
  u8 MCPWM_Base0T0_UpdateEN; /* MCPWM ʱ��0 T0�¼�����ʹ�� */
  u8 MCPWM_Base0T1_UpdateEN; /* MCPWM ʱ��0 T1�¼�����ʹ�� */
  u8 MCPWM_Base1T0_UpdateEN; /* MCPWM ʱ��1 T0�¼�����ʹ�� */
  u8 MCPWM_Base1T1_UpdateEN; /* MCPWM ʱ��1 T1�¼�����ʹ�� */
  u8 MCPWM_Auto0_ERR_EN;     /* MCPWM ʱ��0�����¼��Ƿ��Զ���MOE, ʹ�ܿ��� */
  u8 MCPWM_Auto1_ERR_EN;     /* MCPWM ʱ��1�����¼��Ƿ��Զ���MOE, ʹ�ܿ��� */

  u8 FAIL0_INPUT_EN;    /* FAIL0 ���빦��ʹ�� */
  u8 FAIL1_INPUT_EN;    /* FAIL1 ���빦��ʹ�� */
  u8 FAIL0_Signal_Sel;  /* FAIL0 �ź�ѡ�񣬱Ƚ���0��GPIO */
  u8 FAIL1_Signal_Sel;  /* FAIL1 �ź�ѡ�񣬱Ƚ���0��GPIO */
  u8 FAIL0_Polarity;    /* FAIL0 �źż������ã�����Ч�����Ч */
  u8 FAIL1_Polarity;    /* FAIL1 �źż������ã�����Ч�����Ч */
  u8 DebugMode_PWM_out; /* Debugʱ��MCU����Halt, MCPWM�ź��Ƿ�������� */
  u8 FAIL2_INPUT_EN;    /* FAIL2 ���빦��ʹ�� */
  u8 FAIL3_INPUT_EN;    /* FAIL3 ���빦��ʹ�� */
  u8 FAIL2_Signal_Sel;  /* FAIL2 �ź�ѡ�񣬱Ƚ���0��GPIO */
  u8 FAIL3_Signal_Sel;  /* FAIL3 �ź�ѡ�񣬱Ƚ���0��GPIO */
  u8 FAIL2_Polarity;    /* FAIL2 �źż������ã�����Ч�����Ч */
  u8 FAIL3_Polarity;    /* FAIL3 �źż������ã�����Ч�����Ч */

  u8 CH0P_default_output; /* CH0P MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH0N_default_output; /* CH0N MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH1P_default_output; /* CH1P MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH1N_default_output; /* CH1N MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH2P_default_output; /* CH2P MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH2N_default_output; /* CH2N MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH3P_default_output; /* CH3P MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */
  u8 CH3N_default_output; /* CH3N MOEΪ0ʱ����FAIL�¼�ʱ��Ĭ�ϵ�ƽ��� */

  u8 CNT0_T0_Update_INT_EN;  /* ʱ��0 T0�����¼��Д�ʹ�� */
  u8 CNT0_T1_Update_INT_EN;  /* ʱ��0 T1�����¼��Д�ʹ�� */
	u8 CNT0_Update_TH00_EN;    /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH00�ж�Դʹ��*/
	u8 CNT0_Update_TH01_EN;    /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH01�ж�Դʹ��*/
	u8 CNT0_Update_TH10_EN;    /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH10�ж�Դʹ��*/
	u8 CNT0_Update_TH11_EN;    /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH11�ж�Դʹ��*/
	u8 CNT0_Update_TH20_EN;    /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH20�ж�Դʹ��*/
	u8 CNT0_Update_TH21_EN;    /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH21�ж�Դʹ��*/
	u8 CNT0_Update_TH30_EN;    /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH30�ж�Դʹ��*/
	u8 CNT0_Update_TH31_EN;    /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH31�ж�Դʹ��*/		
  u8 CNT0_TMR0_Match_INT_EN; /* ʱ��0 TMR0�����¼�ƥ���¼��ж�ʹ�� */
  u8 CNT0_TMR1_Match_INT_EN; /* ʱ��0 TMR1�����¼�ƥ���¼��ж�ʹ�� */
	u8 CNT0_TMR2_Match_INT_EN; /* ʱ��0 TMR2�����¼�ƥ���¼��ж�ʹ�� */
  u8 CNT0_TMR3_Match_INT_EN; /* ʱ��0 TMR3�����¼�ƥ���¼��ж�ʹ�� */
  u8 CNT0_Update_EN;         /* �Ĵ������µ� MCPWM ʵ������ϵͳ���ж�Դʹ�� */

  u8 CNT1_T0_Update_INT_EN;  /* ʱ��1 T0�����¼��Д�ʹ�� */
  u8 CNT1_T1_Update_INT_EN;  /* ʱ��1 T1�����¼��Д�ʹ�� */
	u8 CNT1_Update_TH30_EN;    /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH30�ж�Դʹ��*/
	u8 CNT1_Update_TH31_EN;    /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH31�ж�Դʹ��*/		
	u8 CNT1_TMR2_Match_INT_EN; /* ʱ��1 TMR2�����¼�ƥ���¼��ж�ʹ�� */
  u8 CNT1_TMR3_Match_INT_EN; /* ʱ��1 TMR3�����¼�ƥ���¼��ж�ʹ�� */
  u8 CNT1_Update_EN;         /* �Ĵ������µ� MCPWM ʵ������ϵͳ���ж�Դʹ�� */

  u8 TMR0_DMA_RE;   /* MCPWM����������TMR0��DMA����ʹ��*/
  u8 TMR1_DMA_RE;   /* MCPWM����������TMR1��DMA����ʹ��*/
  u8 TMR2_DMA_RE;   /* MCPWM����������TMR2��DMA����ʹ��*/
  u8 TMR3_DMA_RE;   /* MCPWM����������TMR3��DMA����ʹ��*/
  u8 TR0_T0_DMA_RE; /* ʱ��0 T0�¼�DMA����ʹ��*/
  u8 TR0_T1_DMA_RE; /* ʱ��0 T1�¼�DMA����ʹ��*/
  u8 TR1_T0_DMA_RE; /* ʱ��1 T0�¼�DMA����ʹ��*/
  u8 TR1_T1_DMA_RE; /* ʱ��1 T1�¼�DMA����ʹ��*/

  u8 FAIL0_INT_EN; /* FAIL0�¼��ж�ʹ�� (MCPWM_CH0-CH2��ͣ�¼�)*/
  u8 FAIL1_INT_EN; /* FAIL1�¼��ж�ʹ�� (MCPWM_CH0-CH2��ͣ�¼�)*/
  u8 FAIL2_INT_EN; /* FAIL2�¼��ж�ʹ�� (MCPWM_CH3��ͣ�¼�)*/
  u8 FAIL3_INT_EN; /* FAIL3�¼��ж�ʹ�� (MCPWM_CH3��ͣ�¼�)*/

  u16 AUEN;   /* �Զ�����ʹ�ܼĴ��� */
	
	u8  IO_PPE; /* ����ģʽʹ���ź� */

} MCPWM_InitTypeDef;

#define MCPWM_MOE_ENABLE_MASK ((u16)0x0040)   /* ��MOEλMASKλ */
#define MCPWM_MOE_DISABLE_MASK ((u16)~0x0040) /* ��MOEλMASKλ */


#define PWM_ENABLE_BK0IF  BIT4  /* FAIL0 �ж�Դ�¼�*/
#define PWM_ENABLE_BK1IF  BIT5  /* FAIL1 �ж�Դ�¼�*/
#define PWM_ENABLE_CMP0IF BIT6  /* FAIL2 �ж�Դ�¼�*/
#define PWM_ENABLE_CMP1IF BIT7  /* FAIL3 �ж�Դ�¼�*/

#define MCPWM_TMR0_IF BIT10 /* ����ֵ���� MCPWM_TMR0 �ж�Դ�¼� */

#define TH00_AUEN BIT0 /* MCPWM_TH00 �Զ�����ʹ�� */
#define TH01_AUEN BIT1 
#define TH10_AUEN BIT2
#define TH11_AUEN BIT3
#define TH20_AUEN BIT4
#define TH21_AUEN BIT5
#define TH30_AUEN BIT6
#define TH31_AUEN BIT7
#define TMR0_AUEN BIT8
#define TMR1_AUEN BIT9
#define TMR2_AUEN BIT10
#define TMR3_AUEN BIT11
#define TH0_AUEN BIT12  /* MCPWM_0TH �Զ�����ʹ�� */
#define TH1_AUEN BIT13  /* MCPWM_1TH �Զ�����ʹ�� */
#define CNT0_AUEN BIT14 /* MCPWM_0CNT �Զ�����ʹ�� */
#define CNT1_AUEN BIT15 /* MCPWM_1CNT �Զ�����ʹ�� */


#define CENTRAL_PWM_MODE 0 /* ���Ķ���PWMģʽ */
#define EDGE_PWM_MODE 1    /* ���ض���PWMģʽ */

#define HIGH_LEVEL 1 /* MCPWMͨ������״̬����ߵ�ƽ */
#define LOW_LEVEL 0  /* MCPWMͨ������״̬����͵�ƽ */

#define HIGH_LEVEL_VALID 0 /* FAIL����ѡ�� �ߵ�ƽ��Ч */
#define LOW_LEVEL_VALID 1  /* FAIL����ѡ�� �͵�ƽ��Ч */

#define FAIL_SEL_CMP 1 /* Fail�¼���Դ�Ƚ��� */
#define FAIL_SEL_IO 0  /* Fail�¼���ԴIO */

#define FAIL0_IF BIT4 /* FAIL0 �жϱ�־λ д1���� */
#define FAIL1_IF BIT5 /* FAIL0 �жϱ�־λ д1���� */
#define FAIL2_IF BIT6 /* FAIL0 �жϱ�־λ д1���� */
#define FAIL3_IF BIT7 /* FAIL0 �жϱ�־λ д1���� */

#define  CNT0_T0_Update_INT_IF  BIT0  /* ʱ��0 T0�����¼��Д��¼� */
#define  CNT0_T1_Update_INT_IF  BIT1  /* ʱ��0 T1�����¼��Д��¼� */
#define  CNT0_Update_TH00_IF    BIT2  /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH00�ж�Դ�¼�*/
#define  CNT0_Update_TH01_IF    BIT3  /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH01�ж�Դ�¼�*/
#define  CNT0_Update_TH10_IF    BIT4  /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH10�ж�Դ�¼�*/
#define  CNT0_Update_TH11_IF    BIT5  /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH11�ж�Դ�¼�*/
#define  CNT0_Update_TH20_IF    BIT6  /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH20�ж�Դ�¼�*/
#define  CNT0_Update_TH21_IF    BIT7  /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH21�ж�Դ�¼�*/
#define  CNT0_Update_TH30_IF    BIT8  /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH30�ж�Դ�¼�*/
#define  CNT0_Update_TH31_IF    BIT9  /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH31�ж�Դ�¼�*/		
#define  CNT0_TMR0_Match_INT_IF BIT10 /* ʱ��0 TMR0�����¼�ƥ���¼��ж��¼� */
#define  CNT0_TMR1_Match_INT_IF BIT11 /* ʱ��0 TMR1�����¼�ƥ���¼��ж��¼� */
#define  CNT0_TMR2_Match_INT_IF BIT12 /* ʱ��0 TMR2�����¼�ƥ���¼��ж��¼� */
#define  CNT0_TMR3_Match_INT_IF BIT13 /* ʱ��0 TMR3�����¼�ƥ���¼��ж��¼� */
#define  CNT0_Update_IF         BIT14 /* �Ĵ������µ� MCPWM ʵ������ϵͳ���ж�Դ�¼� */

#define  CNT1_T0_Update_INT_IF  BIT0  /* ʱ��1 T0�����¼��Д��¼� */
#define  CNT1_T1_Update_INT_IF  BIT1  /* ʱ��1 T1�����¼��Д��¼� */
#define  CNT1_Update_TH30_IF    BIT8  /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH30�ж�Դ�¼�*/
#define  CNT1_Update_TH31_IF    BIT9  /* MCPWM ʵ������ϵͳ�м������ļ���ֵ����MCPWM_TH31�ж�Դ�¼�*/		
#define  CNT1_TMR2_Match_INT_IF BIT12 /* ʱ��1 TMR2�����¼�ƥ���¼��ж��¼� */
#define  CNT1_TMR3_Match_INT_IF BIT13 /* ʱ��1 TMR3�����¼�ƥ���¼��ж��¼� */
#define  CNT1_Update_IF         BIT14 /* �Ĵ������µ� MCPWM ʵ������ϵͳ���ж�Դ�¼� */

#define  MCPWM_IO0_PPEN  BIT0         /* IO0 ����ģʽʹ���ź� */
#define  MCPWM_IO1_PPEN  BIT1         /* IO1 ����ģʽʹ���ź� */
#define  MCPWM_IO2_PPEN  BIT2         /* IO2 ����ģʽʹ���ź� */
#define  MCPWM_IO3_PPEN  BIT3         /* IO3 ����ģʽʹ���ź� */

#define PWM_Clk_Div1     0x00         /*MCPWM����Ƶ��48M*/
#define PWM_Clk_Div2     0x01         /*MCPWM����Ƶ��24M*/
#define PWM_Clk_Div4     0x02         /*MCPWM����Ƶ��12M*/
#define PWM_Clk_Div8     0x03         /*MCPWM����Ƶ��6M*/  


#define MCPWM_UPDATE_REG()  \
  {                         \
    MCPWM_PRT = 0x0000DEAD; \
    MCPWM_UPDATE = 0x00ff;  \
    MCPWM_PRT = 0x0000CAFE; \
  }
#define MCPWM1     ((MCPWM_REG_TypeDef *) MCPWM_BASE)

void PWMOutputs(MCPWM_REG_TypeDef *MCPWMx, FuncState t_state);
void PWMOutputs_CH3(MCPWM_REG_TypeDef *MCPWMx, FuncState t_state);
void MCPWM_Init(MCPWM_REG_TypeDef *MCPWMx, MCPWM_InitTypeDef *MCPWM_InitStruct);
void MCPWM_StructInit(MCPWM_InitTypeDef *MCPWM_InitStruct);
void PWM_CH3_Outputs(MCPWM_REG_TypeDef *MCPWMx, FuncState t_state);
void MCPWM_SwapFunction(void);
#endif /*__CHANHOM_PWM_H */

/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
