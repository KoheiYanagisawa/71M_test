<<<<<<< HEAD
#ifndef LCD_H_
#define LCD_H_
//====================================//
// インクルード                  						       //
//====================================//
#include "r_smc_entry.h"
#include <stdio.h>
#include <stdarg.h>
//====================================//
// シンボル定義									//
//====================================//
// スレーブアドレス
#define LCD_SLAVEADDRESS	0x7cU
// 液晶関連変数
#define LCD_MAX_X	17		// 表示文字数 横 16 or 20
#define LCD_MAX_Y	2		// 表示文字数 縦  2 or  4
#define RSBIT0		0x00		// コマンド送信ビット
#define RSBIT1		0x40		// データ送信ビット

#define CLOCK		240		// 動作周波数[MHz]

#define BUS_LCD_FREE 			0		// 通信可能
#define BUS_LCD_BUSY 			1		// 通信中

/******************************** 自動生成関数 *********************************/
#define	I2C_LCD_SEND	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, word, 2)
#define	I2C_LCD_CMD	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, Command, 2)
/***************************************************************************/
//====================================//
// グローバル変数の宣言							//
//====================================//
extern char	busLCD;
//====================================//
// プロトタイプ宣言								//
//====================================//
// LCD関連
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
//�ｿｽC�ｿｽ�ｿｽ�ｿｽN�ｿｽ�ｿｽ�ｿｽ[�ｿｽh-----------------------------------------------------------------------------------------------

#include "r_smc_entry.h"

//�ｿｽV�ｿｽ�ｿｽ�ｿｽ{�ｿｽ�ｿｽ�ｿｽ�ｿｽ`-----------------------------------------------------------------------------------------------

// �ｿｽX�ｿｽ�ｿｽ�ｿｽ[�ｿｽu�ｿｽA�ｿｽh�ｿｽ�ｿｽ�ｿｽX

#define LCD_SLAVEADDRESS	0x7cU

// �ｿｽt�ｿｽ�ｿｽ�ｿｽﾖ連�ｿｽﾏ撰ｿｽ

#define LCD_MAX_X	17		// �ｿｽ\�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ �ｿｽ�ｿｽ 16 or 20
#define LCD_MAX_Y	2		// �ｿｽ\�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ �ｿｽc  2 or  4
#define RSBIT0		0x00		// �ｿｽR�ｿｽ}�ｿｽ�ｿｽ�ｿｽh�ｿｽ�ｿｽ�ｿｽM�ｿｽr�ｿｽb�ｿｽg
#define RSBIT1		0x40		// �ｿｽf�ｿｽ[�ｿｽ^�ｿｽ�ｿｽ�ｿｽM�ｿｽr�ｿｽb�ｿｽg

#define BUS_LCD_FREE 			0		// �ｿｽﾊ信�ｿｽﾂ能
#define BUS_LCD_BUSY 			1		// �ｿｽﾊ信�ｿｽ�ｿｽ

//�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾖ撰ｿｽ

#define	I2C_LCD_SEND	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, word, 2)      //�ｿｽf�ｿｽ[�ｿｽ^�ｿｽ�ｿｽ�ｿｽM�ｿｽp
#define	I2C_LCD_CMD	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, Command, 2)   //�ｿｽR�ｿｽ}�ｿｽ�ｿｽ�ｿｽh�ｿｽ�ｿｽ�ｿｽM�ｿｽp

//�ｿｽO�ｿｽ�ｿｽ�ｿｽ[�ｿｽo�ｿｽ�ｿｽ�ｿｽﾏ撰ｿｽ-----------------------------------------------------------------------------------------------

extern int cnt_lcd;

//�ｿｽv�ｿｽ�ｿｽ�ｿｽg�ｿｽ^�ｿｽC�ｿｽv�ｿｽ骭ｾ

//LCD�ｿｽﾖ係

void lcd_CMD(unsigned char cmd);
void lcd_DATE(unsigned char date);
void wait_lcd(int time);
void inti_lcd(void);
void LCDprint(int x, int y, char *str);


#endif
>>>>>>> origin/master
