/****************************************************************************/
/* 対象マイコン R8C/38A or R8C/38C                                          */
/* ﾌｧｲﾙ内容     I2C(ST7032i)液晶制御ライブラリ                              */
/* バージョン   Ver.1.10                                                    */
/* Date         2012.03.11                                                  */
/* Copyright    ジャパンマイコンカーラリー実行委員会                        */
/****************************************************************************/

/*======================================*/
/* インクルード                         */
/*======================================*/
#include <stdio.h>                      /* 標準Cﾗｲﾌﾞﾗﾘ 入出力           */
#include <stdarg.h>                     /* 標準Cﾗｲﾌﾞﾗﾘ 可変個数の実引数 */
#include "sfr_r838a.h"                  /* R8C/38A SFRの定義ファイル    */
#include "lcd_st7032i_lib.h"            /* ST7032i(I2C)液晶表示ライブラ */

/*======================================*/
/* シンボル定義                         */
/*======================================*/

#define I2C_SFR             1           /* 1:マイコンのSFR使用          */
                                        /* 0:使用せずにポートで処理     */
/*
1の場合、端子が固定(P3_5とP3_7)ですが、マイコンの負荷が少なくないます。
0の場合、自由に端子を選ぶことができますが、マイコンの負荷が大きくなりま
す。できるだけ、"1"で使用してください。

●I2C_SFR = 1 のときのポート設定
　P3_7:液晶のSDA端子
　P3_5:液晶のSCL端子
　※変更はできません
*/

/* I2C_SFR = 0 のときのポート設定 ※ポート0は設定できません */
#define i2c_sda         p3_7            /* 液晶のSDA端子                */
#define i2c_sdaddr      pd3_7           /* 液晶のSDA端子の入出力設定ﾚｼﾞｽﾀ*/
#define i2c_scl         p3_5            /* 液晶のSCL端子                */
#define i2c_sclddr      pd3_5           /* 液晶のSCL端子の入出力設定ﾚｼﾞｽﾀ*/

/* I2C_SFR = 0 のときのSDA端子、SCL端子の設定　※変更しないでください */
#define i2c_SDA_0();    i2c_sda = 0;i2c_sdaddr = 1;     /* SDA = "0"    */
#define i2c_SDA_1();    i2c_sdaddr = 0;                 /* SDA = "1"    */
#define i2c_SCL_0();    i2c_scl = 0;i2c_sclddr = 1;     /* SCL = "0"    */
#define i2c_SCL_1();    i2c_sclddr = 0;                 /* SCL = "1"    */

/* 表示文字数 */
#define LCD_MAX_X           8           /* 横文字数  8 or 16 or 20      */
#define LCD_MAX_Y           2           /* 縦文字数  1 or  2 or  4      */

/* 液晶制御コード */
#define LCD_INST            0x00        /* インストラクション           */
#define LCD_DATA            0x80        /* データ                       */

/* その他定義 */
#define ACK                 0           /* ACK有効(ACK=0)               */
#define ACK_NO              1           /* ACK無効(ACK=1)               */
#define ACK_ERROR           2           /* ACKチェック時、その他のエラー*/

#define STOP_RD             0           /* ストップの直前は読み込み     */
#define STOP_WR             1           /* ストップの直前は書き込み     */

/*======================================*/
/* グローバル変数の宣言                 */
/*======================================*/
static volatile char            buffLcdData[ LCD_MAX_X * LCD_MAX_Y ];
                                        /* 表示バッファ                 */
static volatile int             lcdBuffPosition;
                                        /* バッファに書き込む位置       */
static volatile int             lcdRefreshFlag;
                                        /* リフレッシュフラグ           */
static volatile int             lcdMode;
                                        /* 表示処理No管理               */
static volatile unsigned long   lcdCnt;
                                        /* 液晶タイミング用カウンタ     */
static volatile int             lcdCtrt = 25;
                                        /* 液晶の濃さ 0～63             */
                                        /* 濃さを変えたい場合はこの     */
                                        /* 数値を変えてください         */
static volatile int             lcdCtrt2;
                                        /* 液晶の濃さ 比較用            */
static volatile unsigned char   i2c_write_ret;
                                        /* I2C書き込んだ後の返信電文    */

/************************************************************************/
/* モジュール名 lcd_wait                                                */
/* 処理概要     ごく短いタイマ                                          */
/* 引数         1あたり約1us、ただし最適化オプションや                  */
/*              コンパイラのバージョンで変わることがあります            */
/* 戻り値       無し                                                    */
/* メモ         最適化オプションやコンパイラのバージョンで              */
/*              時間が変わることがあります                              */
/************************************************************************/
static void lcd_wait( volatile int i )
{
    while( i-- );
}

/************************************************************************/
/* モジュール名 i2c_start                                               */
/* 処理概要     I2C スタート関連レジスタ設定、スタート信号送信          */
/* 引数         無し                                                    */
/* 戻り値       0:異常 1:正常                                           */
/************************************************************************/
static int i2c_start( void )
{
#if I2C_SFR
    int i = 1000, ret = 1;

    stop_icsr = 0;

    while( bbsy_iccr2 == 1 ) {
        if( !(i--) ) {
            ret = 0;
            break;
        }
    }

    iccr1 |= 0x30;                      /* マスタ送信モード             */
    iccr2  = 0x90;                      /* スタート条件発行             */

    return ret;
#else
    i2c_SDA_1();
    i2c_SCL_1();
    lcd_wait( 1 );

    i2c_SDA_0();
    i2c_SCL_1();
    lcd_wait( 1 );

    i2c_SDA_0();
    i2c_SCL_0();
    lcd_wait( 1 );

    return 1;
#endif
}

/************************************************************************/
/* モジュール名 i2c_stop                                                */
/* 処理概要     I2C ストップ信号送信                                    */
/* 引数         STOP_RD:stopの手前はリード  STOP_WR:stopの手前はライト  */
/* 戻り値       0:異常 1:正常                                           */
/************************************************************************/
static int i2c_stop( int mode )
{
#if I2C_SFR
    int i = 1000, ret = 1;

    if( mode == STOP_WR ) {
        iccr2 = 0x10;                   /* ストップ条件発行             */
        tend_icsr = 0;
        nackf_icsr = 0;
        while( stop_icsr == 0 ) {
            if( !(i--) ) {
                ret = 0;
                break;                  /* タイムアウト処理             */
            }
        }
    }
    iccr1 &= 0xcf;                      /* スレーブ受信モード           */

    return ret;
#else
    i2c_SDA_0();
    i2c_SCL_0();
    lcd_wait( 1 );

    i2c_SDA_0();
    i2c_SCL_1();
    lcd_wait( 1 );

    i2c_SDA_1();
    i2c_SCL_1();
    lcd_wait( 1 );

    return 1;
#endif
}

/************************************************************************/
/* モジュール名 i2c_write                                               */
/* 処理概要     I2C　１バイト書き込み                                   */
/* 引数         signed char データ                                      */
/* 戻り値       無し                                                    */
/************************************************************************/
static void i2c_write( signed char data )
{
#if I2C_SFR
    icdrt = data;
#else
    int i;

    for( i = 0; i<8; i++ ) {
        /* data set */
        if( data & 0x80 ) {
            i2c_SDA_1();
        } else {
            i2c_SDA_0();
        }

        /* SCL ON */
        i2c_SCL_1();
        lcd_wait( 1 );

        /* SCL OFF  */
        i2c_SCL_0();
        lcd_wait( 1 );

        /* 次の準備 */
        data <<= 1;
    }

    /* acknowledge read */
    i2c_SDA_1();
    lcd_wait( 1 );

    /* SCL ON */
    i2c_SCL_1();
    lcd_wait( 1 );

    i2c_write_ret = i2c_sda;

    /* SCL OFF  */
    i2c_SCL_0();
#endif
}

/************************************************************************/
/* モジュール名 i2c_ack_check                                           */
/* 処理概要     I2C 書き込み後のacknowledgeチェック                     */
/* 引数         signed char データ                                      */
/* 戻り値       int  acknowledge 0:有効  1:無効 ACK_ERROR:その他のエラー*/
/************************************************************************/
static int i2c_ack_check( void )
{
#if I2C_SFR
    if( tdre_icsr == 0 ) return ACK_ERROR;
    if( tend_icsr == 0 ) return ACK_ERROR;

    return ackbr_icier;
#else
    return i2c_write_ret;
#endif
}

/************************************************************************/
/* モジュール名 i2c_read                                                */
/* 処理概要     I2C １バイト読み込み                                    */
/* 引数         int ACK：データが続く ACK_NO：データ終了                */
/* 戻り値       signed char データ                                      */
/************************************************************************/
signed char i2c_read( int ack )
{
#if I2C_SFR
    signed char ret;
    volatile int i;

    tend_icsr = 0;
    iccr1 &= 0xef;
    tdre_icsr = 0;
    ackbt_icier = 1;
    ret = icdrr;                        /* ダミーリード                 */

    if( ack == ACK_NO ) {
        rcvd_iccr1 = 1;                 /* 次の受信動作を禁止           */
    }

    i = 1000;
    while( rdrf_icsr == 0 ) {
        if( !(i--) ) return 0;
    }

    iccr2 = 0x10;

    i = 1000;
    while( stop_icsr == 0 ) {
        if( !(i--) ) return 0;
    }

    ret = icdrr;
    rcvd_iccr1 = 0;
    ackbt_icier = 0;

    return ret;
#else
    char    ret;
    int     i;

    i2c_SDA_1();

    for( i = 0; i<8; i++ ) {
        ret <<= 1;

        /* SCL ON */
        i2c_SCL_1();
        lcd_wait( 1 );

        /* data read */
        if( i2c_sda ) {
            ret |= 0x01;
        }

        /* SCL OFF  */
        i2c_SCL_0();
    }

    /* acknowledge write */
    if( ack == ACK ) {
        i2c_SDA_0();
    } else {
        i2c_SDA_1();
    }

    /* SCL ON */
    i2c_SCL_1();
    lcd_wait( 1 );

    /* SCL OFF  */
    i2c_SCL_0();

    return ret;
#endif
}

/************************************************************************/
/* モジュール名 lcdTimer                                                */
/* 処理概要     割り込みによる正確なタイマ                              */
/* 引数         タイマ値 1=1ms                                          */
/* 戻り値       無し                                                    */
/* メモ         設定のタイミングで1ms未満の誤差があります               */
/************************************************************************/
static void lcdTimer( unsigned long timer_set )
{
    volatile unsigned long t;

    t = lcdCnt;

    while( lcdCnt - t < timer_set );
}

/************************************************************************/
/* モジュール名 lcdOut                                                  */
/* 処理概要     I2C液晶コマンド出力                                     */
/* 引数         コマンド種類、データ                                    */
/* 戻り値       0:異常 1:正常                                           */
/************************************************************************/
static int lcdOut( char command, char data )
{
    int retry, ret, mode = 0;
    int error = 10;                     // エラーチェック回数

    while( 1 ) {

    switch( mode ) {
    case 0:
        //  スタート発行
        retry = 100;
        while( 1 ) {
            ret = i2c_start();
            if( ret == 0 ) {
                // エラーならリトライする
                if( !(retry--) ) {
                    mode =  91;
                    break;
                }
            } else {
                // 正常なら次へ
                mode = 1;
                break;
            }
        }
        break;

    case 1:
        // スレーブアドレス転送
        retry = 100;
        i2c_write( 0x7c | !!(command&0x40) );
        while( 1 ) {
            if( i2c_ack_check() != ACK ) {
                // エラーならリトライする
                if( !(retry--) ) {
                    mode =  91;
                    break;
                }
            } else {
                // 正常なら次へ
                mode = 2;
                break;
            }
        }
        break;

    case 2:
        // コントロールバイト転送
        retry = 100;
        i2c_write( (command & 0x80) >> 1 );
        while( 1 ) {
            if( i2c_ack_check() != ACK ) {
                // エラーならリトライする
                if( !(retry--) ) {
                    mode =  91;
                    break;
                }
            } else {
                // 正常なら次へ
                mode = 3;
                break;
            }
        }
        break;

    case 3:
        // データ転送
        retry = 100;
        i2c_write( data );
        while( 1 ) {
            if( i2c_ack_check() != ACK ) {
                // エラーならリトライする
                if( !(retry--) ) {
                    mode =  91;
                    break;
                }
            } else {
                // 正常なら次へ
                mode = 4;
                break;
            }
        }
        break;

    case 4:
        // ストップ発行
        ret = i2c_stop( STOP_WR );
        if( ret == 0 ) {
            mode = 91;
            break;
        } else {
            return 1;           // 正常に終了
        }
        break;

    case 91:
        // エラー処理
        error--;
        if( !error ) return 0;  // エラー終了

        // ストップ発行
        lcd_wait( 100 );
        i2c_stop( STOP_WR );
        lcd_wait( 100 );

        // スタート発行に戻る
        mode = 0;
        break;
    }

    }
    return 0;   // エラー終了
}

/************************************************************************/
/* モジュール名 initLcd                                                 */
/* 処理概要     ST7032iコントローラ液晶の初期化                         */
/* 引数         なし                                                    */
/* 戻り値       0:異常 1:正常                                           */
/************************************************************************/
int initLcd( void )
{
    int i, ret;

    // 変数初期化
    for( i=0; i<=LCD_MAX_X*LCD_MAX_Y-1; i++ ) {
        buffLcdData[ i ] = ' ';
    }
    lcdCtrt2 = lcdCtrt;

#if I2C_SFR
    // ポートの入出力設定
    pd3 &= 0x5f;                        /* P3_7:SDA P3_5:SCL            */

    // I2Cの設定
    iicsel = 1;
    stop_icsr = 0;
    ice_iccr1 = 1;
    icmr  = 0x00;
    iccr1 = 0x8d;                       /* CKS=f1/200 = 100KHz          */
    icier = 0x00;
    icsr  = 0x00;
    sar   = 0x00;
#else
    i2c_sdaddr = 0;
    i2c_sclddr = 0;
#endif

    lcdTimer( 40 );                     /* 40ms以上のタイマ             */

    // 液晶の初期設定
    ret = lcdOut( LCD_INST, 0x38 );     /* Function set                 */
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us以上のタイマ           */

    ret = lcdOut( LCD_INST, 0x39 );     /* Function set                 */
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us以上のタイマ           */

    ret = lcdOut( LCD_INST, 0x10 );     /* Internal OSC frequency       */
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us以上のタイマ           */

    ret = lcdOut( LCD_INST, 0x70 |      /* Constrast set                */
        (lcdCtrt & 0x0f) );
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us以上のタイマ           */

    ret = lcdOut( LCD_INST, 0x5c |      /* Power/ICON/Constrast control */
        (lcdCtrt & 0x30)>>4 );
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us以上のタイマ           */

    ret = lcdOut( LCD_INST, 0x6a );     /* Follower control             */
    if( !ret ) return 0;
    lcdTimer( 205 );                    /* 200ms以上のタイマ            */

    ret = lcdOut( LCD_INST, 0x0c );     /* Display ON/OFF               */
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us以上のタイマ           */

    ret = lcdOut( LCD_INST, 0x01 );     /* Display ON/OFF               */
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us以上のタイマ           */

    ret = lcdOut( LCD_INST, 0x06 );     /* Display ON/OFF               */
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us以上のタイマ           */

    lcdMode = 1;                        /* 液晶接続完了                 */

    return 1;
}

/************************************************************************/
/* モジュール名 lcdShowProcess                                          */
/* 処理概要     I2C液晶表示処理                                         */
/* 引数         なし                                                    */
/* 戻り値       なし                                                    */
/* メモ         この関数は割り込みで1msごとに実行してください           */
/************************************************************************/
void lcdShowProcess( void )
{
    static int lcdNowLocate;            /* 現在の表示している位置       */
    static int lcdMode2;                /* 表示後の戻り先               */
    static signed char cmd, data;
    int ret, i;

    lcdCnt++;

    switch( lcdMode ) {
    case 0:
        // 液晶未接続時は何もしない
        break;

    case 1:
        // データ更新されたかチェック
        if( lcdRefreshFlag ) {
            lcdRefreshFlag = 0;
            lcdNowLocate = 0;
            lcdMode = 11;
            break;
        }
        lcdMode = 2;
        break;

    case 2:
        // コントラスト　変更された？
        if( lcdCtrt2 != lcdCtrt ) {
            lcdCtrt2 = lcdCtrt;
            lcdMode = 3;
            break;
        }
        lcdMode = 1;
        break;

    case 3:
        // コントラスト設定1
        cmd  = LCD_INST;
        data = 0x70 | (lcdCtrt2 & 0x0f);
        lcdMode2 = 4;
        lcdMode = 21;
        break;

    case 4:
        // コントラスト設定2
        cmd  = LCD_INST;
        data = 0x5c | ( (lcdCtrt2 & 0x30) >> 4 );
        lcdMode2 = 1;
        lcdMode = 21;
        break;

    case 11:
        // 改行位置の確認
        if( lcdNowLocate % LCD_MAX_X == 0 ) {
            i = lcdNowLocate / LCD_MAX_X;
            if( i == 1 ) {
                i = 0x40;
            } else if( i == 2 ) {
                i = 0x14;
            } else if( i == 3 ) {
                i = 0x54;
            }
            cmd  = LCD_INST;
            data = i | 0x80;
            lcdMode2 = 12;
            lcdMode = 21;
        } else {
            lcdMode = 12;
        }
        break;

    case 12:
        // データ表示処理
        cmd  = LCD_DATA;
        data = buffLcdData[ lcdNowLocate++ ];
        lcdMode2 = 13;
        lcdMode = 21;
        break;

    case 13:
        // 改行チェック
        if( lcdNowLocate >= LCD_MAX_X * LCD_MAX_Y ) {
            lcdMode = 2;
        } else {
            lcdMode = 11;
        }
        break;

    /* 20番台　I2C液晶制御 */
    case 21:
        // スタート発行
        ret = i2c_start();
        if( ret != 0 ) {
            // スレーブアドレス転送
            i2c_write( 0x7c | !!(cmd&0x40) );
            lcdMode++;
        } else {
            lcdMode = 0;
        }
        break;

    case 22:
        // ACKチェック、コントロールバイト転送
        if( i2c_ack_check() == ACK ) {
            //  コントロールバイト転送
            i2c_write( (cmd & 0x80) >> 1 );
            lcdMode++;
        } else {
            lcdMode = 0;
        }
        break;

    case 23:
        // ACKチェック、データ転送
        if( i2c_ack_check() == ACK ) {
            // データ転送
            i2c_write( data );
            lcdMode++;
        } else {
            lcdMode = 0;
        }
        break;

    case 24:
        // ACKチェック、ストップ発行
        if( i2c_ack_check() == ACK ) {
            // ストップ発行
            ret = i2c_stop( STOP_WR );
            if( ret == 0 ) {
                lcdMode = 0;
                break;
            }
            lcdMode = lcdMode2;
        } else {
            lcdMode = 0;
        }
        break;

    }
}

/************************************************************************/
/* モジュール名 lcdPrintf                                               */
/* 処理概要     I2C液晶へ表示　表示位置は過去に表示した位置の次から     */
/* 引数         printfと同じ                                            */
/* 戻り値       正常時：出力した文字列　異常時：負の数                  */
/************************************************************************/
int lcdPrintf( char *format, ... )
{
    volatile va_list argptr;
    volatile char    *p;
    volatile int     ret = 0;
    volatile char    work[ LCD_MAX_X * LCD_MAX_Y + 16 ];
                                        /* 表示バッファ一時作業エリア   */

    va_start(argptr, format);
    ret = vsprintf( work, format, argptr );
    va_end(argptr);

    if( ret > 0 ) {
        /* vsprintfが正常なら液晶バッファへ転送 */
        p = work;
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

/************************************************************************/
/* モジュール名 lcdPosition                                             */
/* 処理概要     I2C液晶の表示位置指定                                   */
/* 引数         横位置 , 縦位置                                         */
/* 戻り値       なし                                                    */
/************************************************************************/
void lcdPosition( char x, char y )
{
    if( x >= LCD_MAX_X ) return;
    if( y >= LCD_MAX_Y ) return;

    lcdBuffPosition = x + y * LCD_MAX_X;
}

/************************************************************************/
/* モジュール名 lcdContrast                                             */
/* 処理概要     I2C液晶のコントララスト設定                             */
/* 引数         int コントラスト                                        */
/* 戻り値       なし                                                    */
/************************************************************************/
void lcdContrast( int i )
{
    if( i >= 63 ) i = 63;
    if( i <=  0 ) i =  0;

    lcdCtrt = i;
}

/************************************************************************/
/* end of file                                                          */
/************************************************************************/

/*
改訂経歴

2013.02.28 Ver.1.00 作成
2013.03.11 Ver.1.10 作成
*/
