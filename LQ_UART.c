/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱i.MX RT1052核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0，龙邱开源代码，仅供参考，后果自负
【最后更新】2018年10月18日
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
//LPUART6_RX     J11？G11

//LPUART7_TX     P3
//LPUART7_RX     N4

//LPUART8_TX     H2
//LPUART8_RX     J2

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
//IAR，需要在options -> C/C++compiler -> Preprocessor 添加宏定义 _DLIB_FILE_DESCRIPTOR
#if 1
//#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((LPUART1->STAT&LPUART_STAT_TDRE_MASK)==0);    //使用串口1作为printf的输出口
	LPUART1->DATA=(uint8_t)ch;	
	return ch;
}
#endif 


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】得到串口时钟频率 一般为80Mhz
【软件版本】V1.0
【最后更新】2018年10月18日 
【函数名】
【返回值】返回串口的时钟
【参数值】无
【实例】 
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
【作  者】LQ-005
【功能说明】初始化串口，设置波特率
【软件版本】V1.0
【最后更新】2018年10月18日 
【函数名】
【返回值】无
【参数值】无
【实例】 LQ_UART_Init(LPUART1, 115200);  //初始化串口1， 波特率115200
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_UART_Init(LPUART_Type *base, uint32_t bound)
{	
    if(base == LPUART1)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart1);	//使能LPUART1时钟
        //LPUART1所使用的IO功能配置，即：从ALT0~ALT7选择合适的功能。
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_LPUART1_TX,0U);	//LPUART1_TX   K14
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_LPUART1_RX,0U);	//LPUART1_RX   L14
        
        //配置IO引脚GPIO_AD_B0_12和GPIO_AD_B0_13的功能
        //低转换速度,驱动能力为R0/6,速度为100Mhz，关闭开路功能，使能pull/keepr
        //选择keeper功能，下拉100K Ohm，关闭Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_12_LPUART1_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_13_LPUART1_RX,0x10B0u); 
        
    }
    else if(base == LPUART2)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart2);	//使能LPUART1时钟
        //LPUART1所使用的IO功能配置，即：从ALT0~ALT7选择合适的功能。
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_LPUART2_TX,0U);	//LPUART2_TX    L11
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_LPUART2_RX,0U);	//LPUART2_RX    M12
        
        //配置IO引脚GPIO_AD_B0_12和GPIO_AD_B0_13的功能
        //低转换速度,驱动能力为R0/6,速度为100Mhz，关闭开路功能，使能pull/keepr
        //选择keeper功能，下拉100K Ohm，关闭Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_02_LPUART2_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_03_LPUART2_RX,0x10B0u); 
    }
    else if(base == LPUART3)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart3);	//使能LPUART1时钟
        //LPUART1所使用的IO功能配置，即：从ALT0~ALT7选择合适的功能。
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_LPUART3_TX,0U);	//LPUART3_TX     J12
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_LPUART3_RX,0U);	//LPUART3_RX     K10
        
//        IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_LPUART3_TX,0U);	
//        IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_LPUART3_RX,0U);	
        //配置IO引脚GPIO_AD_B0_12和GPIO_AD_B0_13的功能
        //低转换速度,驱动能力为R0/6,速度为100Mhz，关闭开路功能，使能pull/keepr
        //选择keeper功能，下拉100K Ohm，关闭Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_06_LPUART3_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_07_LPUART3_RX,0x10B0u); 
        
//        IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_08_LPUART3_TX,0x10B0u); 
//        IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_09_LPUART3_RX,0x10B0u); 
    }
    else if(base == LPUART4)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart4);	//使能LPUART1时钟
        //LPUART1所使用的IO功能配置，即：从ALT0~ALT7选择合适的功能。
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_LPUART4_TX,0U);	//LPUART4_TX     L5
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_01_LPUART4_RX,0U);	//LPUART4_RX     M5
        
        //配置IO引脚GPIO_AD_B0_12和GPIO_AD_B0_13的功能
        //低转换速度,驱动能力为R0/6,速度为100Mhz，关闭开路功能，使能pull/keepr
        //选择keeper功能，下拉100K Ohm，关闭Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_00_LPUART4_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_01_LPUART4_RX,0x10B0u); 
    }
    else if(base == LPUART5)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart5);	//使能LPUART1时钟
        //LPUART1所使用的IO功能配置，即：从ALT0~ALT7选择合适的功能。
        IOMUXC_SetPinMux(IOMUXC_GPIO_B1_12_LPUART5_TX,0U);	//LPUART5_TX       D13
        IOMUXC_SetPinMux(IOMUXC_GPIO_B1_13_LPUART5_RX,0U);	//LPUART5_RX       D14
        
        //配置IO引脚GPIO_AD_B0_12和GPIO_AD_B0_13的功能
        //低转换速度,驱动能力为R0/6,速度为100Mhz，关闭开路功能，使能pull/keepr
        //选择keeper功能，下拉100K Ohm，关闭Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_12_LPUART5_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_13_LPUART5_RX,0x10B0u); 
    }
    else if(base == LPUART6)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart6);	//使能LPUART1时钟
        //LPUART1所使用的IO功能配置，即：从ALT0~ALT7选择合适的功能。
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_LPUART6_TX,0U);	//LPUART6_TX   M11
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_03_LPUART6_RX,0U);	//LPUART6_RX   J11
        
        //配置IO引脚GPIO_AD_B0_12和GPIO_AD_B0_13的功能
        //低转换速度,驱动能力为R0/6,速度为100Mhz，关闭开路功能，使能pull/keepr
        //选择keeper功能，下拉100K Ohm，关闭Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_02_LPUART6_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_03_LPUART6_RX,0x10B0u); 
    }
    else if(base == LPUART7)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart7);	//使能LPUART1时钟
        //LPUART1所使用的IO功能配置，即：从ALT0~ALT7选择合适的功能。
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_08_LPUART7_TX,0U);	//LPUART7_TX   P3
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_09_LPUART7_RX,0U);	//LPUART7_RX   N4
        
        //配置IO引脚GPIO_AD_B0_12和GPIO_AD_B0_13的功能
        //低转换速度,驱动能力为R0/6,速度为100Mhz，关闭开路功能，使能pull/keepr
        //选择keeper功能，下拉100K Ohm，关闭Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_08_LPUART7_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_09_LPUART7_RX,0x10B0u); 
    }
    else if(base == LPUART8)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart8);	//使能LPUART1时钟
        //LPUART1所使用的IO功能配置，即：从ALT0~ALT7选择合适的功能。
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_LPUART8_TX,0U);	//LPUART8_TX    H2
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_LPUART8_RX,0U);	//LPUART8_RX    J2
        
        //配置IO引脚GPIO_AD_B0_12和GPIO_AD_B0_13的功能
        //低转换速度,驱动能力为R0/6,速度为100Mhz，关闭开路功能，使能pull/keepr
        //选择keeper功能，下拉100K Ohm，关闭Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_04_LPUART8_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_05_LPUART8_RX,0x10B0u); 
    }
	CLOCK_SetMux(kCLOCK_UartMux,0); 	//设置UART时钟源为PLL3 80Mhz，PLL3/6=480/6=80MHz
    CLOCK_SetDiv(kCLOCK_UartDiv,0); 	//设置UART时钟1分频，即UART时钟为80Mhz
	
    lpuart_config_t lpuart_config;              //串口配置结构体
	LPUART_GetDefaultConfig(&lpuart_config);    //得到默认配置，后面在根据实际情况配置
	
	lpuart_config.baudRate_Bps=bound;						//波特率
	lpuart_config.dataBitsCount=kLPUART_EightDataBits;		//8位
	lpuart_config.stopBitCount=kLPUART_OneStopBit;			//1位停止位
	lpuart_config.parityMode=kLPUART_ParityDisabled;		//无奇偶校验
	lpuart_config.enableRx=true;							//使能接收
	lpuart_config.enableTx=true;							//使能发送
	
    uint32_t  freq=0;							//串口的时钟源频率
	freq=LQ_GetUartSrcFreq();	                //得到串口时钟频率
    
	LPUART_Init(base,&lpuart_config,freq);	    //初始化LPUART1 

	//LPUART中断设置
	LPUART_EnableInterrupts(base,kLPUART_RxDataRegFullInterruptEnable); //使能接收中断  使用其他中断请自行修改
   
    if(base == LPUART1)
    {
        //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
       NVIC_SetPriority(LPUART1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
       EnableIRQ(LPUART1_IRQn);	                            //使能LPUART1中断      
    }
    else if(base == LPUART2)
    {
        //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
        NVIC_SetPriority(LPUART2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART2_IRQn);	                            //使能LPUART1中断      
    }
    else if(base == LPUART3)
    {
        //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
        NVIC_SetPriority(LPUART3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART3_IRQn);	                            //使能LPUART1中断    
    }
    else if(base == LPUART4)
    {
        //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
        NVIC_SetPriority(LPUART4_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART4_IRQn);	                            //使能LPUART1中断     
    }
    else if(base == LPUART5)
    {
        //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
        NVIC_SetPriority(LPUART5_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART5_IRQn);	                            //使能LPUART1中断     
    }
    else if(base == LPUART6)
    {
        //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
        NVIC_SetPriority(LPUART6_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART6_IRQn);	                            //使能LPUART1中断    
    }
    else if(base == LPUART7)
    {
        //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
        NVIC_SetPriority(LPUART7_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART7_IRQn);	                            //使能LPUART1中断       
    }
    else if(base == LPUART8)
    {
        //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
        NVIC_SetPriority(LPUART8_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART8_IRQn);	                            //使能LPUART1中断       
    }   

}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】发送一个字符
【软件版本】V1.0
【最后更新】2018年10月18日 
【函数名】
【返回值】无
【参数值】
【实例】 LQ_UART_PutChar(LPUART1, char);  //串口1  发送char
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_UART_PutChar(LPUART_Type *base, uint8_t data)
{
    while (!(base->STAT & LPUART_STAT_TDRE_MASK));    //等待base->STAT为空
    base->DATA = data;
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】Z
【功能说明】发送一个字符串
【软件版本】V1.0
【最后更新】2018年10月18日 
【函数名】
【返回值】无
【参数值】
【实例】 LQ_UART_PutBuff(LPUART1, buff, 10);//串口1，发送一个长度为10地址为buff的数组
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_UART_PutBuff(LPUART_Type *base, uint8_t * buff, uint32_t length)
{
    while (length--)
    {
        while (!(base->STAT & LPUART_STAT_TDRE_MASK));    //等待base->STAT为空
        base->DATA = *(buff++);
    }
}


uint8_t LPUART_RX_BUF[100];   //接收缓冲区
volatile static uint8_t __res;      //缓冲区下标
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】Z
【功能说明】LPUART1中断服务函数
【软件版本】V1.0
【最后更新】2018年10月18日 
【函数名】
【返回值】无
【参数值】无  
【实例】
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LPUART1_IRQHandler(void)
{
	if((LPUART1->STAT)&kLPUART_RxDataRegFullFlag)                          //接收中断
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART1);					//将数据缓存到LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//数据同步屏蔽指令
}
void LPUART2_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART2->STAT)&kLPUART_RxDataRegFullFlag) //接收中断
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART2);				    //将数据缓存到LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//数据同步屏蔽指令
}
void LPUART3_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART3->STAT)&kLPUART_RxDataRegFullFlag)                       //接收中断
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART3);					//将数据缓存到LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//数据同步屏蔽指令
}

void LPUART4_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART4->STAT)&kLPUART_RxDataRegFullFlag)                      //接收中断
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART4);				   //将数据缓存到LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//数据同步屏蔽指令
}

void LPUART5_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART5->STAT)&kLPUART_RxDataRegFullFlag)                       //接收中断
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART5);				    //将数据缓存到LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//数据同步屏蔽指令
}

void LPUART6_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART6->STAT)&kLPUART_RxDataRegFullFlag)                       //接收中断
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART6);					//将数据缓存到LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//数据同步屏蔽指令
}

void LPUART7_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART7->STAT)&kLPUART_RxDataRegFullFlag)                       //接收中断
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART7);					//将数据缓存到LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//数据同步屏蔽指令
}

void LPUART8_IRQHandler(void)
{
	static uint8_t __res=0;
	
	if((LPUART8->STAT)&kLPUART_RxDataRegFullFlag)                       //接收中断
	{
		LPUART_RX_BUF[__res] = LPUART_ReadByte(LPUART8);					//将数据缓存到LPUART_RX_BUF[100]
		__res ++;
	}
	__DSB();				//数据同步屏蔽指令
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】Z
【功能说明】测试串口模块
【软件版本】V1.0
【最后更新】2018年10月18日 
【函数名】
【返回值】无
【参数值】无  注意：使用DAPlink自带的串口时，不要一直发送，会导致系统重启 
【实例】 Test_UART(LPUART1, buff, 10);
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

void Test_UART(void)
{
    
    LED_Init();                      //LED初始化
    LQ_UART_Init(LPUART1, 115200);   //初始化串口
    LQ_UART_Init(LPUART2, 115200);  
    LQ_UART_Init(LPUART3, 57600);
    LQ_UART_Init(LPUART4, 38400);
    LQ_UART_Init(LPUART5, 19200);
    LQ_UART_Init(LPUART6, 9600);
    //    LQ_UART_Init(LPUART7, 256000);  //SPIFlash使用该引脚
    LQ_UART_Init(LPUART8, 256000);
    delayms(100);
    printf("\r\n龙邱串口测试例程\r\n");
    printf("串口模块波特率:\n");
    printf("LPUART1 init: 115200!\n");
    printf("LPUART2 init: 115200!\n");//打印信息
    printf("LPUART3 init: 57600!\n");
    printf("LPUART4 init: 38400!\n");
    printf("LPUART5 init: 19200!\n");
    printf("LPUART6 init: 9600!\n");
    printf("LPUART8 init: 256000!\n");
    while(1)
    {
        uint8_t a = 'a';
        LQ_UART_PutChar(LPUART1, a);           //打印字符a
        LQ_UART_PutChar(LPUART2, a+1);
        LQ_UART_PutChar(LPUART3, a+2);
        LQ_UART_PutChar(LPUART4, a+3);
        LQ_UART_PutChar(LPUART5, a+4);
        LQ_UART_PutChar(LPUART6, a+5);
        LQ_UART_PutChar(LPUART8, a+7);
        delayms(100);
        uint8_t buff[10] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
        LQ_UART_PutBuff(LPUART1, buff, 10);    //打印 十六进制字符串
        LQ_UART_PutBuff(LPUART2, buff, 10);
        LQ_UART_PutBuff(LPUART3, buff, 10);
        LQ_UART_PutBuff(LPUART4, buff, 10);
        LQ_UART_PutBuff(LPUART5, buff, 10);
        LQ_UART_PutBuff(LPUART6, buff, 10);
        LQ_UART_PutBuff(LPUART8, buff, 10);
        delayms(100);
        if(__res > 9)                             //测试串口接收功能，接收10个字符后将接收到的字符打印出来
        {
            __res = 0;                            //接受缓冲区满，直接覆盖
            printf("UART1 接收中断 OK！\n");
            printf("UART1 接收到如下数据：\n");
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