/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_spi.h
 * �ļ���ʶ��
 * ����ժҪ�� SPI����ͷ�ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 21/11/10
 *
 *******************************************************************************/
 
#ifndef __snr8503x_SPI_H
#define __snr8503x_SPI_H


/* Includes ------------------------------------------------------------------*/
#include "snr8503x.h"
#include "basic.h"

typedef enum
{
   SPI_Master = 0x01,
   SPI_Slave  = 0x00
}SPI_Mode;

typedef enum
{
   SPI_Full    = 0x0,           //ȫ˫��
   SPI_Half_Tx = 0x2,           //��˫����������
   SPI_Half_Rx = 0x3            //��˫����������
}SPI_Duplex;

typedef struct
{
   __IO uint32_t CFG;
   __IO uint32_t IE;
   __IO uint32_t BAUD;
   __IO uint32_t TX_DATA;
   __IO uint32_t RX_DATA;
   __IO uint32_t SIZE;
}SPI_TypeDef;

typedef struct
{
   SPI_Duplex Duplex;       //��˫��ģʽ����
   uint8_t    CS;           //SPI ���豸�£�Ƭѡ�ź���Դ��0:Slave ģʽ�£�Ƭѡ�źź�Ϊ��Чֵ 1:Slave ģʽ�£�Ƭѡ�ź����� Master �豸
   SPI_Mode   Mode;         //SPI ����ģʽѡ��
   uint8_t    CPHA;         //SPI ��λѡ��
   uint8_t    CPOL;         //SPI ����ѡ��
   uint8_t    ENDIAN;       //SPI ģ�鴫��˳��
   uint8_t    EN;           //SPI Enable Signal, 0: disable;1: enable

   uint8_t    IRQEna;       //SPI �ж�ʹ�ܡ�
   uint8_t    TRANS_TRIG;   //���䴥��ѡ��

   uint8_t    TRANS_MODE;   //SPI ���ݰ��Ʒ�ʽ��0 DMA ��ʽ��
   uint8_t    BAUD;         //SPI ���䲨��������, SPI �����ٶ� = ϵͳʱ�� / (2*(BAUD + 1)),��СΪ3

   uint8_t    BITSIZE;      //�ֽڳ��ȼĴ�����8-16
}SPI_InitTypeDef;

#define SPI_FIRSTSEND_LSB 1
#define SPI_FIRSTSEND_MSB 0

#define SPI_DMA_ENABLE  0
#define SPI_DMA_DISABLE 1

/*�ж�ʹ�ܶ���*/
#define SPI_IRQEna_Enable              BIT7            //SPI Interrupt Enable
#define SPI_IRQEna_TranDone            BIT6            //Transmit Done IRQ
#define SPI_IRQEna_SSErr               BIT5            //SS Signal Error IRQ
#define SPI_IRQEna_DataOver            BIT4            //Transmit Data Over Flow IRQ

/*�жϱ�־����*/
#define SPI_IF_TranDone                BIT2            //Transmit Done IF
#define SPI_IF_SSErr                   BIT1            //SS Signal Error IF
#define SPI_IF_DataOver                BIT0            //Transmit Data Over Flow IF

void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct);

uint8_t SPI_GetIRQFlag(SPI_TypeDef *SPIx);

void    SPI_SendData(SPI_TypeDef *SPIx, uint8_t n);
uint8_t SPI_ReadData(SPI_TypeDef *SPIx);
#endif /*__snr8503x_SPI_H */

/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
