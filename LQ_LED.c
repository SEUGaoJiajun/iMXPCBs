/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
�������汾��V1.0
�������¡�2019��3��12��
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

GPIO2_IO23  -------->  �ܽ�B12   ----- >  ���İ�G��
GPIO3_IO26  -------->  �ܽ�A7    ----- >  ���İ�R��
GPIO3_IO27  -------->  �ܽ�C7    ----- >  ���İ�B��

GPIO2_IO22  -------->  �ܽ�C12   ----- >  ĸ��D0
GPIO2_IO25  -------->  �ܽ�A13   ----- >  ĸ��D1
�ֶν��ͣ� 
2.0��SRE ����λ��0 
SRE(Slew Rate Field)��ת���ٶ��ֶΣ���������һ�����Ե����ߵ͵�ƽ�л��������½�ʱ���ٶȵ��������һ���Ӧ����ʹ��оƬĬ�ϵ����þͿ����ˡ�����Ҫ΢��SI��EMI����ʱ���Գ����޸����� 
��ѡ��ֵ�� 
0 SRE_0_Slow_Slew_Rate �� Slow Slew Rate��ת���ٶ��� 
1 SRE_1_Fast_Slew_Rate �� Fast Slew Rate�� ת���ٶȿ�

2.1��DSE ����λ5-3 
DSE(Drive Strength Field)�����������ֶΣ���Ϊ���ʱ��Ч 
��ѡ��ֵ�� 
000 DSE_0_output_driver_disabled_ �� output driver disabled; ��ֹ��� 
001 DSE_1_R0_260_Ohm___3_3V__150_Ohm_1_8V__240_Ohm_for_DDR_ �� R0(260 Ohm @ 
3.3V, 150 Ohm@1.8V, 240 Ohm for DDR) -R0��260ŷķ@3.3v��150ŷķ@1.8v 
010 DSE_2_R0_2 �� R0/2 -R0�Ķ���֮һ��һ����ͬ 
011 DSE_3_R0_3 �� R0/3 
100 DSE_4_R0_4 �� R0/4 
101 DSE_5_R0_5 �� R0/5 
110 DSE_6_R0_6 �� R0/6 
111 DSE_7_R0_7 �� R0/7

2.2��SPEED ����λ7-6 
Speed Field���ٶ��ֶ� 
��ѡ��ֵ 
00 SPEED_0_low_50MHz_ �� low(50MHz) ���50MHz 
01 SPEED_1_medium_100MHz_ �� medium(100MHz)�м�ֵ100MHz 
10 SPEED_2_medium_100MHz_ �� medium(100MHz)�м�ֵ100MHz 
11 SPEED_3_max_200MHz_ �� max(200MHz) ���200MHz

2.3��ODE ����λ11 
ODE(Open Drain Enable Field)��©����·��������Ϊ���ʱ��Ч�������ⲿ��ѹ������������ 
��ѡ��ֵ�� 
0 ODE_0_Open_Drain_Disabled �� Open Drain Disabled ����ֹ©����· 
1 ODE_1_Open_Drain_Enabled �� Open Drain Enabled�� ʹ��©����·

2.4��PKE ����λ12 
PKE(Pull / Keep Enable Field)����/����ʹ���ֶ� 
��ѡ��ֵ�� 
0 PKE_0_Pull_Keeper_Disabled �� Pull/Keeper Disabled�� ��ֹ��/���� 
1 PKE_1_Pull_Keeper_Enabled �� Pull/Keeper Enabled�� ʹ����/����

2.5��PUE ����λ13 
PUE(Pull / Keep Select Field)����/����ѡ���ֶΣ��������߲���ͬʱ���ã� 
���֣�ʹ������״̬������������IO����NVCC_xxx�ص�֮��ʹ���뻺����������Զ�ά���ڹص�֮ǰ���߼�״̬�����ֵ�����ڵ͹��ĵ�Ӧ���еõ����֡� 
ʹ�����״̬�������������ں˹���ص�֮��ʹIO������Զ�ά���ڹص�֮ǰ���߼�״̬(��Ҫע��������״̬������������������ͬʱ����)�����ֵͬ�����������ڵ͹��ĵ�Ӧ���� 
��ѡ��ֵ�� 
0 PUE_0_Keeper �� Keeper ������ 
1 PUE_1_Pull �� Pull ����

2.6��PUS ����λ15-14 
PUS(Pull Up / Down Config. Field)������/�������ã�������Ҫ�������������źŵ�����������ȷ�������źŵĵ�ƽ����ֹ���ţ� 
��ѡ��ֵ�� 
00 PUS_0_100K_Ohm_Pull_Down �� 100K Ohm Pull Down ��100Kŷķ������ 
01 PUS_1_47K_Ohm_Pull_Up �� 47K Ohm Pull Up ��47Kŷķ������ 
10 PUS_2_100K_Ohm_Pull_Up �� 100K Ohm Pull Up ��100Kŷķ������ 
11 PUS_3_22K_Ohm_Pull_Up �� 22K Ohm Pull Up ��22Kŷķ������

2.77��HYS ����λ16 
HYS(Hyst. Enable Field)������ʹ���ֶΣ�������Ϊ����ʱ��Ч 
0 HYS_0_Hysteresis_Disabled �� Hysteresis Disabled����ֹ���� 
1 HYS_1_Hysteresis_Enabled �� Hysteresis Enabled�� ʹ�ܴ���
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"

//GPIO2_IO23  -------->  �ܽ�B12   ----- >  ���İ�G��
//GPIO3_IO26  -------->  �ܽ�A7    ----- >  ���İ�R��
//GPIO3_IO27  -------->  �ܽ�C7    ----- >  ���İ�B��

//GPIO2_IO22  -------->  �ܽ�C12   ----- >  ĸ��D1
//GPIO2_IO25  -------->  �ܽ�A13   ----- >  ĸ��D0
 
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵������ʼ�����İ��ĸ��LED����IO��
�������汾��V1.0
�������¡�2019��03��12�� 
������ֵ����
������ֵ����
������  ��LED_Init();
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LED_Init(void)
{    
    CLOCK_EnableClock(kCLOCK_Iomuxc);           // IO��ʱ��ʹ��
    /*       ���İ��ϵ�LED       */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_GPIO2_IO23, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_GPIO3_IO26, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_41_GPIO3_IO27, 0U);
    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_07_GPIO2_IO23,0x10B0u);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_40_GPIO3_IO26,0x10B0u);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_41_GPIO3_IO27,0x10B0u);
    
    //����ڹܽ����ýṹ��
    gpio_pin_config_t GPIO_Output_Config = {kGPIO_DigitalOutput, //GPIOΪ�������
                                            0,                   //�͵�ƽ
                                            kGPIO_NoIntmode      //���ж�ģʽ
                                            };  
    
    GPIO_PinInit(GPIO2,23, &GPIO_Output_Config);     //B12  ���İ�G��
    GPIO_PinInit(GPIO3,26, &GPIO_Output_Config);     //A7   ���İ�R��   
    GPIO_PinInit(GPIO3,27, &GPIO_Output_Config);     //C7   ���İ�B��
    
    /*             ĸ���ϵ�lED����             */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_GPIO2_IO22, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_GPIO2_IO25, 0U);
    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_06_GPIO2_IO22,0x10B0u);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_09_GPIO2_IO25,0x10B0u);
    
    GPIO_PinInit(GPIO2,22, &GPIO_Output_Config);      //C12  D1
    GPIO_PinInit(GPIO2,25, &GPIO_Output_Config);      //A13  D0
    
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵����ָ������ɫ
�������汾��V1.0
�������¡�2019��03��12�� 
������ֵ����
������ֵ���Ƶ���ɫ  LED_t color     
������  ��LED_Color(red);   //�����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LED_Color(LED_t color)
{
    switch(color)
    {
        case white:
            GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED��; 
            break;
        case black:
            GPIO_PinWrite(GPIO2,23, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED��; 
            break;
        case red:
            GPIO_PinWrite(GPIO2,23, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED��; 
            break;
        case green:
            GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED��; 
            break;
        case blue:
            GPIO_PinWrite(GPIO2,23, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED��; 
            break;
        case yellow:
            GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED��; 
            break;
        case violet:
            GPIO_PinWrite(GPIO2,23, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED��; 
            break;
        case cyan:
            GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED��; 
            break;
    }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����ָ����ɫ�Ʒ�ת
�������汾��V1.0
�������¡�2018��11��14�� 
����������
������ֵ����
������ֵ���Ƶ���ɫ  LED_t color  
������  ��LED_Color(red);   //��Ʒ�ת
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LED_Color_Reverse(LED_t color)
{
    static uint8_t count = 0;
    if(count++ % 2)
    {
        LED_Color(color);   //��ָ����ɫ�ĵ�
    }
    else
    {
        LED_Color(black);   //��
    }
    
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵��������LED������ˮ��
�������汾��V1.0
�������¡�2018��11��14�� 
����������
������ֵ����
������ֵ����
������  Test_LED();   
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_LED(void)
{
  LED_Init();   
  while (1)
  {          
        LED_Color(red);     //���
        delayms(500);
        LED_Color(green);   //�̵�
        delayms(500);
        LED_Color(blue);    //����
        delayms(500);
        LED_Color(violet);  //�ϵ�
        delayms(500);
        LED_Color(yellow);  //�Ƶ�
        delayms(500);
        LED_Color(cyan);    //���
        delayms(500);
        LED_Color(white);   //�׵�
        delayms(500);
        LED_Color(black);   //�ص�
        delayms(500);
        
        for(int i = 0; i < 20; i++)
        {
            LED_Color_Reverse(red);     //�����˸
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_Color_Reverse(green);   //�̵���˸
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_Color_Reverse(blue);    //������˸
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_Color_Reverse(violet);  //�ϵ���˸
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_Color_Reverse(yellow);  //�Ƶ���˸
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_Color_Reverse(cyan);    //�����˸
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_Color_Reverse(white);   //�׵���˸
            delayms(100);
        }
  }
}
