#include "delay.h"
#include "snr8503x.h"

static u32 fac_us = 0;
static u32 fac_ms = 0;

void delay_init(u32 SYSCLK)
{
 	SysTick->CTRL&=~(1<<2);					//SYSTICKʹ���ⲿʱ��Դ��1/8 HCLK	 
	fac_us=SYSCLK/8;						    //�����Ƿ�ʹ��OS,fac_us����Ҫʹ��,ÿ����1us����Ҫ���ٴ�������Ϊ��ͨ��һ�������Ĵ�����ʱ�ġ�
	fac_ms=(u16)fac_us*1000;				//��OS��,����ÿ��ms��Ҫ��systickʱ����   
}

void delay_us(u32 nus)
{
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 				//ʱ�����	  		 
	SysTick->VAL=0x00;        				//��ռ�����
	SysTick->CTRL=0x01 ;      				//��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;      	 			//�رռ�����
	SysTick->VAL =0X00;       				//��ռ����� 
}

void delay_xms(u32 nms)
{
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;			//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           			//��ռ�����
	SysTick->CTRL=0x01 ;          			//��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       				//�رռ�����
	SysTick->VAL =0X00;     		  		//��ռ�����	  	    
} 
//��ʱnms 
//nms:0~65535
void delay_ms(u32 nms)
{
#if 1
	u8 repeat=nms/540;						//������540,�ǿ��ǵ�ĳЩ�ͻ����ܳ�Ƶʹ��,
											//���糬Ƶ��248M��ʱ��,delay_xms���ֻ����ʱ541ms������
	u16 remain=nms%540;
	while(repeat)
	{
		delay_xms(540);
		repeat--;
	}
	if(remain)delay_xms(remain);
#else
	u32 t_cnt;

	for(t_cnt = 0; t_cnt < nms*1000; t_cnt++)
	{
		__nop();
	}
#endif
} 
