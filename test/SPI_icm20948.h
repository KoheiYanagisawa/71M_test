#ifndef SPI_icm20948_H
#define SPI_icm20948_H
//====================================//
// �C���N���[�h                       //
//====================================//
#include "r_smc_entry.h"
#include <stdio.h>



//====================================//
// �V���{����`			      //
//====================================//
#define BUS_IMU_FREE 			0		// �ʐM�\
#define BUS_IMU_BUSY 			1		// �ʐM��



#define	READ		0x80
#define WRITE		0x00


#define REG_BANK_SEL	0x7f
#define WHO_AM_I	0x00



/******************************** ���������֐� *********************************/
//#define	SPI_IMU_SEND_RECEIVE	R_Config_SCI2_SPI_Master_Send_Receive(send_buf, 2, receive_buf,1)
/***************************************************************************/
typedef enum{
	ub_0 = 0 << 4,
	ub_1 = 1 << 4,
	ub_2 = 2 << 4,
	ub_3 = 3 << 4
} userbank;
//====================================//
// �O���[�o���ϐ��̐錾		      //
//====================================//

extern char	busIMU;







//====================================//
// �v���g�^�C�v�錾		      //
//====================================//
void cs_high();
void cs_low();
void spi_init();
void wait_imu ( short waitTime );


#endif