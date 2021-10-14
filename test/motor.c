#include "motor.h"

signed char	accele_fR;		// 右前モーターPWM値
signed char	accele_fL;		// 左前モーターPWM値
signed char	accele_rR;		// 右後モーターPWM値
signed char	accele_rL;		// 左後モーターPWM値

void motor_mode(short int rR, short int rL){
	SR_rR = rR;
	SR_rL = rL;
}

void motor_rear(signed char accelR, signed char accelL){
	uint16_t pwmrR, pwmrL;
	
	accele_rR = accelR;
	accele_rL = accelL;
	
	pwmrR = TGR_MOTOR * accele_rR / 100;
	pwmrL = TGR_MOTOR * accele_rL / 100;
	
	//右後輪//
	if(accelR >= 0) DIR_rR = FORWARD;	//正転
	else{
		pwmrR = -pwmrR;
		DIR_rR  = REVERSE;		//逆転
	}
	PWM_rR_OUT;				//PWM出力
	
	//左後輪//
	if(accelL>= 0) DIR_rL = FORWARD;	//正転
	else{
		pwmrL = -pwmrL;
		DIR_rL = REVERSE;		//逆転
	}
	PWM_rL_OUT;				//PWM出力
	
}
