#include "GRAYSCALE.h"

void Gray_scale_sensor_init()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

  GPIO_InitTypeDef GPIO_initstructure;
  GPIO_initstructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
  GPIO_initstructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
  GPIO_initstructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_initstructure);

  GPIO_initstructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
  GPIO_init(GPIOB,&GPIO_initstructure);
  

}

uint16_t Gray_scale_sensor_get()
{
  
  uint16_t value=0;
  value|=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)<<3;
  value|=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)<<2;
  value|=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)<<1;
  value|=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)<<0;
  return value;
}