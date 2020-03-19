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

int main(void)
{        
    BOARD_ConfigMPU();                   /* ��ʼ���ڴ汣����Ԫ */      
    BOARD_InitSDRAMPins();               /* SDRAM��ʼ�� */
    BOARD_BootClockRUN();                /* ��ʼ��������ʱ�� */ 
    LQ_GPT_Init();                       /* ��ʱ������ʼ�� GPT����������ʼ��*/
//    BOARD_InitDEBUG_UARTPins();          /* UART���ԿڹܽŸ��ó�ʼ��  */
//    BOARD_InitDebugConsole();            /* UART���Կڳ�ʼ�� ����ʹ�� PRINTF���� */
    LED_Init();                          /* ��ʼ�����İ�Ϳ������ϵ�LED�ӿ� */
    LQ_UART_Init(LPUART1, 115200);       /* ����1��ʼ�� ����ʹ�� printf���� */
    systime.init();                      /* ����systick��ʱ�� */
    /*�����ж����ȼ���  0: 0����ռ���ȼ�16λ�������ȼ� 
     *1: 2����ռ���ȼ� 8�������ȼ� 2: 4����ռ���ȼ� 4�������ȼ� 
     *3: 8����ռ���ȼ� 2�������ȼ� 4: 16����ռ���ȼ� 0�������ȼ�
     */
    /* �������ȼ��� 2: 4����ռ���ȼ� 4�������ȼ� */
    NVIC_SetPriorityGrouping(0x07 - 2); 
    delayms(50);
    
    /****************��ӡϵͳʱ��******************/
    printf("\r\n");
    printf("*****LQ_1052*****\r\n");
    printf("CPU:             %d Hz\r\n", CLOCK_GetFreq(kCLOCK_CpuClk));
    printf("AHB:             %d Hz\r\n", CLOCK_GetFreq(kCLOCK_AhbClk));
    printf("SEMC:            %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SemcClk));
    printf("SYSPLL:          %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllClk));
    printf("Video:           %d Hz\r\n", CLOCK_GetFreq(kCLOCK_VideoPllClk));
    printf("SYSPLLPFD0:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk));
    printf("SYSPLLPFD1:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd1Clk));
    printf("SYSPLLPFD2:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd2Clk));
    printf("SYSPLLPFD3:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd3Clk));
    printf("USB1PLL:          %d Hz\r\n", CLOCK_GetFreq(kCLOCK_Usb1PllClk));
    printf("USB1PLLPFD0:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_Usb1PllPfd0Clk));
    printf("USB1PLLPFD1:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_Usb1PllPfd1Clk));
    printf("USB1PLLPFD2:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_Usb1PllPfd2Clk));
    printf("USB1PLLPFD3:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_Usb1PllPfd3Clk));

//-----------------------------------------------------------------------------------------
//���1�� ʹ�� L5  M5   ���2��ʹ��A8  A9  ���3��ʹ�� B9 C9  ���4��A10 J1
//-----------------------------------------------------------------------------------------      
    Test_Motor();                         //���Ե��
}                                                                                  
                                                                                   
                                                                                    
                                                                                    
                                                                                  