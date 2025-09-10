#include "OLED.h"
#include "MPU6050.h"

// TODO: 完成灰度传感器的驱动
// GSS->需要四个IO口
#include "GRAYSCALE.h"

#include "ENCODER.h"
#include "TIM.h"
#include "MOTOR.h"
#include "PID.h"
#include "math.h"

float dt = 0.01f; // 10ms
float yaw = 0.0f;
PID pid_v_L, pid_v_R, pid_yaw;
int16_t v_setpoint_L = 0, yaw_setpoint = 0, v_setpoint_R = 0;

float t;

MPU6050 mpu;
MPU_Conv conv;
float offset_z = 0.0f;

int main()
{
    OLED_Init();
    MPU6050_init();
    ENCODER_L_Init();
    MOTOR_Init();
    // TODO: 初始化灰度传感器
    // TODO: PID参数的调试
    PID_Init(&pid_v_L, 0.3f, 0.3f, 0.2f, 900.0f, 900.0f);
    PID_Init(&pid_v_R, 0.3f, 0.3f, 0.2f, 900.0f, 900.0f);
    PID_Init(&pid_yaw, 1.5f, 0.0f, 0.0f, 80.0f, 80.0f);
    // TODO: 完成setpoint的设置
    pid_v_L.setpoint = 500.0f;
    pid_v_R.setpoint = 500.0f;
    offset_z = MPU_GetOffset_z();

    // 需要在计算完OFFSET_Z后初始化
    TIM_init();

    while (1)
    {
        if (Gray_scale_sensor_get() == 0b0110 || Gray_scale_sensor_get() == 0b1111)
        {
            yaw_setpoint = yaw;
        }
        else if (Gray_scale_sensor_get() == 0b1110)
        {
            yaw_setpoint = 30;
        }
        else if (Gray_scale_sensor_get() == 0b0111)
        {
            yaw_setpoint = -30;
        }
        else if (Gray_scale_sensor_get() == 0b1000)
        {
            yaw_setpoint = 60;
        }
        else if (Gray_scale_sensor_get() == 0b0001)
        {
            yaw_setpoint = -60;
        }
        OLED_ShowString(0, 0, "L:s", OLED_6X8);
        OLED_ShowFloatNum(32, 0, pid_v_L.setpoint, 5, 3, OLED_6X8);
        OLED_ShowString(0, 10, "L:a", OLED_6X8);
        OLED_ShowFloatNum(32, 10, pid_v_L.actual, 5, 3, OLED_6X8);
        OLED_ShowFloatNum(0, 20, t, 5, 3, OLED_6X8);
        OLED_Update();
    }
}

void TIM4_IRQHandler()
{
    static uint16_t count;
    count++;
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
    {
        t = PID_Compute(&pid_v_L, ENCODER_L_GetCount());
        MOTOR_SetSpeed((int16_t)t, 1);
        MOTOR_SetSpeed((int16_t)PID_Compute(&pid_v_R, ENCODER_R_GetCount()), 2);

        if (count >= 2)
        {
            count = 0;
            MPU_GetConv(&mpu, &conv);
            yaw += ((conv.GyroZ_dps - offset_z) * dt);
            if (yaw > 180.0f)
                yaw -= 360.0f;
            else if (yaw < -180.0f)
                yaw += 360.0f;

            pid_v_L.setpoint = 500 * (1 - tan((yaw_setpoint - yaw) / 57.3f));
            pid_v_R.setpoint = 500 * (1 + tan((yaw_setpoint - yaw) / 57.3f));
        }
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}

// /**************************************************************
//  * @file    PID_SetArg.h
//  * @brief   实现对电机参数的测量与对PID参数的设置
//  * @version 0.0
//  * @date    2025.9.10
//  * @author  jw
//  * @note
//  **************************************************************/

// #include "PID.h"
// #include "MOTOR.h"
// #include "OLED.h"
// #include "ENCODER.h"

// int16_t v;

// int main(){
//   MOTOR_Init();
//   OLED_Init();
//   ENCODER_L_Init();

//   while (1)
//   {
//     v=ENCODER_L_GetCount();
//     OLED_ShowString(0,0,"V:",OLED_6X8);
//     OLED_ShowSignedNum(0,10,v,6,OLED_6X8);
//   }

// }