/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_sys.c
 * �ļ���ʶ��
 * ����ժҪ�� SYS������������
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 2021��11��09��
 *
 *******************************************************************************/
#include "snr8503x_sys.h"
#include "snr8503x.h"


/*******************************************************************************
 �������ƣ�    void SYS_Init(SYS_InitTypeDef* SYS_InitStruct)
 ����������    SYSģ���ʼ������
 �����ı�    ��
 ���������    SYS_InitTypeDef* SYS_InitStruct
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li              ����
 *******************************************************************************/
void SYS_Init(SYS_InitTypeDef* SYS_InitStruct)
{
    uint32_t tmp1;

    SYS_WR_PROTECT = 0x7A83;    //���ϵͳ�Ĵ���д����
    tmp1 = SYS_AFE_REG0;
    tmp1 &= 0x7FFF;
    tmp1 |= (SYS_InitStruct->PLL_SrcSel << 15);
    SYS_AFE_REG0 = tmp1;
    SYS_CLK_CFG = SYS_InitStruct->PLL_DivSel + (SYS_InitStruct->PLL_ReDiv << 8);
    
    SYS_CLK_DIV0 = SYS_InitStruct->Clk_DivI2C;
    SYS_CLK_DIV2 = SYS_InitStruct->Clk_DivUART;
    SYS_CLK_FEN = SYS_InitStruct->Clk_FEN;
    SYS_WR_PROTECT = 0;
}

/*******************************************************************************
 �������ƣ�    void SYS_StructInit(SYS_InitTypeDef* SYS_InitStruct)
 ����������    SYS�ṹ���ʼ��
 �����ı�    ��
 ���������    SYS_InitTypeDef* SYS_InitStruct
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li              ����
 *******************************************************************************/
void SYS_StructInit(SYS_InitTypeDef* SYS_InitStruct)
{
    SYS_InitStruct -> PLL_SrcSel  = SYS_PLLSRSEL_RCH;
    SYS_InitStruct -> PLL_DivSel  = 0xFF;
    SYS_InitStruct -> PLL_ReDiv   = SYS_PLLREDIV_1;
                                  
    SYS_InitStruct -> Clk_DivI2C  = SYS_Clk_SPIDiv1;
    SYS_InitStruct -> Clk_DivUART = SYS_Clk_UARTDiv1;
    SYS_InitStruct -> Clk_FEN     = 0;
}

/*******************************************************************************
 �������ƣ�    void SYS_ClearRst(void)
 ����������    SYS�����λ��־
 �����ı�    ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ���ڸ�λ��¼�����ڵ���ʱ�������ִ�������Ҫһ��ʱ�䣬��Ӧ�������������¼״̬
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li              ����
 *******************************************************************************/
void SYS_ClearRst(void)
{
    AON_EVT_RCD = 0xCA40;
}

/*******************************************************************************
 �������ƣ�    uint32_t SYS_GetRstSource(void)
 ����������    ���SYS��λԴ�ź�
 �����ı�    ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li              ����
 *******************************************************************************/
uint32_t SYS_GetRstSource(void)
{
    return AON_EVT_RCD;
}

/*******************************************************************************
 �������ƣ�    void SYS_ModuleClockCmd(uint32_t nModule, FuncState state)
 ����������    ģ��ʱ��ʹ�ܺ�ֹͣ
 �����ı�    ��
 ���������    uint32_t nModule����Ӧ��ģ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li              ����
 *******************************************************************************/
void SYS_ModuleClockCmd(uint32_t nModule, FuncState state)
{
    SYS_WR_PROTECT = 0x7A83;    //���ϵͳ�Ĵ���д����
    if (state != DISABLE)
    {
        SYS_CLK_FEN |= nModule;
    }
    else
    {
        SYS_CLK_FEN &= ~nModule;
    }
    SYS_WR_PROTECT = 0;
}

/*******************************************************************************
 �������ƣ�    void SYS_AnalogModuleClockCmd(uint32_t nModule, FuncState state)
 ����������    ģ��ģ��ʹ�ܺ�ֹͣ
 �����ı�    ��
 ���������    uint32_t nModule����Ӧ��ģ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    ģ�ⲿ��ʱ����ʹ�ܣ�PGA��ADC��DAC
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li              ����
 *******************************************************************************/
void SYS_AnalogModuleClockCmd(uint32_t nModule, FuncState state)
{
    SYS_WR_PROTECT = 0x7A83;    //���ϵͳ�Ĵ���д����
    
    if (state == ENABLE)
    {
        if(nModule & SYS_AnalogModule_BGP)
        {//BGP������ģ�鼫���෴
            SYS_AFE_REG0 &= ~SYS_AnalogModule_BGP;
            nModule &= ~SYS_AnalogModule_BGP;
        }
        SYS_AFE_REG0 |= nModule;
    }
    else
    {
        if(nModule & SYS_AnalogModule_BGP)
        {//BGP������ģ�鼫���෴
            SYS_AFE_REG0 |= SYS_AnalogModule_BGP;
            nModule |= SYS_AnalogModule_BGP;
        }
        SYS_AFE_REG0 &= ~nModule;
    }
    SYS_WR_PROTECT = 0;
}

/*******************************************************************************
 �������ƣ�    void SYS_SoftResetModule(uint32_t nModule)
 ����������    ģ����λ
 �����ı�    ��
 ���������    uint32_t nModule����Ӧ��ģ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li              ����
 *******************************************************************************/
void SYS_SoftResetModule(uint32_t nModule)
{
    SYS_WR_PROTECT = 0x7A83;    //���ϵͳ�Ĵ���д����
    SYS_SFT_RST = nModule;
    SYS_SFT_RST = 0;
    SYS_WR_PROTECT = 0;
}
/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
