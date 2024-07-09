/*******************************************************************************
 * ��Ȩ���� (C)2021, SNANER SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� snr8503x_flash.c
 * �ļ���ʶ��
 * ����ժҪ�� Flash������������
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ�   Li
 * ������ڣ� 2021��10��14��
 *
 *
 *******************************************************************************/
#include "basic.h"
#include "snr8503x.h"

volatile u32 erase_flag = 0;
volatile u32 progm_flag = 0;

/*******************************************************************************
 �������ƣ�    void EraseSector(unsigned long adr, unsigned long nvr)
 ����������    Flash��������������
 �����ı�    ��
 ���������    adr��       ������ַ  (һ������512�ֽ�)             
                    erase_flag�����ú���ǰ���븳ֵ0x9A0D361F������ִ�в����������������ܷ�
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/10/14    V1.0           Li               ����
 *******************************************************************************/
void EraseSector(u32 adr)
{
  u32 key1, key2, key3;

  key1 = 0x0;
  key2 = 0x0;
  key3 = 0x0;
  if (erase_flag == 0x9A0D361F)
  { //get flash_cfg addr
    SYS_FLSE = 0x8FCA;
    key1 = 0xB00C060A;
    key2 = 0x2A003015;
    key3 = erase_flag ^ key1 ^ key2;
    REG32(key3) &= ~0x80008000;
    FLASH_ADDR = adr;
    REG32(key3) |= (0x80000000);
    key1 = 0x0;
    key2 = 0x0;
    key3 = 0x0;
  }

  if (erase_flag == 0x9A0D361F)
  { //get flash_erase addr
    SYS_FLSE = 0x8FCA;
    key1 = 0xB001341A;
    key2 = 0x2A0D0215;
    key3 = erase_flag ^ key1 ^ key2;
    REG32(key3) = 0x7654DCBA; //trig sector erase, FLASH_ERASE
    FLASH_CFG &= ~0x80000000;
    erase_flag = 0x00000000;
    key1 = 0x0;
    key2 = 0x0;
    key3 = 0x0;
  }
  SYS_FLSE = 0x0;
  FLASH_CFG &= ~0x80000000;
  erase_flag = 0x00000000;
  key1 = 0x0;
  key2 = 0x0;
  key3 = 0x0;
}

/*******************************************************************************
 �������ƣ�    ProgramPage(unsigned long adr, unsigned long sz, unsigned char *buf)
 ����������    Flash��̲���
 �����ı�    ��
 ���������    adr��������ַ  
               sz : ����ֽ�����(0~512�ֽ�) 
               buf: Ҫ��̵���������ָ�룻            
               erase_flag�����ú���ǰ���븳ֵ0x9AFDA40C������ִ�б�̣������������ܷ�
 ���������    ��
 �� �� ֵ��    1����̳ɹ���  0: ���ʧ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/10/14    V1.0           Li               ����
 *******************************************************************************/

int ProgramPage(u32 adr, u32 sz, u8 *buf)
{
  /* Add your Code */
  volatile u32 Addr, size;
  volatile u8 *p;
  volatile u8 t_rlt = 1;
  u32 key1, key2, key3;
  key1 = 0x0;
  key2 = 0x0;
  key3 = 0x0;

  if (progm_flag == 0x9AFDA40C)
  {
    SYS_FLSP = 0x8F35;
    //get flash_cfg addr
    key1 = 0x6A5C040F;
    key2 = 0xF0A0A003;
    key3 = progm_flag ^ key1 ^ key2;
    REG32(key3) &= ~0x80008000;
    FLASH_ADDR = adr;
    REG32(key3) |= (0x08000000);
    progm_flag = 0;
    key1 = 0x0;
    key2 = 0x0;
    key3 = 0x0;

    p = buf;
    size = (sz + 3) & ~3; // align the word
    Addr = adr;
    while (size)
    {
      FLASH_ADDR = (Addr & ~0x00000003);                                        // address alignment
      FLASH_WDATA = *p + (*(p + 1) << 8) + (*(p + 2) << 16) + (*(p + 3) << 24); // write data to flash

      p += 4;
      size -= 4; // Go to next word
      Addr += 4;
    }

    p = buf;
    size = (sz + 3) & ~3; // align the word
    Addr = adr;
    while (size)
    {
      u32 t_RData;
      FLASH_ADDR = (Addr & ~0x00000003); // address alignment
      t_RData = *p + (*(p + 1) << 8) + (*(p + 2) << 16) + (*(p + 3) << 24);
      if (t_RData != FLASH_RDATA)
      {
        t_rlt = 0;
      }

      p += 4;
      size -= 4;
      Addr += 4;
    }
  }
  SYS_FLSP = 0x0;
  FLASH_CFG &= ~0x08000800;
  key1 = 0x0;
  key2 = 0x0;
  key3 = 0x0;
  progm_flag = 0;
  return (t_rlt);
}

/*******************************************************************************
 �������ƣ�    void MCPWM0_RegUpdate(void)
 ����������    ��ȡFLASH���ݺ���
 ���������    adr��Ҫ��ȡ���ݵĵ�ַ  
               nvr��Ϊ0����ȡMAIN���ݣ�Ϊ1����ȡNVR����
 ���������    ��ȡ������ֵ
 �� �� ֵ��    data
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/10/14    V1.0            Li              ����
 *******************************************************************************/
u32 Read_Flash(uint32_t adr)
{
  uint32_t data;
  FLASH_CFG &= ~BIT11; //�ָ�MIAN����
  FLASH_ADDR = adr;
  data = FLASH_RDATA;
  return data;
}

/*******************************************************************************
 �������ƣ�    void MCPWM0_RegUpdate(void)
 ����������    ��ȡFLASH���ַ���ݺ���
 ���������    adr��Ҫ��ȡ���ݵĵ�ַ
               nvr��Ϊ0����ȡMAIN���ݣ�Ϊ1����ȡNVR����
							 buf:��ȡ���ݴ洢�ĵ�ַ
               sz :��ȡsz����
 ���������    ��ȡ������ֵ
 �� �� ֵ��    data
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2021/10/14    V1.0           Li               ����
 *******************************************************************************/
void Read_More_Flash(u32 adr, u32 sz, u32 *buf)
{
  volatile u32 Addr = 0;
  volatile u32 size = 0;
  volatile u32 *p;
  size = sz;
  Addr = adr;
  p = buf;
  while (size)
  {
    *p = Read_Flash(Addr);
    while (!(FLASH_READY & BIT0))
      ;
    size -= 1;
    Addr += 4;
    p += 1;
  }
}
/************************ (C) COPYRIGHT SNANER SEMICONDUCTOR *****END OF FILE****/
