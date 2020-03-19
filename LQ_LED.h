/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱i.MX RT1052核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2019年03月12日
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
#ifndef __LQ_LED_H__
#define __LQ_LED_H__

//定义颜色枚举
typedef enum
{
  white = 0,  //白色
  black = 1,  //黑色
  red   = 2,  //红
  green = 3,  //绿
  blue  = 4,  //蓝色 
  yellow= 5,  //黄色
  violet= 6,  //紫色
  cyan  = 7,  //青色
}LED_t;

void LED_Color(LED_t color);
void LED_Color_Reverse(LED_t color);
void LED_Init(void);
void Test_LED(void);

#endif 
