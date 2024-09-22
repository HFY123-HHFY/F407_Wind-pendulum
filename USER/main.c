/**
    ******************************************************************************
    * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
    * @author  MCD Application Team
    * @version V1.8.1
    * @date    27-January-2022
    * @brief   Main program body
    ******************************************************************************
    * @attention
    *
    * Copyright (c) 2016 STMicroelectronics.
    * All rights reserved.
    *
    * This software is licensed under terms that can be found in the LICENSE file
    * in the root directory of this software component.
    * If no LICENSE file comes with this software, it is provided AS-IS.
    *
    ******************************************************************************
    */

/* Includes ------------------------------------------------------------------*/



#include "stm32f4xx.h"

#include "bsp.h"
#include <OLED.h>
#include <usart.h>
#include <delay.h>
#include <shell.h>
#include <mpu6050.h>
#include <inv_mpu.h>

//��������Ƕ�
float pitch,roll,yaw;
//����������ٶ�
//short 

/*

ÿһ�����ж��е�����Ϣ��������Ҳ���õ������Ҳ�������bug��

*/
int main(void) 
{
    
    /* ��������ĳ�ʼ�������������������  */
    if(BSP_Init())
    {
        printf("peripheral init failed\n");
        
    }
    else
    {
        printf("peripheral init done\n");
    }
     

    /* ǰ̨������ѯ  */
    while (1)
    {
        
        //printf("->pitch:%f\n",pitch);
        OLED_Printf(0,0,OLED_6X8,"pitch:%f",pitch);
        OLED_Update();
    }
    


    for(;;);
        

}





