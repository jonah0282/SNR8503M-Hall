#include "snr8503x.h"
#include "Global_Variable.h"
#include "MosTest.h"
#include "snr8503x_adc.h"
#include "hardware_config.h"
#include "M1_StateMachine.h"
#include "motor_structure.h"

#define MOS_SHORT_VALUE    5000  //30A
#define BUS_SHORT_VALUE    5000

stru_MOS_test MOS_Selftest;
 
void MosTest(void)
{
    volatile u8 i;

    MOS_Selftest.MosTest_start = 1;
    MOS_Selftest.MOSfail_flg = 0;	
		MOS_Selftest.PWM_Setting = (0.1*PWM_PERIOD);

		MOS_Selftest.Sample_Point = MOS_Selftest.PWM_Setting >> 1;

    for(i = 0; i < 5; i++)
    {		
			LED_ONOFF
			
      MOS_Selftest.check_step = i;			
			MOS_Check_Step(MOS_Selftest.check_step);
			
			MOS_Selftest.PWM_cnt = 0;
			while(MOS_Selftest.PWM_cnt < 1) {;}		// ADC Interrupt cnt
			PWMOutputs(MCPWM0,ENABLE);						// Enable PWM Output

			while(MOS_Selftest.PWM_cnt < 2) {;}
			PWMOutputs(MCPWM0,DISABLE);						// Disable PWM Output
			
			MOS_Selftest.Bus_current[i] = ((s16)(ADC_DAT0 - User_sys.BLDC_SensorlessCtr.PeakCurrOffset));		// Get Current value

			if((MOS_Selftest.Bus_current[i] > BUS_SHORT_VALUE) && (i < 2))		// Current error
			{
				MOS_Selftest.MOSfail_flg = 1;
			}
			else if(MOS_Selftest.Bus_current[i] > MOS_SHORT_VALUE)						// Current error 
			{
				MOS_Selftest.MOSfail_flg = 1;
			} 
			
			MOS_Selftest.PWM_delay = 0;								// delay for next detect
			while(MOS_Selftest.PWM_delay < 5) {;}			
			
      if((MOS_Selftest.MOSfail_flg) || (User_sys.BLDC_SensorlessCtr.sys_error_flg))		// System error
      {
				e1M1_MainState = M1_MainState_Fault;						// MainState Fault
				e1M1_RunSubState = M1_RunState_Calib;						// RunState Calib							
        User_sys.BLDC_SensorlessCtr.sys_error_flg |= MOSFET_ERROR;		  
        break;
      }					
		}			

    __disable_irq();
    ADC_init();
    MCPWM_init();
		ADC_STATE_RESET();
    __enable_irq();
}


void MOS_Check_Step(unsigned char MOS_Check_step_cnt)
{
   MCPWM_PRT = 0x0000DEAD;
	
	 switch (MOS_Check_step_cnt)
	 {
     case 0: 
		 {//����MOS���ԣ�����������,����������
			 MCPWM_IO01 = DRIVER_POLARITY | 0x0808;
			 MCPWM_IO23 = DRIVER_POLARITY | 0x08;			 
			 break;
		 }		 
     case 1: 
		 {//����MOS���ԣ�����������,����������
			 MCPWM_IO01 = DRIVER_POLARITY | 0x0404;
			 MCPWM_IO23 = DRIVER_POLARITY | 0x04;			 					 					 
			 break;
		 }
		 
     case 2: 
		 {//����AC����·��A��PWM��B�����գ�C�࿪����
			 MCPWM_IO01 = DRIVER_POLARITY | 0x0c00;
			 MCPWM_IO23 = DRIVER_POLARITY |0x1c;		 

					// A��ON��B������ C��PWM 
					// A ON | B float | C PWM			 
//				MCPWM_IO01 = DRIVER_POLARITY | (0x0c1c);		// ����ģʽ
//				MCPWM_IO23 = DRIVER_POLARITY | 0x04;
			 
			 break;
		 }		 
     case 3: 
		 {//����AB����·��B��PWM��C�����գ�A�࿪����
			 MCPWM_IO01 = DRIVER_POLARITY | 0x001c;
			 MCPWM_IO23 = DRIVER_POLARITY | 0x0c;			

					// A��ON��B��PWM C������ ����������ع����¼�
					// A ON | B PWM | C float
//					MCPWM_IO01 = DRIVER_POLARITY | 0x041c;      	// 
//					MCPWM_IO23 = DRIVER_POLARITY | (0x0c);			 
			 break;
		 }	
     case 4: 
		 {//����BC����·��C��PWM��A�����գ�B�࿪����
			 MCPWM_IO01 = DRIVER_POLARITY | 0x1c0c;
			 MCPWM_IO23 = DRIVER_POLARITY ;				

					// A�����գ�B��ON C��PWM  ����������ع����¼�
					// A float | B ON | C PWM
//					MCPWM_IO01 = DRIVER_POLARITY | (0x1c0c);		// ����ģʽ
//					MCPWM_IO23 = DRIVER_POLARITY | 0x04;	 			 
			 break;
		 }	     		 
	 }

	 MCPWM_TH00 = -MOS_Selftest.PWM_Setting;  /* ����PWM���ռ�ձȡ�*/
   MCPWM_TH01 = MOS_Selftest.PWM_Setting;

   MCPWM_TH10 = -MOS_Selftest.PWM_Setting;
   MCPWM_TH11 = MOS_Selftest.PWM_Setting;

   MCPWM_TH20 = -MOS_Selftest.PWM_Setting;
   MCPWM_TH21 = MOS_Selftest.PWM_Setting;
	 
	 Motor.Control.u32MCPWM_TH_temp = MOS_Selftest.PWM_Setting;
	 
	 MCPWM_TMR0 = MOS_Selftest.Sample_Point;

   MCPWM_UPDATE = 0xffff;	   
	 
	 MCPWM_PRT = 0x0000CAFE;
	 
   ADC_CHN0 = ADC_PEAK_CUR_CHANNEL | (ADC_PEAK_CUR_CHANNEL << 4) | ( ADC_PEAK_CUR_CHANNEL << 8) | (ADC_PEAK_CUR_CHANNEL << 12);
	 ADC_STATE_RESET();
}


