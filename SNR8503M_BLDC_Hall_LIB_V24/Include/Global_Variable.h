/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� Global_Variable.h
 * �ļ���ʶ��
 * ����ժҪ�� ȫ�ֱ��������ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 2020��8��5��
 *
 * �޸ļ�¼1��
 * �޸����ڣ�2020��8��5��
 * �� �� �ţ�V 1.0
 * �� �� �ˣ�Li
 * �޸����ݣ�����
 *
 *******************************************************************************/

#ifndef __GLOBAL_VARIABLE__
#define __GLOBAL_VARIABLE__

#include "mc_type.h"
#include "basic.h"


#define SHORT_ERROR          BIT0  /* ��·���� */
#define LOW_VOL_ERROR        BIT1  /* ��ѹ���� */
#define HIG_VOL_ERROR        BIT2  /* ��ѹ���� */
#define BLOCK_ERROR          BIT3  /* ��ת���� */
#define DC_OFFSET_ERROR      BIT4  /* ֱ��ƫ�ù��� */
#define MOS_OVER_ERROR       BIT5  /* MOS���¹��� */
#define MOS_LOW_ERROR        BIT6  /* MOS���¹��� */
#define BAT_OVER_ERROR       BIT7  /* ��ع��¹��� */
#define BAT_LOW_ERROR        BIT8  /* ��ص��¹��� */
#define OVER_LOAD_ERROR      BIT9  /* �������� */
#define PHASE_DROP_ERROR     BIT10 /* ȱ����� */
#define MOSFET_ERROR         BIT11 /* MOS�Լ���� */

extern unsigned char Read_hall_tab[6];

typedef struct
{
    volatile u16 nSys_TimerPWM;   /* PWM���ڼ���Cnt */ 
  
    s16 nSpeed_ADC;       					/* �ٶȿ���ADCֵ */
		s16 nBUS_Vol_ADC;      					/* ĸ�ߵ�ѹADCֵ */
		s16 nMOS_NTC_ADC;      					/* NTC�¶�ADCֵ */	
		s16 nBAT_NTC_ADC;      					/* ����¶Ȳ���ADC */
	
    u8 	communicate_Step;   				/* ��ǰ�����Ƕ�λ�� */
		u8 	Hallstate;   								/* ��ǰ�������״̬ */

    s16 PeakCurrOffset;   					/* ��ֵ����ƫ�� */
    s16 peakBusCurrent;   					/* ��ֵ���� */	
		u16 peakBusCurrentIn;						/* �޵�������ֵ */	
		u32 u32Ibus_sum;								/* �����ۼ� */
		u32 u32Ibus_Filt;								/* ƽ������ */
		u32 u32Ibus_Final;							/* ���յ��� */
		u8  bIbus_Limit_Cur_Flag;
		u16 u16CurLimt_PWMValue_Dec;
	
    s16 PhaseA_offset;    					/* A������ADC offsetֵ */
    s16 PhaseB_offset;    					/* B������ADC offsetֵ */
    s16 PhaseC_offset;    					/* C������ADC offsetֵ */
		u8 	get_offset_flg;							/* offset error */
		u16 sys_error_flg;							/* sysstem error */
	
		u16 MotorBlockCnt;							/* ��ת���� */
	
		u32 u32SW_LimitCurrent_Value;		/* �޵������� */
	
} stru_BLDC_sensorlessCtr;

extern const char sVersion[10];                      /* ����汾 */


typedef struct
{
	stru_TaskSchedulerDef 		struTaskScheduler;    	/* ������Ƚṹ�� */
	stru_BLDC_sensorlessCtr 	BLDC_SensorlessCtr; 		/* ������ƽṹ�� */
}LMotor_TypeDef;
extern LMotor_TypeDef User_sys;

extern void DebugPWM_OutputFunction(void);

#endif

/* ********************** (C) COPYRIGHT SNANER SEMICONDUCTOR ******************** */
/* ------------------------------END OF FILE------------------------------------ */
