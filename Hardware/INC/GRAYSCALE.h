/**************************************************************
 * @file    GRAYSCALE.h
 * @brief   实现四路灰度传感器的读取
 * @version 0.0
 * @date    2025.9.9
 * @author  jw
 * @note    使用PA4,PA5,PB0,PB1四个IO口读取灰度传感器的值
 **************************************************************/

#ifndef _GRAYSCALE_H
#define _GRAYSCALE_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"

void Gray_scale_sensor_init();
uint16_t Gray_scale_sensor_get();



#endif