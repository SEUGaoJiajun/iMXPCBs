/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2019��3��13��
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
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵������ʼ��GPT������  GPT1��������ʱ��  GPT2������ȷ��ʱ
������汾��V1.0
�������¡�2019��03��12�� 
������ֵ����
������ֵ����     
������  LQ_GPT_Init();   //��ʼ��GPT
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_GPT_Init(void)
{
    gpt_config_t gptConfig;
    /*Clock setting for GPT 150M*/
    CLOCK_SetMux(kCLOCK_PerclkMux, 0);
    CLOCK_SetDiv(kCLOCK_PerclkDiv, 0);
    
    GPT_GetDefaultConfig(&gptConfig);
    gptConfig.enableRunInDbg = true;    //����debug����¿���ʹ��
    GPT_Init(GPT1, &gptConfig);          //��ʼ��GPT1
    GPT_Init(GPT2, &gptConfig);          //��ʼ��GPT2
    
    GPT_SetClockDivider(GPT1, 150);      // GPT ʱ�� 150M / 150 = 1M
    GPT_SetClockDivider(GPT2, 15);       // GPT ʱ�� 150M / 15 =  10M
    
    GPT_SetOutputCompareValue(GPT1, kGPT_OutputCompare_Channel1, 0XFFFFFFFF);   //GPT ��32Ϊ������ ����������ֵ 0xFFFF FFFF 
    GPT_SetOutputCompareValue(GPT2, kGPT_OutputCompare_Channel1, 0XFFFFFFFF);   //GPT ��32Ϊ������ ����������ֵ 0xFFFF FFFF 

}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵����GPT ��������ȷ��ʱ
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ����
������ֵ���� GPT ��32Ϊ������ �����ʱ4294967295 / 10 000000 = 429s
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void delayms(uint32_t ms)
{
    delayus(ms * 1000);
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����GPT ��������ʱ
������汾��V1.0
�������¡�2019��02��18�� 
����������
������ֵ����
������ֵ���� �����ʱ4294967295 / 10 000000 = 429s
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void delayus(uint32_t us)
{
    /* Start Timer */
    GPT_StartTimer(GPT2);
    uint32_t time = us * 10 - 7;
    while(GPT_GetCurrentTimerCount(GPT2) < time);
    
    GPT_StopTimer(GPT2);
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����GPT ��������ʼ��ʱ
������汾��V1.0
�������¡�2019��02��18�� 
����������
������ֵ����
������ֵ����  
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void gpt_time_start(void)
{
    GPT_StopTimer(GPT1);
    GPT_StartTimer(GPT1);   //ˢ�� GPT1
    GPT_StartTimer(GPT1);
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����GPT �������õ�ʱ�� us
������汾��V1.0
�������¡�2019��02��18�� 
����������
������ֵ����
������ֵ���� ����ʱ 4294967295 / 1 000000 = 4290s  
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
uint32_t gpt_time_get(void)
{
    if(GPT_GetStatusFlags(GPT1, kGPT_RollOverFlag))   //���
        return 0;
    else
        return GPT_GetCurrentTimerCount(GPT1) - 1;
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵��������GPI  GPT1��������ʱ��  GPT2������ȷ��ʱ
������汾��V1.0
�������¡�2019��3��13�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_GPT_Timer(void)
{
    LQ_GPT_Init();                       //��ʼ��GPT������  GPT1��������ʱ��  GPT2������ȷ��ʱ            
    LQ_UART_Init(LPUART1, 115200);       //����1��ʼ�� ����ʹ�� printf����
    printf("\r\n����GPT����        \r\n");
    printf("\r\nGPT1��������ʱ��  GPT2������ȷ��ʱ\r\n");
    uint32_t time = 0, last_time = 0;
    gpt_time_start();               //GPT1��ʼ��ʱ
    while(1)
    {
        delayus(10);
        GPIO_PinReverse (GPIO2, 22); 
        time = gpt_time_get();      //�õ�GPT1��ǰʱ��
        printf("delay 10 us is %u \n", time - last_time);
        last_time = gpt_time_get(); //ע�� ��ӡҲ��Ҫʱ��
        delayms(10);
        time = gpt_time_get();      //�õ�GPT1��ǰʱ��
        printf("delay 10 ms is %u \n", time - last_time);
        last_time = gpt_time_get(); //ע�� ��ӡҲ��Ҫʱ��
    }
}
