/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_gpio.c
 * �ļ���ʶ��
 * ����ժҪ�� GPIO������������
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 2021/11/10
 *
 *******************************************************************************/
#include "snr8503x_gpio.h"
#include "snr8503x.h"

/*******************************************************************************
 �������ƣ�    void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
 ����������    GPIO��ʼ��
 �����ı�    ��
 ���������    GPIOx:GPIO����, GPIO_InitStruct:GPIO��ʼ���ṹ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 *******************************************************************************/
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
{
    uint32_t pinpos = 0x00, pos = 0x00, currentpin = 0x00, tempreg = 0x00;

    /*-------------------------- Configure the port pins -----------------------*/
    for (pinpos = 0x00; pinpos < 0x10; pinpos++)
    {
        pos = ((uint32_t)0x01) << pinpos;

        /* Get the port pins position */
        currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
        if (currentpin == pos)
        {
            if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN)
            {
                tempreg = GPIOx->PIE; /*ʹ������*/
                tempreg |= (BIT0 << pinpos);
                GPIOx->PIE = tempreg;

                tempreg = GPIOx->POE; /*��ֹ���*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->POE = tempreg;
            }
            else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT)
            {
                tempreg = GPIOx->PIE; /*��ֹ����*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->PIE = tempreg;

                tempreg = GPIOx->POE; /*ʹ�����*/
                tempreg |= (BIT0 << pinpos);
                GPIOx->POE = tempreg;
            }
            else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_ANA)
            {
                tempreg = GPIOx->POE; /*��ֹ���*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->POE = tempreg;
            }

            if (GPIO_InitStruct->GPIO_PuPd == GPIO_PuPd_UP)
            {
                tempreg = GPIOx->PUE;
                tempreg |= (BIT0 << pinpos);
                GPIOx->PUE = tempreg;
            }
            else if (GPIO_InitStruct->GPIO_PuPd == GPIO_PuPd_DOWN)
            {
            }
            else if (GPIO_InitStruct->GPIO_PuPd == GPIO_PuPd_NOPULL)
            {
                tempreg = GPIOx->PUE;
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->PUE = tempreg;
            }

            tempreg = GPIOx->PODE;
            if (GPIO_InitStruct->GPIO_PODEna == (uint32_t)ENABLE)
            {
                tempreg |= (BIT0 << pinpos);
            }
            else
            {
                tempreg &= ~(BIT0 << pinpos);
            }
            GPIOx->PODE = tempreg;
        }
    }
}

/*******************************************************************************
 �������ƣ�    void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
 ����������    GPIO�ṹ���ʼ��
 �����ı�    ��
 ���������    GPIO_InitStruct:GPIO��ʼ���ṹ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 *******************************************************************************/
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct)
{
    GPIO_InitStruct->GPIO_Pin    = GPIO_Pin_NONE;
    GPIO_InitStruct->GPIO_Mode   = GPIO_Mode_IN;
    GPIO_InitStruct->GPIO_PuPd   = GPIO_PuPd_NOPULL;
    GPIO_InitStruct->GPIO_PODEna = DISABLE;
}

/*******************************************************************************
 �������ƣ�    uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
 ����������    ��ȡGPIO��ָ��Pin������ֵ
 �����ı�    ��
 ���������    GPIOx:GPIO����, GPIO_Pin:ָ����Pin
 ���������    ��
 �� �� ֵ��    ָ��Pin������ֵ
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 *******************************************************************************/
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;
    if ((GPIOx->PDI & GPIO_Pin) != 0)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/*******************************************************************************
 �������ƣ�    uint32_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
 ����������    ��ȡGPIO����������
 �����ı�    ��
 ���������    GPIOx:GPIO����
 ���������    ��
 �� �� ֵ��    ��������
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 *******************************************************************************/
uint32_t GPIO_ReadInputData(GPIO_TypeDef *GPIOx)
{
    return GPIOx->PDI;
}

/*******************************************************************************
 �������ƣ�    uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
 ����������    ��ȡGPIO��ָ��Pin�����ֵ
 �����ı�    ��
 ���������    GPIOx:GPIO����, GPIO_Pin:ָ����Pin
 ���������    ��
 �� �� ֵ��    ָ��Pin�����ֵ
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 *******************************************************************************/
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;
    if ((GPIOx->PDO & GPIO_Pin) != 0)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/*******************************************************************************
 �������ƣ�    uint32_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
 ����������    ��ȡGPIO�ĵ�ǰ�������
 �����ı�    ��
 ���������    GPIOx:GPIO����
 ���������    ��
 �� �� ֵ��    �������
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 *******************************************************************************/
uint32_t GPIO_ReadOutputData(GPIO_TypeDef *GPIOx)
{
    return GPIOx->PDO;
}

/*******************************************************************************
 �������ƣ�    void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
 ����������    GPIOָ��Pin��1
 �����ı�    ��
 ���������    GPIOx:GPIO����, GPIO_Pin:ָ����Pin
 ���������    ��
 �� �� ֵ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 *******************************************************************************/
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->BSRR = GPIO_Pin;
}

/*******************************************************************************
 �������ƣ�    void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
 ����������    GPIOָ��Pin��0
 �����ı�    ��
 ���������    GPIOx:GPIO����, GPIO_Pin:ָ����Pin
 ���������    ��
 �� �� ֵ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 *******************************************************************************/
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->BRR = GPIO_Pin;
}

/*******************************************************************************
 �������ƣ�    void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t BitVal)
 ����������    ��GPIOָ����Pinд������
 �����ı�    ��
 ���������    GPIOx:GPIO����, GPIO_Pin:ָ����Pin, BitVal:д���Bitֵ
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 *******************************************************************************/
void GPIO_WriteBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
    if (BitVal != Bit_RESET)
    {
        GPIOx->BSRR = GPIO_Pin;
    }
    else
    {
        GPIOx->BRR = GPIO_Pin;
    }
}

/*******************************************************************************
 �������ƣ�    void GPIO_Write(GPIO_TypeDef* GPIOx, uint32_t Val)
 ����������    ��GPIOд������
 �����ı�    ��
 ���������    GPIOx:GPIO����, Val:д���ֵ
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 *******************************************************************************/
void GPIO_Write(GPIO_TypeDef *GPIOx, uint32_t Val)
{
    GPIOx->PDO = Val;
}

/*******************************************************************************
 �������ƣ�    void GPIO_PadAFConfig(GPIO_TypeDef* GPIOx, uint32_t GPIO_PadSource, uint32_t GPIO_AF)
 ����������    GPIO����ѡ��
 �����ı�    ��
 ���������    GPIOx:GPIO����, GPIO_PadSource:ָ����PadSource, GPIO_AF:ָ���Ĺ���
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 *******************************************************************************/
void GPIO_PinAFConfig(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint32_t GPIO_AF)
{
    uint32_t temp;
    switch (GPIO_PinSource)
    {
    /*F3210*/
    case 0:
    {
        temp = GPIOx->F3210 & 0xFFF0;  /*get F321*/
        GPIOx->F3210 = temp + GPIO_AF; /*F321 + F0*/
        break;
    }
    case 1:
    {
        temp = GPIOx->F3210 & 0xFF0F;
        GPIOx->F3210 = temp + (GPIO_AF << 4);
        break;
    }
    case 2:
    { /* 2020.8.13 Repair bug HL */
        temp = GPIOx->F3210 & 0xF0FF;
        GPIOx->F3210 = temp + (GPIO_AF << 8);
        break;
    }
    case 3:
    {
        temp = GPIOx->F3210 & 0x0FFF;
        GPIOx->F3210 = temp + (GPIO_AF << 12);
        break;
    }
    /*F7654*/
    case 4:
    {
        temp = GPIOx->F7654 & 0xFFF0;
        GPIOx->F7654 = temp + GPIO_AF;
        break;
    }
    case 5:
    {
        temp = GPIOx->F7654 & 0xFF0F;
        GPIOx->F7654 = temp + (GPIO_AF << 4);
        break;
    }
    case 6:
    {
        temp = GPIOx->F7654 & 0xF0FF;
        GPIOx->F7654 = temp + (GPIO_AF << 8);
        break;
    }
    case 7:
    {
        temp = GPIOx->F7654 & 0x0FFF;
        GPIOx->F7654 = temp + (GPIO_AF << 12);
        break;
    }
    /*FBA98*/
    case 8:
    {
        temp = GPIOx->FBA98 & 0xFFF0;
        GPIOx->FBA98 = temp + GPIO_AF;
        break;
    }
    case 9:
    {
        temp = GPIOx->FBA98 & 0xFF0F;
        GPIOx->FBA98 = temp + (GPIO_AF << 4);
        break;
    }
    case 10:
    {
        temp = GPIOx->FBA98 & 0xF0FF;
        GPIOx->FBA98 = temp + (GPIO_AF << 8);
        break;
    }
    case 11:
    {
        temp = GPIOx->FBA98 & 0x0FFF;
        GPIOx->FBA98 = temp + (GPIO_AF << 12);
        break;
    }
    /*FFEDC*/
    case 12:
    {
        temp = GPIOx->FFEDC & 0xFFF0;
        GPIOx->FFEDC = temp + GPIO_AF;
        break;
    }
    case 13:
    {
        temp = GPIOx->FFEDC & 0xFF0F;
        GPIOx->FFEDC = temp + (GPIO_AF << 4);
        break;
    }
    case 14:
    {
        temp = GPIOx->FFEDC & 0xF0FF;
        GPIOx->FFEDC = temp + (GPIO_AF << 8);
        break;
    }
    case 15:
    {
        temp = GPIOx->FFEDC & 0x0FFF;
        GPIOx->FFEDC = temp + (GPIO_AF << 12);
        break;
    }
    default:
        break;
    }
}
/*******************************************************************************
 �������ƣ�    void EXTI_Trigger_Config(GPIO_TypeDef* GPIOx, uint32_t GPIO_PadSource, uint16_t EXTI_Trigger)
 ����������    GPIO�ⲿ��������ѡ��
 �����ı�    ��
 ���������    GPIOx:GPIO����, GPIO_PadSource:ָ����PadSource, EXTI_Trigger:ָ���Ĵ�������
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ��Ҫ��EXTI_IE����Ч
              �ο�  �û��ֲ�   �� 15-19 GPIO �ж���Դ�ֲ���
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 *******************************************************************************/
void EXTI_Trigger_Config(GPIO_TypeDef *GPIOx, uint32_t GPIO_PinSource, uint16_t EXTI_Trigger)
{
    if(GPIOx == GPIO0)
    {
        switch (GPIO_PinSource)
        {
            case 0:
                EXTI->CR0 = (EXTI->CR0 & 0xfffc) | (EXTI_Trigger);
                break;
            case 2:
                EXTI->CR0 = (EXTI->CR0 & 0xfff3) | (EXTI_Trigger << 2);
                break;
            case 4:
                EXTI->CR0 = (EXTI->CR0 & 0xffcf) | (EXTI_Trigger << 4);
                break;
            case 5:
                EXTI->CR0 = (EXTI->CR0 & 0xff3f) | (EXTI_Trigger << 6);
                break;
            case 6:
                EXTI->CR0 = (EXTI->CR0 & 0xfcff) | (EXTI_Trigger << 8);
                break;
            case 7:
                EXTI->CR0 = (EXTI->CR0 & 0xf3ff) | (EXTI_Trigger << 10);
                break;
            case 8:
                EXTI->CR0 = (EXTI->CR0 & 0xcfff) | (EXTI_Trigger << 12);
                break;
            case 9:
                EXTI->CR0 = (EXTI->CR0 & 0x3fff) | (EXTI_Trigger << 14);
                break;
            case 14:
                EXTI->CR1 = (EXTI->CR0 & 0xfffc) | (EXTI_Trigger);
                break;
            case 15:
                EXTI->CR1 = (EXTI->CR0 & 0xfff3) | (EXTI_Trigger << 2);
                break;
            default:break;

        }
    }
    if(GPIOx == GPIO1)
    {
        switch (GPIO_PinSource)
        {
            case 4:
                EXTI->CR1 = (EXTI->CR0 & 0xffcf) | (EXTI_Trigger << 4);
                break;
            case 5:
                EXTI->CR1 = (EXTI->CR0 & 0xff3f) | (EXTI_Trigger << 6);
                break;
            case 6:
                EXTI->CR1 = (EXTI->CR0 & 0xfcff) | (EXTI_Trigger << 8);
                break;
            case 7:
                EXTI->CR1 = (EXTI->CR0 & 0xf3ff) | (EXTI_Trigger << 10);
                break;
            case 8:
                EXTI->CR1 = (EXTI->CR0 & 0xcfff) | (EXTI_Trigger << 12);
                break;
            case 9:
                EXTI->CR1 = (EXTI->CR0 & 0x3fff) | (EXTI_Trigger << 14);
                break;
            default:break;
        }
    }
}

/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
