#ifndef LCD_C
#define LCD_C
//インクルード----------------------------------------------------------------------------------------------------------------

#include"LCD.h"

//グローバル変数--------------------------------------------------------------------------------------------------------------


//動作関数--------------------------------------------------------------------------------------------------------------------

//コマンド送信関数

void lcd_CMD(unsigned char cmd){
	uint8_t Command[2] = { RSBIT0, cmd };
	I2C_LCD_CMD;

}

//データ送信関数

void lcd_DATE(unsigned char date){
	uint8_t word[2] = { RSBIT1, date };	
	I2C_LCD_SEND;
}
//遅延関数

void wait_lcd(int time){
	cnt_lcd = 0;
	while(time >= cnt_lcd){
	}
	return 0;
}
//LCD初期化関数
void inti_lcd(void){
	
	wait_lcd(4);
	lcd_CMD(0x38);	// function set			: データ線は8本・表示は２行・フォントは5x8ドット
	wait_lcd(1);
	lcd_CMD(0x39);	// function set           	: 拡張コマンドの設定を有効にする
	wait_lcd(1);
	lcd_CMD(0x14);	// Internal OSC frequency 	: バイアスの選択と内部OSC周波数の調整
	wait_lcd(1);
	lcd_CMD(0x70);	// Contrast set          	: コントラスト調整データ(下位4ビット)
	wait_lcd(1);
	lcd_CMD(0x56);	// Power/ICON/Contrast control	: 昇圧回路有効、コントラスト調整データ(上位2ビット)
	wait_lcd(1);
	lcd_CMD(0x6c);	// Follower control     	: フォロア回路をON、増幅率の調整を行う
	wait_lcd(200);
	lcd_CMD(0x38);	// function set         	: 拡張コマンドを設定を無効にする
	wait_lcd(1);
	lcd_CMD(0x0c);	// display ON/OFF control      	: 画面表示はON・カーソル表示はOFF・カーソル点滅はOFF
	wait_lcd(1);
	lcd_CMD(0x01);	// Clear Display 		: 画面全体に20Hのｽﾍﾟｰｽで表示、ｶｰｿﾙはcol=0,row=0に移動
	wait_lcd(2);
	
}
//LCDカーソル移動
static void lcdLocate(int x, int y){
	
	volatile unsigned char work = 0x80;		//set DDRAM address
	
	//xの計算
	work += x;
	
	//yの計算
	if(y == 1) work += 0x40;
	else if(y == 2) work += 0x14;
	
	//コマンド入力
	lcd_CMD(work);
	
}

#endif