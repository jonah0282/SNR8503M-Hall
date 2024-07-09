/*******************************************************************************
 * all rights reserved (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * file name： Main.c
 * File ID：
 * abstract： Project main code
 * other instructions： none
 * current version： V 1.0
 * author： Li
 * Completion Date： 2020/8/5
 *
 * Modify record 1：
 * Modification date： 2020/8/16
 * version number： V 1.0
 * Modifier： Li
 * Modify content： create
 *
 *******************************************************************************/
#include "main.h"
#include "PID.h"
#include "MC_Drive.h"
#include "SpeedRamp.h"
#include "motor_structure.h"
#include "M1_StateMachine.h"
#include "UR_Ctrl.h"


/*******************************************************************************
 function name：    int main(void)
 Function description：    Main program entry
 Input parameters：    none
 Output parameters：    none
 return value：    none
 other instructions：
 Modification date      version number          Modifier            Modify content
 -----------------------------------------------------------------------------
 2020/8/5      V1.0             Li          create
 *******************************************************************************/

int main(void)
{
  SoftDelay(20000);      /* Delay waiting for hardware initialization to stabilize 20000--2.68ms */  //  
  SoftDelay(20000);      /* Delay waiting for hardware initialization to stabilize 20000--2.68ms */  //  	
	
	Hardware_init();			 /* Hardware initialization */
	
	Init_Parameter();
	
	InitPI();
	sys_init();            /* system initialization */

	MosTest();
	LED_ON
	FG_ON
	
	////Potentiometer threshold low value, threshold high value, output maximum value, input maximum value
	InitNormalization(VSP_START_VALUE,VSP_MAX_VALUE,MIN_PWM_DUTY,MAX_PWM_DUTY,&RP);		// speed open loop
	InitNormalization(VSP_START_VALUE,VSP_MAX_VALUE,MOTOR_SPEED_MIN_RPM,MOTOR_SPEED_MAX_RPM,&SPEED_Cmd);		// Speed ??closed loop

	#if EN_HALL_PHASE_COMPENSATION		
		InitNormalization(START_SPEED_COMPENSATION,MAX_SPEED_COMPENSATION,MIN_ADVANCE_ANGLE,MAX_ADVANCE_ANGLE,&Speed_PHASE_COMPENSATION_Cmd);		// Phase compensation
	#endif
	
	// read CWCCW
	CWCCW_PowerOn();	
	
	// Get the Hall signal before starting
	hall_info = HALL_GetFilterValue();    	/* Get HALL value and filter result*/
	Motor.BLDC.u8HallValueRenew = hall_info;
	// According to forward and reverse, get the next hall signal
	if(Motor.BLDC.u8Direction == CCW)
	{
		Motor.BLDC.u8HallValueRenew = (0x07) & (~Motor.BLDC.u8HallValueRenew);
	}
	Motor.BLDC.u8HallValueOld = Motor.BLDC.u8HallValueRenew;
	
	for (;;)
	{
			Task_Scheduler();
	}
}


/*******************************************************************************
 function name：    void Task_Scheduler(void)
 Function description：    Task scheduling function by time slice
 Modification date      version number          Modifier            Modify content
 -----------------------------------------------------------------------------
 2022/5/30      V1.0                     create
 *******************************************************************************/
void Task_Scheduler(void)
{
    if(User_sys.struTaskScheduler.bTimeCnt1ms >= TASK_SCHEDU_1MS)
    {   
			/* 1Millisecond events, task scheduling */
			User_sys.struTaskScheduler.bTimeCnt1ms = 0;
			
			// Speed command Input
			Motor.USER.u16VSP_filt_value = procHander((u16) User_sys.BLDC_SensorlessCtr.nSpeed_ADC);		/* Speed command */
			VSP_Control_Motor();		/* Speed command to RPM */ 		
			
			// Hall phase compensation
			Phase_COMPENSATION_Cal();
			
			// Voltage protection detection
			Vol_protect();											
			
			// Stall detection
			Motor_Block_Protect();
			
			// Limit maximum current
			Current_Limit();
							
			/* Graded current limiting protection */
			OVER_current_protect(); 
			
			// MOS temperature protection		
			MOS_TEMP_protect();

			/*  Statemachine */
			sM1_STATE[e1M1_MainState]();
    }  

    if( User_sys.struTaskScheduler.nTimeCnt10ms >= TASK_SCHEDU_10MS )
    {   /* 10Millisecond events, task scheduling */
        User_sys.struTaskScheduler.nTimeCnt10ms = 0;
			
				/* Motor LED indication */
				Motor_LED_DISP();
			
				/* Motor steering setting */
				CWCCW_ReadIO();			
		}
		
    if( User_sys.struTaskScheduler.nTimeCnt100ms >= TASK_SCHEDU_100MS )
		{
			User_sys.struTaskScheduler.nTimeCnt100ms = 0;
			//UART_SendHalfWord(User_sys.BLDC_SensorlessCtr.nMOS_NTC_ADC);
			//UART0_SendByte(User_sys.BLDC_SensorlessCtr.nMOS_NTC_ADC);
		}			
		#if (UART0_FUNCTION == ENABLE_FUNCTION)
		UartDealRX();
		UartDealTX();
		#endif
}

/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */



