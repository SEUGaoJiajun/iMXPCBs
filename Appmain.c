/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2019��03��13��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR8.20.1�����ϰ汾
��Target �� i.MX RT1052
��Crystal�� 24.000Mhz
��ARM PLL�� 1200MHz
��SYS PLL�� 528MHz
��USB PLL�� 480MHz
================================================
���ؼ�����ģʽ��0010
����      ģʽ��0001
����      ģʽ��0010
------------------------------------------------
��JLINKV9/OB�����ϰ汾��������SDRAM��QSPI FLASH;
��LQDAPLINKV3��������SDRAM��QSPI FLASH;
------------------------------------------------
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

void delayms(uint32_t ms)
{
    uint32_t i,j;
    
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 200000; j++)//600M--1ms
        __NOP();//asm("NOP");   
    }
    return ;
}
void delayus(uint32_t us) 
{
    uint32_t i,j;
    
    for (i = 0; i < us; i++)
    {
        for (j = 0; j < 290; j++)//600M--1us
        __NOP();//asm("NOP");   
    }
    return ;
} 

int main(void)
{        
    BOARD_ConfigMPU();                   /* ��ʼ���ڴ汣����Ԫ */      
    BOARD_InitSDRAMPins();               /* SDRAM��ʼ�� */
    BOARD_BootClockRUN();                /* ��ʼ��������ʱ�� */ 
//-----------------------------------------------------------------------------------------  
//  LED ��������  ����GPIO�����     
//-----------------------------------------------------------------------------------------
    Test_LED();                                  
}
