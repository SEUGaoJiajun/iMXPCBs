/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��2��1��
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
#ifndef _LQ_INLUDE_FILES_H_
#define _LQ_INLUDE_FILES_H_
    #include "stdio.h"
    #include "math.h"
//SDK�ײ�������
    #include "fsl_cache.h"
    #include "fsl_common.h"
    #include "fsl_clock.h"
    #include "fsl_gpio.h"
    #include "board.h"
    #include "pin_mux.h"
    #include "fsl_iomuxc.h"
//�û��Զ����ļ�    
    #include "LQ_GPIOmacro.h" //GPIO��51������ʽ 
    #include "LQ_LED.h"       //LEDָʾ
    
//�û��Զ��庯��
    void delayus(uint32_t us);
    void delayms(uint32_t ms); 
#endif //_LQ_INLUDE_FILES_H_
