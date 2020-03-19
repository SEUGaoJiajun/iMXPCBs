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
#include "include.h"

#define WDOG_WCT_INSTRUCITON_COUNT (256U)



//���Ź���ʱʱ�䣬ʵ��ʱ��Ϊ(time+1)*0.5s
void LQ_WDOG_Init(WDOG_Type *base, uint8_t time)
{
    wdog_config_t config;
    CLOCK_EnableClock(kCLOCK_Wdog1); 			//ʹ�ܿ��Ź�ʱ��
    CLOCK_EnableClock(kCLOCK_Wdog2); 			//ʹ�ܿ��Ź�ʱ��
    /*
    * wdogConfig->enableWdog = true;            //ʹ�ܿ��Ź�
    * wdogConfig->workMode.enableWait = true;   //�ȴ�ģʽ����Ȼ����
    * wdogConfig->workMode.enableStop = false;  //ֹͣģʽ�¹ر�
    * wdogConfig->workMode.enableDebug = false; //debugģʽ�ر�
    * wdogConfig->enableInterrupt = false;      //��ʹ���ж�
    * wdogConfig->enablePowerdown = false;      //
    * wdogConfig->resetExtension = flase;
    * wdogConfig->timeoutValue = 0xFFU;         //����ι��ʱ��
    * wdogConfig->interruptTimeValue = 0x04u;   //��ι��ǰ �೤ʱ������ж� ����ι��
    */
    WDOG_GetDefaultConfig(&config);             //��ȡĬ�����ò���
    config.timeoutValue = time;                 //���Ź���ʱʱ�䣬ʵ��ʱ��Ϊ(timeoutValue+1)*0.5s
    WDOG_Init(base, &config);
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵�������Կ��Ź�����
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_WDOG(void)
{
    
    LQ_WDOG_Init(WDOG1, 9);
    printf("--- Start Wdog test ---\r\n");
    
    for (uint32_t i = 0; i < 10; i++)
    {
        WDOG_Refresh(WDOG1);     //ι��
        printf("--- Refresh wdog %d time ---\r\n", i + 1);
    }

    printf("\r\nEnd of Wdog example!\r\n");
    while (1)
    {
    }
}
