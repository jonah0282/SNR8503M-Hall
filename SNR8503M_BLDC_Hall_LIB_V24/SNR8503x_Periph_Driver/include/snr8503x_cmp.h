/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_cmp.h
 * �ļ���ʶ��
 * ����ժҪ�� �Ƚ�������ͷ�ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 2021��11��09��
 *
 *******************************************************************************/
#ifndef __snr8503x_cmp_H
#define __snr8503x_cmp_H
/* Includes ------------------------------------------------------------------*/
#include "snr8503x.h"
#include "basic.h"
// �Ƚ����ز�ѡ��
#define CMP_HYS_20mV         0
#define CMP_HYS_0mV          1

// �Ƚ��� 1 �ź�����ѡ��
#define CMP1_SELP_CMP1_IP0   0
#define CMP1_SELP_OPA0_IP    1
#define CMP1_SELP_OPA0_OUT   2
#define CMP1_SELP_CMP1_IP1   3
#define CMP1_SELP_CMP1_IP2   4
#define CMP1_SELP_CMP1_IP3   5

// �Ƚ��� 1 �źŸ���ѡ��
#define CMP1_SELN_CMP1_IN    0
#define CMP1_SELN_REF        1
#define CMP1_SELN_DAC        2
#define CMP1_SELN_HALL_MID   3

// �Ƚ��� 0 �ź�����ѡ��
#define CMP0_SELP_CMP0_IP0   0
#define CMP0_SELP_OPA0_IP    1
#define CMP0_SELP_OPA0_OUT   2
#define CMP0_SELP_CMP0_IP1   3
#define CMP0_SELP_CMP0_IP2   4
#define CMP0_SELP_CMP0_IP3   5

// �Ƚ��� 0 �źŸ���ѡ��
#define CMP0_SELN_CMP0_IN    0
#define CMP0_SELN_REF        1
#define CMP0_SELN_DAC        2
#define CMP0_SELN_HALL_MID   3

typedef struct
{
    __IO uint32_t IE;       // �Ƚ����ж�ʹ�ܼĴ���
    __IO uint32_t IF;       // �Ƚ����жϱ�־�Ĵ���
    __IO uint32_t TCLK;     // �Ƚ�����Ƶʱ�ӿ��ƼĴ���
    __IO uint32_t CFG;      // �Ƚ������ƼĴ���
    __IO uint32_t BLCWIN;   // �Ƚ����������ƼĴ���
    __IO uint32_t DATA;     // �Ƚ��������ֵ�Ĵ���
} CMP_TypeDef;

typedef struct
{
    // �Ƚ���IO����
    u32 FIL_CLK10_DIV16;    // �Ƚ��� 1/0 �˲�
    u32 CLK10_EN;           // �Ƚ��� 1/0 �˲�ʱ��ʹ��
    u32 FIL_CLK10_DIV2;     // �Ƚ��� 1/0 �˲�ʱ�ӷ�Ƶ
    u32 CMP_FT;             // �Ƚ������ٱȽ�ʹ��
    u32 CMP_HYS;            // �Ƚ����ز�ѡ��
    
    // �Ƚ���1
    u32 CMP1_RE;            // �Ƚ��� 1 DMA ����ʹ��
    u32 CMP1_IE;            // �Ƚ��� 1 �ж�ʹ��
    u32 CMP1_W_PWM_POL;     // �Ƚ��� 1 ���� PWM �źż���ѡ��
    u32 CMP1_IRQ_TRIG;      // �Ƚ��� 1 ���ش���ʹ��
    u32 CMP1_IN_EN;         // �Ƚ��� 1 �ź�����ʹ��
    u32 CMP1_POL;           // �Ƚ��� 1 ����ѡ��
    u32 CMP1_SELP;          // �Ƚ��� 1 �ź�����ѡ��
    u32 CMP1_SELN;          // �Ƚ��� 1 �źŸ���ѡ��
    u32 CMP1_CHN3P_WIN_EN;  // MCPWM ģ�� CHN3_P ͨ��ʹ�ܱȽ��� 1 ����
    u32 CMP1_CHN2P_WIN_EN;  // MCPWM ģ�� CHN2_P ͨ��ʹ�ܱȽ��� 1 ����
    u32 CMP1_CHN1P_WIN_EN;  // MCPWM ģ�� CHN1_P ͨ��ʹ�ܱȽ��� 1 ����
    u32 CMP1_CHN0P_WIN_EN;  // MCPWM ģ�� CHN0_P ͨ��ʹ�ܱȽ��� 1 ����
    
    // �Ƚ���0
    u32 CMP0_IE;            // �Ƚ��� 0 �ж�ʹ��
    u32 CMP0_RE;            // �Ƚ��� 0 DMA ����ʹ��
    u32 CMP0_W_PWM_POL;     // �Ƚ��� 0 ���� PWM �źż���ѡ��
    u32 CMP0_IRQ_TRIG;      // �Ƚ��� 0 ���ش���ʹ��
    u32 CMP0_IN_EN;         // �Ƚ��� 0 �ź�����ʹ��
    u32 CMP0_POL;           // �Ƚ��� 0 ����ѡ��
    u32 CMP0_SELP;          // �Ƚ��� 0 �ź�����ѡ��
    u32 CMP0_SELN;          // �Ƚ��� 0 �źŸ���ѡ��
    u32 CMP0_CHN3P_WIN_EN;  // MCPWM ģ�� CHN3_P ͨ��ʹ�ܱȽ��� 0 ����
    u32 CMP0_CHN2P_WIN_EN;  // MCPWM ģ�� CHN2_P ͨ��ʹ�ܱȽ��� 0 ����
    u32 CMP0_CHN1P_WIN_EN;  // MCPWM ģ�� CHN1_P ͨ��ʹ�ܱȽ��� 0 ����
    u32 CMP0_CHN0P_WIN_EN;  // MCPWM ģ�� CHN0_P ͨ��ʹ�ܱȽ��� 0 ����
}CMP_InitTypeDef;

void CMP_Init(CMP_InitTypeDef *);        // CMP��ʼ��
void CMP_StructInit(CMP_InitTypeDef *);   // CMP���ýṹ���ʼ��

#endif /*__snr8503x_cmp_H */
/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
