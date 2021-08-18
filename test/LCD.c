<<<<<<< HEAD
//=====================================//
// ƒCƒ“ƒNƒ‹[ƒh									 //
//====================================//
#include "LCD.h"
#include "Timer.h"
//====================================//
// ƒOƒ[ƒoƒ‹•Ï”‚ÌéŒ¾								//
//====================================//
// LCDŠÖ˜A
static volatile char	buffLcdData[ LCD_MAX_X / LCD_MAX_Y ];		// •\Ž¦ƒoƒbƒtƒ@
static char		buffLcdData2[ LCD_MAX_X / LCD_MAX_Y + 10 ]; 	// •\Ž¦ƒoƒbƒtƒ@ˆêŽžì‹ÆƒGƒŠƒA
static volatile int	lcdBuffPosition;				// ƒoƒbƒtƒ@‚É‘‚«ž‚ÞˆÊ’u
static volatile int	lcdMode2 = 1;					// •\Ž¦ˆ—NoŠÇ—
static volatile int	lcdNowLocate;					// Œ»Ý‚Ì•\Ž¦‚µ‚Ä‚¢‚éˆÊ’u
static volatile int	lcdRefreshFlag;					// ƒŠƒtƒŒƒbƒVƒ…ƒtƒ‰ƒO

char	busLCD = BUS_LCD_FREE;
//////////////////////////////////////////////////////////////////////////
// ƒ‚ƒWƒ…[ƒ‹–¼ lcd_put	                                                //
// ˆ—ŠT—v     ƒf[ƒ^‘—M	                                        //
// ˆø”         data                                                    //
// –ß‚è’l       ‚È‚µ                                                    //
//////////////////////////////////////////////////////////////////////////
void lcd_put( unsigned char data )
{
	uint8_t word[2] = { RSBIT1, data };
=======
#ifndef LCD_C
#define LCD_C
//ï¿½Cï¿½ï¿½ï¿½Nï¿½ï¿½ï¿½[ï¿½h----------------------------------------------------------------------------------------------------------------

#include"LCD.h"

//ï¿½Oï¿½ï¿½ï¿½[ï¿½oï¿½ï¿½ï¿½Ïï¿½--------------------------------------------------------------------------------------------------------------


//ï¿½ï¿½ï¿½ï¿½Öï¿½--------------------------------------------------------------------------------------------------------------------

//ï¿½Rï¿½}ï¿½ï¿½ï¿½hï¿½ï¿½ï¿½Mï¿½Öï¿½

void lcd_CMD(unsigned char cmd){
	uint8_t Command[2] = { RSBIT0, cmd };
	I2C_LCD_CMD;

}

//ï¿½fï¿½[ï¿½^ï¿½ï¿½ï¿½Mï¿½Öï¿½

void lcd_DATE(unsigned char date){
	uint8_t word[2] = { RSBIT1, date };	
>>>>>>> origin/master
	I2C_LCD_SEND;
	busLCD = BUS_LCD_BUSY;
	while(busLCD)__nop();
}
<<<<<<< HEAD
//////////////////////////////////////////////////////////////////////////
// ƒ‚ƒWƒ…[ƒ‹–¼ lcd_CMD	                                                //
// ˆ—ŠT—v     ƒRƒ}ƒ“ƒh‘—M                                            //
// ˆø”         cmd                                                     //
// –ß‚è’l       ‚È‚µ                                                    //
//////////////////////////////////////////////////////////////////////////
void lcd_CMD( unsigned char cmd ) 
{
	uint8_t Command[2] = { RSBIT0, cmd };
 	I2C_LCD_CMD;
	busLCD = BUS_LCD_BUSY;
	while(busLCD)__nop();
}
//////////////////////////////////////////////////////////////////////////
// ƒ‚ƒWƒ…[ƒ‹–¼ wait_lcd						//
// ˆ—ŠT—v     ’x‰„ˆ—						//
// ˆø”         ’x‰„ŽžŠÔ(ms)						//
// –ß‚è’l       ‚È‚µ                                                    //
//////////////////////////////////////////////////////////////////////////
void wait_lcd ( short Time )
{
	volatile int time, i = 0;
=======
//ï¿½xï¿½ï¿½ï¿½Öï¿½

void wait_lcd(int time){
	cnt_lcd = 0;
	while(time >= cnt_lcd){
	}
	return 0;
}
//LCDï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Öï¿½
void inti_lcd(void){
>>>>>>> origin/master
	
	time = (int)Time * ( CLOCK * 1000 )/ 16;
	for ( i = 0; i < time; i++) __nop();
}
//////////////////////////////////////////////////////////////////////////
// ƒ‚ƒWƒ…[ƒ‹–¼ inti_lcd						//
// ˆ—ŠT—v     LCD‚Ì‰Šú‰»						//
// ˆø”         ‚È‚µ							//
// –ß‚è’l       ‚È‚µ                                                    //
//////////////////////////////////////////////////////////////////////////
 void inti_lcd(void)
 {
	//printf("ok");
	wait_lcd(4);
	lcd_CMD(0x38);	// function set			: ï¿½fï¿½[ï¿½^ï¿½ï¿½ï¿½ï¿½8ï¿½{ï¿½Eï¿½\ï¿½ï¿½ï¿½Í‚Qï¿½sï¿½Eï¿½tï¿½Hï¿½ï¿½ï¿½gï¿½ï¿½5x8ï¿½hï¿½bï¿½g
	wait_lcd(1);
	lcd_CMD(0x39);	// function set           	: ï¿½gï¿½ï¿½ï¿½Rï¿½}ï¿½ï¿½ï¿½hï¿½ÌÝ’ï¿½ï¿½Lï¿½ï¿½ï¿½É‚ï¿½ï¿½ï¿½
	wait_lcd(1);
	lcd_CMD(0x14);	// Internal OSC frequency 	: ï¿½oï¿½Cï¿½Aï¿½Xï¿½Ì‘Iï¿½ï¿½ï¿½Æ“ï¿½ï¿½ï¿½OSCï¿½ï¿½ï¿½gï¿½ï¿½ï¿½Ì’ï¿½ï¿½ï¿½
	wait_lcd(1);
	lcd_CMD(0x70);	// Contrast set          	: ï¿½Rï¿½ï¿½ï¿½gï¿½ï¿½ï¿½Xï¿½gï¿½ï¿½ï¿½ï¿½ï¿½fï¿½[ï¿½^(ï¿½ï¿½ï¿½ï¿½4ï¿½rï¿½bï¿½g)
	wait_lcd(1);
	lcd_CMD(0x56);	// Power/ICON/Contrast control	: ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Hï¿½Lï¿½ï¿½ï¿½Aï¿½Rï¿½ï¿½ï¿½gï¿½ï¿½ï¿½Xï¿½gï¿½ï¿½ï¿½ï¿½ï¿½fï¿½[ï¿½^(ï¿½ï¿½ï¿½2ï¿½rï¿½bï¿½g)
	wait_lcd(1);
	lcd_CMD(0x6c);	// Follower control     	: ï¿½tï¿½Hï¿½ï¿½ï¿½Aï¿½ï¿½Hï¿½ï¿½ONï¿½Aï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì’ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½sï¿½ï¿½
	wait_lcd(200);
	lcd_CMD(0x38);	// function set         	: ï¿½gï¿½ï¿½ï¿½Rï¿½}ï¿½ï¿½ï¿½hï¿½ï¿½Ý’ï¿½ð–³Œï¿½ï¿½É‚ï¿½ï¿½ï¿½
	wait_lcd(1);
	lcd_CMD(0x0c);	// display ON/OFF control      	: ï¿½ï¿½Ê•\ï¿½ï¿½ï¿½ï¿½ONï¿½Eï¿½Jï¿½[ï¿½\ï¿½ï¿½ï¿½\ï¿½ï¿½ï¿½ï¿½OFFï¿½Eï¿½Jï¿½[ï¿½\ï¿½ï¿½ï¿½_ï¿½Å‚ï¿½OFF
	wait_lcd(1);
	lcd_CMD(0x01);	// Clear Display 		: ï¿½ï¿½Ê‘Sï¿½Ì‚ï¿½20Hï¿½Ì½ï¿½ß°ï¿½ï¿½Å•\ï¿½ï¿½ï¿½Aï¿½ï¿½ï¿½Ù‚ï¿½col=0,row=0ï¿½ÉˆÚ“ï¿½
	wait_lcd(2);
}
<<<<<<< HEAD
//////////////////////////////////////////////////////////////////////////
// ƒ‚ƒWƒ…[ƒ‹–¼ lcdLocate						//
// ˆ—ŠT—v     ‰t»ƒJ[ƒ\ƒ‹ˆÚ“®					//
// ˆø”         x , y							//
// –ß‚è’l       ‚È‚µ							//
//////////////////////////////////////////////////////////////////////////
static void lcdLocate( int x, int y )
{
	//printf("ok");	
    volatile unsigned char work = 0x80;

    // x‚ÌŒvŽZ
    work += x;

    // y‚ÌŒvŽZ
    if( y == 1 ) {
        work += 0x40;
    } else if( y == 2 ) {
        work += 0x14;
    } else if( y == 3 ) {
        work += 0x54;
    }

    // ƒJ[ƒ\ƒ‹ˆÚ“®
    lcd_CMD(work);
}
//////////////////////////////////////////////////////////////////////////
// ƒ‚ƒWƒ…[ƒ‹–¼ lcdShowProcess						//
// ˆ—ŠT—v     ‰t»•\Ž¦ˆ—						//
// ˆø”         ‚È‚µ							//
// –ß‚è’l       ‚È‚µ							//
// ƒƒ‚         ‚±‚ÌŠÖ”‚ÍŠ„‚èž‚Ý‚Å1ms‚²‚Æ‚ÉŽÀs‚µ‚Ä‚­‚¾‚³‚¢		//
//////////////////////////////////////////////////////////////////////////
void lcdShowProcess( void )
{
	//printf("ok");
    switch( lcdMode2 ) {
    case 1: // ƒf[ƒ^XV‚³‚ê‚½‚©ƒ`ƒFƒbƒN
    	if( lcdRefreshFlag ) {
    		lcdRefreshFlag = 0;
    		lcdMode2 = 2;
	}
        break;

    case 2: // ˆÊ’u‰Šú‰»
	lcdNowLocate = 0;
    	lcdLocate( 0, 0 );
	lcdMode2 = 3;
        break;

    case 3: // ‰üsˆÊ’u‚ÌŠm”F 
	if( lcdNowLocate % LCD_MAX_X == 0 ) {
    		lcdLocate( 0, lcdNowLocate / LCD_MAX_X );
	}
	lcdMode2 = 4;
        break;

    case 4: // ƒf[ƒ^•\Ž¦ˆ—
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
// ƒ‚ƒWƒ…[ƒ‹–¼ lcdPrintf						//
// ˆ—ŠT—v     ‰t»‚Ö•\Ž¦ •\Ž¦ˆÊ’u‚Í‰ß‹Ž‚É•\Ž¦‚µ‚½ˆÊ’u‚ÌŽŸ‚©‚ç		//
// ˆø”         printf‚Æ“¯‚¶						//
// –ß‚è’l       ³íŽžFo—Í‚µ‚½•¶Žš—ñ ˆÙíŽžF•‰‚Ì”			//
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
        // vsprintf‚ª³í‚È‚ç‰t»ƒoƒbƒtƒ@‚Ö“]‘—
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
// ƒ‚ƒWƒ…[ƒ‹–¼ lcdPosition                                             //
// ˆ—ŠT—v     ‰t»‚Ì•\Ž¦ˆÊ’uŽw’è                                      //
// ˆø”         ‰¡ˆÊ’u , cˆÊ’u                                         //
// –ß‚è’l       ‚È‚µ                                                    //
//////////////////////////////////////////////////////////////////////////
void lcdPosition(char x ,char y)
{
    if( x >= LCD_MAX_X ) return;
    if( y >= LCD_MAX_Y ) return;
=======
//LCDï¿½Jï¿½[ï¿½\ï¿½ï¿½ï¿½Ú“ï¿½
static void lcdLocate(int x, int y){
	
	volatile unsigned char work = 0x80;		//set DDRAM address
	
	//xï¿½ÌŒvï¿½Z
	work += x;
	
	//yï¿½ÌŒvï¿½Z
	if(y == 1) work += 0x40;
	else if(y == 2) work += 0x14;
	
	//ï¿½Rï¿½}ï¿½ï¿½ï¿½hï¿½ï¿½ï¿½ï¿½
	lcd_CMD(work);
	
}
//æ¶²æ™¶è¡¨ç¤ºé–¢æ•°
void lcd_print (char *str){
	for (int i = 0 ; i < strlen(str); i ++) lcd_DATE (str[1]) ;
}

//æ–‡å­—åˆ—è¡¨ç¤ºé–¢æ•°
void LCDprint(int x, int y, char *str){
	//ã‚«ãƒ¼ã‚½ãƒ«ã‚’ï¼ˆï½˜ã€ï½™ï¼‰ã«ç§»å‹•ã—ã¦æ–‡å­—åˆ—ã‚’è¡¨ç¤º
	lcdLocate(x, y);
	lcd_print(str);
}
>>>>>>> origin/master

    lcdBuffPosition = x + y * LCD_MAX_X;
}