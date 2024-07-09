/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_I2C.h
 * �ļ���ʶ��
 * ����ժҪ�� I2C������������ͷ�ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 2021��11��09��
 *
 *******************************************************************************/
#ifndef __snr8503x_I2C_H
#define __snr8503x_I2C_H
/* Includes ------------------------------------------------------------------*/
#include "snr8503x.h"
#include "basic.h"

//I2C_BUS_STATE   I2C����״̬
#define I2C_BUS_STATE_STT_ERR     BIT7   // ���ߴ���
#define I2C_BUS_STATE_LOST_ARB    BIT6   // �����ٲö�ʧ
#define I2C_BUS_STATE_STOP_EVT    BIT5   // STOP�¼���¼

#define I2C_BUS_STATE_ADDR_DATA   BIT3   // ���ڴ����ַ����

#define I2C_BUS_STATE_RX_ACK      BIT1   // ���յ�ACK��Ӧ
#define I2C_BUS_STATE_Done        BIT0   // �������

typedef struct
{
    __IO uint32_t ADDR;   // I2C��ַ�Ĵ���
    __IO uint32_t CFG;    // I2C���üĴ���
    __IO uint32_t SCR;    // I2C״̬�Ĵ���
    __IO uint32_t DATA;   // I2C���ݼĴ���
    __IO uint32_t MSCR;   // I2C��ģʽ�Ĵ���
    __IO uint32_t BCR;    // I2C������ƼĴ���
    __IO uint32_t BSIZE;  // I2C���䳤�ȼĴ���
} I2C_TypeDef;

typedef struct
{
    u32 ADDR_CMP_EN;       // I2C Ӳ����ַ�Ƚ�ʹ�ܿ���
    u32 ADDR;              // �����ڴ�ģʽ�£�I2C �豸Ӳ����ַ
    
    u32 IE;                // I2C �ж�ʹ���ź�
    u32 TC_IE;             // I2C ���ݴ�������ж�ʹ��
    u32 BUS_ERR_IE;        // I2C ���ߴ����¼��ж�ʹ���ź�
    u32 STOP_IE;           // I2C STOP �¼��ж�ʹ���ź�
    u32 NACK_IE;           // NACK �¼��ж�ʹ��
    
    u32 MST_MODE;          // I2C ��ģʽʹ���ź�
    u32 SLV_MODE;          // I2C ��ģʽʹ���ź�
    
    u32 ADDR_CMP_IE;       // Ӳ����ַƥ���ж�ʹ��
    u32 BUSRT_EN;          // I2C �����ݴ���ʹ��
    u32 SIZE;              // I2C ���ݴ��䳤��
}I2C_InitTypeDef;

void I2C_Init(I2C_InitTypeDef *);        // I2C��ʼ��
void I2C_StrutInit(I2C_InitTypeDef *);   // I2C���ýṹ���ʼ��

u8 Read_I2c_Bus_State(u16);            // ��I2C����״̬
void Clear_I2c_Bus_State(u16);          // I2C����״̬��λ

#endif /*__snr8503x_I2C_H */
/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
