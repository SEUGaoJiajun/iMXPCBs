/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�LPC546XX���İ�
����    д��CHIUSIR
����    ע��
�������汾��V1.0
�������¡�2017��11��27��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
���������䡿chiusir@163.com
----------------------------------------------------------------
ʹ��PWM��Ҫ������¼������裺
��һ��(���岽)��ѡ������ͨ�����ܽţ�����ͨ��ѡ��궨��    
�ڶ���(���岽)���޸Ĺܽź궨�壬�������ùܽ�               
������(���岽)���������ùܽź��������ùܽŶ�Ӧ����         
���Ĳ�(���岽)������PWM��ʼ������������PWMƵ�ʺͳ�ʼռ�ձ� 
���岽(���岽)������PWMˢ�º�����ʵ�ֵ���Ͷ������       
���Ժ�����Test_Servo();      ����PWM����      ���ֶ����������               
���Ժ�����Test_Motor();      ����PWM����      �����������                  
----------------------------------------------------------------
PWM1, kPWM_Module_0, kPWM_PwmA   J4
PWM1, kPWM_Module_0, kPWM_PwmB   J3
PWM1, kPWM_Module_1, kPWM_PwmA   J1     ���4�ӿ�
PWM1, kPWM_Module_1, kPWM_PwmB   K1
PWM1, kPWM_Module_2, kPWM_PwmA   H2
PWM1, kPWM_Module_2, kPWM_PwmB   J2
PWM1, kPWM_Module_3, kPWM_PwmA   L5     ���1�ӿ�
PWM1, kPWM_Module_3, kPWM_PwmB   M5     ���1�ӿ�

PWM2, kPWM_Module_0, kPWM_PwmA   A8     ���2�ӿ�
PWM2, kPWM_Module_0, kPWM_PwmB   A9     ���2�ӿ�
PWM2, kPWM_Module_1, kPWM_PwmA   B9     ���3�ӿ�
PWM2, kPWM_Module_1, kPWM_PwmB   C9     ���3�ӿ�
PWM2, kPWM_Module_2, kPWM_PwmA   D9
PWM2, kPWM_Module_2, kPWM_PwmB   A10    ���4�ӿ�
PWM2, kPWM_Module_3, kPWM_PwmA   M3     ����ӿ�
PWM2, kPWM_Module_3, kPWM_PwmB   M4     ����ӿ�
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h" 

/* ���ռ�ձ� */
#define DUTY_MAX  10000     


/**
  * @brief    �ı�ռ�ձ�
  *
  * @param    base       ��PWMģ�� PWM1~PWM4
  * @param    subModule  ��PWMģ���µ���ģ�� kPWM_Module_0 ~ kPWM_Module_3 
  * @param    pwmSignal  ��kPWM_PwmA/kPWM_PwmB
  * @param    currPwmMode�����뷽ʽ
  * @param    duty       ��ռ�ձ�*DUTY_MAX
  *
  * @return   ��
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/23 ������
  */
void PWM_UpdateDuty(PWM_Type *base,
                            pwm_submodule_t subModule,
                            pwm_channels_t pwmSignal,
                            pwm_mode_t currPwmMode,
                            uint16_t duty)
{    
    assert(pwmSignal < 2);
    uint16_t pulseCnt = 0, pwmHighPulse = 0;
    int16_t modulo = 0;

    switch (currPwmMode)
    {
        case kPWM_SignedCenterAligned:
            modulo = base->SM[subModule].VAL1;
            pulseCnt = modulo * 2;
            /* Calculate pulse width */
            pwmHighPulse = (pulseCnt * duty) / DUTY_MAX;   //ռ�ձ� =  duty / DUTY_MAX ���޸�

            /* Setup the PWM dutycycle */
            if (pwmSignal == kPWM_PwmA)
            {
                base->SM[subModule].VAL2 = (-(pwmHighPulse / 2));
                base->SM[subModule].VAL3 = (pwmHighPulse / 2);
            }
            else
            {
                base->SM[subModule].VAL4 = (-(pwmHighPulse / 2));
                base->SM[subModule].VAL5 = (pwmHighPulse / 2);
            }
            break;
        case kPWM_CenterAligned:
            pulseCnt = base->SM[subModule].VAL1;
            /* Calculate pulse width */
            pwmHighPulse = (pulseCnt * duty) / DUTY_MAX;   //ռ�ձ� =  duty / DUTY_MAX ���޸�

            /* Setup the PWM dutycycle */
            if (pwmSignal == kPWM_PwmA)
            {
                base->SM[subModule].VAL2 = ((pulseCnt - pwmHighPulse) / 2);
                base->SM[subModule].VAL3 = ((pulseCnt + pwmHighPulse) / 2);
            }
            else
            {
                base->SM[subModule].VAL4 = ((pulseCnt - pwmHighPulse) / 2);
                base->SM[subModule].VAL5 = ((pulseCnt + pwmHighPulse) / 2);
            }
            break;
        case kPWM_SignedEdgeAligned:
            modulo = base->SM[subModule].VAL1;
            pulseCnt = modulo * 2;
            /* Calculate pulse width */
            pwmHighPulse =  (pulseCnt * duty) / DUTY_MAX;   //ռ�ձ� =  duty / DUTY_MAX ���޸�

            /* Setup the PWM dutycycle */
            if (pwmSignal == kPWM_PwmA)
            {
                base->SM[subModule].VAL2 = (-modulo);
                base->SM[subModule].VAL3 = (-modulo + pwmHighPulse);
            }
            else
            {
                base->SM[subModule].VAL4 = (-modulo);
                base->SM[subModule].VAL5 = (-modulo + pwmHighPulse);
            }
            break;
        case kPWM_EdgeAligned:
            pulseCnt = base->SM[subModule].VAL1;
            /* Calculate pulse width */
            pwmHighPulse =  (pulseCnt * duty) / DUTY_MAX;   //ռ�ձ� =  duty / DUTY_MAX ���޸�

            /* Setup the PWM dutycycle */
            if (pwmSignal == kPWM_PwmA)
            {
                base->SM[subModule].VAL2 = 0;
                base->SM[subModule].VAL3 = pwmHighPulse;
            }
            else
            {
                base->SM[subModule].VAL4 = 0;
                base->SM[subModule].VAL5 = pwmHighPulse;
            }
            break;
        default:
            break;
    }
}

/**
  * @brief    PWM���ų�ʼ��
  *
  * @param    pwm_num = 1 ��ʾ PWM1 ģ�飬pwm_num = 2 ��ʾ PWM2 ģ�飬
              pwm_num = 3 ��ʾ PWM3 ģ�飬pwm_num = 4 ��ʾ PWM4 ģ��
  * @param    subModule     ��PWMģ���µ���ģ�� kPWM_Module_0 ~ kPWM_Module_3 
  * @param    pwm_channels  ��PWMģ���µ���ģ�� ��ͨ�� �� kPWM_PwmA �� kPWM_PwmB  �� kPWM_PwmA_B 
  *
  * @return   
  *
  * @note     ֻ��Ϊʹ������ĸ�巽�㶨��ģ���û�а������е����ţ�û�е���Ҫ���вο�RT1052�ٷ��ֲ���������Ÿ��� �޸�
  *
  * @example  
  *
  * @date     2019/5/23 ������
  */
void LQ_PWM_InitPins(uint8_t pwm_num, pwm_submodule_t subModule, pwm_channels_t pwm_channels)
{
    CLOCK_EnableClock(kCLOCK_Iomuxc);          /* ��ioʱ�� */
    
    switch(pwm_num)//ѡ��PWMģ��
    {
        case 1:    //PWM1ģ��
        {
            switch(subModule)  //ѡ��PWM��ģ��
            {
                case 0:        //ѡ��PWM1ģ���subModule0��ģ��
                {
                    if(pwm_channels == kPWM_PwmA || pwm_channels == kPWM_PwmA_B)  //ʹ��PWMAҪ��ʼ��������
                    {
                        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_FLEXPWM1_PWMA00, 0U);   /* GPIO_SD_B0_00 is configured as FLEXPWM1_PWMA00 */
                        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_00_FLEXPWM1_PWMA00, 0x10B0u);   
                    }
                    if(pwm_channels == kPWM_PwmB || pwm_channels == kPWM_PwmA_B)  //ʹ��PWMBҪ��ʼ��������
                    {
                        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_FLEXPWM1_PWMB00, 0U);   /* GPIO_SD_B0_00 is configured as FLEXPWM1_PWMA00 */
                        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_01_FLEXPWM1_PWMB00, 0x10B0u);  
                    }
                    break;
                }
                case 1:        //ѡ��PWM1ģ���subModule1��ģ��
                {
                    if(pwm_channels == kPWM_PwmA || pwm_channels == kPWM_PwmA_B)
                    {
                        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_02_FLEXPWM1_PWMA01, 0U);   //J1
                        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_02_FLEXPWM1_PWMA01, 0x10B0u);
                    }
                    if(pwm_channels == kPWM_PwmB || pwm_channels == kPWM_PwmA_B)
                    {
                        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_03_FLEXPWM1_PWMB01, 0U);   //K1
                        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_03_FLEXPWM1_PWMB01, 0x10B0u);  
                    }                                                         
                    break;
                }
                case 2:        //ѡ��PWM1ģ���subModule2��ģ��
                {
                    if(pwm_channels == kPWM_PwmA || pwm_channels == kPWM_PwmA_B)
                    {
                        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_FLEXPWM1_PWMA02, 0U);  //H2
                        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_04_FLEXPWM1_PWMA02, 0x10B0u);  
                    }
                    if(pwm_channels == kPWM_PwmB || pwm_channels == kPWM_PwmA_B)
                    {
                        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_FLEXPWM1_PWMB02, 0U);   //J2
                        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_05_FLEXPWM1_PWMB02, 0x10B0u);
                    }
                    break;
                }
                case 3:        //ѡ��PWM1ģ���subModule3��ģ��
                {
                    if(pwm_channels == kPWM_PwmA || pwm_channels == kPWM_PwmA_B)
                    {
                        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_FLEXPWM1_PWMA03, 0U);   //L5
                        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_00_FLEXPWM1_PWMA03, 0x10B0u);    
                    }
                    if(pwm_channels == kPWM_PwmB || pwm_channels == kPWM_PwmA_B)
                    {
                        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_01_FLEXPWM1_PWMB03, 0U);   //M5
                        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_01_FLEXPWM1_PWMB03, 0x10B0u);                    
                    }
                                                                          
                    break;
                }
                default:
                    break;
            }
            
            break;
        }
        case 2:    //PWM2ģ��
        {
            switch(subModule)  //ѡ��PWM��ģ��
            {
                case 0:        //ѡ��PWM2ģ���subModule0��ģ��
                {
                    if(pwm_channels == kPWM_PwmA || pwm_channels == kPWM_PwmA_B)
                    {
                      IOMUXC_SetPinMux(IOMUXC_GPIO_B0_06_FLEXPWM2_PWMA00, 0U);    //A8
                      IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_06_FLEXPWM2_PWMA00, 0x10B0u);  
                    }
                    if(pwm_channels == kPWM_PwmB || pwm_channels == kPWM_PwmA_B)
                    {
                      IOMUXC_SetPinMux(IOMUXC_GPIO_B0_07_FLEXPWM2_PWMB00, 0U);    //A9
                      IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_07_FLEXPWM2_PWMB00, 0x10B0u);
                    }
                    break;
                }
                case 1:        //ѡ��PWM2ģ���subModule1��ģ��
                {
                    if(pwm_channels == kPWM_PwmA || pwm_channels == kPWM_PwmA_B)
                    {
                      IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_FLEXPWM2_PWMA01, 0U);    //B9
                      IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_08_FLEXPWM2_PWMA01, 0x10B0u); 
                    }
                    if(pwm_channels == kPWM_PwmB || pwm_channels == kPWM_PwmA_B)
                    {
                      IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_FLEXPWM2_PWMB01, 0U);     //C9
                      IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_09_FLEXPWM2_PWMB01, 0x10B0u);
                    }
                    break;
                }
                case 2:        //ѡ��PWM2ģ���subModule2��ģ��
                {
                    if(pwm_channels == kPWM_PwmA || pwm_channels == kPWM_PwmA_B)
                    {
                        IOMUXC_SetPinMux(IOMUXC_GPIO_B0_10_FLEXPWM2_PWMA02, 0U);   //D9
                        IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_10_FLEXPWM2_PWMA02, 0x10B0u);    
                    }
                    if(pwm_channels == kPWM_PwmB || pwm_channels == kPWM_PwmA_B)
                    {
                        IOMUXC_SetPinMux(IOMUXC_GPIO_B0_11_FLEXPWM2_PWMB02, 0U);     //A10
                        IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_11_FLEXPWM2_PWMB02, 0x10B0u);
                    }
                    break;
                }
                case 3:        //ѡ��PWM2ģ���subModule3��ģ��
                {
                    if(pwm_channels == kPWM_PwmA || pwm_channels == kPWM_PwmA_B)
                    {
                        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_02_FLEXPWM2_PWMA03, 0U);      //M3
                        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_02_FLEXPWM2_PWMA03, 0x10B0u);    
                    }
                    if(pwm_channels == kPWM_PwmB || pwm_channels == kPWM_PwmA_B)
                    {
                        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_03_FLEXPWM2_PWMB03, 0U);      //M4
                        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_03_FLEXPWM2_PWMB03, 0x10B0u); 
//                        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_FLEXPWM2_PWMB03, 0U);        //H10                    
//                        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_01_FLEXPWM2_PWMB03, 0x10B0u); 
                    }
                                                                             
                    break;
                }
                default:
                    break;
            }
            
            break;
        }
        case 3:    //PWM3ģ��
        {
            switch(subModule)  //ѡ��PWM��ģ��
            {
                case 0:        //ѡ��PWM1ģ���subModule0��ģ��
                {
                    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_29_FLEXPWM3_PWMA00, 0U);   /* GPIO_SD_B0_00 is configured as FLEXPWM1_PWMA00 */
                    IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_29_FLEXPWM3_PWMA00, 0x10B0u);                                                         
                    break;
                }
                case 1:        //ѡ��PWM1ģ���subModule1��ģ��
                {
                    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_31_FLEXPWM3_PWMA01, 0U);   /* GPIO_SD_B0_00 is configured as FLEXPWM1_PWMA00 */
                    IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_31_FLEXPWM3_PWMA01, 0x10B0u);                                                         
                    break;
                }
                case 2:        //ѡ��PWM1ģ���subModule2��ģ��
                {
                    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_33_FLEXPWM3_PWMA02, 0U);   /* GPIO_SD_B0_00 is configured as FLEXPWM1_PWMA00 */
                    IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_33_FLEXPWM3_PWMA02, 0x10B0u);                                                         
                    break;
                }
                case 3:        //ѡ��PWM1ģ���subModule3��ģ��
                {
                    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_21_FLEXPWM3_PWMA03, 0U);   /* GPIO_SD_B0_00 is configured as FLEXPWM1_PWMA00 */
                    IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_21_FLEXPWM3_PWMA03, 0x10B0u);                                                         
                    break;
                }
                default:
                    break;
            }
            
            break;
        }
        case 4:    //PWM4ģ��
        {
            switch(subModule)  //ѡ��PWM��ģ��
            {
                case 0:        //ѡ��PWM1ģ���subModule0��ģ��
                {
                    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_FLEXPWM4_PWMA00, 0U);   /* GPIO_SD_B0_00 is configured as FLEXPWM1_PWMA00 */
                    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_08_FLEXPWM4_PWMA00, 0x10B0u);                                                         
                    break;
                }
                case 1:        //ѡ��PWM1ģ���subModule1��ģ��
                {
                    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_FLEXPWM4_PWMA01, 0U);   /* GPIO_SD_B0_00 is configured as FLEXPWM1_PWMA00 */
                    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_09_FLEXPWM4_PWMA01, 0x10B0u);                                                         
                    break;
                }
                case 2:        //ѡ��PWM1ģ���subModule2��ģ��
                {
                    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_14_FLEXPWM4_PWMA02, 0U);   /* GPIO_SD_B0_00 is configured as FLEXPWM1_PWMA00 */
                    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_14_FLEXPWM4_PWMA02, 0x10B0u);                                                         
                    break;
                }
                case 3:        //ѡ��PWM1ģ���subModule3��ģ��
                {
                    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_15_FLEXPWM4_PWMA03, 0U);   /* GPIO_SD_B0_00 is configured as FLEXPWM1_PWMA00 */
                    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_15_FLEXPWM4_PWMA03, 0x10B0u);                                                         
                    break;
                }
                default:
                    break;
            }
            
            break;
        }
        default:
            break;    
    }
    
    
}


/**
  * @brief    PWM���ܳ�ʼ��
  *
  * @param    base          ��PWMģ�� PWM1~PWM4
  * @param    subModule     ��PWMģ���µ���ģ�� kPWM_Module_0 ~ kPWM_Module_3 
  * @param    pwm_channels  ��PWMģ���µ���ģ�� ��ͨ�� �� kPWM_PwmA �� kPWM_PwmB  �� kPWM_PwmA_B 
  * @param    Frequency     ��Ƶ��
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/23 ������
  */
void LQ_PWM_Init(PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwm_channels, uint16_t Frequency)
{
    if(base == PWM1)
    {
        LQ_PWM_InitPins(1, subModule, pwm_channels); //�ܽŸ���ѡ��
    }
    else if(base == PWM2)
    {
        LQ_PWM_InitPins(2, subModule, pwm_channels); //�ܽŸ���ѡ��
    }
    else if(base == PWM3)
    {
        LQ_PWM_InitPins(3, subModule, pwm_channels); //�ܽŸ���ѡ��
    }
    else if(base == PWM4)
    {
        LQ_PWM_InitPins(4, subModule, pwm_channels); //�ܽŸ���ѡ��
    }
    else printf("Please input PWM1 ~ PWM4 \n"); 
    CLOCK_SetDiv(kCLOCK_AhbDiv, 0x0); /* Set AHB PODF to 0, divide by 1 */ //600MHz 
    CLOCK_SetDiv(kCLOCK_IpgDiv, 0x2); /* Set IPG PODF to 2, divede by 3 */ //600MHz 3��Ƶ 200MHz
    
    uint32_t pwmSourceClockInHz;   //PWMʱ��Դ
    pwmSourceClockInHz = CLOCK_GetFreq(kCLOCK_IpgClk);//ʱ��Դ  200MHz
    printf("pwmSourceClockInHz  %d\n", pwmSourceClockInHz); 
    
    
    pwm_config_t pwmConfig;// PWM��ʼ���ṹ��
    /*pwmConfigĬ�ϲ���
    * pwmConfig.enableDebugMode = false;
    * pwmConfig.enableWait = false;
    * pwmConfig.reloadSelect = kPWM_LocalReload;
    * pwmConfig.faultFilterCount = 0;
    * pwmConfig.faultFilterPeriod = 0;
    * pwmConfig.clockSource = kPWM_BusClock;
    * pwmConfig.prescale = kPWM_Prescale_Divide_1;
    * pwmConfig.initializationControl = kPWM_Initialize_LocalSync;
    * pwmConfig.forceTrigger = kPWM_Force_Local;
    * pwmConfig.reloadFrequency = kPWM_LoadEveryOportunity;
    * pwmConfig.reloadLogic = kPWM_ReloadImmediate;
    * pwmConfig.pairOperation = kPWM_Independent;   //PWMA��PWMB�������
    */
    PWM_GetDefaultConfig(&pwmConfig);               //�õ�Ĭ�ϵ�PWM��ʼ���ṹ��
    
    pwmConfig.reloadLogic   = kPWM_ReloadPwmFullCycle;   //ѭ�����
    
    pwmConfig.enableDebugMode = true;    
    
    /* ������ѷ�Ƶϵ�� */
    uint32_t temp = pwmSourceClockInHz / Frequency;
    uint8_t div = 0;
    while(temp > 0xFFFF)
    {
        div++;
        temp = temp >> 1;
    }
    pwmConfig.prescale = (pwm_clock_prescale_t)div;   

    if (PWM_Init(base, subModule, &pwmConfig) == kStatus_Fail)
    {
        printf("PWM subModule %d initialization failed\n",subModule);
        return ;
    }  
    base->SM[subModule].DISMAP[0]=0;      //���ι��ϼ�⹦��
    
    pwm_signal_param_t pwmSignal[2];      //PWM��ģ���ʼ���ṹ��
    uint16_t deadTimeVal = 0;
    /* Set deadtime count, we set this to about 650ns */
    //  deadTimeVal = ((uint64_t)pwmSourceClockInHz * 650) / 1000000000;//�����趨 ��������ˢ���PWMA��PWMB�������ʱʹ�� 
    
    pwmSignal[0].pwmChannel = kPWM_PwmA; //Ĭ��ʹ��ͨ��A
    if(pwm_channels == kPWM_PwmB)        //���ʹ��ͨ��B
    {
        pwmSignal[0].pwmChannel = kPWM_PwmB;  // ʹ��PWMB
    }
    pwmSignal[0].level = kPWM_HighTrue;   //�����ƽΪ�ߵ�ƽ
    pwmSignal[0].dutyCyclePercent = 0;    //��ʼռ�ձ� 0%
    pwmSignal[0].deadtimeValue = deadTimeVal;//����ʱ��
    
    /*��AB��ͨ��ͬʱʹ�� ��������*/
    pwmSignal[1].pwmChannel = kPWM_PwmB;  // ʹ��PWMB
    pwmSignal[1].level = kPWM_HighTrue;   //�����ƽΪ�ߵ�ƽ
    pwmSignal[1].dutyCyclePercent = 0;    //��ʼռ�ձ� 0%
    pwmSignal[1].deadtimeValue = deadTimeVal;//����ʱ��
    
    if(pwm_channels == kPWM_PwmA_B)  //A B��ͨ��ͬʱʹ��
    {
           /*����pwm��ʱ�� = pwmSourceClockInHz��Ƶ�� = Frequency ���뷽ʽ = kPWM_SignedCenterAligned��*/
        PWM_SetupPwm(base, subModule, pwmSignal, 2, kPWM_SignedCenterAligned, Frequency,pwmSourceClockInHz); 
    }
    else  //��ʹ��A B�е�һ��ʱ
    {
         /*����pwm��ʱ�� = pwmSourceClockInHz��Ƶ�� = Frequency ���뷽ʽ = kPWM_SignedCenterAligned��*/
        PWM_SetupPwm(base, subModule, pwmSignal, 1, kPWM_SignedCenterAligned, Frequency,pwmSourceClockInHz); 
    }   
    
    PWM_SetPwmLdok(base, 1u<<subModule, true);//����pwm�� load okλ
    
    PWM_StartTimer(base, 1u<<subModule); //������ʱ��
    
}


/**
  * @brief    ����ռ�ձ�
  *
  * @param    base          ��PWMģ�� PWM1~PWM4
  * @param    subModule     ��PWMģ���µ���ģ�� kPWM_Module_0 ~ kPWM_Module_3 
  * @param    pwm_channels  ��PWMģ���µ���ģ�� ��ͨ�� �� kPWM_PwmA �� kPWM_PwmB  �� kPWM_PwmA_B 
  * @param    duty          ��ռ�ձ�*DUTY_MAX  
  *
  * @return   
  *
  * @note     ͬʱ���� һ����ģ���A �� B�಻Ҫ���������
  * @note     Ĭ�϶��뷽ʽkPWM_SignedCenterAligned�� ���������޸�  
  *
  * @example  
  *
  * @date     2019/5/23 ������
  */
inline void LQ_PWM_SetDuty(PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwm_channels, uint16_t duty)
{
    assert(duty <= DUTY_MAX);
    PWM_UpdateDuty(base, subModule, pwm_channels, kPWM_SignedCenterAligned, duty); 
    PWM_SetPwmLdok(base, 1u<<subModule, true);
}

/**
  * @brief    ͬʱ���� һ����ģ���A �� B��  ���������
  *
  * @param    base          ��PWMģ�� PWM1~PWM4
  * @param    subModule     ��PWMģ���µ���ģ�� kPWM_Module_0 ~ kPWM_Module_3 
  * @param    pwm_channels  ��PWMģ���µ���ģ�� ��ͨ�� �� kPWM_PwmA �� kPWM_PwmB  �� kPWM_PwmA_B 
  * @param    duty          ��ռ�ձ�*DUTY_MAX  
  *
  * @return   
  *
  * @note     ͬʱ���� һ����ģ���A �� B��  ���������
  * @note     Ĭ�϶��뷽ʽkPWM_SignedCenterAligned�� ���������޸�  
  *
  * @example  
  *
  * @date     2019/5/23 ������
  */
inline void LQ_PWMA_B_SetDuty(PWM_Type *base, pwm_submodule_t subModule, uint16_t dutyA, uint16_t dutyB)
{
    assert( dutyA <= DUTY_MAX);
    assert( dutyB <= DUTY_MAX);
    PWM_UpdateDuty(base, subModule, kPWM_PwmA, kPWM_SignedCenterAligned, dutyA); 
    PWM_UpdateDuty(base, subModule, kPWM_PwmB, kPWM_SignedCenterAligned, dutyB); 
    PWM_SetPwmLdok(base, 1u<<subModule, true);
}


/**
  * @brief    ���ö��ռ�ձ�
  *
  * @param    duty          ��ռ�ձ�*DUTY_MAX   
  *
  * @return   
  *
  * @note      �����ֵ 1.5ms�ߵ�ƽ��PWM��    �޷��� 1.3 - 1.7ms֮��
  *
  * @example  
  *
  * @date     2019/5/23 ������
  */
inline void LQ_SetServoDty(uint16_t duty)    
{
    if(duty > 850) duty = 850;    //�޷����������޸�
    if(duty < 650) duty = 650;
    LQ_PWMA_B_SetDuty(PWM2, kPWM_Module_3, duty, duty); //M3 M4  
}


/**
  * @brief    ���õ��ռ�ձ�
  *
  * @param    num�� 1�����1�� ʹ�� L5  M5  
                    2�����2�� ʹ�� A8  A9  
                    3�����3�� ʹ�� B9  C9  
                    4�����4�� ʹ�� A10 J1
  *
  * @return   
  *
  * @note     �������ת���Ե��ڵ�����ߵ�����Ҳ���Կ���PWM����  ����������ת�ͳ����ж���Ĳ�һ�������������޸�
  *
  * @example  
  *
  * @date     2019/5/23 ������
  */
inline void LQ_SetMotorDty(uint8_t num, short duty)  
{
    assert(num < 5);
    
    switch(num)
    {
        case 1:
            if(duty >= 0)  
            {
                LQ_PWMA_B_SetDuty(PWM1, kPWM_Module_3, 0, duty);
            }
            else
            {
                LQ_PWMA_B_SetDuty(PWM1, kPWM_Module_3, -duty, 0);
            }
            break;
            
        case 2:
            if(duty >= 0)  
            {
                LQ_PWMA_B_SetDuty(PWM2, kPWM_Module_0, 0, duty);
            }
            else
            {
                LQ_PWMA_B_SetDuty(PWM2, kPWM_Module_0, -duty, 0);
            }
            break;
            
        case 3:
            if(duty >= 0)  
            {
                LQ_PWMA_B_SetDuty(PWM2, kPWM_Module_1, 0, duty);
            }
            else
            {
                LQ_PWMA_B_SetDuty(PWM2, kPWM_Module_1, -duty, 0);
            }
            break;
            
        case 4:
            if(duty >= 0)  
            {
                LQ_PWM_SetDuty(PWM2,    kPWM_Module_2, kPWM_PwmB , 0);
                LQ_PWM_SetDuty(PWM1,    kPWM_Module_1, kPWM_PwmA , duty);
            }
            else
            {
                LQ_PWM_SetDuty(PWM2,    kPWM_Module_2, kPWM_PwmB , -duty);
                LQ_PWM_SetDuty(PWM1,    kPWM_Module_1, kPWM_PwmA , 0);
            }
            break;
    }
  
}

/**
  * @brief    �������
  *
  * @param    
  *
  * @return   
  *
  * @note     ����ʹ�ô˺���ʱ�������Ҫװ���̣���ֹ���������������ֵ����װ������������������ֵ
  *
  * @example  
  *
  * @date     2019/5/23 ������
  */
#ifdef TFT1_8
void Test_Servo(void)
{
    char txt[16];
    int servopwm = 0; 
    float time=0;
    TFTSPI_Init(1);                //TFT1.8��ʼ��  
    TFTSPI_CLS(u16BLUE);           //����
    LQ_KEY_Init();                 //����������ڳ�ʼ��   
    
    /*��ʼ�����PWM�ӿ�  kPWM_PwmA  M3  M4*/
    LQ_PWM_Init(PWM2, kPWM_Module_3, kPWM_PwmA_B,  50); //M3 M4
    
    LQ_SetServoDty(750);           //��ֵ
    
    TFTSPI_P8X16Str(1,0,"LQ Servo PWM",u16RED,u16BLUE);
    sprintf(txt,"Fre:50 Hz");              
    TFTSPI_P8X16Str(3,1,txt,u16RED,u16BLUE);             //��Ļ��ʾPWMƵ��
    while (1)
    {    
        
        switch(LQ_KEY_Read(1))  //��ⰴ�� mode:0������mode:1����
        {
            case 0:
            break;
            case 1:
                servopwm -= 10;
                LQ_SetServoDty(750 + servopwm);//ˢ��servopwmƵ��
                break;           
            case 2:           
                servopwm = 0;
                LQ_SetServoDty(750 + servopwm);//ˢ��servopwmƵ��
                break;
            case 3:           
                servopwm += 10;
                LQ_SetServoDty(750 + servopwm);//ˢ��servopwmƵ��
                break;
        }
        time=(750 + servopwm)*20.0/10000;
        if(servopwm > 100) servopwm = 100;
        if(servopwm < -100) servopwm = -100;
        sprintf(txt,"PWM: %4.2f %",(float)servopwm/100.0f);
        TFTSPI_P8X16Str(3,2,txt,u16RED,u16BLUE);         //��ʾռ�ձ�
        sprintf(txt,"Time:%4.3fms",time);
        TFTSPI_P8X16Str(3,3,txt,u16RED,u16BLUE);         //��ʾ�ߵ�ƽʱ��
        printf(txt); 
        
        //LED��˸
        LED_Color_Reverse(red);     //���   
        delayms(50);
    }
}


/**
  * @brief    �������
  *
  * @param    
  *
  * @return   
  *
  * @note     ���1�� ʹ�� L5  M5   ���2��ʹ��A8  A9  ���3��ʹ�� B9 C9  ���4��A10 J1
  *
  * @example  
  *
  * @date     2019/5/23 ������
  */
void Test_Motor(void)
{    
    char txt[16];
    short motorpwm=0;   
    TFTSPI_Init(1);               //TFT1.8��ʼ��  
    TFTSPI_CLS(u16BLUE);           //����
    LQ_KEY_Init();          //����������ڳ�ʼ��   
    /*��ʼ�����PWM�ӿ�   */
    LQ_PWM_Init(PWM2, kPWM_Module_0, kPWM_PwmA_B, 12000);//  A8 A9
    LQ_PWM_Init(PWM2, kPWM_Module_1, kPWM_PwmA_B, 12000);//  B9 C9
    LQ_PWM_Init(PWM2, kPWM_Module_2, kPWM_PwmB,   12000);//  A10
    LQ_PWM_Init(PWM1, kPWM_Module_1, kPWM_PwmA,   12000);//  J1
    LQ_PWM_Init(PWM1, kPWM_Module_3, kPWM_PwmA_B, 12000);//  L5 M5
    TFTSPI_P8X16Str(3,0,"LQ Motor PWM",u16RED,u16BLUE);
    
    while (1)
    {        
        switch(LQ_KEY_Read(0))  //��ⰴ��
        {
            case 0:
                break;
            case 1:
                motorpwm -= 100;
                if(motorpwm < -10000) motorpwm = -10000;
                LQ_SetMotorDty(1, motorpwm);
                LQ_SetMotorDty(2, motorpwm);
                LQ_SetMotorDty(3, motorpwm);
                LQ_SetMotorDty(4, motorpwm);
                break;           
            case 3:           
                motorpwm += 100;
                if(motorpwm > 10000) motorpwm = 10000;
                LQ_SetMotorDty(1, motorpwm);
                LQ_SetMotorDty(2, motorpwm);
                LQ_SetMotorDty(3, motorpwm);
                LQ_SetMotorDty(4, motorpwm);
                break;
            case 2:
                motorpwm = 0;
                LQ_SetMotorDty(1, motorpwm);
                LQ_SetMotorDty(2, motorpwm);
                LQ_SetMotorDty(3, motorpwm);
                LQ_SetMotorDty(4, motorpwm);
            break;
        }
        
        sprintf(txt,"PWM: %4.2f %",motorpwm/100.0f);
        TFTSPI_P8X16Str(3,3,txt,u16RED,u16BLUE);
        printf(txt); 
        
        //LED��˸
        LED_Color_Reverse(red);     //���   
        delayms(50);
    }
}
#endif

/**
  * @brief    �������
  *
  * @param    
  *
  * @return   
  *
  * @note     ����ʹ�ô˺���ʱ�������Ҫװ���̣���ֹ���������������ֵ����װ������������������ֵ
  *
  * @example  
  *
  * @date     2019/5/23 ������
  */
#ifdef OLED
void Test_Servo(void)
{
    char txt[16];
    int servopwm = 0; 
    
    LCD_Init();
    LQ_KEY_Init();          //����������ڳ�ʼ��
    LCD_CLS();              //LCD����   
     
    /*��ʼ�����PWM�ӿ�  kPWM_PwmA  M3  M4*/
    LQ_PWM_Init(PWM2, kPWM_Module_3, kPWM_PwmA_B,  50);  //M3 M4
    
    LQ_SetServoDty(750);  //��ֵ
    
    LCD_P8x16Str(13,0,"LQ Servo PWM");
    
    while (1)
    {    
        
        switch(LQ_KEY_Read(0))  //��ⰴ��
        {
            case 0:
            break;
            case 1:
                servopwm -= 10;
                LQ_SetServoDty(750 + servopwm);//ˢ��servopwmƵ��
                break;           
            case 2:           
                servopwm = 0;
                LQ_SetServoDty(750 + servopwm);//ˢ��servopwmƵ��
                break;
            case 3:           
                servopwm += 10;
                LQ_SetServoDty(750 + servopwm);//ˢ��servopwmƵ��
                break;
        }
        sprintf(txt,"PWM: %4.2f %",(float)servopwm/100.0f);
        LCD_P8x16Str(2,3,txt);
        printf(txt); 
        
        //LED��˸
        LED_Color_Reverse(red);     //���   
        delayms(50);
    }
}

/**
  * @brief    �������
  *
  * @param    
  *
  * @return   
  *
  * @note     ���1�� ʹ�� L5  M5   ���2��ʹ��A8  A9  ���3��ʹ�� B9 C9  ���4��A10 J1
  *
  * @example  
  *
  * @date     2019/5/23 ������
  */
void Test_Motor(void)
{    
    char txt[16];
    short motorpwm=0;   
    LCD_Init();
    LQ_KEY_Init();          //����������ڳ�ʼ��
    LCD_CLS();              //LCD����    
    /*��ʼ�����PWM�ӿ�   */
    LQ_PWM_Init(PWM2, kPWM_Module_0, kPWM_PwmA_B, 12000);// A8 A9
    LQ_PWM_Init(PWM2, kPWM_Module_1, kPWM_PwmA_B, 12000);// B9 C9
    LQ_PWM_Init(PWM2, kPWM_Module_2, kPWM_PwmB,   12000);// A10
    LQ_PWM_Init(PWM1, kPWM_Module_1, kPWM_PwmA,   12000);// J1
    LQ_PWM_Init(PWM1, kPWM_Module_3, kPWM_PwmA_B, 12000);// L5 M5
    LCD_P8x16Str(13,0,(uint8_t*)"LQ Motor PWM");
    
    while (1)
    {        
        switch(LQ_KEY_Read(0))  //��ⰴ��
        {
            case 0:
                break;
            case 1:
                motorpwm -= 100;
                if(motorpwm < -10000) motorpwm = -10000;
                LQ_SetMotorDty(1, motorpwm);
                LQ_SetMotorDty(2, motorpwm);
                LQ_SetMotorDty(3, motorpwm);
                LQ_SetMotorDty(4, motorpwm);
                break;           
            case 3:           
                motorpwm += 100;
                if(motorpwm > 10000) motorpwm = 10000;
                LQ_SetMotorDty(1, motorpwm);
                LQ_SetMotorDty(2, motorpwm);
                LQ_SetMotorDty(3, motorpwm);
                LQ_SetMotorDty(4, motorpwm);
                break;
            case 2:
                motorpwm = 0;
                LQ_SetMotorDty(1, motorpwm);
                LQ_SetMotorDty(2, motorpwm);
                LQ_SetMotorDty(3, motorpwm);
                LQ_SetMotorDty(4, motorpwm);
            break;
        }
        
        sprintf(txt,"PWM: %4.2f %",motorpwm/100.0f);
        LCD_P8x16Str(2,3,(uint8_t*)txt);
        printf(txt); 
        
        //LED��˸
        LED_Color_Reverse(red);     //���   
        delayms(50);
    }
}
#endif

/**
  * @brief    ����PWM
  *
  * @param    
  *
  * @return   
  *
  * @note     ��������ĸ���ϵ�PWM�ӿ��Ƿ���PWM���������ʾ��������
  *
  * @example  
  *
  * @date     2019/5/23 ������
  */
void Test_PWM_nCH(void)
{    
    uint32_t pwmVal = 4;  
    
     /*��ʼ�����PWM�ӿ�  */
    LQ_PWM_Init(PWM2, kPWM_Module_0, kPWM_PwmA_B, 100);  // A8 A9
    LQ_PWM_Init(PWM2, kPWM_Module_1, kPWM_PwmA_B, 1000); //B9 C9
    LQ_PWM_Init(PWM2, kPWM_Module_2, kPWM_PwmB, 10000);  //  A10
    LQ_PWM_Init(PWM1, kPWM_Module_3, kPWM_PwmA_B, 20000);//L5 M5
    LQ_PWM_Init(PWM1, kPWM_Module_1, kPWM_PwmA,   12000);//J1
    LQ_PWM_Init(PWM2, kPWM_Module_3, kPWM_PwmA_B,  50);  //M3 M4

    while (1U)
    {
        delayms(100);        //��ʱ100����
        pwmVal = pwmVal + 4;
        
        /* Reset the duty cycle percentage */
        if (pwmVal > 100)
        {
            pwmVal =2;
        }
        LQ_PWM_SetDuty(PWM1,    kPWM_Module_1, kPWM_PwmA, pwmVal*50);
        LQ_PWMA_B_SetDuty(PWM1, kPWM_Module_3, pwmVal*100, pwmVal*50); 
        LQ_PWMA_B_SetDuty(PWM2, kPWM_Module_0, pwmVal*100, pwmVal*50);
        LQ_PWMA_B_SetDuty(PWM2, kPWM_Module_1, pwmVal*100, pwmVal*50);
        LQ_PWM_SetDuty(PWM2,    kPWM_Module_2, kPWM_PwmB , pwmVal*100);
        LQ_PWMA_B_SetDuty(PWM2, kPWM_Module_3, pwmVal*100, pwmVal*50);  
        
        LED_Color_Reverse(red);     //���   
        delayms(500);
    }
}