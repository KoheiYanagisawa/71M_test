<<<<<<< HEAD
#ifndef LCD_H_
#define LCD_H_
//====================================//
// �C���N���[�h                  						       //
//====================================//
#include "r_smc_entry.h"
#include <stdio.h>
#include <stdarg.h>
//====================================//
// �V���{����`									//
//====================================//
// �X���[�u�A�h���X
#define LCD_SLAVEADDRESS	0x7cU
// �t���֘A�ϐ�
#define LCD_MAX_X	17		// �\�������� �� 16 or 20
#define LCD_MAX_Y	2		// �\�������� �c  2 or  4
#define RSBIT0		0x00		// �R�}���h���M�r�b�g
#define RSBIT1		0x40		// �f�[�^���M�r�b�g

#define CLOCK		240		// ������g��[MHz]

#define BUS_LCD_FREE 			0		// �ʐM�\
#define BUS_LCD_BUSY 			1		// �ʐM��

/******************************** ���������֐� *********************************/
#define	I2C_LCD_SEND	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, word, 2)
#define	I2C_LCD_CMD	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, Command, 2)
/***************************************************************************/
//====================================//
// �O���[�o���ϐ��̐錾							//
//====================================//
extern char	busLCD;
//====================================//
// �v���g�^�C�v�錾								//
//====================================//
// LCD�֘A
void wait_lcd ( short waitTime );
void lcdShowProcess( void );
void lcdPosition( char x ,char y );
void inti_lcd( void );
void lcd_CMD( unsigned char cmd );
void lcd_put( unsigned char data );
int lcdPrintf( char *format, ... );
void lcdcursol (void);

#endif // LCD_H_
=======
#ifndef LCD_H
#define LCD_H
//�C���N���[�h-----------------------------------------------------------------------------------------------

#include "r_smc_entry.h"

//�V���{����`-----------------------------------------------------------------------------------------------

// �X���[�u�A�h���X

#define LCD_SLAVEADDRESS	0x7cU

// �t���֘A�ϐ�

#define LCD_MAX_X	17		// �\�������� �� 16 or 20
#define LCD_MAX_Y	2		// �\�������� �c  2 or  4
#define RSBIT0		0x00		// �R�}���h���M�r�b�g
#define RSBIT1		0x40		// �f�[�^���M�r�b�g

#define BUS_LCD_FREE 			0		// �ʐM�\
#define BUS_LCD_BUSY 			1		// �ʐM��

//���������֐�

#define	I2C_LCD_SEND	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, word, 2)      //�f�[�^���M�p
#define	I2C_LCD_CMD	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, Command, 2)   //�R�}���h���M�p

//�O���[�o���ϐ�-----------------------------------------------------------------------------------------------

extern int cnt_lcd;

//�v���g�^�C�v�錾

//LCD�֌W

void lcd_CMD(unsigned char cmd);
void lcd_DATE(unsigned char date);
void wait_lcd(int time);
void inti_lcd(void);
void LCDprint(int x, int y, char *str);


#endif
>>>>>>> origin/master
