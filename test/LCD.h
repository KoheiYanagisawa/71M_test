<<<<<<< HEAD
#ifndef LCD_H_
#define LCD_H_
//====================================//
// ƒCƒ“ƒNƒ‹[ƒh                  						       //
//====================================//
#include "r_smc_entry.h"
#include <stdio.h>
#include <stdarg.h>
//====================================//
// ƒVƒ“ƒ{ƒ‹’è‹`									//
//====================================//
// ƒXƒŒ[ƒuƒAƒhƒŒƒX
#define LCD_SLAVEADDRESS	0x7cU
// ‰t»ŠÖ˜A•Ï”
#define LCD_MAX_X	17		// •\Ž¦•¶Žš” ‰¡ 16 or 20
#define LCD_MAX_Y	2		// •\Ž¦•¶Žš” c  2 or  4
#define RSBIT0		0x00		// ƒRƒ}ƒ“ƒh‘—Mƒrƒbƒg
#define RSBIT1		0x40		// ƒf[ƒ^‘—Mƒrƒbƒg

#define CLOCK		240		// “®ìŽü”g”[MHz]

#define BUS_LCD_FREE 			0		// ’ÊM‰Â”\
#define BUS_LCD_BUSY 			1		// ’ÊM’†

/******************************** Ž©“®¶¬ŠÖ” *********************************/
#define	I2C_LCD_SEND	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, word, 2)
#define	I2C_LCD_CMD	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, Command, 2)
/***************************************************************************/
//====================================//
// ƒOƒ[ƒoƒ‹•Ï”‚ÌéŒ¾							//
//====================================//
extern char	busLCD;
//====================================//
// ƒvƒƒgƒ^ƒCƒvéŒ¾								//
//====================================//
// LCDŠÖ˜A
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
//ï¿½Cï¿½ï¿½ï¿½Nï¿½ï¿½ï¿½[ï¿½h-----------------------------------------------------------------------------------------------

#include "r_smc_entry.h"

//ï¿½Vï¿½ï¿½ï¿½{ï¿½ï¿½ï¿½ï¿½`-----------------------------------------------------------------------------------------------

// ï¿½Xï¿½ï¿½ï¿½[ï¿½uï¿½Aï¿½hï¿½ï¿½ï¿½X

#define LCD_SLAVEADDRESS	0x7cU

// ï¿½tï¿½ï¿½ï¿½Ö˜Aï¿½Ïï¿½

#define LCD_MAX_X	17		// ï¿½\ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ 16 or 20
#define LCD_MAX_Y	2		// ï¿½\ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½c  2 or  4
#define RSBIT0		0x00		// ï¿½Rï¿½}ï¿½ï¿½ï¿½hï¿½ï¿½ï¿½Mï¿½rï¿½bï¿½g
#define RSBIT1		0x40		// ï¿½fï¿½[ï¿½^ï¿½ï¿½ï¿½Mï¿½rï¿½bï¿½g

#define BUS_LCD_FREE 			0		// ï¿½ÊMï¿½Â”\
#define BUS_LCD_BUSY 			1		// ï¿½ÊMï¿½ï¿½

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Öï¿½

#define	I2C_LCD_SEND	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, word, 2)      //ï¿½fï¿½[ï¿½^ï¿½ï¿½ï¿½Mï¿½p
#define	I2C_LCD_CMD	R_Config_SCI12_IIC_Master_Send(LCD_SLAVEADDRESS, Command, 2)   //ï¿½Rï¿½}ï¿½ï¿½ï¿½hï¿½ï¿½ï¿½Mï¿½p

//ï¿½Oï¿½ï¿½ï¿½[ï¿½oï¿½ï¿½ï¿½Ïï¿½-----------------------------------------------------------------------------------------------

extern int cnt_lcd;

//ï¿½vï¿½ï¿½ï¿½gï¿½^ï¿½Cï¿½vï¿½éŒ¾

//LCDï¿½ÖŒW

void lcd_CMD(unsigned char cmd);
void lcd_DATE(unsigned char date);
void wait_lcd(int time);
void inti_lcd(void);
void LCDprint(int x, int y, char *str);


#endif
>>>>>>> origin/master
