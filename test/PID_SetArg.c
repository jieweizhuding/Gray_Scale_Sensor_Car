/**************************************************************
 * @file    PID_SetArg.h
 * @brief   实现对电机参数的测量与对PID参数的设置
 * @version 0.0
 * @date    2025.9.10
 * @author  jw
 * @note    
 **************************************************************/


#include "PID.h"
#include "MOTOR.h"
#include "OLED.h"
#include "ENCODER.h"

int16_t v;

int main(){
  MOTOR_Init();
  OLED_Init();
  ENCODER_L_Init();

  while (1)
  {
    v=ENCODER_L_GetCount();
    OLED_ShowString(0,0,"V:",OLED_6X8);
    OLED_ShowSignedNum(0,10,v,6,OLED_6X8);
  }
  
}