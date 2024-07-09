/*******************************************************************************
 * �ļ����ƣ� Protect.c
 * �ļ���ʶ��
 * ����ժҪ�� ���򱣻�����
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� 
 * ������ڣ�
 *******************************************************************************/
#include "global_variable.h"
#include "MC_Parameter.h"
#include "motor_structure.h"
#include "M1_StateMachine.h"
#include "MC_Drive.h"
#include "SpeedRamp.h"
#include "PID.h"

u16 procHander(u16 hallbarADvalue);
void Vol_protect(void);
void Motor_Block_Protect(void);
void Current_Limit(void);
void OVER_current_protect(void);
void MOS_TEMP_protect(void);
void BAT_TEMP_protect(void);

/*******************************************************************************
 �������ƣ�    void MOS_TEMP_protect(void)
 ����������    MOS�¶ȱ�������
 *******************************************************************************/
volatile u16 Over_MOStemp_Cnt,RSM_Over_MOStemp_Cnt,Over_BATtemp_Cnt;
volatile u32 mos_tmp_test,mos_RSM_test;
void MOS_TEMP_protect(void)
{
    if(User_sys.BLDC_SensorlessCtr.nMOS_NTC_ADC < MOS_TEMP_OVER_THD)		/* MOS���� */
    {   
				RSM_Over_MOStemp_Cnt = 0;
        if(Over_MOStemp_Cnt < MOS_TEMP_OVER_TIME)
        {
            Over_MOStemp_Cnt++;
        }
        else
        {       
						Over_MOStemp_Cnt = 0;
					
						Motor.BLDC.u8FlagMotorIsRunning = 0;			// Motor stop
						e1M1_MainState = M1_MainState_Fault;						// MainState Fault
						e1M1_RunSubState = M1_RunState_Calib;						// RunState Calib
	
            User_sys.BLDC_SensorlessCtr.sys_error_flg |= MOS_OVER_ERROR;
					
						#if EN_BRAKE
								BLDC_Brake();
								
						#else
								BLDC_Stop();			
						#endif
        }
    }
		else
		{
			if (Over_MOStemp_Cnt != 0)
				Over_MOStemp_Cnt --;
		}

		if((User_sys.BLDC_SensorlessCtr.nMOS_NTC_ADC > RSM_MOS_TEMP_OVER_THD))
		{
				Over_MOStemp_Cnt = 0;
			  if(RSM_Over_MOStemp_Cnt < RSM_MOS_TEMP_OVER_TIME)
				{
						RSM_Over_MOStemp_Cnt++;
				}
				else
				{
					RSM_Over_MOStemp_Cnt = 0;
					User_sys.BLDC_SensorlessCtr.sys_error_flg &= ~MOS_OVER_ERROR;
				}					
		}	
		else
		{
			if (RSM_Over_MOStemp_Cnt != 0)
			RSM_Over_MOStemp_Cnt --;
		}
}

/*******************************************************************************
 �������ƣ�    u16 procHander(u16 hallbarADvalue)
 ����������    ��������˲�
 *******************************************************************************/
u16 procHander(u16 hallbarADvalue)
{   /* �����ְ��źŵ�ֵ*/
    static u16 adjFilter1;
    u16 tempChar;

    hallbarADvalue = hallbarADvalue & 0xfff;
    if(hallbarADvalue & 0x800)
    {
        hallbarADvalue = 0;
    }
    tempChar = (u16)(((hallbarADvalue + (u32) adjFilter1 * 7)) >> 3); /* �����˲� */
		adjFilter1 = tempChar;
    return (tempChar);
}

u16 nBUS_Vol_ADCIn;						/* �޵�ѹ����ֵ */	
u32 u32Vol_ADC_sum;						/* ��ѹ�ۼ� */
u32 u32Vol_ADC_Filt;					/* ƽ����ѹ */
u32 u32Vol_ADC_Final;					/* ���յ�ѹ */	
u32 u32Vol_V_Final;						/* ���յ�ѹV */	
u32 u32POW_W_Final;						/* ���չ��� */	
void Current_Limit(void)
{
	//�����˲�
	if(User_sys.BLDC_SensorlessCtr.peakBusCurrent < 0)
	{
		User_sys.BLDC_SensorlessCtr.peakBusCurrentIn = 0;
	}
	else
	{
		User_sys.BLDC_SensorlessCtr.peakBusCurrentIn = User_sys.BLDC_SensorlessCtr.peakBusCurrent & 0x7FFF;
	}
	
	User_sys.BLDC_SensorlessCtr.u32Ibus_sum += User_sys.BLDC_SensorlessCtr.peakBusCurrentIn;
	User_sys.BLDC_SensorlessCtr.u32Ibus_sum  = User_sys.BLDC_SensorlessCtr.u32Ibus_sum - User_sys.BLDC_SensorlessCtr.u32Ibus_Filt;
	User_sys.BLDC_SensorlessCtr.u32Ibus_Filt = User_sys.BLDC_SensorlessCtr.u32Ibus_sum  >> 2;
	
	User_sys.BLDC_SensorlessCtr.u32Ibus_Final = User_sys.BLDC_SensorlessCtr.u32Ibus_Filt;
	
	
	#if (CUR_POW_SEL == CURLIM_FUNCTION)
	User_sys.BLDC_SensorlessCtr.u32SW_LimitCurrent_Value = CURRENT_LIM_VALUE;		
	#else
	User_sys.BLDC_SensorlessCtr.u32SW_LimitCurrent_Value = POW_LIM_VALUE;
	
	//��ѹ�˲�
	if(User_sys.BLDC_SensorlessCtr.nBUS_Vol_ADC < 0)
	{
		nBUS_Vol_ADCIn = 0;
	}
	else
	{
		nBUS_Vol_ADCIn = User_sys.BLDC_SensorlessCtr.nBUS_Vol_ADC;
	}
	
	u32Vol_ADC_sum += nBUS_Vol_ADCIn;
	u32Vol_ADC_sum  = u32Vol_ADC_sum - u32Vol_ADC_Filt;
	u32Vol_ADC_Filt = u32Vol_ADC_sum  >> 2;
	
	u32Vol_ADC_Final = u32Vol_ADC_Filt;	
	u32Vol_V_Final = u32Vol_ADC_Final*3.6*VOLTAGE_SHUNT_RATIO/32752;		 													

	u32POW_W_Final = (User_sys.BLDC_SensorlessCtr.u32Ibus_Final*u32Vol_V_Final)>>7;		//����128�����ٵ�ѹ����Ӱ��	
	
	//����
	if(u32POW_W_Final < (User_sys.BLDC_SensorlessCtr.u32SW_LimitCurrent_Value - 5)) 
	{		
		User_sys.BLDC_SensorlessCtr.bIbus_Limit_Cur_Flag = 0;		/* �޵�����־λ */			
	}
	else if(u32POW_W_Final > (User_sys.BLDC_SensorlessCtr.u32SW_LimitCurrent_Value + 5)) 
	{
		User_sys.BLDC_SensorlessCtr.bIbus_Limit_Cur_Flag = 1;
	}
	#endif
}

/*******************************************************************************
 �������ƣ�    OVER_current_protect(void)
 ����������    �ּ�����
 *******************************************************************************/
volatile u16 over_current_time1,over_current_time2;
void OVER_current_protect(void)
{
   if(Motor.BLDC.u8FlagMotorIsRunning == 1)		/*���й���*/
	 {
	    if(User_sys.BLDC_SensorlessCtr.peakBusCurrent > OVER_CURRENT_FIRST_THD)
			{/*��һ������*/
			  if(over_current_time1 < TIME_LIMIT_FIRST)
				{
				  over_current_time1++;
				}
				else
				{
					Motor.BLDC.u8FlagMotorIsRunning = 0;			// Motor stop
					e1M1_MainState = M1_MainState_Fault;						// MainState Fault
					e1M1_RunSubState = M1_RunState_Calib;						// RunState Calib
					User_sys.BLDC_SensorlessCtr.sys_error_flg |= OVER_LOAD_ERROR;			
					#if EN_BRAKE
						BLDC_Brake();
					#else
						BLDC_Stop();			
					#endif
				}			
			}
			else
			{
			   if(over_current_time1)
				 {
				   over_current_time1--;
				 }
			}
	 
	    if(User_sys.BLDC_SensorlessCtr.peakBusCurrent > OVER_CURRENT_SECOND_THD)
			{/*�ڶ�������*/
			  if(over_current_time2 < TIME_LIMIT_SECOND)
				{
				  over_current_time2++;
				}
				else
				{
					Motor.BLDC.u8FlagMotorIsRunning = 0;			// Motor stop
					e1M1_MainState = M1_MainState_Fault;						// MainState Fault
					e1M1_RunSubState = M1_RunState_Calib;						// RunState Calib
					User_sys.BLDC_SensorlessCtr.sys_error_flg |= OVER_LOAD_ERROR;	
					#if EN_BRAKE
							BLDC_Brake();
					#else
							BLDC_Stop();			
					#endif					
				}			
			}
			else
			{
			   if(over_current_time2)
				 {
				   over_current_time2--;
				 }
			}			
					
	 }
	 else
	 {
		  over_current_time1 = 0;
	    over_current_time2 = 0;
	 }
}

/*******************************************************************************
 �������ƣ�    void Vol_protect(void)
 ����������    �����������
 *******************************************************************************/
void Vol_protect(void)
{
	static u16 LowVolatageCnt_fast;
	static u16 LowVolatageCnt_slow;
	static u16 Dis_UV_ProtectCnt;
	
	static u16 OvrVolatageCnt_fast;
	static u16 Dis_OV_ProtectCnt_slow;
	
	if(Motor.BLDC.u8FlagMotorIsRunning == 1)		/*���й�����Ƿѹ*/
	{
	  if(User_sys.BLDC_SensorlessCtr.nBUS_Vol_ADC < LOW_VOLATAGE_FIRST)
		{
				if(LowVolatageCnt_slow < LV_PROTECT_TIME_SLOW)		/* ��ѹ��ʱʱ����� */
				{
						LowVolatageCnt_slow++;
				}
				else
				{
						Motor.BLDC.u8FlagMotorIsRunning = 0;			// Motor stop
						e1M1_MainState = M1_MainState_Fault;						// MainState Fault
						e1M1_RunSubState = M1_RunState_Calib;						// RunState Calib
					
						LowVolatageCnt_slow = LV_PROTECT_TIME_SLOW;
						LowVolatageCnt_fast = LV_PROTECT_TIME_FAST;
						Dis_UV_ProtectCnt = DIS_UV_PROTECT_TIME;				// Dis_UV_Protect delay cnt
						User_sys.BLDC_SensorlessCtr.sys_error_flg |= LOW_VOL_ERROR;		// UV_Protect flag
					
						#if EN_BRAKE
								BLDC_Brake();
						#else
								BLDC_Stop();			
						#endif
				}	
		}
		else
		{
				if(LowVolatageCnt_slow)
				{
					 LowVolatageCnt_slow--;	
				}
		}
	}
	else		/*����֮ǰǷѹ*/
	{
		if(User_sys.BLDC_SensorlessCtr.nBUS_Vol_ADC < LOW_VOLATAGE_SECOND)
		{
				if(LowVolatageCnt_fast < LV_PROTECT_TIME_FAST)
				{
						LowVolatageCnt_fast++;
				}
				else
				{
						Motor.BLDC.u8FlagMotorIsRunning = 0;			// Motor stop
						e1M1_MainState = M1_MainState_Fault;						// MainState Fault
						e1M1_RunSubState = M1_RunState_Calib;						// RunState Calib
					
						LowVolatageCnt_slow = LV_PROTECT_TIME_SLOW;
						LowVolatageCnt_fast = LV_PROTECT_TIME_FAST;
						Dis_UV_ProtectCnt = DIS_UV_PROTECT_TIME;				// Dis_UV_Protect delay cnt
						User_sys.BLDC_SensorlessCtr.sys_error_flg |= LOW_VOL_ERROR;		// UV_Protect flag
					
						#if EN_BRAKE
								BLDC_Brake();
						#else
								BLDC_Stop();			
						#endif
				}
		}
		else if(User_sys.BLDC_SensorlessCtr.nBUS_Vol_ADC > RSM_LO_VOLATAGE_ADC)
		{  
			if(Motor.BLDC.u8FlagEnMotorRun == 1)			// Speed command enable motor startup
			{
					if(Dis_UV_ProtectCnt > 0)
					{
						Dis_UV_ProtectCnt--;
					}
					else
					{
						Dis_UV_ProtectCnt = 0;
						LowVolatageCnt_fast = 0;
						
//						if ((User_sys.BLDC_SensorlessCtr.sys_error_flg & LOW_VOL_ERROR) == LOW_VOL_ERROR )
//							Motor.BLDC.u8FlagEnMotorRun = 0;		// Motor stop	
						User_sys.BLDC_SensorlessCtr.sys_error_flg &= ~LOW_VOL_ERROR;
					}
			}
			else				// Speed command = 0 
			{
					if(LowVolatageCnt_fast > 0)		// �� Speed command = 0 ʱ, ���ٽ����ѹ����
					{
						LowVolatageCnt_fast--;
					}
					else
					{
						Dis_UV_ProtectCnt = 0;
						LowVolatageCnt_fast = 0;
						
//						if ((User_sys.BLDC_SensorlessCtr.sys_error_flg & LOW_VOL_ERROR) == LOW_VOL_ERROR )
//							Motor.BLDC.u8FlagEnMotorRun = 0;		// Motor stop	
						User_sys.BLDC_SensorlessCtr.sys_error_flg &= ~LOW_VOL_ERROR;
					}				
			}
		}
	}
			
	//* ��ѹ���� *//
	if (User_sys.BLDC_SensorlessCtr.nBUS_Vol_ADC > OV_VOLTAGE_ADC)
	{
		if(OvrVolatageCnt_fast < OV_PROTECT_TIME_FAST)		/*��ѹ��������*/
		{
			OvrVolatageCnt_fast++;			
		}
		else
		{	
			Motor.BLDC.u8FlagMotorIsRunning = 0;			// Motor stop
			e1M1_MainState = M1_MainState_Fault;						// MainState Fault
			e1M1_RunSubState = M1_RunState_Calib;						// RunState Calib
			
			OvrVolatageCnt_fast = OV_PROTECT_TIME_FAST;
			Dis_OV_ProtectCnt_slow = DIS_OV_PROTECT_TIME_SLOW;
			User_sys.BLDC_SensorlessCtr.sys_error_flg |= HIG_VOL_ERROR;

			#if EN_BRAKE
					BLDC_Brake();
			#else
					BLDC_Stop();			
			#endif
		}
	}
	else 	//* �����ѹ���� *//
	{
			if((User_sys.BLDC_SensorlessCtr.nBUS_Vol_ADC < RSM_OV_VOLTAGE_ADC))
			{
				if(Motor.BLDC.u8FlagEnMotorRun == 1)
				{
					if(Dis_OV_ProtectCnt_slow > 0)	
					{
						Dis_OV_ProtectCnt_slow--;
					}
					else
					{
						Dis_OV_ProtectCnt_slow = 0;
						OvrVolatageCnt_fast = 0;
					
//						if ((User_sys.BLDC_SensorlessCtr.sys_error_flg & HIG_VOL_ERROR) == HIG_VOL_ERROR )
//							Motor.BLDC.u8FlagEnMotorRun = 0;		// Motor stop							
						User_sys.BLDC_SensorlessCtr.sys_error_flg &= ~HIG_VOL_ERROR;
					}									
				}
				else				// Speed command = 0 
				{
					if(OvrVolatageCnt_fast > 0)			// �� Speed command = 0 ʱ, ���ٽ����ѹ����
					{
						OvrVolatageCnt_fast--;
					}
					else
					{
						Dis_OV_ProtectCnt_slow = 0;
						OvrVolatageCnt_fast = 0;
						
//						if ((User_sys.BLDC_SensorlessCtr.sys_error_flg & HIG_VOL_ERROR) == HIG_VOL_ERROR )
//							Motor.BLDC.u8FlagEnMotorRun = 0;		// Motor stop								
						User_sys.BLDC_SensorlessCtr.sys_error_flg &= ~HIG_VOL_ERROR;
					}	
				}
			}
	}
}


///*******************************************************************************
// �������ƣ�    void Motor_Block_Protect(void)
// ����������    �����ת��������
// *******************************************************************************/
void Motor_Block_Protect(void)
{
		#if EN_MOTOR_BLOCK_DETECT
			if(Motor.Control.u16MotorShakeDelayProtectCnt > MOTOR_BLOCK_DETECT_CNT)
			{
				User_sys.BLDC_SensorlessCtr.sys_error_flg |= BLOCK_ERROR;
				
				User_sys.BLDC_SensorlessCtr.MotorBlockCnt = 0;	/* Motor rotor block cnt */
				
				Motor.BLDC.u8FlagMotorIsRunning = 0;			// Motor stop
				e1M1_MainState = M1_MainState_Fault;						// MainState Fault
				e1M1_RunSubState = M1_RunState_Calib;						// RunState Calib
				
				#if EN_BRAKE
					BLDC_Brake();
				#else
					BLDC_Stop();			
				#endif			
				
				Motor.Control.u16MotorShakeDelayProtectCnt = 0;
			}
		#endif		
}


/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
