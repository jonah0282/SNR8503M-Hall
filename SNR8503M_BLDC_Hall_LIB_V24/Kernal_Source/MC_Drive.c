/*-------------------- Includes -----------------------*/
#include "MC_Drive.h"
#include "Global_Variable.h"
#include "motor_structure.h"
#include "M1_StateMachine.h"
#include "SpeedRamp.h"
#include "MC_Parameter.h"
#include "PID.h"
#include "commonfunc.h"

u8 CWCCW_bIOInput = 0;	

u32 hall_cnt = 0;
u8  hall_info = 0;

/*------------------- Private variables ---------------*/
void Phase_COMPENSATION_Cal(void);
void VSP_Control_Motor(void);

void BLDC_Stop(void);
void BLDC_Brake(void);

/*------------------ Private functions ----------------*/
void Phase_COMPENSATION_Cal(void)
{
//	// ���õ����ڼ����ת��, ʹ��Ӳ������������
//	Ele_Speed_Division.Dividend = MOTOR_e_K;																	// ������, �� MOTOR_e_K �����������ͷ�Χ, �������ǰ����������λ
//	Ele_Speed_Division.Divisor 	= Motor.Control.u32MotorElePeriodValueTemp;		// ����, һ����������360��, ����60��
//	Motor.Control.u32MotorEleRPM = DSP_CalcDivision(&Ele_Speed_Division);			// Ӳ����������
		Motor.Control.u32MotorEleRPM = MOTOR_e_K / Motor.Control.u32MotorElePeriodValueTemp;
		Motor.Control.u32MotorEleRPM <<= 2;																				// ������λ, �ó���ʵ��ת��

	
	// ת���˲�
	Motor.Control.u32MotorEleRPM_sum 	+= 	Motor.Control.u32MotorEleRPM;						
	Motor.Control.u32MotorEleRPM_sum 	-=	Motor.Control.u32MotorEleRPM_Filt;			
	Motor.Control.u32MotorEleRPM_Filt  = 	Motor.Control.u32MotorEleRPM_sum >> 2;	
	Motor.Control.u32MotorEleRPM_Final = 	Motor.Control.u32MotorEleRPM_Filt;			// �˲���ĵ�ת��

	#if EN_HALL_PHASE_COMPENSATION
		// ���ݵ����ת��, ����������λ�����Ƕ�
		CalcNormalization(Motor.Control.u32MotorEleRPM_Final,&Speed_PHASE_COMPENSATION_Cmd);			/* ��λ����������һ������ */
		Motor.Control.u32Cal_Hall_advance_Angle = Speed_PHASE_COMPENSATION_Cmd.Out;
		Motor.Control.u32Cal_Hall_Angle_Act_Cmd = 60 - Motor.Control.u32Cal_Hall_advance_Angle;		/* ��ǰn��, ����ʱ 60 - n �Ⱥ���л��� */

		// ����ת���ж��Ƿ���Ҫ������λ����
		if(Motor.Control.u32MotorEleRPM_Final > EN_PHASE_COMPENSATION_SPEED)				// >�趨��ת��
		{	
			Motor.Control.u8Cal_Hall_Angle_OK_flag = 1;
		}	
		else if(Motor.Control.u32MotorEleRPM_Final < DIS_PHASE_COMPENSATION_SPEED)	// <�趨��ת��
		{
			Motor.Control.u8Cal_Hall_Angle_OK_flag = 0;
		}
		
		// ���Ʋ����Ǵ�С
		if(Motor.Control.u32Cal_Hall_Angle_Act_Cmd > LIMIT_MAX_ADVANCE_ANGLE)	
		{
			Motor.Control.u32Cal_Hall_Angle_Act_Cmd = LIMIT_MAX_ADVANCE_ANGLE;
		}
		else if(Motor.Control.u32Cal_Hall_Angle_Act_Cmd < LIMIT_MIN_ADVANCE_ANGLE)	
		{
			Motor.Control.u32Cal_Hall_Angle_Act_Cmd = LIMIT_MIN_ADVANCE_ANGLE;		
		}
	#endif
}



//s32 DesirdDuty;
void VSP_Control_Motor(void)
{
	static  s32 RefDUTY;
	static  s32 DesirdDuty;
	
	if(Motor.USER.u16VSP_filt_value < VSP_OFF_VALUE)					// ��λ��δ����
	{
		Motor.BLDC.u8_ControlStep = 0;

		#if EN_BRAKE
				BLDC_Brake();
		#else
				BLDC_Stop();			
		#endif

		Motor.BLDC.u16_TimCnt = 0;
		Motor.BLDC.u8FlagEnMotorRun = 0;		// Motor stop	
		Motor.BLDC.u8FlagMotorIsRunning = 0;
	
		//e1M1_RunSubState = M1_RunState_Calib;
	}
	else if(Motor.USER.u16VSP_filt_value > VSP_START_VALUE)
	{
		if(Motor.BLDC.u16_TimCnt < 3)
		{
			Motor.BLDC.u16_TimCnt++;
			Motor.BLDC.u8FlagEnMotorRun = 1; 		// Enable Motor Start
		}
		else
		{
			Motor.BLDC.u16_TimCnt = 3;
		}
	}
	
	// Motor speed control 
	if(Motor.BLDC.u8FlagMotorIsRunning == 1)
	{			
		if (Motor.Control.u32MotorRPMFilte_cnt < STARTUP_DRAG_TIME)	// ����ǰ��, ʹ��Сռ�ձ�����
		{
			Motor.Control.u32MotorRAMP_OK_flag = 0;
			Motor.Control.u32MotorRPMFilte_cnt++;		// ʹ��Сռ�ձ�������ʱ����
			DesirdDuty = MOTOR_STARTUP_PWMDUTY;
		}
		else
		{
			Motor.Control.u32MotorRAMP_OK_flag = 1;
			
			#if EN_MOTOR_SPEED_CLOSELOOP	// �ջ�����
				CalcNormalization(Motor.USER.u16VSP_filt_value,&SPEED_Cmd);		/* ���ٲ�����һ������ */
				SPEEDValue.Dest = CalcGraudNormalizationData(SPEED_Cmd.Out,MOTOR_SPEED_MIN_RPM,SPEED_ACC_MS,SPEED_DEC_MS,1);	/*����������	���Ӽ�������*/
			#else	
			// ����VSP
				CalcNormalization(Motor.USER.u16VSP_filt_value,&RP);					/* ���ٲ�����һ������ */	
				RPValue.Dest = CalcGraudNormalizationData(RP.Out,MIN_PWM_DUTY,VSP_DUTY_ACC_LOAD,VSP_DUTY_DEC_LOAD,1);	/*����PWMռ�ձ�������Ӽ�������*/
			#endif
			
			// ����ת��RPM, ʹ��Ӳ������������
//			Ele_Speed_Division.Dividend = MOTOR_SPEED_X; 		// ������
//			Ele_Speed_Division.Divisor 	= Motor.Control.u32MotorElePeriodValueTemp;		// ����, һ����������360��, ����60��
//			Motor.Control.u32MotorRPM 	= DSP_CalcDivision(&Ele_Speed_Division);
			Motor.Control.u32MotorRPM = MOTOR_SPEED_X / Motor.Control.u32MotorElePeriodValueTemp;	
			Motor.Control.u32MotorRPM	<<= 2;		// �� MOTOR_SPEED_X �������ǰ��С4��, ���軹ԭ��ʵ����
			
			Motor.Control.u32MotorRPM_sum += Motor.Control.u32MotorRPM;
			Motor.Control.u32MotorRPM_sum -= Motor.Control.u32MotorRPM_Filt;
			Motor.Control.u32MotorRPM_Filt = Motor.Control.u32MotorRPM_sum >> 2;
			Motor.Control.u32MotorRPMFinal = Motor.Control.u32MotorRPM_Filt;

			//����
			#if EN_MOTOR_SPEED_CLOSELOOP	// �ٶȱջ�
				if(++Motor.USER.SpeedPI_Prc >= SPEED_PI_PRC)  //�ٶȻ�����
				{
					Motor.USER.SpeedPI_Prc = 0;
					PIParmS.qInMeas = Motor.Control.u32MotorRPMFinal;
					PIParmS.qInRef = SPEEDValue.Dest; 
					CalcPI(&PIParmS); 
				}
				RefDUTY = PIParmS.qOut;
				DesirdDuty = PiCurrentLimitPWMDuty(RefDUTY,1);  			//�����������ƺ��PWMռ�ձ�ֵ	
			#else	// ��������
				RefDUTY = RPValue.Dest;
				DesirdDuty = PiCurrentLimitPWMDuty(RefDUTY,1);  			//�����������ƺ��PWMռ�ձ�ֵ	
			#endif	
		}

		if (DesirdDuty > MAX_PWM_DUTY)
		{
			DesirdDuty = MAX_PWM_DUTY;
		}
		
		if(DesirdDuty < MIN_PWM_DUTY)
		{
			DesirdDuty = MIN_PWM_DUTY;
		}
		MCPWM_TH00 = 	-	DesirdDuty;
		MCPWM_TH01 = 		DesirdDuty;
		MCPWM_TH10 = 	-	DesirdDuty;
		MCPWM_TH11 = 		DesirdDuty;
		MCPWM_TH20 = 	-	DesirdDuty;
		MCPWM_TH21 = 		DesirdDuty;			
		
		Motor.Control.u32MCPWM_TH_temp = DesirdDuty;
	}
	else
	{
		PiCurrentLimitPWMDuty(0,0);  
		#if EN_MOTOR_SPEED_CLOSELOOP	// �ջ�����			
			CalcGraudNormalizationData(0,MOTOR_SPEED_MIN_RPM,0,0,0);		
		#else													// VSP����	
			CalcGraudNormalizationData(0,MIN_PWM_DUTY,0,0,0);		
		#endif
	}
}


//////////////////////////////////////////////////////////////////////////

//��������: PiCurrentLimitPWMDuty(u16 Duty_In,u8 newstate)

//��������˵������ֵ��������PI���ں�װ��Dutyֵ

//�������: ��

//�������: ��

//���ú���: ��

//���ʱ��:2022-02-28

//����: Danny

///////////////////////////////////////////////////////////////

u16 PiCurrentLimitPWMDuty(u16 Duty_In,u8 newstate)
{
    static u32 ReturnValue;
		static u32 DutyValueIn;	
		static u8  DataAccelerate = 20;  
		DutyValueIn = Duty_In;
		if(newstate)
		{
			if(User_sys.BLDC_SensorlessCtr.u32Ibus_Final > User_sys.BLDC_SensorlessCtr.u32SW_LimitCurrent_Value) //��ֵ����������
			{
				PIParmIevg.qInMeas = User_sys.BLDC_SensorlessCtr.u32Ibus_Final;         
				PIParmIevg.qInRef = User_sys.BLDC_SensorlessCtr.u32SW_LimitCurrent_Value; 
				CalcPI(&PIParmIevg);  
				ReturnValue = PIParmIevg.qOut;
				RPValue.Act = PIParmIevg.qOut;
			}
			else
			{    
				ReturnValue  = Adj(ReturnValue,DutyValueIn,DataAccelerate);
				PIParmIevg.qdSum = ReturnValue << 15;
				PIParmIevg.qOut = ReturnValue; 
			}					
		}
		else
		{
			ReturnValue = MIN_PWM_DUTY;
		}
		return(ReturnValue);
}

/*******************************************************************************
 �������ƣ�    void Motor_LED_Error(void)
 ����������    ���LED����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Li Li          ����
 *******************************************************************************/
void Motor_LED_Error(void)
{
	static u8 Err100ms_CNT = 0;	
	static u8 MotorErrTiems = 0;
	static u8 MotorErrStep = 0;
	static u8 MotorErrCNT = 0;
	
	Err100ms_CNT++;
	if (Err100ms_CNT > 20)																													//200ms
	{
		Err100ms_CNT = 0;
		
		//����ָʾ
		if(User_sys.BLDC_SensorlessCtr.sys_error_flg == SHORT_ERROR)									/* ��·���� */
		{
			MotorErrTiems = 2;																													//1�����壬ͣ2��
		}
		else if (User_sys.BLDC_SensorlessCtr.sys_error_flg == LOW_VOL_ERROR)					/* ��ѹ���� */
		{
			MotorErrTiems = 4;																													//2�����壬ͣ2��
		}
		else if (User_sys.BLDC_SensorlessCtr.sys_error_flg == HIG_VOL_ERROR)					/* ��ѹ���� */
		{
			MotorErrTiems = 6;																													//3�����壬ͣ2��
		}
		else if (User_sys.BLDC_SensorlessCtr.sys_error_flg == BLOCK_ERROR)						/* ��ת���� */
		{
			MotorErrTiems = 8;																													//4�����壬ͣ2��		
		}
		else if (User_sys.BLDC_SensorlessCtr.sys_error_flg == DC_OFFSET_ERROR)				/* ֱ��ƫ�ù��� */
		{
			MotorErrTiems = 10;																													//5�����壬ͣ2��						
		}
		else if (User_sys.BLDC_SensorlessCtr.sys_error_flg == MOS_OVER_ERROR)					/* MOS���¹��� */
		{
			MotorErrTiems = 12;																													//6�����壬ͣ2��						
		}			
		else if (User_sys.BLDC_SensorlessCtr.sys_error_flg == MOS_LOW_ERROR)					/* MOS���¹��� */
		{
			MotorErrTiems = 14;																													//7�����壬ͣ2��
		}
		else if (User_sys.BLDC_SensorlessCtr.sys_error_flg == BAT_OVER_ERROR)					 /* ��ع��¹��� */
		{
			MotorErrTiems = 16;																													//8�����壬ͣ2��
		}		
		else if (User_sys.BLDC_SensorlessCtr.sys_error_flg == BAT_LOW_ERROR)					 /* ��ص��¹��� */
		{
			MotorErrTiems = 18;																													//9�����壬ͣ2��
		}	
		else if (User_sys.BLDC_SensorlessCtr.sys_error_flg == OVER_LOAD_ERROR)				/* �������� */
		{
			MotorErrTiems = 20;																													//10�����壬ͣ2��
		}	
		else if (User_sys.BLDC_SensorlessCtr.sys_error_flg == PHASE_DROP_ERROR)				/* ȱ����� */
		{
			MotorErrTiems = 22;																													//11�����壬ͣ2��
		}		
		else if (User_sys.BLDC_SensorlessCtr.sys_error_flg == MOSFET_ERROR)						/* MOS�Լ���� */
		{
			MotorErrTiems = 24;																													//12�����壬ͣ2��
		}		
		
		switch(MotorErrStep)
		{
			case 0:
				LED_ONOFF;
			  FG_ONOFF;
				MotorErrCNT++;
				if (MotorErrCNT >= MotorErrTiems)				//���ƴ���
				{
					MotorErrCNT = 0;
					MotorErrStep = 1;
				}								
				break;
				
			case 1:
				LED_OFF;		
				FG_ON;
				MotorErrCNT++;
				if (MotorErrCNT >= 10)										//2s
				{
					MotorErrCNT = 0;
					MotorErrStep = 0;
				}
				break;	
				
			default:
				break;
		}			
	}	
}

/*******************************************************************************
 �������ƣ�    void Motor_LED_DISP(void)
 ����������    ���LED��ʾ
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Li Li          ����
 *******************************************************************************/
void Motor_LED_DISP(void)
{
	static u8 cnt_led=0;
	if (Motor.BLDC.u8FlagEnMotorRun == 0)		// Motor stop	
	{
		if (User_sys.BLDC_SensorlessCtr.sys_error_flg == 0)		//no err
		{		
			cnt_led++;
			if (cnt_led >= 50)
			{
				cnt_led = 0;
				LED_ONOFF;
			}		
			FG_OFF;
		}
		else 
		{
			Motor_LED_Error();
		}
	}
	else																										// Motor run
	{
		if (User_sys.BLDC_SensorlessCtr.sys_error_flg == 0)		//no err
		{
			LED_ON;
		}
		else
		{
			Motor_LED_Error();
		}
	}
}

/*******************************************************************************
 �������ƣ�    void CWCCW_ReadIO(void)
 ����������    ���ת���趨
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Li          ����
 *******************************************************************************/
void CWCCW_PowerOn(void)
{
	#if EN_IOSET_CWCCW
	CWCCW_bIOInput = GPIO_ReadInputDataBit(GPIO_CWCCW, GPIO_PIN_CWCCW);
	Motor.BLDC.u8Direction = CWCCW_bIOInput;
	#else
	Motor.BLDC.u8Direction = CW_CCW;  
	#endif

}

/*******************************************************************************
 �������ƣ�    void CWCCW_ReadIO(void)
 ����������    ���ת���趨
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/9/20      V1.0           Li          ����
 *******************************************************************************/
void CWCCW_ReadIO(void)
{
	static u8 CWCCW_IOInputCNT1 = 0;
	static u8 CWCCW_IOInputCNT2 = 0;

	if (GPIO_ReadInputDataBit(GPIO_CWCCW, GPIO_PIN_CWCCW) == 0)	
	{
		CWCCW_IOInputCNT2 = 0;
		if (CWCCW_bIOInput == 1)
		{
			CWCCW_IOInputCNT1++;
			if (CWCCW_IOInputCNT1 > 5)
			{
				CWCCW_IOInputCNT1 = 0;
				CWCCW_bIOInput = 0;
				Motor.BLDC.u8Direction = CWCCW_bIOInput;
			}		
		}		
	}
	else
	{
		CWCCW_IOInputCNT1 = 0;
		if (CWCCW_bIOInput == 0)
		{
			CWCCW_bIOInput = 0;
			CWCCW_IOInputCNT2++;
			if (CWCCW_IOInputCNT2 > 5)
			{
				CWCCW_IOInputCNT2 = 0;
				CWCCW_bIOInput = 1;
				Motor.BLDC.u8Direction = CWCCW_bIOInput;
			}
		}
	}		
}
			

void BLDC_Stop(void)
{
	MCPWM_TH00 = -0;
	MCPWM_TH01 =  0;
	MCPWM_TH10 = -0;
	MCPWM_TH11 =  0;
	MCPWM_TH20 = -0;
	MCPWM_TH21 =  0; 
	PWMOutputs(MCPWM0,DISABLE);

	Motor.Control.u32MCPWM_TH_temp = 0;
}

void BLDC_Brake(void)
{
	MCPWM_TH00 = -0;
  MCPWM_TH01 =  0;
  MCPWM_TH10 = -0;
  MCPWM_TH11 =  0;
  MCPWM_TH20 = -0;
  MCPWM_TH21 =  0; 
 
	Motor.Control.u32MCPWM_TH_temp = 0;
	
  //����������,����������
  MCPWM_PRT = 0x0000DEAD;
  MCPWM_IO01 = DRIVER_POLARITY | 0x1C1C;
  MCPWM_IO23 = DRIVER_POLARITY | 0x1C;
  MCPWM_PRT = 0x0000CAFE;

  PWMOutputs(MCPWM0,ENABLE);
}






