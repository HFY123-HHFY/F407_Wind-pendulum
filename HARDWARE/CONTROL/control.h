#ifndef CONTROL_H
#define CONTROL_H

/* ����  */
void Motor_PWM_TIM8_Init();

/* ��һ��  */
float PidControl_LineState(float target, float feedback);
float PidControl_SwingState(float target, float feedback);
void Task_MoveLine();

/* �ڶ���  */



#endif 