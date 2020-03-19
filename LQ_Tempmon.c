/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱i.MX RT1052核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0，龙邱开源代码，仅供参考，后果自负
【最后更新】2019年03月18日
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
                      
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】温度中断服务函数  
【软件版本】V1.0
【最后更新】2019年03月13日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void TEMP_LOW_HIGH_IRQHandler(void)
{

/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】紧急温度中断服务函数  
【软件版本】V1.0
【最后更新】2019年03月13日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void TEMP_PANIC_IRQHandler(void)
{

}

void Test_Tempmon(void)
{
    float temperature = 0U; 
    tempmon_config_t config;
    

    printf("芯片温度测试例程. \r\n");
    

    /* 默认的测量频率 
    config->frequency = 0x03U;
     默认高报警温度
    config->highAlarmTemp = 40U;
     默认紧急报警温度 
    config->panicAlarmTemp = 90U;
     默认低报警温度 
    config->lowAlarmTemp = 20U;*/
    TEMPMON_GetDefaultConfig(&config);

    TEMPMON_Init(TEMPMON, &config);
    TEMPMON_StartMeasure(TEMPMON);

    /* Get temperature */
    temperature = TEMPMON_GetCurrentTemperature(TEMPMON);

    printf("芯片当前温度： %.1f ℃. \r\n", temperature);

    while (1)
    {
   
        delayms(10000);
        /* Get current temperature */
        temperature = TEMPMON_GetCurrentTemperature(TEMPMON);
        printf("芯片当前温度： %.1f ℃. \r\n", temperature);
    }
    

}




