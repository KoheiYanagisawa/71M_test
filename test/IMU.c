//======================================//
// �C���N���[�h                         //
//======================================//
#include "IMU.h"
//====================================//
// �O���[�o���ϐ��̐錾							//
//====================================//
// IMU����擾�����f�[�^
volatile int 	rawXa = 0, rawYa = 0, rawZa = 0;	// �����x(16bit�f�[�^)
volatile int 	rawXg = 0, rawYg = 0, rawZg = 0;	// �p�����x(16bit�f�[�^)

volatile short 	rawTemp;			// ���x(16bit�f�[�^)

// �f�[�^����
double 	TurningAngleIMU;	// IMU���狁�߂����[�p�x
double	RollAngleIMU;		// IMU���狁�߂����[�������p�x
double 	PichAngleIMU;		// IMU���狁�߂��s�b�`�����p�x
double	TempIMU;			// IMU�̉��x
short		offset[3];			// �I�t�Z�b�g�l(16bit)

char	whoami;
char cnt_imu = 0;
char	busIMU = BUS_IMU_FREE;

///////////////////////////////////////////////////////////////////////////
// ���W���[���� wait_IMU								//
// �����T�v   �x������									//
// ����         �x������(ms)								//
// �߂�l       �Ȃ�										//
///////////////////////////////////////////////////////////////////////////
void wait_IMU ( short waitTime )
{
	volatile int time, i = 0;
	
	time = (int)waitTime * ( CLOCK * 1000 ) / 16;
	for ( i = 0; i < time; i++) __nop();
}
///////////////////////////////////////////////////////////////
// ���W���[���� IMUWriteByte						//
// �����T�v   �w�肵�����W�X�^�Ƀf�[�^����������			//
// ����         reg:���W�X�^�̃A�h���X data:�������݃f�[�^		//
// �߂�l       �Ȃ�								//
///////////////////////////////////////////////////////////////
void IMUWriteByte( char reg, char data )
{
	uint8_t sendData[2] = { reg, data }, num = 2;
	
	I2C_IMU_COMMAND;		// �R�}���h���M
	busIMU = BUS_IMU_BUSY;
	while(busIMU)__nop();
}
/////////////////////////////////////////////////////////
// ���W���[���� IMUReadByte					//
// �����T�v   �w�肵�����W�X�^�̃f�[�^��ǂ�			//
// ����         reg:���W�X�^�̃A�h���X				//
// �߂�l       ���W�X�^�̒l					//
/////////////////////////////////////////////////////////
char IMUReadByte( char reg )
{
	uint8_t sendData[1] = { 0x75U }, num = 1, reciveData[1] = {0};
  	
	I2C_IMU_COMMAND;		// �R�}���h���M
	busIMU = BUS_IMU_BUSY;
	while(busIMU)__nop();
	I2C_IMU_RECIVE;		// �f�[�^���M
	busIMU = BUS_IMU_BUSY;
	while(busIMU)__nop();
	
	return reciveData[0];
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// ���W���[���� IMUReadArry												//
// �����T�v   �w�肵�����W�X�^����w��̐������f�[�^��ǂ�							//
// ����         reg:���W�X�^�̃A�h���X num2 �󂯎��f�[�^�̐� reciveData �擾�f�[�^���i�[����z��	//
// �߂�l       �Ȃ�														//
///////////////////////////////////////////////////////////////////////////////////////////////////
void IMUReadArry( char reg, char num2, char* reciveData )
{
	uint8_t sendData[1] = { reg }, num = 1;
	
	
	I2C_IMU_COMMAND;
	busIMU = BUS_IMU_BUSY;
	while(busIMU)__nop();
	num = num2;
	I2C_IMU_ARRY;
	busIMU = BUS_IMU_BUSY;
	while(busIMU)__nop();
}
///////////////////////////////////////////////////
// ���W���[���� init_IMU					//
// �����T�v   IMU�̏�����				//
// ����         �Ȃ�						//
// �߂�l       �Ȃ�						//
//////////////////////////////////////////////////
void init_IMU (void)
{
	IMUWriteByte( PWR_MGMT_1, 0x00);	// �X���[�v���[�h����
	printf("step1\n\r");
	IMUWriteByte( INT_PIN_CFG, 0x02);	// �����v���A�b�v������
	printf("step2\n\r");
	IMUWriteByte( CONFIG, 0x00);		// ���[�p�X�t�B���^���g�p���Ȃ�
	printf("step3\n\r");
	IMUWriteByte( ACCEL_CONFIG, 0x18);	// �����W�}16g�ɕύX
	printf("step4\n\r");
	IMUWriteByte( GYRO_CONFIG, 0x10);	// �����W�}1000deg/s�ɕύX
	printf("step5\n\r");
}
///////////////////////////////////////////////////
// ���W���[���� IMUProcess				//
// �����T�v   �Z���Z�f�[�^�̎擾			//
// ����         �Ȃ�						//
// �߂�l       �Ȃ�						//
//////////////////////////////////////////////////
void IMUProcess (void)
{
	char 	axisData[14];	// �p�����x�A���x��8bit�����f�[�^�i�[��
	
	IMUReadArry( GYRO_XOUT_H, 6, axisData);
	//printf("step1\n\r");
	rawXg = (short)((axisData[0] << 8 & 0xff00 ) | axisData[1]);
	//printf("step2\n\r");
	rawYg = (short)((axisData[2] << 8 & 0xff00 ) | axisData[3]);
	//printf("step3\n\r");
	rawZg = (short)((axisData[4] << 8 & 0xff00 ) | axisData[5]);
	//printf("step4\n\r");
	
	
}