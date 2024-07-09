/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_dsp.h
 * �ļ���ʶ��
 * ����ժҪ�� DSP����ͷ�ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� 
 * ������ڣ� 
 *
 * �޸ļ�¼1��
 * �޸����ڣ�
 * �� �� �ţ�V 1.0
 * �� �� �ˣ�
 * �޸����ݣ�����
 *
 * �޸ļ�¼2��
 * �޸����ڣ�
 * �� �� �ţ�
 * �� �� �ˣ�
 * �޸����ݣ�
 *
 *******************************************************************************/
 
#ifndef __snr8503x_DSP_H
#define __snr8503x_DSP_H

/* Includes ------------------------------------------------------------------*/
#include "snr8503x.h"
#include "snr8503x_sys.h"
#include "basic.h"

typedef struct
{
	  s32 Dividend;     /* ������ */
	  s32 Divisor;      /* ����   */
    s32 Quotient;     /* ��     */
    s32 Remainder;    /* ����   */
} stru_DiviComponents;/* ��������ṹ�� */

void DSP_Cmd(FuncState state);                          		/* DSPʹ�ܺ͹ر� */
int32_t DSP_CalcDivision(stru_DiviComponents *stru_Divi);  	/* DSP�������� */
uint32_t DSP_GetSqrt(u32 Data); /*DSPȡ�ÿ����� sprt(Data)*/

#endif 

/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
