
#ifndef __MAIN_H_
#define __MAIN_H_

#include "hardware_config.h"

void Hardware_init(void);
void sys_init(void);
void Task_Scheduler(void);

void Flash_write(void);
//void Clear_error(void);

extern void MosTest(void);
extern void Init_Parameter(void);
extern void variable_reset(void);
extern u16 procHander(u16 hallbarADvalue);
extern void Phase_COMPENSATION_Cal(void);
extern void VSP_Control_Motor(void);
extern void Vol_protect(void);
extern void Motor_Block_Protect(void);
extern void Current_Limit(void);
extern void OVER_current_protect(void);
extern void MOS_TEMP_protect(void);
extern void BAT_TEMP_protect(void);

#define TASK_SCHEDU_1MS                   (2)                                      /* �������1ms����ʱ�� */
#define TASK_SCHEDU_10MS                  (20)                                     /* �������10ms����ʱ�� */
#define TASK_SCHEDU_100MS                 (200)                                    /* �������100ms����ʱ�� */
#define TASK_SCHEDU_500MS                 (1000)                                   /* �������500ms����ʱ�� */

/*******************************************************************************
 �������ƣ�    void SetTimeOut_Counter(u16 hTimeout)
 ����������    ���õȴ������ȴ�ʱ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Li Li          ����
 *******************************************************************************/
#define SetTimeOut_Counter(SetTimeLeftCnt, hTimeout)  {SetTimeLeftCnt = hTimeout;}


#endif  /* __MAIN_H_ */


