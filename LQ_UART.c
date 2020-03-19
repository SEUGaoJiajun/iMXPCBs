/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2018��10��18��
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
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"
#include "stdio.h"	

//LPUART1_TX     K14
//LPUART1_RX     L14

//LPUART2_TX     L11
//LPUART2_RX     M12

//LPUART3_TX     J12
//LPUART3_RX     K10

//LPUART4_TX     L5
//LPUART4_RX     M5

//LPUART5_TX     D13
//LPUART5_RX     D14

//LPUART6_TX     M11
//LPUART6_RX     J11��G11

//LPUART7_TX     P3
//LPUART7_RX     N4

//LPUART8_TX     H2
//LPUART8_RX     J2

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
//IAR����Ҫ��options -> C/C++compiler -> Preprocessor ��Ӻ궨�� _DLIB_FILE_DESCRIPTOR
#if 1
//#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((LPUART1->STAT&LPUART_STAT_TDRE_MASK)==0);    //ʹ�ô���1��Ϊprintf�������
	LPUART1->DATA=(uint8_t)ch;	
	return ch;
}
#endif 


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵�����õ�����ʱ��Ƶ�� һ��Ϊ80Mhz
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ�����ش��ڵ�ʱ��
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
uint32_t LQ_GetUartSrcFreq(void)
{
    uint32_t freq;

    /* To make it simple, we assume default PLL and divider settings, and the only variable
       from application is use PLL3 source or OSC source */
    if (CLOCK_GetMux(kCLOCK_UartMux) == 0) /* PLL3 div6 80M */
    {
        freq = (CLOCK_GetPllFreq(kCLOCK_PllUsb1) / 6U) / (CLOCK_GetDiv(kCLOCK_UartDiv) + 1U);
    }
    else
    {
        freq = CLOCK_GetOscFreq() / (CLOCK_GetDiv(kCLOCK_UartDiv) + 1U);
    }

    return freq;
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵������ʼ�����ڣ����ò�����
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� LQ_UART_Init(LPUART1, 115200);  //��ʼ������1�� ������115200
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_UART_Init(LPUART_Type *base, uint32_t bound)
{	
    if(base == LPUART1)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart1);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_LPUART1_TX,0U);	//LPUART1_TX   K14
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_LPUART1_RX,0U);	//LPUART1_RX   L14
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_12_LPUART1_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_13_LPUART1_RX,0x10B0u); 
        
    }
    else if(base == LPUART2)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart2);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_LPUART2_TX,0U);	//LPUART2_TX    L11
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_LPUART2_RX,0U);	//LPUART2_RX    M12
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_02_LPUART2_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_03_LPUART2_RX,0x10B0u); 
    }
    else if(base == LPUART3)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart3);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_LPUART3_TX,0U);	//LPUART3_TX     J12
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_LPUART3_RX,0U);	//LPUART3_RX     K10
        
//        IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_LPUART3_TX,0U);	
//        IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_LPUART3_RX,0U);	
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_06_LPUART3_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_07_LPUART3_RX,0x10B0u); 
        
//        IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_08_LPUART3_TX,0x10B0u); 
//        IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_09_LPUART3_RX,0x10B0u); 
    }
    else if(base == LPUART4)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart4);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_LPUART4_TX,0U);	//LPUART4_TX     L5
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_01_LPUART4_RX,0U);	//LPUART4_RX     M5
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_00_LPUART4_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_01_LPUART4_RX,0x10B0u); 
    }
    else if(base == LPUART5)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart5);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_B1_12_LPUART5_TX,0U);	//LPUART5_TX       D13
        IOMUXC_SetPinMux(IOMUXC_GPIO_B1_13_LPUART5_RX,0U);	//LPUART5_RX       D14
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_12_LPUART5_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_13_LPUART5_RX,0x10B0u); 
    }
    else if(base == LPUART6)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart6);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_LPUART6_TX,0U);	//LPUART6_TX   M11
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_03_LPUART6_RX,0U);	//LPUART6_RX   J11
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_02_LPUART6_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_03_LPUART6_RX,0x10B0u); 
    }
    else if(base == LPUART7)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart7);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_08_LPUART7_TX,0U);	//LPUART7_TX   P3
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_09_LPUART7_RX,0U);	//LPUART7_RX   N4
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_08_LPUART7_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_09_LPUART7_RX,0x10B0u); 
    }
    else if(base == LPUART8)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart8);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_LPUART8_TX,0U);	//LPUART8_TX    H2
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_LPUART8_RX,0U);	//LPUART8_RX    J2
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_04_LPUART8_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_05_LPUART8_RX,0x10B0u); 
    }
	CLOCK_SetMux(kCLOCK_UartMux,0); 	//����UARTʱ��ԴΪPLL3 80Mhz��PLL3/6=480/6=80MHz
    CLOCK_SetDiv(kCLOCK_UartDiv,0); 	//����UARTʱ��1��Ƶ����UARTʱ��Ϊ80Mhz
	
    lpuart_config_t lpuart_config;              //�������ýṹ��
	LPUART_GetDefaultConfig(&lpuart_config);    //�õ�Ĭ�����ã������ڸ���ʵ���������
	
	lpuart_config.baudRate_Bps=bound;						//������
	lpuart_config.dataBitsCount=kLPUART_EightDataBits;		//8λ
	lpuart_config.stopBitCount=kLPUART_OneStopBit;			//1λֹͣλ
	lpuart_config.parityMode=kLPUART_ParityDisabled;		//����żУ��
	lpuart_config.enableRx=true;							//ʹ�ܽ���
	lpuart_config.enableTx=true;							//ʹ�ܷ���
	
    uint32_t  freq=0;							//���ڵ�ʱ��ԴƵ��
	freq=LQ_GetUartSrcFreq();	                //�õ�����ʱ��Ƶ��
    
	LPUART_Init(base,&lpuart_config,freq);	    //��ʼ��LPUART1 

	//LPUART�ж�����
	LPUART_EnableInterrupts(base,kLPUART_RxDataRegFullInterruptEnable); //ʹ�ܽ����ж�  ʹ�������ж��������޸�
   
    if(base == LPUART1)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
       NVIC_SetPriority(LPUART1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
       EnableIRQ(LPUART1_IRQn);	                            //ʹ��LPUART1�ж�      
    }
    else if(base == LPUART2)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART2_IRQn);	                            //ʹ��LPUART1�ж�      
    }
    else if(base == LPUART3)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART3_IRQn);	                            //ʹ��LPUART1�ж�    
    }
    else if(base == LPUART4)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART4_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART4_IRQn);	                            //ʹ��LPUART1�ж�     
    }
    else if(base == LPUART5)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART5_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART5_IRQn);	                            //ʹ��LPUART1�ж�     
    }
    else if(base == LPUART6)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART6_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART6_IRQn);	                            //ʹ��LPUART1�ж�    
    }
    else if(base == LPUART7)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART7_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART7_IRQn);	                            //ʹ��LPUART1�ж�       
    }
    else if(base == LPUART8)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART8_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART8_IRQn);	                            //ʹ��LPUART1�ж�       
    }   

}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵��������һ���ַ�
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ��
��ʵ���� LQ_UART_PutChar(LPUART1, char);  //����1  ����char
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_UART_PutChar(LPUART_Type *base, uint8_t data)
{
    while (!(base->STAT & LPUART_STAT_TDRE_MASK));    //�ȴ�base->STATΪ��
    base->DATA = data;
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵��������һ���ַ���
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ��
��ʵ���� LQ_UART_PutBuff(LPUART1, buff, 10);//����1������һ������Ϊ10��ַΪbuff������
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_UART_PutBuff(LPUART_Type *base, uint8_t * buff, uint32_t length)
{
    while (length--)
    {
        while (!(base->STAT & LPUART_STAT_TDRE_MASK));    //�ȴ�base->STATΪ��
        base->DATA = *(buff++);
    }
}


uint8_t LPUART_RX_BUF[100];   //���ջ�����
volatile static uint8_t __res;      //�������±�
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����LPUART1�жϷ�����
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����  
��ʵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LPUART1_IRQHandler(void)
{
	if((LPUART1->STAT)&kLPUART_RxDataRegFullFlag)                          //�����ж�
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART1);					//�����ݻ��浽LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//����ͬ������ָ��
}
void LPUART2_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART2->STAT)&kLPUART_RxDataRegFullFlag) //�����ж�
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART2);				    //�����ݻ��浽LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//����ͬ������ָ��
}
void LPUART3_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART3->STAT)&kLPUART_RxDataRegFullFlag)                       //�����ж�
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART3);					//�����ݻ��浽LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//����ͬ������ָ��
}

void LPUART4_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART4->STAT)&kLPUART_RxDataRegFullFlag)                      //�����ж�
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART4);				   //�����ݻ��浽LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//����ͬ������ָ��
}

void LPUART5_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART5->STAT)&kLPUART_RxDataRegFullFlag)                       //�����ж�
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART5);				    //�����ݻ��浽LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//����ͬ������ָ��
}

void LPUART6_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART6->STAT)&kLPUART_RxDataRegFullFlag)                       //�����ж�
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART6);					//�����ݻ��浽LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//����ͬ������ָ��
}

void LPUART7_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART7->STAT)&kLPUART_RxDataRegFullFlag)                       //�����ж�
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART7);					//�����ݻ��浽LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//����ͬ������ָ��
}

void LPUART8_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART8->STAT)&kLPUART_RxDataRegFullFlag)                       //�����ж�
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART8);					//�����ݻ��浽LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//����ͬ������ָ��
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵�������Դ���ģ��
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����  ע�⣺ʹ��DAPlink�Դ��Ĵ���ʱ����Ҫһֱ���ͣ��ᵼ��ϵͳ���� 
��ʵ���� Test_UART(LPUART1, buff, 10);
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

void Test_UART(void)
{
    
    LED_Init();                      //LED��ʼ��
    LQ_UART_Init(LPUART1, 115200);   //��ʼ������
    LQ_UART_Init(LPUART2, 115200);  
    LQ_UART_Init(LPUART3, 57600);
    LQ_UART_Init(LPUART4, 38400);
    LQ_UART_Init(LPUART5, 19200);
    LQ_UART_Init(LPUART6, 9600);
    //    LQ_UART_Init(LPUART7, 256000);  //SPIFlashʹ�ø�����
    LQ_UART_Init(LPUART8, 256000);
    delayms(100);
    printf("\r\n���񴮿ڲ�������\r\n");
    printf("����ģ�鲨����:\n");
    printf("LPUART1 init: 115200!\n");
    printf("LPUART2 init: 115200!\n");//��ӡ��Ϣ
    printf("LPUART3 init: 57600!\n");
    printf("LPUART4 init: 38400!\n");
    printf("LPUART5 init: 19200!\n");
    printf("LPUART6 init: 9600!\n");
    printf("LPUART8 init: 256000!\n");
    while(1)
    {
        uint8_t a = 'a';
        LQ_UART_PutChar(LPUART1, a);           //��ӡ�ַ�a
        LQ_UART_PutChar(LPUART2, a+1);
        LQ_UART_PutChar(LPUART3, a+2);
        LQ_UART_PutChar(LPUART4, a+3);
        LQ_UART_PutChar(LPUART5, a+4);
        LQ_UART_PutChar(LPUART6, a+5);
        LQ_UART_PutChar(LPUART8, a+7);
        delayms(100);
        uint8_t buff[10] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
        LQ_UART_PutBuff(LPUART1, buff, 10);    //��ӡ ʮ�������ַ���
        LQ_UART_PutBuff(LPUART2, buff, 10);
        LQ_UART_PutBuff(LPUART3, buff, 10);
        LQ_UART_PutBuff(LPUART4, buff, 10);
        LQ_UART_PutBuff(LPUART5, buff, 10);
        LQ_UART_PutBuff(LPUART6, buff, 10);
        LQ_UART_PutBuff(LPUART8, buff, 10);
        delayms(100);
        if(__res > 9)                             //���Դ��ڽ��չ��ܣ�����10���ַ��󽫽��յ����ַ���ӡ����
        {
            __res = 0;                            //���ܻ���������ֱ�Ӹ���
            printf("UART1 �����ж� OK��\n");
            printf("UART1 ���յ��������ݣ�\n");
            for(uint8_t i = 0; i < 10; i++)
            {
                printf("%c", LPUART_RX_BUF[i]);
            }
            printf("\n");
            delayms(100);
        }
        LED_Color_Reverse(blue);
    }  
}