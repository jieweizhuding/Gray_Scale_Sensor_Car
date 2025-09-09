#include "MOTOR.h"

void MOTOR_Init(void)
{
  PWM_init();
  // Initialize GPIO pins for motor direction control
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  MOTOR_Stop(); // Ensure motor is stopped at initialization
}

//感觉并不会用到，但先实现了
void MOTOR_SetSpeed(int16_t speed, uint8_t motor)
{
  if (speed > 0)
  {
    if (motor == 1)
    {
      // Control motor 1
      GPIO_SetBits(GPIOA, GPIO_Pin_4);   // Example: Set direction pin high
      GPIO_ResetBits(GPIOA, GPIO_Pin_5); // Ensure backward pin is low
      PWM_SetCompare1((uint16_t)speed);
    }
    else if (motor == 2)
    {
      // Control motor 2
      GPIO_SetBits(GPIOA, GPIO_Pin_2);   // Example: Set direction pin high
      GPIO_ResetBits(GPIOA, GPIO_Pin_3); // Ensure backward pin is low
      PWM_SetCompare1((uint16_t)speed);
    }
    else
    {
      return; // Invalid motor selection
    }
  }
  else if (speed < 0)
  {
    if (motor == 1)
    {
      GPIO_SetBits(GPIOA, GPIO_Pin_5);   // Example: Set direction pin high
      GPIO_ResetBits(GPIOA, GPIO_Pin_4); // Ensure forward pin is low
      PWM_SetCompare1((uint16_t)(-speed));
    }
    else if (motor == 2)
    {
      GPIO_SetBits(GPIOA, GPIO_Pin_3);   // Example: Set direction pin high
      GPIO_ResetBits(GPIOA, GPIO_Pin_2); // Ensure forward pin is low
      PWM_SetCompare2((uint16_t)(-speed));
      // Set direction to backward
    }
    else
    {
      return; // Invalid motor selection
    }
  }
  else
  {
    // Stop the motor if speed is zero
    if (motor == 1)
    {
      PWM_SetCompare1(0);
    }
    else if (motor == 2)
    {
      PWM_SetCompare2(0);
    }
    else
    {
      return; // Invalid motor selection
    }
  }
}

void MOTOR_Stop(void)
{
  PWM_SetCompare1(0);
  PWM_SetCompare2(0);
}
