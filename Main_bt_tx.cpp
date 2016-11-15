/*
 * H28_BT_ROBOBA_TX.cpp
 *
 * Created: 2016/06/18 12:31:14
 * Author : sn 
 */ 

#include "Func_bt_tx.h"

//LED0 -> �����ݒ芮��
//LED1 -> Bluetooth�m�F
//LED2 -> Slave�Ƃ̐ڑ�����
//LED3 -> Link Lost ����̕��A��

/************************************************************************/

ISR(USART1_RX_vect)
{
	//Slave�Ƃ̐ڑ��A����
	
	cli();
	
	__LED1_OFF__;	__LED2_OFF__;	__LED3_ON__;
	
	char _data_in[40] = {};
	
	F_In_bt_tx_2(_data_in); //���ʂȏ�������Ȃ��̂ŏ����Ȃ��ł�������
	
	Lcd_put_str(0x40, "Link Lost       ");
	
	//F_BT_Cut(); //�R�}���h���[�h�ɕ��A
	
	__RSE_LOW___;
	
	_delay_ms(50);
	
	__RSE_HIGH__;
	
	F_In_comp_bt_tx_2(_data_in, "\r\nOK\r\n");
	
	E_BT_NUM _num_slave = EB_BT0;
	
	BOOL _flag_success = FALSE;
	
	do 
	{
		_flag_success = F_In_bt_num_bt_tx_2(_num_slave);
	}
	while (_flag_success == FALSE);
	
	__LED1_ON__;
	
	F_Conect_bt_tx_2(_num_slave); //Slave�ƍĐڑ�
	
	__LED2_ON__;
	
	__CTS_LOW___;
	
	__LED3_OFF__;
	
	sei();
}

/************************************************************************/

int main(void)
{
	/************************************************************************/
	//�����ݒ�
	
	F_Set_io_bt_tx_2();
	
	F_Set_uart_bt_tx_2(FALSE);
	
	C_UART_R _uart_r_contr(EU_UART0);
	
	__LED0_ON__;
	
	/************************************************************************/
	
	/************************************************************************/
	//�ڑ�,Bluetooth�̃A�h���X�ǂݎ��
	
	char _data_in[40] = {};
	
	E_BT_NUM _num_slave = EB_BT0;
	
	const BOOL _flag_success = F_In_bt_num_bt_tx_2(_num_slave);
		
	if (_flag_success == FALSE)	
	{
		Lcd_put_str(0x00, "Please Restart  ");
		Lcd_put_str(0x40, "Select Slave Num");
		
		while (1);
	}
	
	F_In_comp_bt_tx_2(_data_in, "\r\nOK\r\n");
	
	__LED1_ON__;

	F_Conect_bt_tx_2(_num_slave); //Slave�Ɛڑ�
	
	F_Set_uart_bt_tx_2(TRUE);
	
	sei();
	
	__LED2_ON__;
	
	/************************************************************************/
	
	__CTS_LOW___;
	
	while (1)
	{
		/************************************************************************/
		//�f�[�^�̓]��
		
		F_In_controler_bt_tx_2(_uart_r_contr, _data_in);
		
		F_Out_bt_tx_2(_data_in);
		
		/************************************************************************/
	}
	
	return 0;
}