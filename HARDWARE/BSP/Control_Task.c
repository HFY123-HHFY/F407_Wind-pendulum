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


/* ��������ֱ��ģʽ  */
void Task_MoveLine()
{
    
    
}