/****************************************************************************/
/* �Ώۃ}�C�R�� R8C/38A or R8C/38C                                          */
/* ̧�ٓ��e     I2C(ST7032i)�t�����䃉�C�u����                              */
/* �o�[�W����   Ver.1.10                                                    */
/* Date         2012.03.11                                                  */
/* Copyright    �W���p���}�C�R���J�[�����[���s�ψ���                        */
/****************************************************************************/

/*======================================*/
/* �C���N���[�h                         */
/*======================================*/
#include <stdio.h>                      /* �W��Cײ���� ���o��           */
#include <stdarg.h>                     /* �W��Cײ���� �ό��̎����� */
#include "sfr_r838a.h"                  /* R8C/38A SFR�̒�`�t�@�C��    */
#include "lcd_st7032i_lib.h"            /* ST7032i(I2C)�t���\�����C�u�� */

/*======================================*/
/* �V���{����`                         */
/*======================================*/

#define I2C_SFR             1           /* 1:�}�C�R����SFR�g�p          */
                                        /* 0:�g�p�����Ƀ|�[�g�ŏ���     */
/*
1�̏ꍇ�A�[�q���Œ�(P3_5��P3_7)�ł����A�}�C�R���̕��ׂ����Ȃ��Ȃ��܂��B
0�̏ꍇ�A���R�ɒ[�q��I�Ԃ��Ƃ��ł��܂����A�}�C�R���̕��ׂ��傫���Ȃ��
���B�ł��邾���A"1"�Ŏg�p���Ă��������B

��I2C_SFR = 1 �̂Ƃ��̃|�[�g�ݒ�
�@P3_7:�t����SDA�[�q
�@P3_5:�t����SCL�[�q
�@���ύX�͂ł��܂���
*/

/* I2C_SFR = 0 �̂Ƃ��̃|�[�g�ݒ� ���|�[�g0�͐ݒ�ł��܂��� */
#define i2c_sda         p3_7            /* �t����SDA�[�q                */
#define i2c_sdaddr      pd3_7           /* �t����SDA�[�q�̓��o�͐ݒ�ڼ޽�*/
#define i2c_scl         p3_5            /* �t����SCL�[�q                */
#define i2c_sclddr      pd3_5           /* �t����SCL�[�q�̓��o�͐ݒ�ڼ޽�*/

/* I2C_SFR = 0 �̂Ƃ���SDA�[�q�ASCL�[�q�̐ݒ�@���ύX���Ȃ��ł������� */
#define i2c_SDA_0();    i2c_sda = 0;i2c_sdaddr = 1;     /* SDA = "0"    */
#define i2c_SDA_1();    i2c_sdaddr = 0;                 /* SDA = "1"    */
#define i2c_SCL_0();    i2c_scl = 0;i2c_sclddr = 1;     /* SCL = "0"    */
#define i2c_SCL_1();    i2c_sclddr = 0;                 /* SCL = "1"    */

/* �\�������� */
#define LCD_MAX_X           8           /* ��������  8 or 16 or 20      */
#define LCD_MAX_Y           2           /* �c������  1 or  2 or  4      */

/* �t������R�[�h */
#define LCD_INST            0x00        /* �C���X�g���N�V����           */
#define LCD_DATA            0x80        /* �f�[�^                       */

/* ���̑���` */
#define ACK                 0           /* ACK�L��(ACK=0)               */
#define ACK_NO              1           /* ACK����(ACK=1)               */
#define ACK_ERROR           2           /* ACK�`�F�b�N���A���̑��̃G���[*/

#define STOP_RD             0           /* �X�g�b�v�̒��O�͓ǂݍ���     */
#define STOP_WR             1           /* �X�g�b�v�̒��O�͏�������     */

/*======================================*/
/* �O���[�o���ϐ��̐錾                 */
/*======================================*/
static volatile char            buffLcdData[ LCD_MAX_X * LCD_MAX_Y ];
                                        /* �\���o�b�t�@                 */
static volatile int             lcdBuffPosition;
                                        /* �o�b�t�@�ɏ������ވʒu       */
static volatile int             lcdRefreshFlag;
                                        /* ���t���b�V���t���O           */
static volatile int             lcdMode;
                                        /* �\������No�Ǘ�               */
static volatile unsigned long   lcdCnt;
                                        /* �t���^�C�~���O�p�J�E���^     */
static volatile int             lcdCtrt = 25;
                                        /* �t���̔Z�� 0�`63             */
                                        /* �Z����ς������ꍇ�͂���     */
                                        /* ���l��ς��Ă�������         */
static volatile int             lcdCtrt2;
                                        /* �t���̔Z�� ��r�p            */
static volatile unsigned char   i2c_write_ret;
                                        /* I2C�������񂾌�̕ԐM�d��    */

/************************************************************************/
/* ���W���[���� lcd_wait                                                */
/* �����T�v     �����Z���^�C�}                                          */
/* ����         1�������1us�A�������œK���I�v�V������                  */
/*              �R���p�C���̃o�[�W�����ŕς�邱�Ƃ�����܂�            */
/* �߂�l       ����                                                    */
/* ����         �œK���I�v�V������R���p�C���̃o�[�W������              */
/*              ���Ԃ��ς�邱�Ƃ�����܂�                              */
/************************************************************************/
static void lcd_wait( volatile int i )
{
    while( i-- );
}

/************************************************************************/
/* ���W���[���� i2c_start                                               */
/* �����T�v     I2C �X�^�[�g�֘A���W�X�^�ݒ�A�X�^�[�g�M�����M          */
/* ����         ����                                                    */
/* �߂�l       0:�ُ� 1:����                                           */
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

    iccr1 |= 0x30;                      /* �}�X�^���M���[�h             */
    iccr2  = 0x90;                      /* �X�^�[�g�������s             */

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
/* ���W���[���� i2c_stop                                                */
/* �����T�v     I2C �X�g�b�v�M�����M                                    */
/* ����         STOP_RD:stop�̎�O�̓��[�h  STOP_WR:stop�̎�O�̓��C�g  */
/* �߂�l       0:�ُ� 1:����                                           */
/************************************************************************/
static int i2c_stop( int mode )
{
#if I2C_SFR
    int i = 1000, ret = 1;

    if( mode == STOP_WR ) {
        iccr2 = 0x10;                   /* �X�g�b�v�������s             */
        tend_icsr = 0;
        nackf_icsr = 0;
        while( stop_icsr == 0 ) {
            if( !(i--) ) {
                ret = 0;
                break;                  /* �^�C���A�E�g����             */
            }
        }
    }
    iccr1 &= 0xcf;                      /* �X���[�u��M���[�h           */

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
/* ���W���[���� i2c_write                                               */
/* �����T�v     I2C�@�P�o�C�g��������                                   */
/* ����         signed char �f�[�^                                      */
/* �߂�l       ����                                                    */
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

        /* ���̏��� */
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
/* ���W���[���� i2c_ack_check                                           */
/* �����T�v     I2C �������݌��acknowledge�`�F�b�N                     */
/* ����         signed char �f�[�^                                      */
/* �߂�l       int  acknowledge 0:�L��  1:���� ACK_ERROR:���̑��̃G���[*/
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
/* ���W���[���� i2c_read                                                */
/* �����T�v     I2C �P�o�C�g�ǂݍ���                                    */
/* ����         int ACK�F�f�[�^������ ACK_NO�F�f�[�^�I��                */
/* �߂�l       signed char �f�[�^                                      */
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
    ret = icdrr;                        /* �_�~�[���[�h                 */

    if( ack == ACK_NO ) {
        rcvd_iccr1 = 1;                 /* ���̎�M������֎~           */
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
/* ���W���[���� lcdTimer                                                */
/* �����T�v     ���荞�݂ɂ�鐳�m�ȃ^�C�}                              */
/* ����         �^�C�}�l 1=1ms                                          */
/* �߂�l       ����                                                    */
/* ����         �ݒ�̃^�C�~���O��1ms�����̌덷������܂�               */
/************************************************************************/
static void lcdTimer( unsigned long timer_set )
{
    volatile unsigned long t;

    t = lcdCnt;

    while( lcdCnt - t < timer_set );
}

/************************************************************************/
/* ���W���[���� lcdOut                                                  */
/* �����T�v     I2C�t���R�}���h�o��                                     */
/* ����         �R�}���h��ށA�f�[�^                                    */
/* �߂�l       0:�ُ� 1:����                                           */
/************************************************************************/
static int lcdOut( char command, char data )
{
    int retry, ret, mode = 0;
    int error = 10;                     // �G���[�`�F�b�N��

    while( 1 ) {

    switch( mode ) {
    case 0:
        //  �X�^�[�g���s
        retry = 100;
        while( 1 ) {
            ret = i2c_start();
            if( ret == 0 ) {
                // �G���[�Ȃ烊�g���C����
                if( !(retry--) ) {
                    mode =  91;
                    break;
                }
            } else {
                // ����Ȃ玟��
                mode = 1;
                break;
            }
        }
        break;

    case 1:
        // �X���[�u�A�h���X�]��
        retry = 100;
        i2c_write( 0x7c | !!(command&0x40) );
        while( 1 ) {
            if( i2c_ack_check() != ACK ) {
                // �G���[�Ȃ烊�g���C����
                if( !(retry--) ) {
                    mode =  91;
                    break;
                }
            } else {
                // ����Ȃ玟��
                mode = 2;
                break;
            }
        }
        break;

    case 2:
        // �R���g���[���o�C�g�]��
        retry = 100;
        i2c_write( (command & 0x80) >> 1 );
        while( 1 ) {
            if( i2c_ack_check() != ACK ) {
                // �G���[�Ȃ烊�g���C����
                if( !(retry--) ) {
                    mode =  91;
                    break;
                }
            } else {
                // ����Ȃ玟��
                mode = 3;
                break;
            }
        }
        break;

    case 3:
        // �f�[�^�]��
        retry = 100;
        i2c_write( data );
        while( 1 ) {
            if( i2c_ack_check() != ACK ) {
                // �G���[�Ȃ烊�g���C����
                if( !(retry--) ) {
                    mode =  91;
                    break;
                }
            } else {
                // ����Ȃ玟��
                mode = 4;
                break;
            }
        }
        break;

    case 4:
        // �X�g�b�v���s
        ret = i2c_stop( STOP_WR );
        if( ret == 0 ) {
            mode = 91;
            break;
        } else {
            return 1;           // ����ɏI��
        }
        break;

    case 91:
        // �G���[����
        error--;
        if( !error ) return 0;  // �G���[�I��

        // �X�g�b�v���s
        lcd_wait( 100 );
        i2c_stop( STOP_WR );
        lcd_wait( 100 );

        // �X�^�[�g���s�ɖ߂�
        mode = 0;
        break;
    }

    }
    return 0;   // �G���[�I��
}

/************************************************************************/
/* ���W���[���� initLcd                                                 */
/* �����T�v     ST7032i�R���g���[���t���̏�����                         */
/* ����         �Ȃ�                                                    */
/* �߂�l       0:�ُ� 1:����                                           */
/************************************************************************/
int initLcd( void )
{
    int i, ret;

    // �ϐ�������
    for( i=0; i<=LCD_MAX_X*LCD_MAX_Y-1; i++ ) {
        buffLcdData[ i ] = ' ';
    }
    lcdCtrt2 = lcdCtrt;

#if I2C_SFR
    // �|�[�g�̓��o�͐ݒ�
    pd3 &= 0x5f;                        /* P3_7:SDA P3_5:SCL            */

    // I2C�̐ݒ�
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

    lcdTimer( 40 );                     /* 40ms�ȏ�̃^�C�}             */

    // �t���̏����ݒ�
    ret = lcdOut( LCD_INST, 0x38 );     /* Function set                 */
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us�ȏ�̃^�C�}           */

    ret = lcdOut( LCD_INST, 0x39 );     /* Function set                 */
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us�ȏ�̃^�C�}           */

    ret = lcdOut( LCD_INST, 0x10 );     /* Internal OSC frequency       */
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us�ȏ�̃^�C�}           */

    ret = lcdOut( LCD_INST, 0x70 |      /* Constrast set                */
        (lcdCtrt & 0x0f) );
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us�ȏ�̃^�C�}           */

    ret = lcdOut( LCD_INST, 0x5c |      /* Power/ICON/Constrast control */
        (lcdCtrt & 0x30)>>4 );
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us�ȏ�̃^�C�}           */

    ret = lcdOut( LCD_INST, 0x6a );     /* Follower control             */
    if( !ret ) return 0;
    lcdTimer( 205 );                    /* 200ms�ȏ�̃^�C�}            */

    ret = lcdOut( LCD_INST, 0x0c );     /* Display ON/OFF               */
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us�ȏ�̃^�C�}           */

    ret = lcdOut( LCD_INST, 0x01 );     /* Display ON/OFF               */
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us�ȏ�̃^�C�}           */

    ret = lcdOut( LCD_INST, 0x06 );     /* Display ON/OFF               */
    if( !ret ) return 0;
    lcd_wait( 100 );                    /* 26.3us�ȏ�̃^�C�}           */

    lcdMode = 1;                        /* �t���ڑ�����                 */

    return 1;
}

/************************************************************************/
/* ���W���[���� lcdShowProcess                                          */
/* �����T�v     I2C�t���\������                                         */
/* ����         �Ȃ�                                                    */
/* �߂�l       �Ȃ�                                                    */
/* ����         ���̊֐��͊��荞�݂�1ms���ƂɎ��s���Ă�������           */
/************************************************************************/
void lcdShowProcess( void )
{
    static int lcdNowLocate;            /* ���݂̕\�����Ă���ʒu       */
    static int lcdMode2;                /* �\����̖߂��               */
    static signed char cmd, data;
    int ret, i;

    lcdCnt++;

    switch( lcdMode ) {
    case 0:
        // �t�����ڑ����͉������Ȃ�
        break;

    case 1:
        // �f�[�^�X�V���ꂽ���`�F�b�N
        if( lcdRefreshFlag ) {
            lcdRefreshFlag = 0;
            lcdNowLocate = 0;
            lcdMode = 11;
            break;
        }
        lcdMode = 2;
        break;

    case 2:
        // �R���g���X�g�@�ύX���ꂽ�H
        if( lcdCtrt2 != lcdCtrt ) {
            lcdCtrt2 = lcdCtrt;
            lcdMode = 3;
            break;
        }
        lcdMode = 1;
        break;

    case 3:
        // �R���g���X�g�ݒ�1
        cmd  = LCD_INST;
        data = 0x70 | (lcdCtrt2 & 0x0f);
        lcdMode2 = 4;
        lcdMode = 21;
        break;

    case 4:
        // �R���g���X�g�ݒ�2
        cmd  = LCD_INST;
        data = 0x5c | ( (lcdCtrt2 & 0x30) >> 4 );
        lcdMode2 = 1;
        lcdMode = 21;
        break;

    case 11:
        // ���s�ʒu�̊m�F
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
        // �f�[�^�\������
        cmd  = LCD_DATA;
        data = buffLcdData[ lcdNowLocate++ ];
        lcdMode2 = 13;
        lcdMode = 21;
        break;

    case 13:
        // ���s�`�F�b�N
        if( lcdNowLocate >= LCD_MAX_X * LCD_MAX_Y ) {
            lcdMode = 2;
        } else {
            lcdMode = 11;
        }
        break;

    /* 20�ԑ�@I2C�t������ */
    case 21:
        // �X�^�[�g���s
        ret = i2c_start();
        if( ret != 0 ) {
            // �X���[�u�A�h���X�]��
            i2c_write( 0x7c | !!(cmd&0x40) );
            lcdMode++;
        } else {
            lcdMode = 0;
        }
        break;

    case 22:
        // ACK�`�F�b�N�A�R���g���[���o�C�g�]��
        if( i2c_ack_check() == ACK ) {
            //  �R���g���[���o�C�g�]��
            i2c_write( (cmd & 0x80) >> 1 );
            lcdMode++;
        } else {
            lcdMode = 0;
        }
        break;

    case 23:
        // ACK�`�F�b�N�A�f�[�^�]��
        if( i2c_ack_check() == ACK ) {
            // �f�[�^�]��
            i2c_write( data );
            lcdMode++;
        } else {
            lcdMode = 0;
        }
        break;

    case 24:
        // ACK�`�F�b�N�A�X�g�b�v���s
        if( i2c_ack_check() == ACK ) {
            // �X�g�b�v���s
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
/* ���W���[���� lcdPrintf                                               */
/* �����T�v     I2C�t���֕\���@�\���ʒu�͉ߋ��ɕ\�������ʒu�̎�����     */
/* ����         printf�Ɠ���                                            */
/* �߂�l       ���펞�F�o�͂���������@�ُ펞�F���̐�                  */
/************************************************************************/
int lcdPrintf( char *format, ... )
{
    volatile va_list argptr;
    volatile char    *p;
    volatile int     ret = 0;
    volatile char    work[ LCD_MAX_X * LCD_MAX_Y + 16 ];
                                        /* �\���o�b�t�@�ꎞ��ƃG���A   */

    va_start(argptr, format);
    ret = vsprintf( work, format, argptr );
    va_end(argptr);

    if( ret > 0 ) {
        /* vsprintf������Ȃ�t���o�b�t�@�֓]�� */
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
/* ���W���[���� lcdPosition                                             */
/* �����T�v     I2C�t���̕\���ʒu�w��                                   */
/* ����         ���ʒu , �c�ʒu                                         */
/* �߂�l       �Ȃ�                                                    */
/************************************************************************/
void lcdPosition( char x, char y )
{
    if( x >= LCD_MAX_X ) return;
    if( y >= LCD_MAX_Y ) return;

    lcdBuffPosition = x + y * LCD_MAX_X;
}

/************************************************************************/
/* ���W���[���� lcdContrast                                             */
/* �����T�v     I2C�t���̃R���g�����X�g�ݒ�                             */
/* ����         int �R���g���X�g                                        */
/* �߂�l       �Ȃ�                                                    */
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
�����o��

2013.02.28 Ver.1.00 �쐬
2013.03.11 Ver.1.10 �쐬
*/
