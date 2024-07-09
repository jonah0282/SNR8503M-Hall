#ifndef PID_h
#define PID_h
#include "commonfunc.h"

typedef struct {
	  signed   int   qdSum;
	  signed   int   qKp;
	  signed   int   qKi;
	  signed   int   qKc;
	  signed   int   qOutMax;
	  signed   int   qOutMin;
	  signed   int   qInRef;
	  signed   int   qInMeas;
	  signed   int   qOut;
} tPIParm;
	
extern tPIParm PIParmIevg;                //��ֵ��������PI�ṹ����� 
extern tPIParm PIParmS;                   //�ٶȵ���PI�ṹ�����

extern void InitPI(void);              //PI��ʼ������
extern void CalcPI( tPIParm *pParm);   //PI�������


#endif
