/*******************************************************************************
 * ��Ȩ���� (C)2019, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� UartCtrl.h
 * �ļ���ʶ��
 * ����ժҪ�� ��λ������
 * ����˵���� ��
 * ��ǰ�汾�� V1.0
 * ��    �ߣ� HuangMG
 * ������ڣ� 2021��5��30��
 *
 *******************************************************************************/
#ifndef __URCTRL_H
#define __URCTRL_H

#include "basic.h"

//-----------------------------------------------------------------------------
#define UART0_BUF_SIZE 256
//-----------------------------------------------------------------------------
typedef struct
{
  u8 buffer[UART0_BUF_SIZE];
  u16 write_pt;
  u16 read_pt;
  u16 cnt;
}_UART0_STRUCT;


extern _UART0_STRUCT rxd_comm0;

extern volatile u8 UART_Flag;

extern void UART0_init(void);
extern void UartDealRX(void);
extern void UartDealTX(void);


#endif
