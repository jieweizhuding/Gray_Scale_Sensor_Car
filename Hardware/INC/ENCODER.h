/**************************************************************
 * @file    ENCODER.h
 * @brief   编码器驱动,实现对电机的测速。
 * @version 0.0
 * @date    2025.9.9
 * @author  jw
 * @note    使用TIM1的CH1和CH2作为编码器接口连接A，B相，并使用TIM2的CH1和CH2作为另一个编码器的接口.
 *          即PA8->TIM1_CH1, PA9->TIM1_CH2, PA0->TIM2_CH1, PA1->TIM2_CH2
 **************************************************************/

#ifndef _ENCODER_H
#define _ENCODER_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

//PA8 -> TIM1_CH1, PA9 -> TIM1_CH2
void ENCODER_L_Init(void);
//PA0 -> TIM2_CH1, PA1 -> TIM2_CH2
void ENCODER_R_Init(void);
int16_t ENCODER_L_GetCount(void);
int16_t ENCODER_R_GetCount(void);


#endif