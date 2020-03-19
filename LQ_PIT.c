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

volatile uint16_t pitIsrCnt0 = 0;   //�����õ�  volatile�ױ�ģ����ж������ı�ı�������ʱ��ü��ϣ����߱�������Ҫ�Ż���ÿ�ζ�ȡ���Ӹñ����ĵ�ַ��ȡ
volatile uint16_t pitIsrCnt1 = 0;  //�����õ�  volatile�ױ�ģ����ж������ı�ı�������ʱ��ü��ϣ����߱�������Ҫ�Ż���ÿ�ζ�ȡ���Ӹñ����ĵ�ַ��ȡ
volatile uint16_t pitIsrCnt2 = 0;  //�����õ�  volatile�ױ�ģ����ж������ı�ı�������ʱ��ü��ϣ����߱�������Ҫ�Ż���ÿ�ζ�ȡ���Ӹñ����ĵ�ַ��ȡ
volatile uint16_t pitIsrCnt3 = 0; //�����õ�  volatile�ױ�ģ����ж������ı�ı�������ʱ��ü��ϣ����߱�������Ҫ�Ż���ÿ�ζ�ȡ���Ӹñ����ĵ�ַ��ȡ

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵����PIT�жϷ�����
������汾��V1.0
�������¡�2019��03��13�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void PIT_IRQHandler(void)
{
    
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_0)&kPIT_TimerFlag)==kPIT_TimerFlag)  /* �ж��ĸ�PITͨ�������ж�.*/
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);    /* �����־λ.*/
        /*�û���������Ӵ���*/     
        pitIsrCnt0++;
//        LED_Ctrl(LED0, RVS);
    }
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_1)&kPIT_TimerFlag)==kPIT_TimerFlag)  /* �ж��ĸ�PITͨ�������ж�.*/
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_1, kPIT_TimerFlag);    /* �����־λ.*/
        /*�û���������Ӵ���*/
        pitIsrCnt1++;
    }
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_2)&kPIT_TimerFlag)==kPIT_TimerFlag)  /* �ж��ĸ�PITͨ�������ж�.*/
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_2, kPIT_TimerFlag);    /* �����־λ.*/
        /*�û���������Ӵ���*/        
        pitIsrCnt2++;
    }
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_3)&kPIT_TimerFlag)==kPIT_TimerFlag)  /* �ж��ĸ�PITͨ�������ж�.*/
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_3, kPIT_TimerFlag);    /* �����־λ.*/
        /*�û���������Ӵ���*/        
        pitIsrCnt3++;
    }
    
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵��������PIT��ʱ�ж�
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_PIT(void)
{ 
    LED_Init();                           //��ʼ��LED
    LQ_PIT_Init(kPIT_Chnl_2, 1000000);    //1000 000us һ���ж�
    LQ_PIT_Init(kPIT_Chnl_3, 2000000);    //2000 000us һ���ж�
    while (true)
    {
         if (pitIsrCnt2)
        {
            LED_Color(red);   //��� 
            pitIsrCnt2=0;
        }
         if (pitIsrCnt3)
        {
            LED_Color(blue);   //���� 
            pitIsrCnt3=0;
        }
    }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����PIT��ʱ�жϳ�ʼ��
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ��PITͨ����pit_chnl_t channel   ��ʱ��ʱ�䣺uint32_t count 
������  ��LQ_PIT_Init(kPIT_Chnl_0, 100000);  //����ͨ��0��ʱ���жϣ�ÿ100000us�ж�һ��
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_PIT_Init(pit_chnl_t channel, uint32_t count)
{
     
    pit_config_t pitConfig;            /* PIT��ʼ���ṹ�� */
      
    CLOCK_SetMux(kCLOCK_PerclkMux, 1U);/* ����ʱ��Դ OSC_CLK*/
    
    CLOCK_SetDiv(kCLOCK_PerclkDiv, 0U);/* ���÷�Ƶϵ��    1 */
    
    PIT_GetDefaultConfig(&pitConfig);  /* �õ�PITĬ�ϲ���   */ 
    
    pitConfig.enableRunInDebug = true; /* debugʱ����       */  
    
    PIT_Init(PIT, &pitConfig);          /* ��ʼ��PIT         */

    PIT_SetTimerPeriod(PIT, channel, USEC_TO_COUNT(count, CLOCK_GetFreq(kCLOCK_OscClk))); //����PITͨ���Ͷ�ʱʱ��

    PIT_EnableInterrupts(PIT, channel, kPIT_TimerInterruptEnable);  //ʹ��ͨ���ж�
    
    //���ȼ����� ��ռ���ȼ�0  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
    NVIC_SetPriority(PIT_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,2));
    
    EnableIRQ(PIT_IRQn);            //ʹ���ж�
   
    PIT_StartTimer(PIT, channel);   //������ʱ��
}

