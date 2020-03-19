/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2019��03��18��
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
                      
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵�����¶��жϷ�����  
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ����
������ֵ����
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
����  �ߡ�LQ-005
������˵���������¶��жϷ�����  
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void TEMP_PANIC_IRQHandler(void)
{

}

void Test_Tempmon(void)
{
    float temperature = 0U; 
    tempmon_config_t config;
    

    printf("оƬ�¶Ȳ�������. \r\n");
    

    /* Ĭ�ϵĲ���Ƶ�� 
    config->frequency = 0x03U;
     Ĭ�ϸ߱����¶�
    config->highAlarmTemp = 40U;
     Ĭ�Ͻ��������¶� 
    config->panicAlarmTemp = 90U;
     Ĭ�ϵͱ����¶� 
    config->lowAlarmTemp = 20U;*/
    TEMPMON_GetDefaultConfig(&config);

    TEMPMON_Init(TEMPMON, &config);
    TEMPMON_StartMeasure(TEMPMON);

    /* Get temperature */
    temperature = TEMPMON_GetCurrentTemperature(TEMPMON);

    printf("оƬ��ǰ�¶ȣ� %.1f ��. \r\n", temperature);

    while (1)
    {
   
        delayms(10000);
        /* Get current temperature */
        temperature = TEMPMON_GetCurrentTemperature(TEMPMON);
        printf("оƬ��ǰ�¶ȣ� %.1f ��. \r\n", temperature);
    }
    

}




