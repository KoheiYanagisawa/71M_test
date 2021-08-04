#ifndef LCD_H
#define LCD_H
//インクルード-----------------------------------------------------------------------------------------------

#include "r_smc_entry.h"

//シンボル定義-----------------------------------------------------------------------------------------------

// スレーブアドレス

#define LCD_SLAVEADDRESS	0x7cU

// 液晶関連変数

#define LCD_MAX_X	17		// 表示文字数 横 16 or 20
#define LCD_MAX_Y	2		// 表示文字数 縦  2 or  4
#define RSBIT0		0x00		// コマンド送信ビット
#define RSBIT1		0x40		// データ送信ビット

#define BUS_LCD_FREE 			0		// 通信可能
#define BUS_LCD_BUSY 			1		// 通信中

//自動生成関数

#define	I2C_LCD_SEND	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, word, 2)      //データ送信用
#define	I2C_LCD_CMD	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, Command, 2)   //コマンド送信用

//グローバル変数-----------------------------------------------------------------------------------------------

extern int cnt_lcd;

//プロトタイプ宣言

//LCD関係

void lcd_CMD(unsigned char cmd);
void lcd_DATE(unsigned char date);
void wait_lcd(int time);
void inti_lcd(void);


#endif