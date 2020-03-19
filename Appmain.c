/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱i.MX RT1052核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0，龙邱开源代码，仅供参考，后果自负
【最后更新】2019年03月13日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR8.20.1及以上版本
【Target 】 i.MX RT1052
【Crystal】 24.000Mhz
【ARM PLL】 1200MHz
【SYS PLL】 528MHz
【USB PLL】 480MHz
================================================
下载及调试模式：0010
下载      模式：0001
运行      模式：0010
------------------------------------------------
用JLINKV9/OB及以上版本可以下载SDRAM和QSPI FLASH;
用LQDAPLINKV3可以下载SDRAM和QSPI FLASH;
------------------------------------------------
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

int main(void)
{        
    BOARD_ConfigMPU();                   /* 初始化内存保护单元 */      
    BOARD_InitSDRAMPins();               /* SDRAM初始化 */
    BOARD_BootClockRUN();                /* 初始化开发板时钟 */ 
    LQ_GPT_Init();                       /* 延时函数初始化 GPT计数函数初始化*/
//    BOARD_InitDEBUG_UARTPins();          /* UART调试口管脚复用初始化  */
//    BOARD_InitDebugConsole();            /* UART调试口初始化 可以使用 PRINTF函数 */
    LED_Init();                          /* 初始化核心板和开发板上的LED接口 */
    LQ_UART_Init(LPUART1, 115200);       /* 串口1初始化 可以使用 printf函数 */
    systime.init();                      /* 开启systick定时器 */
    /*设置中断优先级组  0: 0个抢占优先级16位个子优先级 
     *1: 2个抢占优先级 8个子优先级 2: 4个抢占优先级 4个子优先级 
     *3: 8个抢占优先级 2个子优先级 4: 16个抢占优先级 0个子优先级
     */
    /* 配置优先级组 2: 4个抢占优先级 4个子优先级 */
    NVIC_SetPriorityGrouping(0x07 - 2); 
    delayms(50);
    
    /****************打印系统时钟******************/
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
//电机1： 使用 L5  M5   电机2：使用A8  A9  电机3：使用 B9 C9  电机4：A10 J1
//-----------------------------------------------------------------------------------------      
    Test_Motor();                         //测试电机
}                                                                                  
                                                                                   
                                                                                    
                                                                                    
                                                                                  