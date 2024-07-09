/*-------------------- Includes -----------------------*/
#include "SpeedRamp.h"
#include "Global_Variable.h"
#include "motor_structure.h"

NormalizationType 		RP;
LoopCMP_T 						RPValue;

NormalizationType 		SPEED_Cmd;
LoopCMP_T 						SPEEDValue;

NormalizationType 		Duty_PHASE_COMPENSATION_Cmd;
NormalizationType 		Speed_PHASE_COMPENSATION_Cmd;

/****************************************************************
	��������InitNormalization
	��������λ����һ��������ʼ��
	���룺��
	�������
****************************************************************/
void InitNormalization(u32 Lowdata,u32 highdata,u32 minout,u32 maxout,NormalizationType *u)
{
	u->MinIn = Lowdata; 			//�������
	u->MaxIn = highdata; 			
	u->MinOut = minout;  			
	u->MaxOut = maxout;  			//������ֵ 
	u->Kslope = ((float)u->MaxOut)/(u->MaxIn - u->MinIn);  //б��	= 0.75
	u->State = 0;
	u->OutEn = 0;
	u->Out = 0;
}

//////////////////////////////////////////////////////////////////////////

//��������:u16 CalcGraudNormalizationData(u16 data,u16 Minout,u16 Accelerate,u16 Decelerate,u8 newstate)

//��������˵��:����������

//�������: 

//�������: ��

//���ú���: ��

//���ʱ��:2022-02-28

//����: Li

///////////////////////////////////////////////////////////////
u16 CalcGraudNormalizationData(u16 data,u16 Minout,u16 Accelerate,u16 Decelerate,u8 newstate)
{
		static u16 DataReturn;	
	
		if(newstate == ENABLE)
		{
			if(data <= Minout)
			{
				data = Minout; 
			}
			if(((DataReturn > data)&&(DataReturn < (data + Decelerate)))
					 ||((DataReturn < data)&&(DataReturn > (data - Accelerate))))
			{
				DataReturn = data;
			}
					
			else if(DataReturn > data)
			{
				DataReturn -= Decelerate;
			}
			else if(DataReturn < data)
			{
				DataReturn += Accelerate;
			}
			else
			{
				DataReturn = data;
			}			
		}
		else
		{
			DataReturn = Minout;
		}

	  return(DataReturn);
}


/****************************************************************
	��������CalcNormalization
	��������λ����һ������
	���룺��
	�������
****************************************************************/
void CalcNormalization(u32 value,NormalizationType *u)
{
	u->In = value;

	if(u->In < (u->MinIn - 15))		//��Ч��
	{
		u->State |= 1;
		u->Out = 0;
		
		if(u->State == 3)
		{
			u->State &= 1;
			u->OutEn = 0;
		}
	}
	else if((u->In > u->MinIn))	//��Ч��
	{
		u->State |= 2;
		u->Out = u->Kslope*(u->In - u->MinIn);		//���Թ�һ��
		
		if(u->Out > u->MaxOut)
		{
			u->Out = u->MaxOut;	
		}
		if(u->Out < u->MinOut)
		{
			u->Out = u->MinOut;	
		}		
		
		if(u->State == 3)
		{
			u->State &= 2;
			u->OutEn = 1;
		}
	}
	else				//�ز���״̬����
	{

	}
}

