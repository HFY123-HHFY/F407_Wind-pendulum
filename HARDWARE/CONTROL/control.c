/*

����ļ�  ʵ����  PID���Ƽ��㣬PWM���  �Ƿ����ڿ����е��õ���Ҫ����

*/


#include <stdio.h>
#include <stm32f4xx.h>
#include <bsp.h>

//PID����
float Kp=0,
      Ki=0,
      Kd=0;



/// @brief PID���㺯��
/// @param target Ŀ��ֵ
/// @param feedback ��ǰֵ
/// @return ����ֵ�������ͣ���������
float pidControl(float target, float feedback)
{

    // ����������
    static float error = 0;
    static float lastError = 0;
    static float integral = 0;
    static float derivative = 0;

    // ��������޷�����
    static float integralMin = 0;
    static float integralMax = 0;

    // ����PID�������
    static float output = 0;

    // �������
    error = target - feedback;

    // ���������
    integral += error;

    // ���ƻ������ڻ����޷���Χ��
    if (integral < integralMin) {
        integral = integralMin;
    } else if (integral > integralMax) {
        integral = integralMax;
    }

    // ����΢����
    derivative = error - lastError;

    // ����PID���
    output = Kp * error + Ki * integral + Kd * derivative;

    // ����������
    lastError = error;

    return output;
}

//PWM��������ø߼���ʱ��TIM8�����4·PWM
void Motor_PWM_TIM8_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_Config(GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9, GPIO_Mode_AF, GPIO_PuPd_NOPULL);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM8);

    // ����TIM8
    TIM_TimeBaseInitTypeDef TIM8_TimeBaseInitStruct;
    TIM8_TimeBaseInitStruct.TIM_Period = 8400-1;  
    TIM8_TimeBaseInitStruct.TIM_Prescaler = 1;  
    TIM8_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM8_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM8, &TIM8_TimeBaseInitStruct);


    // ����TIM8��4��ͨ��ΪPWMģʽ
    TIM_OCInitTypeDef TIM8_OCInitStruct;
    TIM8_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM8_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM8_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM8_OCInitStruct.TIM_Pulse = 0;
    TIM8_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM8_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM8_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM8_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

    TIM_OC1Init(TIM8, &TIM8_OCInitStruct);
    TIM_OC2Init(TIM8, &TIM8_OCInitStruct);
    TIM_OC3Init(TIM8, &TIM8_OCInitStruct);
    TIM_OC4Init(TIM8, &TIM8_OCInitStruct);

    TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM8, ENABLE);

    printf("->Motor->TIM8_OC1_OC2_OC3_OC4 Init  done\n");

    // ʹ��TIM8�����
    TIM_CtrlPWMOutputs(TIM8, ENABLE);
    // ʹ��TIM8
    TIM_Cmd(TIM8, ENABLE);

    printf("->Motor->TIM1_TIM8 Enable  done\n");
}

