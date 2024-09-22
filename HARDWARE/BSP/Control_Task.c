/*


����ļ� װ����  �����ڵĺ��Ĳ���---���Ʋ���



*/


#include <stm32f4xx.h>
#include <bsp.h>
#include <control.h>
#include <usart.h>
#include <mpu6050.h>
#include <inv_mpu.h>
#include <stm32f4xx_exti.h>
#include <OLED.h>

//������ԣ���������λ
#define Motor       TIM8
#define LineOut     CCR1
#define LineIn      CCR4
#define SwingOut    CCR2
#define SwingIn     CCR3

extern float pitch,roll,yaw;

/// @brief MPU6050��ֵ�������ⲿ�жϺ���      
void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line15) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line15);

        mpu_dmp_get_data(&pitch, &roll, &yaw);

        

        
    }
}


/*
    PID����1�ջ�����ֱ��״̬��ƫ��
    PID����2�ջ�����ֱ�߰ڶ���Խ��
    

*/
void Task_MoveLine()
{
    //�涨��ˮƽֱ��
    float target_roll = 0;
    static float target_pitch = 15;

    float LineState_Output,SwingState_Output;

    LineState_Output= PidControl_LineState(target_roll, roll);
    SwingState_Output= PidControl_SwingState(target_pitch, pitch);

    //����OUt��ȫ��Ϊ����IN��ȫ��Ϊ��
    if(LineState_Output>0)
    {
        Motor->LineOut = 0;
        Motor->LineIn = (uint32_t)SwingState_Output;
        if(SwingState_Output>0)
        {
            Motor->SwingOut = (uint32_t)LineState_Output;
            Motor->SwingIn= 0;
        }
        else if(SwingState_Output<0)
        {
            Motor->SwingOut = 0;
            Motor->SwingIn = -(uint32_t)LineState_Output;
        }
        else
        {
            Motor->SwingOut = 0;
            Motor->SwingIn = 0;
        }
    }
    else if(LineState_Output<0)
    {
        Motor->LineOut = -(uint32_t)SwingState_Output;
        Motor->LineIn = 0;
        if(SwingState_Output>0)
        {
            Motor->SwingOut = (uint32_t)LineState_Output;
            Motor->SwingIn = 0;
        }
        else if(SwingState_Output<0)
        {
            Motor->SwingOut = 0;
            Motor->SwingIn = -(uint32_t)LineState_Output;
        }
        else
        {
            Motor->SwingOut = 0;
            Motor->SwingIn = 0;
        }
    }
    else
    {
        Motor->LineOut = 0;
        Motor->LineIn = 0;
        if(SwingState_Output>0)
        {
            Motor->SwingOut = (uint32_t)LineState_Output;
            Motor->SwingIn = 0;
        }
        else if(SwingState_Output<0)
        {
            Motor->SwingOut = 0;
            Motor->SwingIn = -(uint32_t)LineState_Output;
        }
        else
        {
            Motor->SwingOut = 0;
            Motor->SwingIn = 0;
        }
    }
    
}