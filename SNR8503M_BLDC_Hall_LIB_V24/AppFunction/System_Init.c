/*******************************************************************************
 * �ļ����ƣ� System_init.c
 * �ļ���ʶ��
 * ����ժҪ�� ��ʱ��غ���
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� 
 * ������ڣ� 
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "hardware_config.h"
#include "MC_parameter.h"
#include "M1_StateMachine.h"
#include "motor_structure.h"

void Multiplex_SWD(void);

void CurrentOffsetCalibration(void);
void DC_offset_protect(void);

volatile u16 ADC_VOL_test;
volatile u16 OPA_OFFSET_VOL_test;
volatile u16 test_OPA_DAC;
volatile u16 test_short_DAC,test_sys_afe_dac;

/*******************************************************************************
 �������ƣ�    sys_init(void)
 ����������    ϵͳ������ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Li Li          ����
 *******************************************************************************/
void sys_init(void)
{	
//	  u8 i;
    while(User_sys.BLDC_SensorlessCtr.nSys_TimerPWM < 200){;} /* ��ʱ150ms */

    User_sys.struTaskScheduler.sVersion = &sVersion[0];/* ��ʼ���汾�� */
  
		CurrentOffsetCalibration();			// Get Current Offset value, BEMF_A��B��C Offset value
		DC_offset_protect();						// Judge DC offset state
			
#if DEBUG_PWM_OUTPUT 
    DebugPWM_OutputFunction(); /* ���Ե�ʱ�����25%��PWM���� */
#endif
}

/*******************************************************************************
 �������ƣ�    void Multiplex_SWD(void)
 ����������    SWD����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Li Li          ����
 *******************************************************************************/
void Multiplex_SWD(void)
{		
		SYS_PROTECT = 0x7a83;
		SYS_IO_CFG &= ~BIT6;         /* SWD����������GPIO�� */			
		SYS_PROTECT = 0;
}

/*******************************************************************************
 �������ƣ�    void Multiplex_nRST(void)
 ����������    nRST����IO
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Li Li          ����
 *******************************************************************************/
void Multiplex_nRST(void)
{
		/*P0.0 NRST*/
		SYS_PROTECT = 0x7a83;
		SYS_IO_CFG |= BIT5;										 		 /*NRST����ΪP0.0*/
		SYS_PROTECT = 0;
}

/*******************************************************************************
 �������ƣ�    void Multiplex_nRST(void)
 ����������    nRST�ָ�
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Li Li          ����
 *******************************************************************************/
void SET_nRST(void)
{
		/*P0.0 NRST*/
		SYS_PROTECT = 0x7a83;
		SYS_IO_CFG &= ~BIT5;										 		 /*P0.0�ָ�ΪNRST*/
		SYS_PROTECT = 0;
}

/*******************************************************************************
 �������ƣ�    void DebugPWM_OutputFunction(void)
 ����������    PWM������ܵ���   ���25%ռ�ձ�
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2017/11/5      V1.0           Li Li          ����
 *******************************************************************************/
void DebugPWM_OutputFunction(void)
{
    MCPWM_TH00 = -(PWM_PERIOD >> 2);
    MCPWM_TH01 = (PWM_PERIOD >> 2);
    MCPWM_TH10 = -(PWM_PERIOD >> 2);
    MCPWM_TH11 = (PWM_PERIOD >> 2);
    MCPWM_TH20 = -(PWM_PERIOD >> 2);
    MCPWM_TH21 = (PWM_PERIOD >> 2);

    PWMOutputs(MCPWM0,ENABLE);
	
		Motor.Control.u32MCPWM_TH_temp = (PWM_PERIOD >> 2);
	
    while(1)
    {
    }
}

void CurrentOffsetCalibration(void)
{
    volatile u32 t_dlay;
    volatile u16 t_cnt;
    volatile s32 t_offset1, t_offset2, t_offset3, t_offset4;

    __disable_irq();

    ADC_SOFTWARE_TRIG_ONLY();			// ADC ʹ���������
    ADC_STATE_RESET();

//    MCPWM_TH00 = 0;
//    MCPWM_TH01 = 0;

//    MCPWM_TH10 = 0;
//    MCPWM_TH11 = 0;

//    MCPWM_TH20 = 0;
//    MCPWM_TH21 = 0;
	
//  	Motor.Control.u32MCPWM_TH_temp = 0;
//     for (t_dlay = 0; t_dlay < 0xffff; t_dlay++)
//        ;
//    PWMOutputs(MCPWM0,ENABLE);
//    for (t_dlay = 0; t_dlay < 0x2ffff; t_dlay++)
//        ;

    t_offset1 = 0;
    t_offset2 = 0;
    t_offset3 = 0;
    t_offset4 = 0;

    ADC_CHN0 = ADC_PEAK_CUR_CHANNEL | (ADC_PEAK_CUR_CHANNEL << 4) | ( ADC_PEAK_CUR_CHANNEL << 8) | (ADC_PEAK_CUR_CHANNEL << 12);

    ADC_IF = 0x1f;

    ADC_SWT = 0x00005AA5;

    for (t_cnt = 0; t_cnt < CALIB_SAMPLES; t_cnt++)		// �ɶ������У׼
    {
        for (t_dlay = 0; t_dlay < 0x1ff; t_dlay++);
        ADC_IF |= BIT1 | BIT0;
        t_offset1 += (s16)((ADC_DAT0));
        t_offset2 += (s16)((ADC_DAT1));
        t_offset3 += (s16)((ADC_DAT2));
        t_offset4 += (s16)((ADC_DAT3));

        /* Clear the ADC0 JEOC pending flag */
        ADC_SWT = 0x00005AA5;
    }
 
    PWMOutputs(MCPWM0,DISABLE);
		
    User_sys.BLDC_SensorlessCtr.PeakCurrOffset = (s16)(t_offset1 >> 9);		// ��ƽ��
                          
    ADC_init();
    MCPWM_init();
    __enable_irq();
}





/*******************************************************************************
 �������ƣ�    void DC_offset_protect(void)
 ����������    ֱ��ƫ�ñ���
 *******************************************************************************/
void DC_offset_protect(void)
{
	// Current offset error
	if ((User_sys.BLDC_SensorlessCtr.PeakCurrOffset  > OFFSET_THD) || (User_sys.BLDC_SensorlessCtr.PeakCurrOffset  < -OFFSET_THD))
	{
			User_sys.BLDC_SensorlessCtr.get_offset_flg = 1;
	}
	
	// system offset error
	if(User_sys.BLDC_SensorlessCtr.get_offset_flg)
	{
		e1M1_MainState = M1_MainState_Fault;						// MainState Fault
		e1M1_RunSubState = M1_RunState_Calib;						// RunState Calib					
		User_sys.BLDC_SensorlessCtr.sys_error_flg |= DC_OFFSET_ERROR;
	}
}

/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
