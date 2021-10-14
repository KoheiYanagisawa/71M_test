#ifndef MOTOR_H
#define MOTOR

#include "r_smc_entry.h"

#define TGR_MOTOR	5998	//�W�F�l�������W�X�^�����l�i�쓮���[�^�j

#define	FORWARD		0	//���]
#define	REVERSE		1	//�t�]

#define BRAKE		0		// �u���[�L���[�h
#define FREE		1		// �t���[���[�h

// �E���(pwm4,MTIOC0C)
#define DIR_rR		PORTC.PODR.BIT.B2	// ���[�^��]����(0:���] 1:�t�])
#define SR_rR		PORTC.PODR.BIT.B3	// 0:�t���[���[�h  1:�u���[�L���[�h
#define PWM_rR_OUT	MTU0.TGRD = pwmrR	// PWM�o��
// �����(pwm3,MTIOC0A)
#define DIR_rL		PORTC.PODR.BIT.B4	// ���[�^��]����(0:���] 1:�t�])
#define SR_rL		PORTC.PODR.BIT.B5	// 0:�t���[���[�h  1:�u���[�L���[�h
#define PWM_rL_OUT	MTU0.TGRB = pwmrL	// PWM�o��

//���[�^�[�֘A
extern signed char	accele_fR;		// �E�O���[�^�[PWM�l
extern signed char	accele_fL;		// ���O���[�^�[PWM�l
extern signed char	accele_rR;		// �E�ヂ�[�^�[PWM�l
extern signed char	accele_rL;		// ���ヂ�[�^�[PWM�l

// ���[�^�[�֘A
void motor_mode(short int rR,short int rL);
void motor_rear(signed char accelR, signed char accelL);

#endif