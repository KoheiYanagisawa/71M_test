#include "motor.h"

signed char	accele_fR;		// �E�O���[�^�[PWM�l
signed char	accele_fL;		// ���O���[�^�[PWM�l
signed char	accele_rR;		// �E�ヂ�[�^�[PWM�l
signed char	accele_rL;		// ���ヂ�[�^�[PWM�l

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
	
	//�E���//
	if(accelR >= 0) DIR_rR = FORWARD;	//���]
	else{
		pwmrR = -pwmrR;
		DIR_rR  = REVERSE;		//�t�]
	}
	PWM_rR_OUT;				//PWM�o��
	
	//�����//
	if(accelL>= 0) DIR_rL = FORWARD;	//���]
	else{
		pwmrL = -pwmrL;
		DIR_rL = REVERSE;		//�t�]
	}
	PWM_rL_OUT;				//PWM�o��
	
}
