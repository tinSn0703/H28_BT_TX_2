/*
 * H28_BT_ROBOBA_TX.cpp
 *
 * Created: 2016/06/18 12:31:14
 * Author : sn 
 */ 

#include "Func_bt_tx.h"

//LED0 -> 初期設定完了
//LED1 -> Bluetooth確認
//LED2 -> Slaveとの接続完了
//LED3 -> Link Lost からの復帰中

/************************************************************************/

ISR(USART1_RX_vect)
{
	//Slaveとの接続、沈黙
	
	cli();
	
	__LED1_OFF__;	__LED2_OFF__;	__LED3_ON__;
	
	char _data_in[40] = {};
	
	F_In_bt_tx_2(_data_in); //無駄な処理じゃないので消さないでください
	
	Lcd_put_str(0x40, "Link Lost       ");
	
	//F_BT_Cut(); //コマンドモードに復帰
	
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
	
	F_Conect_bt_tx_2(_num_slave); //Slaveと再接続
	
	__LED2_ON__;
	
	__CTS_LOW___;
	
	__LED3_OFF__;
	
	sei();
}

/************************************************************************/

int main(void)
{
	/************************************************************************/
	//初期設定
	
	F_Set_io_bt_tx_2();
	
	F_Set_uart_bt_tx_2(FALSE);
	
	C_UART_R _uart_r_contr(EU_UART0);
	
	__LED0_ON__;
	
	/************************************************************************/
	
	/************************************************************************/
	//接続,Bluetoothのアドレス読み取り
	
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

	F_Conect_bt_tx_2(_num_slave); //Slaveと接続
	
	F_Set_uart_bt_tx_2(TRUE);
	
	sei();
	
	__LED2_ON__;
	
	/************************************************************************/
	
	__CTS_LOW___;
	
	while (1)
	{
		/************************************************************************/
		//データの転送
		
		F_In_controler_bt_tx_2(_uart_r_contr, _data_in);
		
		F_Out_bt_tx_2(_data_in);
		
		/************************************************************************/
	}
	
	return 0;
}