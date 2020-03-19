/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱i.MX RT1052核心板-智能车板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2017年2月1日
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
#include "include.h"

/* //ADC资源序号与对应的管脚，      管脚名称      BGA管脚编号
ADC1_IN0  Analog channel 1 input0   GPIO_AD_B1_11   J13
ADC1_IN1  Analog channel 1 input1   GPIO_AD_B0_12   K14 
ADC1_IN2  Analog channel 1 input2   GPIO_AD_B0_13   L14
ADC1_IN3  Analog channel 1 input3   GPIO_AD_B0_14   H14
ADC1_IN4  Analog channel 1 input4   GPIO_AD_B0_15   L10
ADC1_IN5  Analog channel 1 input5   GPIO_AD_B1_00   J11
ADC1_IN6  Analog channel 1 input6   GPIO_AD_B1_01   K11
ADC1_IN7  Analog channel 1 input7   GPIO_AD_B1_02   L11
ADC1_IN8  Analog channel 1 input8   GPIO_AD_B1_03   M12
ADC1_IN9  Analog channel 1 input9   GPIO_AD_B1_04   L12
ADC1_IN10 Analog channel 1 input10  GPIO_AD_B1_05   K12
ADC1_IN11 Analog channel 1 input11  GPIO_AD_B1_06   J12
ADC1_IN12 Analog channel 1 input12  GPIO_AD_B1_07   K10
ADC1_IN13 Analog channel 1 input13  GPIO_AD_B1_08   H13
ADC1_IN14 Analog channel 1 input14  GPIO_AD_B1_09   M13
ADC1_IN15 Analog channel 1 input15  GPIO_AD_B1_10   L13

ADC2_IN0  Analog channel 2 input0   GPIO_AD_B1_11   J13
ADC2_IN1  Analog channel 2 input1   GPIO_AD_B1_12   H12
ADC2_IN2  Analog channel 2 input2   GPIO_AD_B1_13   H11
ADC2_IN3  Analog channel 2 input3   GPIO_AD_B1_14   G12
ADC2_IN4  Analog channel 2 input4   GPIO_AD_B1_15   J14
ADC2_IN5  Analog channel 1 input5   GPIO_AD_B1_00   J11
ADC2_IN6  Analog channel 1 input6   GPIO_AD_B1_01   K11
ADC2_IN7  Analog channel 1 input7   GPIO_AD_B1_02   L11
ADC2_IN8  Analog channel 1 input8   GPIO_AD_B1_03   M12
ADC2_IN9  Analog channel 1 input9   GPIO_AD_B1_04   L12
ADC2_IN10 Analog channel 1 input10  GPIO_AD_B1_05   K12
ADC2_IN11 Analog channel 1 input11  GPIO_AD_B1_06   J12
ADC2_IN12 Analog channel 1 input12  GPIO_AD_B1_07   K10
ADC2_IN13 Analog channel 1 input13  GPIO_AD_B1_08   H13
ADC2_IN14 Analog channel 1 input14  GPIO_AD_B1_09   M13
ADC2_IN15 Analog channel 1 input15  GPIO_AD_B1_10   L13
*/

//LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//【作  者】CHIUSIR
//【功能说明】初始化ADC模块
//【软件版本】V1.0
//【最后更新】2017年8月4日 
//【函数名】void LQADC_Init(ADC_Type *base)
//【参数值】ADC1,ADC2
//【返回值】无
//【简  例】ADC_init（ADC1）初始化ADC1模块 
//QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ

void LQADC_Init(ADC_Type *base)
{          
    adc_config_t adcConfigStrcut;   

    /*
    *  config->enableAsynchronousClockOutput = true;
     *  config->enableOverWrite =                 false;
       *  config->enableContinuousConversion =    false;
       *  config->enableHighSpeed =               false;
       *  config->enableLowPower =                false;
       *  config->enableLongSample =              false;
       *  config->referenceVoltageSource =        kADC_ReferenceVoltageSourceVref;
       *  config->samplePeriodMode =              kADC_SamplePeriod2or12Clocks;
       *  config->clockSource =                   kADC_ClockSourceAD;
       *  config->clockDriver =                   kADC_ClockDriver1;
       *  config->resolution =                    kADC_Resolution12Bit;
       */
    ADC_GetDefaultConfig(&adcConfigStrcut);
    //adcConfigStrcut.resolution=kADC_Resolution12Bit;              //默认均为12位
    ADC_Init(base, &adcConfigStrcut);                               //初始化
    
    ADC_SetHardwareAverageConfig(base, kADC_HardwareAverageCount32);//硬件平均值
    /* Do auto hardware calibration. */
    ADC_DoAutoCalibration(base);                                    //硬件校准
    
 }
//LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//【作  者】CHIUSIR
//【功能说明】读取ADC 第 通道数值
//【软件版本】V1.0
//【最后更新】2017年8月4日 
//【函数名】uint16_t ReadADC(ADC_Type *base,ADCn_Ch_e CH)
//【参数值】base：ADC1,ADC2；CH：0~31
//【返回值】12位adc值
//【简  例】batv=ReadADC(ADC1,ADC1_CH0)，读取ADC1第0通道数值
//QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
uint16_t ReadADC(ADC_Type *base,ADCn_Ch_e CH)
{     
  adc_channel_config_t adcChannelConfigStruct;                          //配置结构体
  
  adcChannelConfigStruct.channelNumber = CH;
  adcChannelConfigStruct.enableInterruptOnConversionCompleted = false;  //转换完成中断
  ADC_SetChannelConfig(base, 0, &adcChannelConfigStruct);                //开启转换
  while (0U == ADC_GetChannelStatusFlags(base,0)){;}                    //等待转换完成
  return (ADC_GetChannelConversionValue(base,0));                       //返回转换结果
}


//LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//【作  者】CHIUSIR
//【功能说明】测试并转换为小数值，串口和OLED输出
//【软件版本】V1.0
//【最后更新】2017年8月4日 
//【函数名】uint16_t ReadADC(ADC_Type *base,ADCn_Ch_e CH)
//【参数值】无
//【返回值】无
//【简  例】Test_ADC()，
//QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
#ifdef OLED
void Test_ADC(void)
{
    char txt[16];   
    LCD_Init();                  //LCD初始化
    LCD_CLS();                   //LCD清屏
    LCD_P8x16Str(4,0,"LQ ADC Test"); 
    printf("\r\nLQ ADC Test");
    LQ_KEY_Init();               //按键初始化
    LQADC_Init(ADC1);            //电源低压报警ADC初始化
    uint16_t batv0=(uint16_t)(ReadADC(ADC1,ADC1_CH10)*4.6);  //获取ADC值 K12 电池电压 * 100
    uint16_t batv1=(uint16_t)(ReadADC(ADC1,ADC1_CH4)*0.806);  //获取ADC值 L10
    uint16_t batv2=(uint16_t)(ReadADC(ADC1,ADC1_CH7)*0.806);  //获取ADC值 L11
    uint16_t batv3=(uint16_t)(ReadADC(ADC1,ADC1_CH8)*0.806);  //获取ADC值 M12
    uint16_t batv4=(uint16_t)(ReadADC(ADC1,ADC1_CH3)*0.806);  //获取ADC值 H14
    uint16_t batv5=(uint16_t)(ReadADC(ADC1,ADC1_CH1)*0.806);  //获取ADC值 K14
    uint16_t batv6=(uint16_t)(ReadADC(ADC1,ADC1_CH2)*0.806);  //获取ADC值 L14
    uint8_t key = 0;
    while (1)
    {           
        //测试ADC转换   ADC的基准电压是3.3V的，RT1052母板上，K12通过1K和4.7K的分压电阻测量电池电压 电池电压 =  （ReadADC / 4095） * 3.3 * （1 + 4.7）
        batv0 = (uint16_t)(batv0*0.7 + 0.3*(uint16_t)(ReadADC(ADC1,ADC1_CH10)*4.6));//电压采集 
        
        batv1 = (uint16_t)(batv1*0.7 + 0.3*ReadADC(ADC1,ADC1_CH4)*0.806);             //获取ADC值 L10
        batv2 = (uint16_t)(batv2*0.7 + 0.3*ReadADC(ADC1,ADC1_CH7)*0.806);             //获取ADC值 L11
        batv3 = (uint16_t)(batv3*0.7 + 0.3*ReadADC(ADC1,ADC1_CH8)*0.806);             //获取ADC值 M12
        batv4 = (uint16_t)(batv4*0.7 + 0.3*ReadADC(ADC1,ADC1_CH3)*0.806);             //获取ADC值 H14
        batv5 = (uint16_t)(batv5*0.7 + 0.3*ReadADC(ADC1,ADC1_CH1)*0.806);             //获取ADC值 K14
        batv6 = (uint16_t)(batv6*0.7 + 0.3*ReadADC(ADC1,ADC1_CH2)*0.806);  
        
        switch(LQ_KEY_Read(1))     //按键按下翻页
        {
            case 1:
                LCD_CLS();          //LCD清屏
                key = 0;            //K0 按下 第一页
                break;           
            case 2: 
                LCD_CLS();          //LCD清屏
                key = 1;            //K1 按下 第二页
                break;
            default:
                
                break;
        }
        
        if(0 == key)
        {
            LCD_P8x16Str(4,0,"LQ ADC Test Bat"); 
            
            printf("\r\n/***********************%3.2fV\r\n ",batv0/1000.0f);
            sprintf(txt,"BAT:%3.2fV ",batv0/1000.0f);
            LCD_P8x16Str(20,2,txt);
            
            printf("\r\n/***********************%3.2fV\r\n ",batv1/1000.0f);
            sprintf(txt,"L10:%3.2fV ",batv1/1000.0f);
            LCD_P8x16Str(20,4,txt);
            
            printf("\r\n/***********************%3.2fV\r\n ",batv2/1000.0f);
            sprintf(txt,"L11:%3.2fV ",batv2/1000.0f);
            LCD_P8x16Str(20,6,txt);
            
        }
        if(1 == key)
        {
            printf("\r\n/***********************%3.2fV\r\n ",batv3/1000.0f);
            sprintf(txt,"M12:%3.2fV ",batv3/1000.0f);
            LCD_P8x16Str(20,0,txt);
            
            printf("\r\n/***********************%3.2fV\r\n ",batv4/1000.0f);
            sprintf(txt,"H14:%3.2fV ",batv4/1000.0f);
            LCD_P8x16Str(20,2,txt);
            
            printf("\r\n/***********************%3.2fV\r\n ",batv5/1000.0f);
            sprintf(txt,"K14:%3.2fV ",batv5/1000.0f);
            LCD_P8x16Str(20,4,txt);
            
            printf("\r\n/***********************%3.2fV\r\n ",batv6/1000.0f);
            sprintf(txt,"L14:%3.2fV ",batv6/1000.0f);
            LCD_P8x16Str(20,6,txt);    
        }
   
        LED_Color_Reverse(blue);    //蓝灯   
        delayms(100);
    }
}
#endif
//LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//【作  者】CHIUSIR
//【功能说明】测试并转换为小数值，串口和TFT1.8输出
//【软件版本】V1.0
//【最后更新】2017年8月4日 
//【函数名】uint16_t ReadADC(ADC_Type *base,ADCn_Ch_e CH)
//【参数值】无
//【返回值】无
//【简  例】Test_ADC()，
//QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
#ifdef TFT1_8
void Test_ADC(void)
{
    char txt[16];
      
    TFTSPI_Init(1);                 //LCD初始化  0:横屏  1：竖屏
    TFTSPI_CLS(u16BLUE);            //清屏
    TFTSPI_P8X16Str(2,0,"LQ ADC Test",u16RED,u16BLUE);
    printf("\r\nLQ ADC Test");

    LQADC_Init(ADC1);             //电源低压报警ADC初始化
    uint16_t batv0=(uint16_t)(ReadADC(ADC1,ADC1_CH10)*4.6);   //获取ADC值 K12 电池电压 * 1000
    uint16_t batv1=(uint16_t)(ReadADC(ADC1,ADC1_CH4)*0.806);  //获取ADC值 L10
    uint16_t batv2=(uint16_t)(ReadADC(ADC1,ADC1_CH7)*0.806);  //获取ADC值 L11
    uint16_t batv3=(uint16_t)(ReadADC(ADC1,ADC1_CH8)*0.806);  //获取ADC值 M12
    uint16_t batv4=(uint16_t)(ReadADC(ADC1,ADC1_CH3)*0.806);  //获取ADC值 H14
    uint16_t batv5=(uint16_t)(ReadADC(ADC1,ADC1_CH1)*0.806);  //获取ADC值 K14
    uint16_t batv6=(uint16_t)(ReadADC(ADC1,ADC1_CH2)*0.806);  //获取ADC值 L14
    while (1)
    {           
        //测试ADC转换   ADC的基准电压是3.3V的，RT1052母板上，K12通过1K和4.7K的分压电阻测量电池电压 电池电压 =  （ReadADC / 4095） * 3.3 * （1 + 4.7）
        batv0 = (uint16_t)(batv0*0.7 + 0.3*(uint16_t)(ReadADC(ADC1,ADC1_CH10)*4.6));  //电压采集  mv
        
        batv1 = (uint16_t)(batv1*0.7 + 0.3*ReadADC(ADC1,ADC1_CH4)*0.806);             //获取ADC值 L10
        batv2 = (uint16_t)(batv2*0.7 + 0.3*ReadADC(ADC1,ADC1_CH7)*0.806);             //获取ADC值 L11
        batv3 = (uint16_t)(batv3*0.7 + 0.3*ReadADC(ADC1,ADC1_CH8)*0.806);             //获取ADC值 M12
        batv4 = (uint16_t)(batv4*0.7 + 0.3*ReadADC(ADC1,ADC1_CH3)*0.806);             //获取ADC值 H14
        batv5 = (uint16_t)(batv5*0.7 + 0.3*ReadADC(ADC1,ADC1_CH1)*0.806);             //获取ADC值 K14
        batv6 = (uint16_t)(batv6*0.7 + 0.3*ReadADC(ADC1,ADC1_CH2)*0.806);  
        
        printf("\r\n/***********************%3.2fV\r\n ",batv0/1000.0f);
        sprintf(txt,"BAT:%3.2fV ",batv0/1000.0f);
        TFTSPI_P8X16Str(3,1,txt,u16RED,u16BLUE);
                                  
        printf("\r\n/***********************%3.2fV\r\n ",batv1/1000.0f);
        sprintf(txt,"L10:%3.2fV ",batv1/1000.0f);
        TFTSPI_P8X16Str(3,2,txt,u16RED,u16BLUE);
        
        printf("\r\n/***********************%3.2fV\r\n ",batv2/1000.0f);
        sprintf(txt,"L11:%3.2fV ",batv2/1000.0f);
        TFTSPI_P8X16Str(3,3,txt,u16RED,u16BLUE);
        
        printf("\r\n/***********************%3.2fV\r\n ",batv3/1000.0f);
        sprintf(txt,"M12:%3.2fV ",batv3/1000.0f);
        TFTSPI_P8X16Str(3,4,txt,u16RED,u16BLUE);
        
        printf("\r\n/***********************%3.2fV\r\n ",batv4/1000.0f);
        sprintf(txt,"H14:%3.2fV ",batv4/1000.0f);
        TFTSPI_P8X16Str(3,5,txt,u16RED,u16BLUE);
        
        printf("\r\n/***********************%3.2fV\r\n ",batv5/1000.0f);
        sprintf(txt,"K14:%3.2fV ",batv5/1000.0f);
        TFTSPI_P8X16Str(3,6,txt,u16RED,u16BLUE);
        
        printf("\r\n/***********************%3.2fV\r\n ",batv6/1000.0f);
        sprintf(txt,"L14:%3.2fV ",batv6/1000.0f);
        TFTSPI_P8X16Str(3,7,txt,u16RED,u16BLUE);
        
        LED_Color_Reverse(blue);    //蓝灯   
        delayms(100);
    }
}
#endif