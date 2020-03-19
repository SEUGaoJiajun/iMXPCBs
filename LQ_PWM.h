/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�LPC546XX���İ�
����    д��CHIUSIR
����    ע��
������汾��V1.0
�������¡�2017��11��19��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
���������䡿chiusir@163.com
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
#ifndef __LQPWM_H__
#define __LQPWM_H__


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
void Test_PWM_nCH(void);

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
void Test_Motor(void);

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
void Test_Servo(void);

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
inline void LQ_SetMotorDty(uint8_t num, short duty);

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
inline void LQ_SetServoDty(uint16_t duty);

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
inline void LQ_PWMA_B_SetDuty(PWM_Type *base, pwm_submodule_t subModule, uint16_t dutyA, uint16_t dutyB);


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
inline void LQ_PWM_SetDuty(PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwm_channels, uint16_t duty);

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
void LQ_PWM_Init(PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwm_channels, uint16_t Frequency);


#endif 



