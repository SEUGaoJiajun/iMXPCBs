/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱i.MX RT1052核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2019年3月13日
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

volatile uint16_t pitIsrCnt0 = 0;   //测试用的  volatile易变的，在中断里面会改变的变量定义时最好加上，告诉编译器不要优化，每次读取都从该变量的地址读取
volatile uint16_t pitIsrCnt1 = 0;  //测试用的  volatile易变的，在中断里面会改变的变量定义时最好加上，告诉编译器不要优化，每次读取都从该变量的地址读取
volatile uint16_t pitIsrCnt2 = 0;  //测试用的  volatile易变的，在中断里面会改变的变量定义时最好加上，告诉编译器不要优化，每次读取都从该变量的地址读取
volatile uint16_t pitIsrCnt3 = 0; //测试用的  volatile易变的，在中断里面会改变的变量定义时最好加上，告诉编译器不要优化，每次读取都从该变量的地址读取

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】PIT中断服务函数
【软件版本】V1.0
【最后更新】2019年03月13日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void PIT_IRQHandler(void)
{
    
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_0)&kPIT_TimerFlag)==kPIT_TimerFlag)  /* 判断哪个PIT通道发生中断.*/
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);    /* 清除标志位.*/
        /*用户可自行添加代码*/     
        pitIsrCnt0++;
//        LED_Ctrl(LED0, RVS);
    }
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_1)&kPIT_TimerFlag)==kPIT_TimerFlag)  /* 判断哪个PIT通道发生中断.*/
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_1, kPIT_TimerFlag);    /* 清除标志位.*/
        /*用户可自行添加代码*/
        pitIsrCnt1++;
    }
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_2)&kPIT_TimerFlag)==kPIT_TimerFlag)  /* 判断哪个PIT通道发生中断.*/
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_2, kPIT_TimerFlag);    /* 清除标志位.*/
        /*用户可自行添加代码*/        
        pitIsrCnt2++;
    }
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_3)&kPIT_TimerFlag)==kPIT_TimerFlag)  /* 判断哪个PIT通道发生中断.*/
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_3, kPIT_TimerFlag);    /* 清除标志位.*/
        /*用户可自行添加代码*/        
        pitIsrCnt3++;
    }
    
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】测试PIT定时中断
【软件版本】V1.0
【最后更新】2018年11月24日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_PIT(void)
{ 
    LED_Init();                           //初始化LED
    LQ_PIT_Init(kPIT_Chnl_2, 1000000);    //1000 000us 一次中断
    LQ_PIT_Init(kPIT_Chnl_3, 2000000);    //2000 000us 一次中断
    while (true)
    {
         if (pitIsrCnt2)
        {
            LED_Color(red);   //红灯 
            pitIsrCnt2=0;
        }
         if (pitIsrCnt3)
        {
            LED_Color(blue);   //蓝灯 
            pitIsrCnt3=0;
        }
    }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】Z
【功能说明】PIT定时中断初始化
【软件版本】V1.0
【最后更新】2018年11月24日 
【函数名】
【返回值】无
【参数值】PIT通道：pit_chnl_t channel   定时器时间：uint32_t count 
【例子  】LQ_PIT_Init(kPIT_Chnl_0, 100000);  //开启通道0定时器中断，每100000us中断一次
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_PIT_Init(pit_chnl_t channel, uint32_t count)
{
     
    pit_config_t pitConfig;            /* PIT初始化结构体 */
      
    CLOCK_SetMux(kCLOCK_PerclkMux, 1U);/* 设置时钟源 OSC_CLK*/
    
    CLOCK_SetDiv(kCLOCK_PerclkDiv, 0U);/* 设置分频系数    1 */
    
    PIT_GetDefaultConfig(&pitConfig);  /* 得到PIT默认参数   */ 
    
    pitConfig.enableRunInDebug = true; /* debug时可用       */  
    
    PIT_Init(PIT, &pitConfig);          /* 初始化PIT         */

    PIT_SetTimerPeriod(PIT, channel, USEC_TO_COUNT(count, CLOCK_GetFreq(kCLOCK_OscClk))); //设置PIT通道和定时时间

    PIT_EnableInterrupts(PIT, channel, kPIT_TimerInterruptEnable);  //使能通道中断
    
    //优先级配置 抢占优先级0  子优先级2   越小优先级越高  抢占优先级可打断别的中断
    NVIC_SetPriority(PIT_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,2));
    
    EnableIRQ(PIT_IRQn);            //使能中断
   
    PIT_StartTimer(PIT, channel);   //开启定时器
}

