/**************************************************************
 * @file    MOTOR.h
 * @brief   配置灰度循迹小车的电机
 * @version 0.0
 * @date    2025.9.9
 * @author  jw
 * @note    电机使用TIM3的CH4和CH3通道输出PWM波，即PA6控制左电机，PA7控制右电机
 *          电机方向控制使用PA4,PA5控制左电机，PA2,PA3控制右电机
 **************************************************************/

#ifndef _MOTOR_H
#define _MOTOR_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "PWM.h"


void MOTOR_Init(void);
void MOTOR_SetSpeed(int16_t speed, uint8_t motor);
void MOTOR_Stop(void);

#endif