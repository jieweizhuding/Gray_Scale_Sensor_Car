#include "PID.h"


void PID_Init(PID* pid, float kp, float ki, float kd, float integral_limit, float output_limit) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->integral_limit = integral_limit;
    pid->output_limit = output_limit;
    pid->pre_error = 0.0f;
    pid->cur_error = 0.0f;
    pid->integral = 0.0f;
    pid->setpoint = 0.0f;
    pid->actual = 0.0f;
    pid->output = 0.0f;
}

float PID_Compute(PID* pid, float actual) {
    pid->actual = actual;

    pid->pre_error = pid->cur_error;
    pid->cur_error= pid->setpoint - pid->actual;
    pid->integral += pid->cur_error;

    if (pid->integral > pid->integral_limit) {
        pid->integral = pid->integral_limit;
    } else if (pid->integral < -pid->integral_limit) {
        pid->integral = -pid->integral_limit;
    }

    pid->output = pid->kp * pid->cur_error + pid->ki * pid->integral + pid->kd * (pid->cur_error - pid->pre_error);

    if (pid->output > pid->output_limit) {
        pid->output = pid->output_limit;
    } else if (pid->output < -pid->output_limit) {
        pid->output = -pid->output_limit;
    }

    return pid->output;
}


float PID2_Compute(PID *pido, float actualo)
{
    pido->actual = actualo;
    pido->pre_error = pido->cur_error;
    pido->cur_error = pido->setpoint - pido->actual;
    pido->integral += pido->cur_error;

    if (pido->integral > pido->integral_limit)
    {
        pido->integral = pido->integral_limit;
    }
    else if (pido->integral < -pido->integral_limit)
    {
        pido->integral = -pido->integral_limit;
    }
  return 0.0f;
}
