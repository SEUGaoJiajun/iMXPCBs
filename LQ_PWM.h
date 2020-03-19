/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技LPC546XX核心板
【编    写】CHIUSIR
【备    注】
【软件版本】V1.0
【最后更新】2017年11月19日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
【交流邮箱】chiusir@163.com
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
#ifndef __LQPWM_H__
#define __LQPWM_H__


/**
  * @brief    测试PWM
  *
  * @param    
  *
  * @return   
  *
  * @note     测试龙邱母板上的PWM接口是否有PWM输出，可用示波器测量
  *
  * @example  
  *
  * @date     2019/5/23 星期四
  */
void Test_PWM_nCH(void);

/**
  * @brief    电机测试
  *
  * @param    
  *
  * @return   
  *
  * @note     电机1： 使用 L5  M5   电机2：使用A8  A9  电机3：使用 B9 C9  电机4：A10 J1
  *
  * @example  
  *
  * @date     2019/5/23 星期四
  */
void Test_Motor(void);

/**
  * @brief    舵机测试
  *
  * @param    
  *
  * @return   
  *
  * @note     初次使用此函数时，舵机不要装舵盘，防止舵机卡死，设置中值后再装车，可以自行设置中值
  *
  * @example  
  *
  * @date     2019/5/23 星期四
  */
void Test_Servo(void);

/**
  * @brief    设置电机占空比
  *
  * @param    num： 1：电机1： 使用 L5  M5  
                    2：电机2： 使用 A8  A9  
                    3：电机3： 使用 B9  C9  
                    4：电机4： 使用 A10 J1
  *
  * @return   
  *
  * @note     电机正反转可以调节电机接线调整，也可以控制PWM调整  如果电机正反转和程序中定义的不一样，可以自行修改
  *
  * @example  
  *
  * @date     2019/5/23 星期四
  */
inline void LQ_SetMotorDty(uint8_t num, short duty);

/**
  * @brief    设置舵机占空比
  *
  * @param    duty          ：占空比*DUTY_MAX   
  *
  * @return   
  *
  * @note      舵机中值 1.5ms高电平的PWM波    限幅在 1.3 - 1.7ms之间
  *
  * @example  
  *
  * @date     2019/5/23 星期四
  */
inline void LQ_SetServoDty(uint16_t duty);

/**
  * @brief    同时设置 一个子模块的A 和 B相  用这个函数
  *
  * @param    base          ：PWM模块 PWM1~PWM4
  * @param    subModule     ：PWM模块下的子模块 kPWM_Module_0 ~ kPWM_Module_3 
  * @param    pwm_channels  ：PWM模块下的子模块 的通道 ： kPWM_PwmA 、 kPWM_PwmB  、 kPWM_PwmA_B 
  * @param    duty          ：占空比*DUTY_MAX  
  *
  * @return   
  *
  * @note     同时设置 一个子模块的A 和 B相  用这个函数
  * @note     默认对齐方式kPWM_SignedCenterAligned， 可以自行修改  
  *
  * @example  
  *
  * @date     2019/5/23 星期四
  */
inline void LQ_PWMA_B_SetDuty(PWM_Type *base, pwm_submodule_t subModule, uint16_t dutyA, uint16_t dutyB);


/**
  * @brief    设置占空比
  *
  * @param    base          ：PWM模块 PWM1~PWM4
  * @param    subModule     ：PWM模块下的子模块 kPWM_Module_0 ~ kPWM_Module_3 
  * @param    pwm_channels  ：PWM模块下的子模块 的通道 ： kPWM_PwmA 、 kPWM_PwmB  、 kPWM_PwmA_B 
  * @param    duty          ：占空比*DUTY_MAX  
  *
  * @return   
  *
  * @note     同时设置 一个子模块的A 和 B相不要用这个函数
  * @note     默认对齐方式kPWM_SignedCenterAligned， 可以自行修改  
  *
  * @example  
  *
  * @date     2019/5/23 星期四
  */
inline void LQ_PWM_SetDuty(PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwm_channels, uint16_t duty);

/**
  * @brief    PWM功能初始化
  *
  * @param    base          ：PWM模块 PWM1~PWM4
  * @param    subModule     ：PWM模块下的子模块 kPWM_Module_0 ~ kPWM_Module_3 
  * @param    pwm_channels  ：PWM模块下的子模块 的通道 ： kPWM_PwmA 、 kPWM_PwmB  、 kPWM_PwmA_B 
  * @param    Frequency     ：频率
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/23 星期四
  */
void LQ_PWM_Init(PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwm_channels, uint16_t Frequency);


#endif 



