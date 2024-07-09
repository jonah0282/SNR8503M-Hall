/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_DMA.h
 * �ļ���ʶ��
 * ����ժҪ�� DMA����ͷ�ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 21/11/10
 *
 *******************************************************************************/
 
#ifndef __snr8503x_DMA_H
#define __snr8503x_DMA_H

#include "snr8503x.h"
#include "basic.h"


typedef struct
{
    u8   DMA_Channel_EN;           /* DMA ͨ��ʹ��*/
    u8   DMA_IRQ_EN;               /* DMA �ж�ʹ�� */
    u8   DMA_RMODE;                /* ���ִ���ʹ�� */
    u8   DMA_CIRC;                 /* ѭ��ģʽʹ�� */
    u8   DMA_SINC;                 /* Դ��ַ����ʹ�� */
    u8   DMA_DINC;                 /* Ŀ�ĵ�ַ����ʹ�� */
    u8   DMA_SBTW;                 /* Դ��ַ����λ�� 0:byte, 1:half-word, 2:word */
    u8   DMA_DBTW;                 /* Ŀ�ĵ�ַ����λ�� 0:byte, 1:half-word, 2:word */
    u16  DMA_REQ_EN;               /* ͨ�� x Ӳ�� DMA ����ʹ�ܣ�����Ч */
    u8   DMA_TIMES;                /* DMA ͨ�� x ���ݰ��˴��� */
    u32  DMA_SADR;           /* DMA ͨ�� x Դ��ַ */
    u32  DMA_DADR;           /* DMA ͨ�� x Ŀ�ĵ�ַ */

} DMA_InitTypeDef;

typedef struct
{
    __IO uint32_t DMA_CCR;
    __IO uint32_t DMA_REN;
    __IO uint32_t DMA_CTMS;
    __IO uint32_t DMA_SADR;
    __IO uint32_t DMA_DADR;
} DMA_RegTypeDef;


#define DMA_CH0             ((DMA_RegTypeDef *) DMA_BASE)
#define DMA_CH1             ((DMA_RegTypeDef *) (DMA_BASE+0x20))
#define DMA_CH2             ((DMA_RegTypeDef *) (DMA_BASE+0x40))
#define DMA_CH3             ((DMA_RegTypeDef *) (DMA_BASE+0x60))


#define DMA_TCIE                 BIT0       /* ��������ж�ʹ�ܣ�����Ч */

#define CH3_FIF                  BIT3       /* ͨ�� 3 ����жϱ�־������Ч��д 1 ���� */
#define CH2_FIF                  BIT2       /* ͨ�� 2 ����жϱ�־������Ч��д 1 ���� */
#define CH1_FIF                  BIT1       /* ͨ�� 1 ����жϱ�־������Ч��д 1 ���� */
#define CH0_FIF                  BIT0       /* ͨ�� 0 ����жϱ�־������Ч��д 1 ���� */

#define PERI2MEMORY              0          /* �������ڴ� */
#define MEMORY2PERI              1          /* �ڴ������� */

#define DMA_BYTE_TRANS           0          /* ����λ�� 0:byte */
#define DMA_HALFWORD_TRANS       1          /* ����λ�� 1:half-word */
#define DMA_WORD_TRANS           2          /* ����λ�� 2:word */ 


#define DMA_SW_TRIG_REQ_EN         BIT15      /* ������� */
#define DMA_I2C_REQ_EN             BIT14      /* I2C DMA����ʹ�� */
#define DMA_GPIO_REQ_EN            BIT13      /* GPIO DMA����ʹ�� */ 
#define DMA_CMP_REQ_EN             BIT12      /* CMP DMA����ʹ�� */
#define DMA_SPI_TX_REQ_EN          BIT11      /* SPI TX DMA����ʹ�� */
#define DMA_SPI_RX_REQ_EN          BIT10      /* SPI RX DMA����ʹ�� */
#define DMA_UART_TX_REQ_EN         BIT7       /* UART TX DMA����ʹ�� */
#define DMA_UART_RX_REQ_EN         BIT6       /* UART RX DMA����ʹ�� */
#define DMA_TIMER1_REQ_EN          BIT5       /* TIMER1 DMA����ʹ�� */ 
#define DMA_TIMER0_REQ_EN          BIT4       /* TIMER0 DMA����ʹ�� */
#define DMA_HALL_REQ_EN            BIT2       /* HALL DMA����ʹ�� */
#define DMA_MCPWM_REQ_EN           BIT1       /* MCPWM DMA����ʹ�� */
#define DMA_ADC_REQ_EN             BIT0       /* ADC DMA����ʹ�� */


void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct);
void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct);

#endif
/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
