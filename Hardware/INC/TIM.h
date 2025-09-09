/**************************************************************
 * @file    TIM.h
 * @brief   配置灰度循迹小车的定时器TIM4
 * @version 0.0
 * @date    2025.9.9
 * @author  jw
 * @note    使用TIM4作为定时器中断，100Hz频率
 **************************************************************/

#ifndef _TIM_H
#define _TIM_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"

void TIM_init();

#endif