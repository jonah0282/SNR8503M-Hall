/*******************************************************************************
 * ��Ȩ���� (C)2015, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_nvr.c
 * �ļ���ʶ�� ��У׼ֵ
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Li
 * ������ڣ� 2021��11��12��
 *
 *******************************************************************************/
 // Read_Trim�����ڳ�ʼ���Ĺ����е���
 // Read_Trim��ر�ȫ���ж�
unsigned int Read_Trim(unsigned int addr);              //��Ч��ַ��Χ((addr >= 0x00000190) && (addr <= 0x0000001FF)) || ((addr >= 0x0000024C) && (addr <= 0x000000258))
void Prog_Trim(unsigned int addr, unsigned int data);   //��Ч��ַ��Χ((addr >= 0x000001E0) && (addr <= 0x0000001FF))
/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
