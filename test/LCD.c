<<<<<<< HEAD
//=====================================//
// インクルード									 //
//====================================//
#include "LCD.h"
#include "Timer.h"
//====================================//
// グローバル変数の宣言								//
//====================================//
// LCD関連
static volatile char	buffLcdData[ LCD_MAX_X / LCD_MAX_Y ];		// 表示バッファ
static char		buffLcdData2[ LCD_MAX_X / LCD_MAX_Y + 10 ]; 	// 表示バッファ一時作業エリア
static volatile int	lcdBuffPosition;				// バッファに書き込む位置
static volatile int	lcdMode2 = 1;					// 表示処理No管理
static volatile int	lcdNowLocate;					// 現在の表示している位置
static volatile int	lcdRefreshFlag;					// リフレッシュフラグ

char	busLCD = BUS_LCD_FREE;
//////////////////////////////////////////////////////////////////////////
// モジュール名 lcd_put	                                                //
// 処理概要     データ送信	                                        //
// 引数         data                                                    //
// 戻り値       なし                                                    //
//////////////////////////////////////////////////////////////////////////
void lcd_put( unsigned char data )
{
	uint8_t word[2] = { RSBIT1, data };
=======
#ifndef LCD_C
#define LCD_C
//�ｿｽC�ｿｽ�ｿｽ�ｿｽN�ｿｽ�ｿｽ�ｿｽ[�ｿｽh----------------------------------------------------------------------------------------------------------------

#include"LCD.h"

//�ｿｽO�ｿｽ�ｿｽ�ｿｽ[�ｿｽo�ｿｽ�ｿｽ�ｿｽﾏ撰ｿｽ--------------------------------------------------------------------------------------------------------------


//�ｿｽ�ｿｽ�ｿｽ�ｿｽﾖ撰ｿｽ--------------------------------------------------------------------------------------------------------------------

//�ｿｽR�ｿｽ}�ｿｽ�ｿｽ�ｿｽh�ｿｽ�ｿｽ�ｿｽM�ｿｽﾖ撰ｿｽ

void lcd_CMD(unsigned char cmd){
	uint8_t Command[2] = { RSBIT0, cmd };
	I2C_LCD_CMD;

}

//�ｿｽf�ｿｽ[�ｿｽ^�ｿｽ�ｿｽ�ｿｽM�ｿｽﾖ撰ｿｽ

void lcd_DATE(unsigned char date){
	uint8_t word[2] = { RSBIT1, date };	
>>>>>>> origin/master
	I2C_LCD_SEND;
	busLCD = BUS_LCD_BUSY;
	while(busLCD)__nop();
}
<<<<<<< HEAD
//////////////////////////////////////////////////////////////////////////
// モジュール名 lcd_CMD	                                                //
// 処理概要     コマンド送信                                            //
// 引数         cmd                                                     //
// 戻り値       なし                                                    //
//////////////////////////////////////////////////////////////////////////
void lcd_CMD( unsigned char cmd ) 
{
	uint8_t Command[2] = { RSBIT0, cmd };
 	I2C_LCD_CMD;
	busLCD = BUS_LCD_BUSY;
	while(busLCD)__nop();
}
//////////////////////////////////////////////////////////////////////////
// モジュール名 wait_lcd						//
// 処理概要     遅延処理						//
// 引数         遅延時間(ms)						//
// 戻り値       なし                                                    //
//////////////////////////////////////////////////////////////////////////
void wait_lcd ( short Time )
{
	volatile int time, i = 0;
=======
//�ｿｽx�ｿｽ�ｿｽ�ｿｽﾖ撰ｿｽ

void wait_lcd(int time){
	cnt_lcd = 0;
	while(time >= cnt_lcd){
	}
	return 0;
}
//LCD�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾖ撰ｿｽ
void inti_lcd(void){
>>>>>>> origin/master
	
	time = (int)Time * ( CLOCK * 1000 )/ 16;
	for ( i = 0; i < time; i++) __nop();
}
//////////////////////////////////////////////////////////////////////////
// モジュール名 inti_lcd						//
// 処理概要     LCDの初期化						//
// 引数         なし							//
// 戻り値       なし                                                    //
//////////////////////////////////////////////////////////////////////////
 void inti_lcd(void)
 {
	//printf("ok");
	wait_lcd(4);
	lcd_CMD(0x38);	// function set			: �ｿｽf�ｿｽ[�ｿｽ^�ｿｽ�ｿｽ�ｿｽ�ｿｽ8�ｿｽ{�ｿｽE�ｿｽ\�ｿｽ�ｿｽ�ｿｽﾍ２�ｿｽs�ｿｽE�ｿｽt�ｿｽH�ｿｽ�ｿｽ�ｿｽg�ｿｽ�ｿｽ5x8�ｿｽh�ｿｽb�ｿｽg
	wait_lcd(1);
	lcd_CMD(0x39);	// function set           	: �ｿｽg�ｿｽ�ｿｽ�ｿｽR�ｿｽ}�ｿｽ�ｿｽ�ｿｽh�ｿｽﾌ設抵ｿｽ�ｿｽL�ｿｽ�ｿｽ�ｿｽﾉゑｿｽ�ｿｽ�ｿｽ
	wait_lcd(1);
	lcd_CMD(0x14);	// Internal OSC frequency 	: �ｿｽo�ｿｽC�ｿｽA�ｿｽX�ｿｽﾌ選�ｿｽ�ｿｽ�ｿｽﾆ難ｿｽ�ｿｽ�ｿｽOSC�ｿｽ�ｿｽ�ｿｽg�ｿｽ�ｿｽ�ｿｽﾌ抵ｿｽ�ｿｽ�ｿｽ
	wait_lcd(1);
	lcd_CMD(0x70);	// Contrast set          	: �ｿｽR�ｿｽ�ｿｽ�ｿｽg�ｿｽ�ｿｽ�ｿｽX�ｿｽg�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽf�ｿｽ[�ｿｽ^(�ｿｽ�ｿｽ�ｿｽ�ｿｽ4�ｿｽr�ｿｽb�ｿｽg)
	wait_lcd(1);
	lcd_CMD(0x56);	// Power/ICON/Contrast control	: �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽH�ｿｽL�ｿｽ�ｿｽ�ｿｽA�ｿｽR�ｿｽ�ｿｽ�ｿｽg�ｿｽ�ｿｽ�ｿｽX�ｿｽg�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽf�ｿｽ[�ｿｽ^(�ｿｽ�ｿｽ�ｿｽ2�ｿｽr�ｿｽb�ｿｽg)
	wait_lcd(1);
	lcd_CMD(0x6c);	// Follower control     	: �ｿｽt�ｿｽH�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽH�ｿｽ�ｿｽON�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌ抵ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽs�ｿｽ�ｿｽ
	wait_lcd(200);
	lcd_CMD(0x38);	// function set         	: �ｿｽg�ｿｽ�ｿｽ�ｿｽR�ｿｽ}�ｿｽ�ｿｽ�ｿｽh�ｿｽ�ｿｽﾝ抵ｿｽ�無鯉ｿｽ�ｿｽﾉゑｿｽ�ｿｽ�ｿｽ
	wait_lcd(1);
	lcd_CMD(0x0c);	// display ON/OFF control      	: �ｿｽ�ｿｽﾊ表�ｿｽ�ｿｽ�ｿｽ�ｿｽON�ｿｽE�ｿｽJ�ｿｽ[�ｿｽ\�ｿｽ�ｿｽ�ｿｽ\�ｿｽ�ｿｽ�ｿｽ�ｿｽOFF�ｿｽE�ｿｽJ�ｿｽ[�ｿｽ\�ｿｽ�ｿｽ�ｿｽ_�ｿｽﾅゑｿｽOFF
	wait_lcd(1);
	lcd_CMD(0x01);	// Clear Display 		: �ｿｽ�ｿｽﾊ全�ｿｽﾌゑｿｽ20H�ｿｽﾌｽ�ｿｽﾟｰ�ｿｽ�ｿｽﾅ表�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽﾙゑｿｽcol=0,row=0�ｿｽﾉ移難ｿｽ
	wait_lcd(2);
}
<<<<<<< HEAD
//////////////////////////////////////////////////////////////////////////
// モジュール名 lcdLocate						//
// 処理概要     液晶カーソル移動					//
// 引数         x , y							//
// 戻り値       なし							//
//////////////////////////////////////////////////////////////////////////
static void lcdLocate( int x, int y )
{
	//printf("ok");	
    volatile unsigned char work = 0x80;

    // xの計算
    work += x;

    // yの計算
    if( y == 1 ) {
        work += 0x40;
    } else if( y == 2 ) {
        work += 0x14;
    } else if( y == 3 ) {
        work += 0x54;
    }

    // カーソル移動
    lcd_CMD(work);
}
//////////////////////////////////////////////////////////////////////////
// モジュール名 lcdShowProcess						//
// 処理概要     液晶表示処理						//
// 引数         なし							//
// 戻り値       なし							//
// メモ         この関数は割り込みで1msごとに実行してください		//
//////////////////////////////////////////////////////////////////////////
void lcdShowProcess( void )
{
	//printf("ok");
    switch( lcdMode2 ) {
    case 1: // データ更新されたかチェック
    	if( lcdRefreshFlag ) {
    		lcdRefreshFlag = 0;
    		lcdMode2 = 2;
	}
        break;

    case 2: // 位置初期化
	lcdNowLocate = 0;
    	lcdLocate( 0, 0 );
	lcdMode2 = 3;
        break;

    case 3: // 改行位置の確認 
	if( lcdNowLocate % LCD_MAX_X == 0 ) {
    		lcdLocate( 0, lcdNowLocate / LCD_MAX_X );
	}
	lcdMode2 = 4;
        break;

    case 4: // データ表示処理
	lcd_put(buffLcdData[ lcdNowLocate++ ]);
	if( lcdNowLocate >= LCD_MAX_X * LCD_MAX_Y ) {
		lcdMode2 = 1;
	} else {
		lcdMode2 = 3;
	}
	break;

    default:
	lcdMode2 = 1;
   	break;
    }
}
//////////////////////////////////////////////////////////////////////////
// モジュール名 lcdPrintf						//
// 処理概要     液晶へ表示 表示位置は過去に表示した位置の次から		//
// 引数         printfと同じ						//
// 戻り値       正常時：出力した文字列 異常時：負の数			//
//////////////////////////////////////////////////////////////////////////
int lcdPrintf(char *format, ...)
{
    volatile va_list argptr;
    volatile char    *p;
    volatile short     ret = 0;

    va_start(argptr, format);
    ret = vsprintf( buffLcdData2, format, argptr );
    va_end(argptr);

    if( ret > 0 ) {
        // vsprintfが正常なら液晶バッファへ転送
        p = buffLcdData2;
        while( *p ) {
            buffLcdData[lcdBuffPosition++] = *p++;
            if( lcdBuffPosition >= LCD_MAX_X * LCD_MAX_Y ) {
                lcdBuffPosition = 0;
            }
        }
        lcdRefreshFlag = 1;
    }
    return ret;
}
//////////////////////////////////////////////////////////////////////////
// モジュール名 lcdPosition                                             //
// 処理概要     液晶の表示位置指定                                      //
// 引数         横位置 , 縦位置                                         //
// 戻り値       なし                                                    //
//////////////////////////////////////////////////////////////////////////
void lcdPosition(char x ,char y)
{
    if( x >= LCD_MAX_X ) return;
    if( y >= LCD_MAX_Y ) return;
=======
//LCD�ｿｽJ�ｿｽ[�ｿｽ\�ｿｽ�ｿｽ�ｿｽﾚ難ｿｽ
static void lcdLocate(int x, int y){
	
	volatile unsigned char work = 0x80;		//set DDRAM address
	
	//x�ｿｽﾌ計�ｿｽZ
	work += x;
	
	//y�ｿｽﾌ計�ｿｽZ
	if(y == 1) work += 0x40;
	else if(y == 2) work += 0x14;
	
	//�ｿｽR�ｿｽ}�ｿｽ�ｿｽ�ｿｽh�ｿｽ�ｿｽ�ｿｽ�ｿｽ
	lcd_CMD(work);
	
}
//豸ｲ譎ｶ陦ｨ遉ｺ髢｢謨ｰ
void lcd_print (char *str){
	for (int i = 0 ; i < strlen(str); i ++) lcd_DATE (str[1]) ;
}

//譁�蟄怜�苓｡ｨ遉ｺ髢｢謨ｰ
void LCDprint(int x, int y, char *str){
	//繧ｫ繝ｼ繧ｽ繝ｫ繧抵ｼ茨ｽ倥���ｽ呻ｼ峨↓遘ｻ蜍輔＠縺ｦ譁�蟄怜�励ｒ陦ｨ遉ｺ
	lcdLocate(x, y);
	lcd_print(str);
}
>>>>>>> origin/master

    lcdBuffPosition = x + y * LCD_MAX_X;
}