//======================================//
// インクルード                         //
//======================================//

#include "SPI_icm20948.h"
#include "Timer.h"

//====================================//
// グローバル変数の宣言		      //
//====================================//

char	busIMU = BUS_IMU_FREE;

//////////////////////////////////////////////////////////////////////////
// モジュール名 cs_high	                                //
// 処理概要     	                                        //
// 引数         なし                                            //
// 戻り値       0                                                       //
//////////////////////////////////////////////////////////////////////////
void cs_low(){
	PORTC.PODR.BIT.B6 = 0;
}
//////////////////////////////////////////////////////////////////////////
// モジュール名 cd_low	                                //
// 処理概要     	                                        //
// 引数         なし                                            //
// 戻り値       0                                                       //
//////////////////////////////////////////////////////////////////////////
void cs_high(){
	PORTC.PODR.BIT.B6 = 1;
}
void wait_imu ( short waitTime ){
	cnt_imu = 0;
	while(waitTime > cnt_imu){
		__nop();	
	}
}
static void select_user_bank(userbank ub){
	uint8_t send_buf[2];
	uint8_t receive_buf[2];
	
	send_buf[0] = WRITE|REG_BANK_SEL;
	send_buf[1] = ub;
	
	PORTC.PODR.BIT.B6 = 0;
	busIMU = BUS_IMU_BUSY;
	R_Config_SCI2_SPI_Master_Send_Receive(send_buf, 2,receive_buf,1);
	while(busIMU)__nop();
	PORTC.PODR.BIT.B6 = 1;
	
}
static uint8_t read_single_icm20948_reg(userbank ub, uint8_t reg){
	uint8_t read_reg[2];
	read_reg[0] = READ|reg;
	read_reg[1] = 0x00;
	uint8_t reg_val;
	select_user_bank(ub);
	
	PORTC.PODR.BIT.B6 = 0;
	busIMU = BUS_IMU_BUSY;
	R_Config_SCI2_SPI_Master_Send_Receive(read_reg, 2, reg_val,1);
	while(busIMU)__nop();
	PORTC.PODR.BIT.B6 = 1;
	
	
	return reg_val;
	
}
void spi_init(){
	
	uint8_t icm20948_id = read_single_icm20948_reg(ub_0, WHO_AM_I);
	
	printf("%x\n\r",icm20948_id);
}


