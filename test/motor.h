#ifndef MOTOR_H
#define MOTOR

#include "r_smc_entry.h"

#define TGR_MOTOR	5998	//ジェネラルレジスタ初期値（駆動モータ）

#define	FORWARD		0	//正転
#define	REVERSE		1	//逆転

#define BRAKE		0		// ブレーキモード
#define FREE		1		// フリーモード

// 右後輪(pwm4,MTIOC0C)
#define DIR_rR		PORTC.PODR.BIT.B2	// モータ回転方向(0:正転 1:逆転)
#define SR_rR		PORTC.PODR.BIT.B3	// 0:フリーモード  1:ブレーキモード
#define PWM_rR_OUT	MTU0.TGRD = pwmrR	// PWM出力
// 左後輪(pwm3,MTIOC0A)
#define DIR_rL		PORTC.PODR.BIT.B4	// モータ回転方向(0:正転 1:逆転)
#define SR_rL		PORTC.PODR.BIT.B5	// 0:フリーモード  1:ブレーキモード
#define PWM_rL_OUT	MTU0.TGRB = pwmrL	// PWM出力

//モーター関連
extern signed char	accele_fR;		// 右前モーターPWM値
extern signed char	accele_fL;		// 左前モーターPWM値
extern signed char	accele_rR;		// 右後モーターPWM値
extern signed char	accele_rL;		// 左後モーターPWM値

// モーター関連
void motor_mode(short int rR,short int rL);
void motor_rear(signed char accelR, signed char accelL);

#endif