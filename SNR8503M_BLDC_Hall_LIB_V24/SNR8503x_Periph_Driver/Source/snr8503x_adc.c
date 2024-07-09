/*******************************************************************************
 * ��Ȩ���� (C)2021, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_adc.c
 * �ļ���ʶ��
 * ����ժҪ�� ADC������������
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ�   Li
 * ������ڣ� 2021��10��14��
 *
 *******************************************************************************/
#include "snr8503x_adc.h"
#include "snr8503x.h"
#include "snr8503x_sys.h"

/*******************************************************************************
 �������ƣ�    void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
 ����������    ADC��ʼ��
 �����ı�    ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
2021/10/14    V1.0             Li               ����
 *******************************************************************************/
void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct)
{

    uint16_t t_reg;

	 
	
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_ADC, ENABLE); // ADCģ��ʹ��

	  if(ADC_InitStruct->ADC_SAMP_CLK > 4)
    {      
       t_reg = ADC_InitStruct->ADC_SAMP_CLK - 4;
    }
    else
    {
       t_reg = 0;
    }
		SYS_PROTECT = 0x7A83;    //���ϵͳ�Ĵ���д����
    SYS_AFE_REG2 = (t_reg << 8); //����ADC����ʱ��
	
		SYS_WR_PROTECT = 0;    //ʹ��ϵͳ�Ĵ���д����
		
    ADCx->IE = ADC_InitStruct->IE;

    t_reg = (ADC_InitStruct->Align << 10) | (ADC_InitStruct->Trigger_En) | (ADC_InitStruct->SEL_En << 12) |
            (ADC_InitStruct->Trigger_Cnt << 4) | (ADC_InitStruct->Trigger_Mode << 8);
    ADCx->CFG = t_reg;

    ADCx->CHNT0 = ADC_InitStruct->FirSeg_Ch | (ADC_InitStruct->SecSeg_Ch << 4) |
                  (ADC_InitStruct->ThrSeg_Ch << 8) | (ADC_InitStruct->FouSeg_Ch << 12);
		
		ADC_LTH = ADC_InitStruct->ADC_GEN_LTH;
		
		ADC_HTH = ADC_InitStruct->ADC_GEN_HTH;
		
		ADC_GEN = ADC_InitStruct->ADC_GEN_En;
		
		SYS_WR_PROTECT = 0x7a83;   /* ���ϵͳ�Ĵ���д���� */
		SYS_AFE_REG1 |= ADC_InitStruct->REFOUT_EN << 6;
		SYS_WR_PROTECT = 0;        /* ����ϵͳ�Ĵ���д���� */
}

/*******************************************************************************
 �������ƣ�    void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
 ����������    ADC�ṹ���ʼ��
 �����ı�    ��
 ���������    ��
 ���������    ��
 �� �� ֵ��     ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
2021/10/14    V1.0             Li               ����
 *******************************************************************************/
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct)
{
    ADC_InitStruct->IE = 0;
    ADC_InitStruct->Align = 0;
    ADC_InitStruct->Con_Sample = 0;
    ADC_InitStruct->Trigger_Cnt = 0;
    ADC_InitStruct->FirSeg_Ch = 0;
    ADC_InitStruct->SecSeg_Ch = 0;
    ADC_InitStruct->ThrSeg_Ch = 0;
    ADC_InitStruct->FouSeg_Ch = 0;
    ADC_InitStruct->Trigger_Mode = 0;
    ADC_InitStruct->Trigger_En = 0;
    ADC_InitStruct->SEL_En = 0;
    ADC_InitStruct->ADC_GEN_En = 0;
    ADC_InitStruct->ADC_GEN_HTH = 0;
    ADC_InitStruct->ADC_GEN_LTH = 0;
	  ADC_InitStruct->REFOUT_EN = DISABLE;
}

/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
