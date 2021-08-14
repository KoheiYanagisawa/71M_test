/*======================================*/
/* プロトタイプ宣言 					*/
/*======================================*/
int initLcd( void );
void lcdShowProcess( void );
int lcdPrintf(char far *format, ...);
void lcdPosition(char x ,char y);
void lcdContrast( int i );

/*======================================*/
/* シンボル定義 						*/
/*======================================*/
