/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2019��03��12��
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
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LQ_LED_H__
#define __LQ_LED_H__

//������ɫö��
typedef enum
{
  white = 0,  //��ɫ
  black = 1,  //��ɫ
  red   = 2,  //��
  green = 3,  //��
  blue  = 4,  //��ɫ 
  yellow= 5,  //��ɫ
  violet= 6,  //��ɫ
  cyan  = 7,  //��ɫ
}LED_t;

void LED_Color(LED_t color);
void LED_Color_Reverse(LED_t color);
void LED_Init(void);
void Test_LED(void);

#endif 
