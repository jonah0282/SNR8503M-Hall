/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_cmp.c
 * �ļ���ʶ��
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 2021��11��09��
 *
 *******************************************************************************/
 #include "snr8503x_cmp.h"
 #include "snr8503x_sys.h"
/*******************************************************************************
 �������ƣ�    void cmp_Init(CMP_InitTypeDef *this)
 ����������    �Ƚ�����ʼ��
 ���������    this��I2C���ýṹ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 2021/11/17    V1.1           Li            ����CMP�ź���Դѡ��
 *******************************************************************************/
void CMP_Init(CMP_InitTypeDef *this)
{
    SYS_ModuleClockCmd(SYS_Module_CMP,ENABLE);

    CMP -> IE      = (this -> CMP1_RE           <<  9) | (this -> CMP0_RE           <<  8) |
                     (this -> CMP1_IE           <<  1) | (this -> CMP0_IE);            
    CMP -> TCLK    = (this -> FIL_CLK10_DIV16   <<  4) | (this -> CLK10_EN          <<  3) |
                     (this -> FIL_CLK10_DIV2);                                         
    CMP -> CFG     = (this -> CMP1_W_PWM_POL    <<  7) | (this -> CMP1_IRQ_TRIG     <<  6) |
                     (this -> CMP1_IN_EN        <<  5) | (this -> CMP1_POL          <<  4) |
                     (this -> CMP0_W_PWM_POL    <<  3) | (this -> CMP0_IRQ_TRIG     <<  2) |
                     (this -> CMP0_IN_EN        <<  1) | (this -> CMP0_POL);           
    CMP -> BLCWIN  = (this -> CMP1_CHN3P_WIN_EN <<  7) | (this -> CMP1_CHN2P_WIN_EN <<  6) |
                     (this -> CMP1_CHN1P_WIN_EN <<  5) | (this -> CMP1_CHN0P_WIN_EN <<  4) |
                     (this -> CMP0_CHN3P_WIN_EN <<  3) | (this -> CMP0_CHN2P_WIN_EN <<  2) |
                     (this -> CMP0_CHN1P_WIN_EN <<  1) | (this -> CMP0_CHN0P_WIN_EN);
    SYS_WR_PROTECT = 0x7A83;
    SYS_AFE_REG1   = (SYS_AFE_REG1 & (BIT15 | BIT6 | BIT1 | BIT0)) |
                     (this -> CMP1_SELP         << 12) | (this -> CMP_FT            << 11) |
                     (this -> CMP0_SELP         <<  8) | (this -> CMP_HYS           <<  7) |
                     (this -> CMP1_SELN         <<  4) | (this -> CMP0_SELN         <<  2);
    SYS_WR_PROTECT = 0;
    CMP -> IF = 3;
}
/*******************************************************************************
 �������ƣ�    void CMP_StructInit(CMP_InitTypeDef *this)
 ����������    CMP���ýṹ���ʼ��
 ���������    this CMP���ýṹ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Li            ����
 2021/11/17    V1.1           Li            ����CMP�ź���Դ��ʼ��
 *******************************************************************************/
void CMP_StructInit(CMP_InitTypeDef *this)
{
    // �Ƚ���IO�˲�
    this -> FIL_CLK10_DIV16   = 0 ;                     // �Ƚ��� 1/0 �˲�
    this -> CLK10_EN          = ENABLE ;                // �Ƚ��� 1/0 �˲�ʱ��ʹ��
    this -> FIL_CLK10_DIV2    = 0 ;                     // �Ƚ��� 1/0 �˲�ʱ�ӷ�Ƶ
    this -> CMP_FT            = ENABLE ;                // �Ƚ������ٱȽ�ʹ��
    this -> CMP_HYS           = CMP_HYS_20mV ;          // �Ƚ����ز�ѡ��
        
    //�Ƚ���1      
    this -> CMP1_RE           = DISABLE ;               // �Ƚ��� 1 DMA ����ʹ��
    this -> CMP1_IE           = DISABLE ;               // �Ƚ��� 1 �ж�ʹ��
    this -> CMP1_W_PWM_POL    = 0 ;                     // �Ƚ��� 1 ���� PWM �źż���ѡ��
    this -> CMP1_IRQ_TRIG     = DISABLE ;               // �Ƚ��� 1 ���ش���ʹ��
    this -> CMP1_IN_EN        = 0 ;                     // �Ƚ��� 1 �ź�����ʹ��
    this -> CMP1_POL          = 0 ;                     // �Ƚ��� 1 ����ѡ��
    this -> CMP1_SELP         = CMP1_SELP_CMP1_IP0 ;    // �Ƚ��� 1 �ź�����ѡ��
    this -> CMP1_SELN         = CMP1_SELN_CMP1_IN ;     // �Ƚ��� 1 �źŸ���ѡ��
    this -> CMP1_CHN3P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN3_P ͨ��ʹ�ܱȽ��� 1 ����
    this -> CMP1_CHN2P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN2_P ͨ��ʹ�ܱȽ��� 1 ����
    this -> CMP1_CHN1P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN1_P ͨ��ʹ�ܱȽ��� 1 ����
    this -> CMP1_CHN0P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN0_P ͨ��ʹ�ܱȽ��� 1 ����

    //�Ƚ���0
    this -> CMP0_IE           = DISABLE ;               // �Ƚ��� 0 �ж�ʹ��
    this -> CMP0_RE           = DISABLE ;               // �Ƚ��� 0 DMA ����ʹ��
    this -> CMP0_W_PWM_POL    = 0 ;                     // �Ƚ��� 0 ���� PWM �źż���ѡ��
    this -> CMP0_IRQ_TRIG     = DISABLE ;               // �Ƚ��� 0 ���ش���ʹ��
    this -> CMP0_IN_EN        = 0 ;                     // �Ƚ��� 0 �ź�����ʹ��
    this -> CMP0_POL          = 0 ;                     // �Ƚ��� 0 ����ѡ��
    this -> CMP0_SELP         = CMP0_SELP_CMP0_IP0 ;    // �Ƚ��� 0 �ź�����ѡ��
    this -> CMP0_SELN         = CMP0_SELN_CMP0_IN ;     // �Ƚ��� 0 �źŸ���ѡ��
    this -> CMP0_CHN3P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN3_P ͨ��ʹ�ܱȽ��� 0 ����
    this -> CMP0_CHN2P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN2_P ͨ��ʹ�ܱȽ��� 0 ����
    this -> CMP0_CHN1P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN1_P ͨ��ʹ�ܱȽ��� 0 ����
    this -> CMP0_CHN0P_WIN_EN = DISABLE ;               // MCPWM ģ�� CHN0_P ͨ��ʹ�ܱȽ��� 0 ����
}
/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
