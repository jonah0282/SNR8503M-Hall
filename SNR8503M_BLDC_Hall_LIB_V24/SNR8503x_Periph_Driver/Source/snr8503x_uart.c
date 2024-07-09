/*******************************************************************************
 * ��Ȩ���� (C)2021, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_uart.c
 * �ļ���ʶ��
 * ����ժҪ�� UART������������
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ�   Li
 * ������ڣ� 2021��10��14��
 *
 *******************************************************************************/
#include "snr8503x_uart.h"
#include "snr8503x_sys.h"

/*******************************************************************************
 �������ƣ�    void UART_Init(UART_TypeDef* UARTx, EUART_InitTypeDef* UART_InitStruct)
 ����������    UART��ʼ��
 �����ı�    ��
 ���������    ��
 ���������    ��
 �� �� ֵ��     ��
 ����˵����
 �޸�����       �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/10/14      V1.0           Li             ����
 *******************************************************************************/
void UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct)
{
   uint32_t clkDivUART;
   uint32_t divCoefficient;
   uint32_t parity;
   uint32_t parityEna;

   SYS_ModuleClockCmd(SYS_Module_UART, ENABLE);

   clkDivUART = 0;
   divCoefficient = 48000000 / UART_InitStruct->BaudRate / (1 + clkDivUART);
   while (divCoefficient > 0xFFFF)
   {
      clkDivUART++;
      divCoefficient = 48000000 / UART_InitStruct->BaudRate / (1 + clkDivUART);
   }

   SYS_CLK_DIV2 = clkDivUART;
   divCoefficient = divCoefficient - 1;
   UARTx->DIVL = divCoefficient & 0xFF;
   UARTx->DIVH = (divCoefficient & 0xFF00) >> 8;

   if (UART_InitStruct->ParityMode == UART_Parity_EVEN)
   {
      parityEna = ENABLE;
      parity = 0;
   }
   else if (UART_InitStruct->ParityMode == UART_Parity_ODD)
   {
      parityEna = ENABLE;
      parity = 1;
   }
   else
   {
      parityEna = DISABLE;
      parity = 0;
   }
   UARTx->CTRL = UART_InitStruct->WordLength | (UART_InitStruct->StopBits << 1) | (UART_InitStruct->FirstSend << 2) | (parity << 3) | (parityEna << 4) | (UART_InitStruct->MultiDropEna << 5);

   UARTx->INV = (UART_InitStruct->RXD_INV) | UART_InitStruct->TXD_INV << 1;

   UARTx->ADR = UART_InitStruct->Match485Addr;
   UARTx->RE = UART_InitStruct->DMARE;
   UARTx->IE = UART_InitStruct->IRQEna;
}

/*******************************************************************************
 �������ƣ�    void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
 ����������    UART�ṹ���ʼ��
 �����ı�    ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/10/14      V1.0           Li             ����
 *******************************************************************************/
void UART_StructInit(UART_InitTypeDef *UART_InitStruct)
{
   UART_InitStruct->BaudRate = 9600;
   UART_InitStruct->WordLength = UART_WORDLENGTH_8b;
   UART_InitStruct->StopBits = UART_STOPBITS_1b;
   UART_InitStruct->FirstSend = UART_FIRSTSEND_LSB;
   UART_InitStruct->ParityMode = UART_Parity_NO;

   UART_InitStruct->MultiDropEna = DISABLE;
   UART_InitStruct->DMARE = DISABLE;

   UART_InitStruct->Match485Addr = 0;
   UART_InitStruct->IRQEna = 0;
   UART_InitStruct->RXD_INV = DISABLE;
   UART_InitStruct->TXD_INV = DISABLE;
}

/*******************************************************************************
 �������ƣ�    void UART_SENDDATA(UART_TypeDef *UARTx, uint32_t n)
 ����������    UART��������
 �����ı�    ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/10/14      V1.0           Li             ����
 *******************************************************************************/
void UART_SendData(UART_TypeDef *UARTx, uint32_t n)
{
   UARTx->BUFF = n;
}

/*******************************************************************************
 �������ƣ�    uint32_t UART_ReadData(UART_TypeDef *UARTx)
 ����������    UART������������
 �����ı�    ��
 ���������    UART_TypeDef *UARTx
 ���������    ��
 �� �� ֵ��    ����������
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/10/14      V1.0           Li             ����
 *******************************************************************************/
uint32_t UART_ReadData(UART_TypeDef *UARTx)
{
   return UARTx->BUFF;
}

/*******************************************************************************
 �������ƣ�    uint32_t UART_GetIRQFlag(UART_TypeDef *UARTx)
 ����������    ȡ��UART�жϱ�־
 �����ı�    ��
 ���������    UART_TypeDef *UARTx:Ҫ������UART����
 ���������    ��
 �� �� ֵ��    UART�жϱ�־
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/10/14      V1.0           Li             ����
 *******************************************************************************/
uint32_t UART_GetIRQFlag(UART_TypeDef *UARTx)
{
   return UARTx->IF;
}

/*******************************************************************************
 �������ƣ�    void UART_ClearIRQFlag(UART_TypeDef *UARTx, uint32_t nFlag)
 ����������    ���UART�жϱ�־λ
 �����ı�    ��
 ���������    UART_TypeDef *UARTx:Ҫ������UART����, uint32_t nFlag��ǰ�жϱ�־
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/10/14      V1.0           Li             ����
 *******************************************************************************/
void UART_ClearIRQFlag(UART_TypeDef *UARTx, uint32_t tempFlag)
{
   UARTx->IF = tempFlag;
}

/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
