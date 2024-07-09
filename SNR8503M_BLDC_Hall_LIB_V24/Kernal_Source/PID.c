/*-------------------- Includes -----------------------*/
#include "PID.h"
#include "global_variable.h"
#include "MC_Parameter.h"
#include "motor_structure.h"
#include "M1_StateMachine.h"
#include "MC_Drive.h"
#include "SpeedRamp.h"

/*------------------- Private variables ---------------*/
tPIParm PIParmIevg;                //��ֵ��������PI�ṹ����� 
tPIParm PIParmS;                   //�ٶȵ���PI�ṹ�����

//////////////////////////////////////////////////////////////////////////

//��������:  InitPI()��ʼ��PI

//��������˵��: ��ʼ������������ñ���

//���������

//���������

//���ú�������

//���ʱ��:2022-02-28

//����: Danny

///////////////////////////////////////////////////////////////
void InitPI(void)
{
	PIParmIevg.qOutMax    = MAX_PWM_DUTY;
	PIParmIevg.qOutMin    = MIN_PWM_DUTY;
	PIParmIevg.qKp        = IevgSum_Kp ;
	PIParmIevg.qKi        = IevgSum_Ki ;
	PIParmIevg.qKc        = IevgSum_Kc ;
	PIParmIevg.qdSum      = 0;
	PIParmIevg.qInMeas    = 0;
	PIParmIevg.qOut       = MIN_PWM_DUTY;
	
	PIParmS.qOutMax    = MAX_PWM_DUTY;
	PIParmS.qOutMin    = MIN_PWM_DUTY;
	PIParmS.qKp        = SSum_Kp ;
	PIParmS.qKi        = SSum_Ki ;
	PIParmS.qKc        = SSum_Kc ;
	PIParmS.qdSum      = 0;
	PIParmS.qInMeas    = 0;
	PIParmS.qOut       = MIN_PWM_DUTY;
}

//////////////////////////////////////////////////////////////////////////

//��������:  CalcPI( tPIParm *pParm)PI������

//��������˵��: ���ڵ���ٶȻ��ıջ�����

//���������pParm->qInMeas�ο����� pParm->qInRef��������

//���������PIParmI.qOut PI�������

//���ú�������

//���ʱ��:2022-02-28

//����: Danny

///////////////////////////////////////////////////////////////

void CalcPI( tPIParm *pParm)
{
	signed int   Error;
	signed int   Exc;
	signed long  U;
	Error =  pParm->qInRef - pParm->qInMeas;
	U =  pParm->qdSum + pParm-> qKp * Error;
	U  >>= 15;
	if( U  >  pParm-> qOutMax)
	{
		pParm->qOut = pParm-> qOutMax;
	}
	else if( U  <  pParm-> qOutMin)
	{
		pParm->qOut = pParm-> qOutMin;
	}
	else
	{
		pParm->qOut  =  U;
	}
	Exc = U - pParm->qOut;
	pParm->qdSum +=  pParm-> qKi* Error - pParm-> qKc * Exc;
}




