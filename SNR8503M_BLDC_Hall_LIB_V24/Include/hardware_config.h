/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� hardware_config.h
 * �ļ���ʶ��
 * ����ժҪ�� Ӳ������ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 2020��8��20��
 *
 * �޸ļ�¼1��
 * �޸����ڣ� 2020��8��20��
 * �� �� �ţ� V 2.0
 * �� �� �ˣ� Li
 * �޸����ݣ� ����
 *
 *******************************************************************************/

/*------------------------------prevent recursive inclusion -------------------*/
#ifndef __HARDWARE_CONFIG_H_
#define __HARDWARE_CONFIG_H_

#include "snr8503x.h"
#include "snr8503x_MCPWM.h"
#include "snr8503x_sys.h"
#include "snr8503x_adc.h"
#include "snr8503x_dac.h"
#include "snr8503x_MCPWM.h"
#include "snr8503x_Flash.h"
#include "snr8503x_gpio.h"
#include "snr8503x_dma.h"
#include "snr8503x_cmp.h"
#include "snr8503x_uart.h"
#include "snr8503x_hall.h"
#include "snr8503x_timer.h"
#include "snr8503x_NVR.h"
#include "snr8503x_iwdg.h"
#include "snr8503x_dsp.h"
#include "basic.h"

#include "delay.h"
#include "hardware_init.h"
#include "Global_Variable.h"
#include "MC_Parameter.h"

#define	setbit(x,y)				x |= (1<<y)
#define	clrbit(x,y)				x &= ~(1<<y)
#define	reversebit(x,y)		x ^= (1<<y)
#define	getbit(x,y)				((x) >> (y)&1)

/* ---------------------------- Hall Clock Division --------------------------- */
#define CLK_DIVISION 										(0) 				// Hall ʱ��Դ��Ƶ, ���ݷ�Χ: 0 ~ 3

#if(CLK_DIVISION == 0)
	#define HALL_CLK_K										48					// Hall ʱ��Ƶ��: 48MHz
#elif(CLK_DIVISION == 1)
	#define HALL_CLK_K										24					// Hall ʱ��Ƶ��: 24MHz
#elif(CLK_DIVISION == 2)
	#define HALL_CLK_K										12					// Hall ʱ��Ƶ��: 12MHz
#elif(CLK_DIVISION == 3)
	#define HALL_CLK_K										6						// Hall ʱ��Ƶ��: 6MHz
#endif

/* --------------------------------ADCͨ���Ŷ���------------------------------ */
#define ADC_CHANNEL_OPA0              ADC_CHANNEL_0
#define ADC_CHANNEL_OPA1              ADC_CHANNEL_8

/* ADC���������ʱ��Ӳ����� ------------------------------------------------ */
/* Porting Application Notice ע��������� ------------------------------------ */
#define ADC_BUS_CUR_CHANNEL            ADC_CHANNEL_OPA0    /* ĸ�ߵ��� */
#define ADC_PEAK_CUR_CHANNEL           ADC_CHANNEL_OPA0

#define ADC_BUS_VOL_CHANNEL            ADC_CHANNEL_4       /* ĸ�ߵ�ѹ */
#define ADC_SPEED_CHANNEL              ADC_CHANNEL_5       /* �ٶ��ź� */

#define ADC_MOS_TEMP_CHANNEL           ADC_CHANNEL_9       /* MOS�¶� */

#define ADC_OPA_OUT_CHANNEL            ADC_CHANNEL_5      /* �˷�������� */

#define BEMF_CH_A                      ADC_CHANNEL_1        /* ADC_Ch1 */
#define BEMF_CH_B                      ADC_CHANNEL_2        /* ADC_Ch2 */
#define BEMF_CH_C                      ADC_CHANNEL_3        /* ADC_Ch3 */

#define ADC_STATE_RESET()              {ADC_CFG |= BIT11;}  /* ADC0 ״̬����λ,���Լ��������ȷ��ADC����״̬ */
#define ADC_SOFTWARE_TRIG_ONLY()       {ADC_CFG = 0;}       /* ADC����Ϊ��������� */

// CMP0 Sensorless Detect
#define CMP0_BEMF_CH_U                 CMP0_SELP_CMP0_IP2   /* ADC_Ch1 */
#define CMP0_BEMF_CH_V                 CMP0_SELP_CMP0_IP1   /* ADC_Ch2 */
#define CMP0_BEMF_CH_W                 CMP0_SELP_CMP0_IP3   /* ADC_Ch3 */

/* -----------------------------����������ض��� ------------------------------- */
#define HN_HIGH__LN_HIGH                   0          /* Ԥ��Ԥ���������� �Ϲܸߵ�ƽ��Ч���¹ܸߵ�ƽ��Ч */
#define HN_HIGH__LN_LOW                    1          /* Ԥ��Ԥ���������� �Ϲܸߵ�ƽ��Ч���¹ܵ͵�ƽ��Ч */
#define	PRE_DRIVER_POLARITY								 HN_HIGH__LN_HIGH
#if ((PRE_DRIVER_POLARITY == HN_HIGH__LN_HIGH)) 
#define DRIVER_POLARITY                0x0000      		// ȡ MCPWM_IO01 �� MCPWIO23 ��������CHxN��CHxP�ļ��Ե�����
#else
#define DRIVER_POLARITY                0x0101      // ȡ MCPWM_IO01 �� MCPWIO23 ��������CHxN��CHxP�ļ��Ե�����
#endif

#define DEADTIME_NS                    ((u16)1500)                              /* ����ʱ�� */
#define DEADTIME                       (u16)(((unsigned long long)PWM_MCLK * (unsigned long long)DEADTIME_NS)/1000000000uL)

/* ------------------------------PGA������ض��� ------------------------------ */
#define PGA_GAIN_20                    0                   /* ��������200:10 */
#define PGA_GAIN_9P5                   1                   /* ��������190:20 */
#define PGA_GAIN_6                     2                   /* ��������180:30 */
#define PGA_GAIN_4P25                  3                   /* ��������170:40 */
                                                                                  
#define OPA_GIAN                      (PGA_GAIN_20)

/* ---------------------------CMP�Ƚ���������ض��� --------------------------- */
#define CMP1_SELN_SET                  CMP1_SELN_DAC            /* �Ƚ���1����ѡ��DAC */
#define CMP1_SELP_SET                  CMP1_SELP_CMP1_IP0       /* �Ƚ���1����ѡ���˷�1������ */

#define CMP0_SELN_SET                  CMP0_SELN_HALL_MID       /* �Ƚ���0����ѡ��HALL MID */
//#define CMP0_SELP_SET                  CMP0_SELP_CMP0_IP1       /* �Ƚ���0����ѡ��IP0 */
#define CMP_IP_A                       CMP0_SELP_CMP0_IP2        /* A�෴���Ƶ�ѹ�Ƚ���ͨ�� */
#define CMP_IP_B                       CMP0_SELP_CMP0_IP1        /* B�෴���Ƶ�ѹ�Ƚ���ͨ�� */
#define CMP_IP_C                       CMP0_SELP_CMP0_IP3        /* C�෴���Ƶ�ѹ�Ƚ���ͨ�� */

#define CMP0_IE_ENABLE()                {CMP_IE |= BIT0;}   /* �Ƚ���0�ر�ʹ�� */
#define CMP0_IE_DISABLE()               {CMP_IE &= ~BIT0;}  /* �Ƚ���0�ر�ʹ�� */
#define CMP0_IE_STATE()                 (CMP_IE & BIT0)     /* �жϵ�ǰ�Ƚ���0״̬ */

//#define CMP0_OUT_LEVEL()                (CMP_DATA & BIT0)   /* �Ƚ���0�����ƽԭʼ�ź�״̬ */
#define CMP0_OUT_LEVEL()                (CMP_DATA & BIT8)   /* �Ƚ���0�����ƽ�����˲��ź�״̬ */

#define CMP0_POL_STATE()                (CMP_CFG & BIT0)    /* ��ǰ�Ƚ���0�������ѡ�� */ 

/* ------------------------------������ѡ��------------------------------------ */
#define RUN_IN_RAM_FUNC  __attribute__ ((used, section ("ram3functions")))

/* ------------------------------Ӳ��IO���ƽӿ�-------------------------------- */
/** FG_IO interface */
#define GPIO_FG                     	 	(GPIO1)
#define GPIO_PIN_FG                	   	(GPIO_Pin_3)
#define FG_OFF                         	{GPIO_FG->PDO &= (~GPIO_PIN_FG);} // 0
#define FG_ON                          	{GPIO_FG->PDO |= (GPIO_PIN_FG);}  // 1
#define FG_ONOFF                       	{GPIO_FG->PDO ^= (GPIO_PIN_FG);} 

/** CWCCW_IO interface */
#define GPIO_CWCCW                     	(GPIO0)
#define GPIO_PIN_CWCCW                 	(GPIO_Pin_9)

#define GPIO_Debug                   		(GPIO0)
#define GPIO_PIN_Debug              		(GPIO_Pin_9)
#define Debug_OFF                     	{GPIO_Debug->PDO &= (~GPIO_PIN_Debug);} // 0
#define Debug_ON                       	{GPIO_Debug->PDO |= (GPIO_PIN_Debug);}  // 1
#define Debug_ONOFF                   	{GPIO_Debug->PDO ^= (GPIO_PIN_Debug);} 


/** LED_IO interface */
#define GPIO_LED                     	 (GPIO0)
#define GPIO_PIN_LED                	 (GPIO_Pin_0)
#define LED_ON                         {GPIO_LED->PDO &= (~GPIO_PIN_LED);} // 0
#define LED_OFF                        {GPIO_LED->PDO |= (GPIO_PIN_LED);}  // 1
#define LED_ONOFF                      {GPIO_LED->PDO ^= (GPIO_PIN_LED);} 


/* ----------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------- */
// �����ת�ٻ�������� & ����ʱ��
#define MOTOR_e_RPM              	 			120000     			 		   					/* �����ת��: 12WeRPM */
#define MOTOR_e_K												((60*1000000)>>2)*HALL_CLK_K		/* �򳬳��������ͷ�Χ, �������ǰ��������λ, ����������� */
#define MOTOR_e_PERIOD									(MOTOR_e_K/MOTOR_e_RPM)					/* ������ */
#define MOTOR_e_SINGLE_STEP							(MOTOR_e_PERIOD/6)							/* ����ʱ�� */

#define MOTOR_1K_e_RPM									(1000)					/* ��ת��/Min: 1K Hz */
#define MOTOR_2K_e_RPM									(2000)					/* ��ת��: 2K */
#define MOTOR_3K_e_RPM									(3000)					/* ��ת��: 3K */
#define MOTOR_4K_e_RPM									(4000)					/* ��ת��: 4K */
#define MOTOR_5K_e_RPM									(5000)					/* ��ת��: 5K */
#define MOTOR_6K_e_RPM									(6000)					/* ��ת��: 6K */
#define MOTOR_7K_e_RPM									(7000)					/* ��ת��: 7K */
#define MOTOR_8K_e_RPM									(8000)					/* ��ת��: 8K */
#define MOTOR_9K_e_RPM									(9000)					/* ��ת��: 9K */
#define MOTOR_1W_e_RPM									(10000)					/* ��ת��: 1W */
#define MOTOR_2W_e_RPM									(20000)					/* ��ת��: 2W */
#define MOTOR_3W_e_RPM									(30000)					/* ��ת��: 3W */
#define MOTOR_4W_e_RPM									(40000)					/* ��ת��: 4W */
#define MOTOR_5W_e_RPM									(50000)					/* ��ת��: 5W */
#define MOTOR_6W_e_RPM									(60000)					/* ��ת��: 6W */
#define MOTOR_7W_e_RPM									(70000)					/* ��ת��: 7W */
#define MOTOR_8W_e_RPM									(80000)					/* ��ת��: 8W */
#define MOTOR_9W_e_RPM									(90000)					/* ��ת��: 9W */
#define MOTOR_10W_e_RPM									(100000)				/* ��ת��: 10W */
#define MOTOR_11W_e_RPM									(110000)				/* ��ת��: 11W */
#define MOTOR_12W_e_RPM									(120000)				/* ��ת��: 12W */
/* ----------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------- */

/* ---------------------------- Hall Phase Compensation  --------------------------- */
#define EN_HALL_PHASE_COMPENSATION  		(0)																// �Ƿ���������λ����

#define EN_PHASE_COMPENSATION_SPEED  		(u32)(MOTOR_2W_e_RPM)							// ������λ������ת��
#define DIS_PHASE_COMPENSATION_SPEED  	(u32)(MOTOR_1W_e_RPM)							// �����λ������ת��

#define START_SPEED_COMPENSATION				EN_PHASE_COMPENSATION_SPEED				// ���Է�����С����ֵ
#define MAX_SPEED_COMPENSATION					MOTOR_3W_e_RPM										// ���Է����������ֵ

#define EN_PHASE_COMPENSATION						EN_PHASE_COMPENSATION_SPEED				// ������λ����������
#define DIS_PHASE_COMPENSATION					DIS_PHASE_COMPENSATION_SPEED			// �����λ����������

#define MIN_ADVANCE_ANGLE								15																// ���ݷ�Χ: 15 ~ 45, ʵ��Ч����۲����ѹ���ε���
#define MAX_ADVANCE_ANGLE								45																// ���ݷ�Χ: 15 ~ 45, ʵ��Ч����۲����ѹ���ε���

#define LIMIT_MIN_ADVANCE_ANGLE					15																// ������С������, �̶�ֵ: 15
#define LIMIT_MAX_ADVANCE_ANGLE					45																// ������С������, �̶�ֵ: 45

//#define LED_DELAY_TIME                 60000       /* �ɰ������ʱ�ػ�ʱ�� */ 

//#define LOCK_POWER_ON()                {GPIO0_PDO |= BIT1;}         
//#define LOCK_POWER_OFF()               {GPIO0_PDO &= ~BIT1;}

//#define LED_OFF_TIME                   500         /*LED������˸ʱ������*/
//#define LED_ON_TIME                    500
//#define LED_PERIOD_DELAY               1000        /*LED������˸������ʱʱ������*/

//#define LED_ON()                       {GPIO0_PDO &= ~BIT3;}
//#define LED_OFF()                      {GPIO0_PDO |= BIT3;}

//#define KEYIN_FILTER_TIME              30 /* ���������˲�ʱ�� */

//#define SWITCH_INPUT_MASK              (GPIO1_PDI & BIT13)
//#define DIRECT_INPUT_MASK              (GPIO1_PDI & BIT4)

//#define SWITCH_INPUT                   (BIT0)  /* ���� */
//#define DIRECT_INPUT                   (BIT1)  /* ���� */

#endif  /* __HARDWARE_CONFIG_H_ */

 
/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
 
 
