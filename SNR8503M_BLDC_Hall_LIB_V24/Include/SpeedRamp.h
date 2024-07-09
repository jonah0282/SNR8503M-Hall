
#ifndef __SpeedRamp_H
#define __SpeedRamp_H

#include "main.h"

typedef struct
{
	u32 In;             //����ֵ
	
	u32 MaxIn;          //���ֵ��Чֵ
	u32 MinIn;          //��Сֵ��Чֵ		
	
	u32 MinOut;					// 
	u32 MaxOut;         //��Ӧ����������ֵ
	
	u32 Out;            //���ֵ
	u8  OutEn;          //���ʹ�ܱ�־
  u8  State;          //����״̬
	float Kslope;       //��Ӧб��
}
NormalizationType; //������һ������ر���
extern NormalizationType RP;
extern NormalizationType SPEED_Cmd;
extern NormalizationType Duty_PHASE_COMPENSATION_Cmd;
extern NormalizationType Speed_PHASE_COMPENSATION_Cmd;

typedef struct
{
	s32 Dest;		//�ο�Ŀ����
	s32 Act;		//ʵ��ʹ����
	s32 Max;		//�������ֵ
	s32 Min;		//��С����ֵ
	s32 Inc;		//���ٲ���
	s32 Dec;		//���ٲ���
}LoopCMP_T; 
extern LoopCMP_T RPValue;
extern LoopCMP_T SPEEDValue;

extern u16 CalcGraudNormalizationData(u16 data,u16 Minout,u16 Accelerate,u16 Decelerate,u8 newstate);
extern void InitNormalization(u32 Lowdata,u32 highdata,u32 minout,u32 maxout,NormalizationType *u);
extern void CalcNormalization(u32 value,NormalizationType *u);

#endif


