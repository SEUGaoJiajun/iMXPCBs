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
#ifndef _LQ_INLUDE_FILES_H_
#define _LQ_INLUDE_FILES_H_
    #include "stdio.h"
    #include "math.h"
//SDK底层驱动库
    #include "fsl_cache.h"
    #include "fsl_common.h"
    #include "fsl_clock.h"
    #include "fsl_gpio.h"
    #include "board.h"
    #include "pin_mux.h"
    #include "fsl_iomuxc.h"
//用户自定义文件    
    #include "LQ_GPIOmacro.h" //GPIO口51操作格式 
    #include "LQ_LED.h"       //LED指示
    
//用户自定义函数
    void delayus(uint32_t us);
    void delayms(uint32_t ms); 
#endif //_LQ_INLUDE_FILES_H_
