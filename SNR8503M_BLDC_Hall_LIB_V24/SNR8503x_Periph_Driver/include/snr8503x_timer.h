/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_timer.h
 * �ļ���ʶ��
 * ����ժҪ�� ͨ�ö�ʱ������ͷ�ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 2021��11��09��
 *
 *******************************************************************************/

#ifndef __snr8503x_TIM_H
#define __snr8503x_TIM_H

/* Includes ------------------------------------------------------------------*/

#include "basic.h"

typedef struct
{
    __IO uint32_t CFG;
    __IO uint32_t TH;
    __IO uint32_t CNT;
    __IO uint32_t CMPT0;
    __IO uint32_t CMPT1;
    __IO uint32_t EVT;
    __IO uint32_t FLT;
    __IO uint32_t IE;
    __IO uint32_t IF;
} TIM_TimerTypeDef;


#define TIMER_OPMode_CAP ((uint32_t)0x0000001)    /*����ģʽ*/
#define TIMER_OPMode_CMP ((uint32_t)0x0000000)    /*�Ƚ�ģʽ*/

// ��timerʱ��ΪMCLKʱ
#define TIM_Clk_Div1 0x00   // Timer����Ƶ��48Mhz
#define TIM_Clk_Div2 0x01   // Timer����Ƶ��24Mhz
#define TIM_Clk_Div4 0x02   // Timer����Ƶ��12Mhz
#define TIM_Clk_Div8 0x03   // Timer����Ƶ��6Mhz
#define TIM_Clk_Div16 0x04  // Timer����Ƶ��3Mhz
#define TIM_Clk_Div32 0x05  // Timer����Ƶ��1.5Mhz
#define TIM_Clk_Div64 0x06  // Timer����Ƶ��750Khz
#define TIM_Clk_Div128 0x07 // Timer����Ƶ��375Khz

#define TIM_Clk_SRC_MCLK 0x00    // Timerʹ��оƬ�ڲ�ʱ��
#define TIM_Clk_SRC_Timer00 0x01 // Timerʹ���ⲿTimer00�ź�
#define TIM_Clk_SRC_Timer01 0x02 // Timerʹ���ⲿTimer01�ź�
#define TIM_Clk_SRC_Timer10 0x03 // Timerʹ���ⲿTimer10�ź�
#define TIM_Clk_SRC_Timer11 0x04 // Timerʹ���ⲿTimer11�ź�

#define TIM_SRC1_0 0x00     // Timer���� ���ͨ��0
#define TIM_SRC1_1 0x01     // Timer���� ���ͨ��1
#define TIM_SRC1_CMP0 0x02  // Timer���� �Ƚ��� 0 �����
#define TIM_SRC1_CMP1 0x03  // Timer���� �Ƚ��� 1 �����
#define TIM_SRC1_0XOR1 0x04 // Timer���� ͨ��0��ͨ��1�����

#define TIM_SRC0_0 0x00     // Timer���� ���ͨ��0
#define TIM_SRC0_1 0x01     // Timer���� ���ͨ��1
#define TIM_SRC0_CMP0 0x02  // Timer���� �Ƚ��� 0 �����
#define TIM_SRC0_CMP1 0x03  // Timer���� �Ƚ��� 1 �����
#define TIM_SRC0_0XOR1 0x04 // Timer���� ͨ��0��ͨ��1�����

// Timer����ʹ���ź���Դ
#define TIM_EVT_SRC_Timer00 0x00 // Timer00�Ƚ��¼�
#define TIM_EVT_SRC_Timer01 0x01 // Timer01�Ƚ��¼�
#define TIM_EVT_SRC_Timer10 0x02 // Timer10�Ƚ��¼�
#define TIM_EVT_SRC_Timer11 0x03 // Timer11�Ƚ��¼�
#define TIM_EVT_SRC_MCPWM_0 0x0A // MCPWM TADC0�¼�
#define TIM_EVT_SRC_MCPWM_1 0x0B // MCPWM TADC1�¼�
#define TIM_EVT_SRC_MCPWM_2 0x0C // MCPWM TADC2�¼�
#define TIM_EVT_SRC_MCPWM_3 0x0D // MCPWM TADC3�¼�

// TIMER����DMA����
#define TIM_IRQ_RE_ZC (BIT10) // Timer��������0(����������)
#define TIM_IRQ_RE_CH1 (BIT9) // Timer1�Ƚ�OR�����¼�
#define TIM_IRQ_RE_CH0 (BIT8) // Timer0�Ƚ�OR�����¼�

// TIMER�ж�ʹ��
#define TIM_IRQ_IE_ZC  (BIT2) // Timer��������0(����������)
#define TIM_IRQ_IE_CH1 (BIT1) // Timer1�Ƚ�OR�����¼�
#define TIM_IRQ_IE_CH0 (BIT0) // Timer0�Ƚ�OR�����¼� \
                              // TIMER�ж�ʹ��
#define TIM_IRQ_IF_ZC  (BIT2) // Timer��������0(����������)
#define TIM_IRQ_IF_CH1 (BIT1) // Timer1�Ƚ�OR�����¼�
#define TIM_IRQ_IF_CH0 (BIT0) // Timer0�Ƚ�OR�����¼�

typedef struct
{
    uint32_t EN;          // Timer ģ��ʹ��
    uint32_t CAP1_CLR_EN; // ������ CAP1 �����¼�ʱ������ Timer ������������Ч
    uint32_t CAP0_CLR_EN; // ������ CAP0 �����¼�ʱ������ Timer ������������Ч
    uint32_t ETON;        // Timer ����������ʹ������ 0: �Զ����� 1: �ȴ��ⲿ�¼���������
    uint32_t CLK_DIV;     // Timer ��������Ƶ
    uint32_t CLK_SRC;     // Timer ʱ��Դ
    uint32_t TH;          // Timer �������������ޡ��������� 0 ������ TH ֵ���ٴλ� 0 ��ʼ����

    uint32_t SRC1;          // Timer ͨ�� 1 ����ģʽ�ź���Դ
    uint32_t CH1_POL;       // Timer ͨ�� 1 �ڱȽ�ģʽ�µ�������Կ��ƣ���������0������ֵ
    uint32_t CH1_MODE;      // Timer ͨ�� 1 ����ģʽѡ��0���Ƚ�ģʽ��1������ģʽ
    uint32_t CH1_FE_CAP_EN; // Timer ͨ�� 1 �½��ز����¼�ʹ�ܡ�1:ʹ�ܣ�0:�ر�
    uint32_t CH1_RE_CAP_EN; // Timer ͨ�� 1 �����ز����¼�ʹ�ܡ�1:ʹ�ܣ�0:�ر�
    uint32_t CMP1;          // Timer ͨ�� 1 �Ƚ�����

    uint32_t SRC0;          // Timer ͨ�� 0 ����ģʽ�ź���Դ
    uint32_t CH0_POL;       // Timer ͨ�� 0 �ڱȽ�ģʽ�µ�������Կ��ƣ���������0������ֵ
    uint32_t CH0_MODE;      // Timer ͨ�� 0 ����ģʽѡ��0���Ƚ�ģʽ��1������ģʽ
    uint32_t CH0_FE_CAP_EN; // Timer ͨ�� 0 �½��ز����¼�ʹ�ܡ�1:ʹ�ܣ�0:�ر�
    uint32_t CH0_RE_CAP_EN; // Timer ͨ�� 0 �����ز����¼�ʹ�ܡ�1:ʹ�ܣ�0:�ر�
    uint32_t CMP0;          // Timer ͨ�� 0 �Ƚ�����

    uint32_t CNT;     // Timer ��������ǰ����ֵ��д��������д���µļ���ֵ��
    uint32_t EVT_SRC; // Timer ����ʹ�ܿ�ʼ���ⲿ�¼�ѡ��
    uint32_t FLT;     // ͨ�� 0/1 �ź��˲����ѡ��0-255
    uint32_t IE;      // Timer �ж�ʹ��
} TIM_TimerInitTypeDef;

/*Timer��ʼ��*/
void TIM_TimerInit(TIM_TimerTypeDef *TIMERx, TIM_TimerInitTypeDef *TIM_TimerInitStruct);
void TIM_TimerStrutInit(TIM_TimerInitTypeDef *TIM_TimerInitStruct);
void TIM_TimerCmd(TIM_TimerTypeDef *TIMERx, FuncState state);
uint32_t TIM_GetIRQFlag(TIM_TimerTypeDef *TIMERx , u32 timer_if);
void TIM_ClearIRQFlag(TIM_TimerTypeDef *TIMERx , uint32_t tempFlag);
uint32_t TIM_Timer_GetCount(TIM_TimerTypeDef *TIMERx);
void TIM_Timer_ClearCnt(TIM_TimerTypeDef *TIMERx);
void TIM_Timer_Set_TH_Value(TIM_TimerTypeDef *TIMERx, uint32_t TH_Value);
uint32_t TIM_Timer_GetCMPT0(TIM_TimerTypeDef *TIM_TIMERx);
uint32_t TIM_Timer_GetCMPT1(TIM_TimerTypeDef *TIM_TIMERx);

#endif /*__snr8503x_TIM_H */
/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
