/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱i.MX RT1052核心板-智能车板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2018年2月1日
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
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

#define WDOG_WCT_INSTRUCITON_COUNT (256U)



//看门狗超时时间，实际时间为(time+1)*0.5s
void LQ_WDOG_Init(WDOG_Type *base, uint8_t time)
{
    wdog_config_t config;
    CLOCK_EnableClock(kCLOCK_Wdog1); 			//使能看门狗时钟
    CLOCK_EnableClock(kCLOCK_Wdog2); 			//使能看门狗时钟
    /*
    * wdogConfig->enableWdog = true;            //使能看门狗
    * wdogConfig->workMode.enableWait = true;   //等待模式下仍然开启
    * wdogConfig->workMode.enableStop = false;  //停止模式下关闭
    * wdogConfig->workMode.enableDebug = false; //debug模式关闭
    * wdogConfig->enableInterrupt = false;      //不使能中断
    * wdogConfig->enablePowerdown = false;      //
    * wdogConfig->resetExtension = flase;
    * wdogConfig->timeoutValue = 0xFFU;         //设置喂狗时间
    * wdogConfig->interruptTimeValue = 0x04u;   //在喂狗前 多长时间进入中断 方便喂狗
    */
    WDOG_GetDefaultConfig(&config);             //获取默认配置参数
    config.timeoutValue = time;                 //看门狗超时时间，实际时间为(timeoutValue+1)*0.5s
    WDOG_Init(base, &config);
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【功能说明】测试看门狗功能
【软件版本】V1.0
【最后更新】2018年11月24日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_WDOG(void)
{
    
    LQ_WDOG_Init(WDOG1, 9);
    printf("--- Start Wdog test ---\r\n");
    
    for (uint32_t i = 0; i < 10; i++)
    {
        WDOG_Refresh(WDOG1);     //喂狗
        printf("--- Refresh wdog %d time ---\r\n", i + 1);
    }

    printf("\r\nEnd of Wdog example!\r\n");
    while (1)
    {
    }
}
