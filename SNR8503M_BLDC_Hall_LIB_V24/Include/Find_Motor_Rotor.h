#ifndef _Find_Motor_Rotor_H_
#define _Find_Motor_Rotor_H_


#include "main.h"

//CC1ͨ������Ƚ�ģʽ����(TIM1->CCMR1�Ĵ���������) 
//��Ч��ƽ:��   
//��Ч��ƽ:��
#define CC1_Out_Pwm1 	          (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)//PWMģʽ1 
#define CC1_Out_Effect_level    (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_0)//ǿ��Ϊ��Ч��ƽ
#define CC1_Out_NoEffect_level  (TIM_CCMR1_OC1M_2)//ǿ��Ϊ��Ч��ƽ

//CC2ͨ������Ƚ�ģʽ����(TIM1->CCMR1�Ĵ���������) 
#define CC2_Out_Pwm1            (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1)//PWMģʽ1  
#define CC2_Out_Effect_level    (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_0)//ǿ��Ϊ��Ч��ƽ
#define CC2_Out_NoEffect_level  (TIM_CCMR1_OC2M_2)//ǿ��Ϊ��Ч��ƽ

//CC3ͨ������Ƚ�ģʽ����(TIM1->CCMR2�Ĵ���������) 
#define CC3_Out_Pwm1 	          (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1)//PWMģʽ1  
#define CC3_Out_Effect_level    (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_0)//ǿ��Ϊ��Ч��ƽ
#define CC3_Out_NoEffect_level  (TIM_CCMR2_OC3M_2)//ǿ��Ϊ��Ч��ƽ

//CC123ͨ����������(TIM1->CCER�Ĵ���������)
//0:����Ч 1������Ч
#define CC1_POL_HS  0		                      //(����Ч)
#define CC1_POL_LS  0 //TIM_CCER_CC1NP	          //(����Ч)
#define CC1_POL     (CC1_POL_HS | CC1_POL_LS) //�����ż��Ե���

#define CC2_POL_HS  0               					//(����Ч)
#define CC2_POL_LS  0 //TIM_CCER_CC2NP  					//(����Ч)
#define CC2_POL     (CC2_POL_HS | CC2_POL_LS) //�����ż��Ե���

#define CC3_POL_HS  0               					//(����Ч)
#define CC3_POL_LS  0 //TIM_CCER_CC3NP  					//(����Ч)
#define CC3_POL     (CC3_POL_HS | CC3_POL_LS) //�����ż��Ե���

//CC123ͨ��ʹ������(TIM1->CCER�Ĵ���������)
#define CC1_HS_EN   (TIM_CCER_CC1E|CC1_POL)   //CC1�߱�ʹ��
#define CC1_LS_EN   (TIM_CCER_CC1NE|CC1_POL)  //CC1�ͱ�ʹ��		 

#define CC2_HS_EN 	 (TIM_CCER_CC2E|CC2_POL)  //CC2�߱�ʹ��   
#define CC2_LS_EN    (TIM_CCER_CC2NE|CC2_POL) //CC2�ͱ�ʹ��	  

#define CC3_HS_EN 	 (TIM_CCER_CC3E|CC3_POL)  //CC3�߱�ʹ��     
#define CC3_LS_EN 	 (TIM_CCER_CC3NE|CC3_POL) //CC3�ͱ�ʹ��	 

void ToPwmValue(uint16_t PwmDuty);
void turn_off(void);
void MOS_Electronic_Brake(uint8_t FunInside_over_cur_flag);
void Motor_Rotor_Detect(void);
void Hid_Pulse_Logic(uint8_t temp);
void Find_Motor_Rotor_Position(void);
void sort(uint16_t array[],uint8_t m);
void Sure_CutIn_OpenLoop_MOS_Number(uint8_t temp);
void Hit_pulse_find_position_if_successful_function(void);
void Find_FirstMax_SecondMax_Value(uint16_t array[],uint8_t m);

extern void BLDC_NoHallSystem_Change_Phanse_Logic(uint8_t FunInside_over_cur_flag,uint8_t NoHallNumber);

#endif
