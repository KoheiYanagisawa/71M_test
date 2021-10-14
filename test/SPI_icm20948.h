#ifndef SPI_icm20948_H
#define SPI_icm20948_H
//====================================//
// インクルード                       //
//====================================//
#include "r_smc_entry.h"
#include <stdio.h>



//====================================//
// シンボル定義			      //
//====================================//
#define BUS_IMU_FREE 			0		// 通信可能
#define BUS_IMU_BUSY 			1		// 通信中



#define	READ		0x80
#define WRITE		0x00


#define REG_BANK_SEL	0x7f
#define WHO_AM_I	0x00



/******************************** 自動生成関数 *********************************/
//#define	SPI_IMU_SEND_RECEIVE	R_Config_SCI2_SPI_Master_Send_Receive(send_buf, 2, receive_buf,1)
/***************************************************************************/
typedef enum{
	ub_0 = 0 << 4,
	ub_1 = 1 << 4,
	ub_2 = 2 << 4,
	ub_3 = 3 << 4
} userbank;
//====================================//
// グローバル変数の宣言		      //
//====================================//

extern char	busIMU;







//====================================//
// プロトタイプ宣言		      //
//====================================//
void cs_high();
void cs_low();
void spi_init();
void wait_imu ( short waitTime );


#endif