#include "OLED.h"
#include "MPU6050.h"

//GSS->需要四个IO口
// #include "GRAYSCALE.h"

#include "ENCODER.h"
#include "TIM.h"
#include "MOTOR.h"
#include "PID.h"

float dt = 0.01f; // 10ms
float yaw = 0.0f;
PID pid_v_L,pid_v_R,pid_yaw;
int16_t v_setpoint_L = 0,yaw_setpoint=0,v_setpoint_R=0;

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
    PID_Init(&pid_v_L, 1.0f, 0.0f, 0.0f, 750.0f, 750.0f);
    PID_Init(&pid_v_R, 1.0f, 0.0f, 0.0f, 500.0f, 500.0f);
    PID_Init(&pid_yaw, 1.0f, 0.0f, 0.0f, 100.0f, 100.0f);
    //TODO: 完成setpoint的设置
    pid_v_L.setpoint = 350.0f;
    // pid_yaw.setpoint = yaw_setpoint;
    offset_z=MPU_GetOffset_z();
    

    //需要在计算完OFFSET_Z后初始化
    TIM_init();

    while (1)
    {
        // if(Gray_scale_sensor_get()==0x0000){
        //     // set yaw_setpoint;
        // }else if(){
        //     // ....
        // }

        OLED_ShowString(0, 0, "L:s", OLED_6X8);
        OLED_ShowFloatNum(32, 0, pid_v_L.setpoint, 5,3, OLED_6X8);
        OLED_ShowString(0, 10, "L:a", OLED_6X8);
        OLED_ShowFloatNum(32, 10, pid_v_L.actual, 5,3, OLED_6X8);
        OLED_ShowFloatNum(0, 20, t, 5,3, OLED_6X8);
        OLED_Update();
    }
}



void TIM4_IRQHandler()
{
    static uint16_t count;
    count++;
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
    {
        t=PID_Compute(&pid_v_L, ENCODER_L_GetCount());
        MOTOR_SetSpeed((int16_t)t,1);
        // PID_Compute(&pid_v_R, ENCODER_R_GetCount());

        if(count>=2){
            count=0;
            MPU_GetConv(&mpu, &conv);
            yaw += ((conv.GyroZ_dps-offset_z) * dt);
            if (yaw > 180.0f)
                yaw -= 360.0f;
            else if (yaw < -180.0f)
                yaw += 360.0f;

            pid_v_L.setpoint=PID_Compute(&pid_yaw, yaw)*50;
        }
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}