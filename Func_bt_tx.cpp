
#pragma once

inline void 
F_Set_io_bt_tx_2 ()
{
	DDRA  = 0x00;
	PORTA = (__SW1_BIT__ | __SW2_BIT__ | __SW3_BIT__ | __SW4_BIT__ | __SW5_BIT__ | __SW6_BIT__ | __SW7_BIT__);
	DDRB  = (__BIT_LED0__ | __BIT_LED1__ | __BIT_LED2__);
	PORTB = 0x00;
	DDRC  = __BIT_LED3__;
	PORTC = 0x00;
	DDRD  = (__CTS_BIT__ | __RSE_BIT__);
	PORTD = (__CTS_BIT__ | __RSE_BIT__ | __SW0_BIT__);
	
	INI_LCD();
	
#if __SW_NATU__ == __EVEN__

	Lcd_put_str(0x00, "Master ver.2 Eve");

#elif __SW_NATU__ == __ODD__

	Lcd_put_str(0x00, "Master ver.2 Odd");

#endif
	
}

inline void 
F_Set_uart_bt_tx_2 (BOOL _arg_nf_isr = FALSE)
{
	//115.2kbps double-on parity-off
	//rec,tra-mode 8bit interrupt-off
	
	UBRR1H = 0x00;
	UBRR1L = 0x0a;
	UCSR1A = (1 << U2X);
	UCSR1B = ((1 << RXEN) | (1 << TXEN) | (_arg_nf_isr << RXCIE));
	UCSR1C = ((1 << UCSZ0) | (1 << UCSZ1));
}

inline BOOL
F_In_bt_num_bt_tx_2 (E_BT_NUM &_arg_re_bt_slave_num)
{
	switch (__SW_READ__)
	{
		case 0xfe:	_arg_re_bt_slave_num = EB_BT0;	break;
		case 0x01:	_arg_re_bt_slave_num = EB_BT1;	break;
		case 0xfd:	_arg_re_bt_slave_num = EB_BT2;	break;
		case 0x02:	_arg_re_bt_slave_num = EB_BT3;	break;
		case 0xfb:	_arg_re_bt_slave_num = EB_BT4;	break;
		case 0x04:	_arg_re_bt_slave_num = EB_BT5;	break;
		case 0xf7:	_arg_re_bt_slave_num = EB_BT6;	break;
		case 0x08:	_arg_re_bt_slave_num = EB_BT7;	break;
		case 0xef:	_arg_re_bt_slave_num = EB_BT8;	break;
		case 0x10:	_arg_re_bt_slave_num = EB_BT9;	break;
		case 0xdf:	_arg_re_bt_slave_num = EB_BTA;	break;
		case 0x20:	_arg_re_bt_slave_num = EB_BTB;	break;
		case 0xbf:	_arg_re_bt_slave_num = EB_BTC;	break;
		case 0x40:	_arg_re_bt_slave_num = EB_BTD;	break;
		case 0x7f:	_arg_re_bt_slave_num = EB_BTE;	break;
		case 0x80:	_arg_re_bt_slave_num = EB_BTF;	break;
		
		default:	return FALSE;
	}
	
	return TRUE;
}


inline void
F_Out_bt_tx_2 (const char _arg_data_out[])
{
	F_BT_Out(__UART_BLUETOOTH__, _arg_data_out);
}

inline void
F_In_bt_tx_2 (char _arg_re_data_in[])
{
	F_BT_In(__UART_BLUETOOTH__, _arg_re_data_in);
}

inline void
F_In_comp_bt_tx_2 (const char _arg_data_comp[])
{
	F_BT_In_comp(__UART_BLUETOOTH__, _arg_data_comp);
}

inline void 
F_In_comp_bt_tx_2
(
	char		_arg_re_data_in[], 
	const char	_arg_data_comp[]
)
{
	F_BT_In_comp(__UART_BLUETOOTH__, _arg_re_data_in, _arg_data_comp);
}

inline void
F_In_controler_bt_tx_2 
(
	C_UART_R &_arg_uart_r, 
	char _arg_re_data_in[]
)
{
	char _data_in[__BT_DATA_NUM__] = {0x3f, 0x7f, 0x8f, 0xc0};

	uchar _flag_loop = 0x0f;
	
	while (_flag_loop)
	{		
		char _temp = _arg_uart_r.In(FALSE);
		
		if (_arg_uart_r != EU_ERROR)
		{			
			_data_in[(_temp & 0xc0)>>6] = _temp;
			
			_flag_loop &= ~(1 << ((_temp & 0xc0)>>6));
		}
	}
	
	for(usint i = 0; i < __BT_DATA_NUM__; i++)
	{
		if (((_data_in[i] >> 4) & 0x0f) < 0x0a)
		{
			_arg_re_data_in[(i * 2) + 0] = (0x30 + (((_data_in[i] >> 4) & 0x0f) - 0));
		}
		else
		{
			_arg_re_data_in[(i * 2) + 0] = (0x40 + (((_data_in[i] >> 4) & 0x0f) - 9));
		}
		
		if (((_data_in[i] >> 0) & 0x0f) < 0x0a)
		{
			_arg_re_data_in[(i * 2) + 1] = (0x30 + (((_data_in[i] >> 0) & 0x0f) - 0));
		}
		else
		{
			_arg_re_data_in[(i * 2) + 1] = (0x40 + (((_data_in[i] >> 0) & 0x0f) - 9));
		}
	}
	
	_arg_re_data_in[(__BT_DATA_NUM__ * 2) + 0] = '\r';
	_arg_re_data_in[(__BT_DATA_NUM__ * 2) + 1] = '\n';
	_arg_re_data_in[(__BT_DATA_NUM__ * 2) + 2] = '\0';
	
	Lcd_put_str(0x07, _arg_re_data_in);
}

inline void
F_Conect_bt_tx_2 (const E_BT_NUM _arg_slave_num)
{
	char _slave_addr[__BT_ADDR_BYTE__] = {};
	
	char _CONMASTER_[32] = "AT+CONMASTER=1,000190xxxxxx\r\n";
	char _CONNECTED_[32] = "\r\n+CONNECTED=000190xxxxxx\r\n";
	
	switch (_arg_slave_num)
	{
		case EB_BT0:	F_Str_copy(_slave_addr, "000190EAD4B5"); break;
		case EB_BT1:	F_Str_copy(_slave_addr, "000190EAD491"); break;
		case EB_BT2:	F_Str_copy(_slave_addr, "000190E53F09"); break;
		case EB_BT3:	F_Str_copy(_slave_addr, "000190EAD491"); break;
		case EB_BT4:	F_Str_copy(_slave_addr, "000190EAD49A"); break;
		case EB_BT5:	F_Str_copy(_slave_addr, "000190E53A7B"); break;
		case EB_BT6:	F_Str_copy(_slave_addr, "000190EB1273"); break;
		case EB_BT7:	F_Str_copy(_slave_addr, "000190EB1416"); break;
		case EB_BT8:	F_Str_copy(_slave_addr, "000190EB105D"); break;
		case EB_BT9:	F_Str_copy(_slave_addr, "000190EB1057"); break;
		case EB_BTA:	F_Str_copy(_slave_addr, "000190EB105A"); break;
		case EB_BTB:	F_Str_copy(_slave_addr, "000190EB1052"); break;
		case EB_BTC:	F_Str_copy(_slave_addr, "000190EB1050"); break;
		case EB_BTD:	F_Str_copy(_slave_addr, "000190EB105C"); break;
		case EB_BTE:	F_Str_copy(_slave_addr, "000190EB104F"); break;
		case EB_BTF:	F_Str_copy(_slave_addr, "000190EB104E"); break;
	}

	for (usint i = 0; i < __BT_ADDR_BYTE__; i++)
	{
		_CONMASTER_[15 + i] = _slave_addr[i];
		_CONNECTED_[13 + i] = _slave_addr[i];
	}
		
	Lcd_put_str(0x40, "Connecting_     ");
	Lcd_put_num(0x4b, _arg_slave_num + 1, 2, ED_10);
	
	char _data_in[40] = {};
	
	Go_start_connect:
	
	F_Out_bt_tx_2(_CONMASTER_);
	
	F_In_comp_bt_tx_2(_data_in, "\r\nACK\r\n");
	
	do
	{
		F_In_bt_tx_2(_data_in);
		
		if (F_Str_comp("\r\nTIMEOUT\r\n", _data_in))
		{
			goto Go_start_connect;
		}
	}
	while (F_Str_comp(_CONNECTED_, _data_in) != TRUE);
	
	F_In_comp_bt_tx_2(_data_in, "\r\nOK\r\n");
	
	Lcd_put_str(0x40, "Connected_      ");
	Lcd_put_num(0x4a, _arg_slave_num + 1, 2, ED_10);
}

