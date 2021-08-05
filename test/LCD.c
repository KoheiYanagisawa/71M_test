#ifndef LCD_C
#define LCD_C
//�C���N���[�h----------------------------------------------------------------------------------------------------------------

#include"LCD.h"

//�O���[�o���ϐ�--------------------------------------------------------------------------------------------------------------


//����֐�--------------------------------------------------------------------------------------------------------------------

//�R�}���h���M�֐�

void lcd_CMD(unsigned char cmd){
	uint8_t Command[2] = { RSBIT0, cmd };
	I2C_LCD_CMD;

}

//�f�[�^���M�֐�

void lcd_DATE(unsigned char date){
	uint8_t word[2] = { RSBIT1, date };	
	I2C_LCD_SEND;
}
//�x���֐�

void wait_lcd(int time){
	cnt_lcd = 0;
	while(time >= cnt_lcd){
	}
	return 0;
}
//LCD�������֐�
void inti_lcd(void){
	
	wait_lcd(4);
	lcd_CMD(0x38);	// function set			: �f�[�^����8�{�E�\���͂Q�s�E�t�H���g��5x8�h�b�g
	wait_lcd(1);
	lcd_CMD(0x39);	// function set           	: �g���R�}���h�̐ݒ��L���ɂ���
	wait_lcd(1);
	lcd_CMD(0x14);	// Internal OSC frequency 	: �o�C�A�X�̑I���Ɠ���OSC���g���̒���
	wait_lcd(1);
	lcd_CMD(0x70);	// Contrast set          	: �R���g���X�g�����f�[�^(����4�r�b�g)
	wait_lcd(1);
	lcd_CMD(0x56);	// Power/ICON/Contrast control	: ������H�L���A�R���g���X�g�����f�[�^(���2�r�b�g)
	wait_lcd(1);
	lcd_CMD(0x6c);	// Follower control     	: �t�H���A��H��ON�A�������̒������s��
	wait_lcd(200);
	lcd_CMD(0x38);	// function set         	: �g���R�}���h��ݒ�𖳌��ɂ���
	wait_lcd(1);
	lcd_CMD(0x0c);	// display ON/OFF control      	: ��ʕ\����ON�E�J�[�\���\����OFF�E�J�[�\���_�ł�OFF
	wait_lcd(1);
	lcd_CMD(0x01);	// Clear Display 		: ��ʑS�̂�20H�̽�߰��ŕ\���A���ق�col=0,row=0�Ɉړ�
	wait_lcd(2);
	
}
//LCD�J�[�\���ړ�
static void lcdLocate(int x, int y){
	
	volatile unsigned char work = 0x80;		//set DDRAM address
	
	//x�̌v�Z
	work += x;
	
	//y�̌v�Z
	if(y == 1) work += 0x40;
	else if(y == 2) work += 0x14;
	
	//�R�}���h����
	lcd_CMD(work);
	
}
//液晶表示関数
void lcd_print (char *str){
	for (int i = 0 ; i < strlen(str); i ++) lcd_DATE (str[1]) ;
}

//文字列表示関数
void LCDprint(int x, int y, char *str){
	//カーソルを（ｘ、ｙ）に移動して文字列を表示
	lcdLocate(x, y);
	lcd_print(str);
}

#endif