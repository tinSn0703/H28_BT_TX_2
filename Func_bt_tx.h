
#pragma once

#define __CTS__ EI_IO4
#define __RTS__ EI_IO5
#define __RSE__ EI_IO6

/************************************************************************/

#include <H28_BT/H28_BT.h>

#include <FallMoon/akilcd_tx.h>

/************************************************************************/

#define __EVEN__ 0
#define __ODD__  1

#define __SW_NATU__	__EVEN__
//奇数番を使う場合は__ODD__、偶数番の場合は__EVEN__にしてください。

#define __UART_BLUETOOTH__ EU_UART1

#define __BIT_LED0__ (1 << PB0)
#define __BIT_LED1__ (1 << PB1)
#define __BIT_LED2__ (1 << PB2)
#define __BIT_LED3__ (1 << PC6)

#define __LED0_ON__ PORTB |= __BIT_LED0__
#define __LED1_ON__ PORTB |= __BIT_LED1__
#define __LED2_ON__ PORTB |= __BIT_LED2__
#define __LED3_ON__ PORTC |= __BIT_LED3__

#define __LED0_OFF__ PORTB &= ~__BIT_LED0__
#define __LED1_OFF__ PORTB &= ~__BIT_LED1__
#define __LED2_OFF__ PORTB &= ~__BIT_LED2__
#define __LED3_OFF__ PORTC &= ~__BIT_LED3__

#define __SW0_BIT__ (1 << PD1)
#define __SW1_BIT__ (1 << PA1)
#define __SW2_BIT__ (1 << PA2)
#define __SW3_BIT__ (1 << PA3)
#define __SW4_BIT__ (1 << PA4)
#define __SW5_BIT__ (1 << PA5)
#define __SW6_BIT__ (1 << PA6)
#define __SW7_BIT__ (1 << PA7)

#if __SW_NATU__ == __EVEN__

#	define __SW_READ__ ((~((PINA & 0xfe) | ((PIND >> 1) & 1))) & 0xff)

#elif __SW_NATU__ == __ODD__

#	define __SW_READ__ ((((PINA & 0xfe) | ((PIND >> 1) & 1))) & 0xff)

#endif

/************************************************************************/

/** Made 2016 / 11 / 06 (Sun)
 * \brief
 *	IOレジスタの設定を行う
 */
void F_Set_io_bt_tx_2 ();

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	Bluetoothに使用するUARTを設定する。UART1。
 *
 * \param _arg_nf_isr : 割り込み処理のON/OFF
 */
void F_Set_uart_bt_tx_2 (BOOL _arg_nf_isr);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	Slaveの番号をDIPスイッチから読み取る。
 *	成功した場合、TRUE、失敗した場合FALSEをreturnする
 * 
 * \return BOOL 読み取りの成否の通知
 */
BOOL F_In_bt_num_bt_tx_2(E_BT_NUM &_arg_re_bt_slave_num);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	コントローラからのデータを受け取り、Bluetoothで送信する形へ変換する。
 *	変換は、データを16進数で表したものを文字列にしたものにする。 
 *
 * \param _arg_re_data_in : 受信したデータ。変換済み。そのまま送信してね。
 */
void F_In_controler_bt_tx_2 (C_UART_R &_arg_uart_r, char _arg_re_data_in[]);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	Bluetoothへ_arg_data_outを送信する。UART1を使う。
 *	送信完了するまで続きます。プログラムが停止したら疑ってみてね。
 *
 * \param _arg_data_out : 送信するdata
 */
inline void F_Out_bt_tx_2 (const char _arg_data_out[]);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	Bluetoothから受信する。UART1を使います。
 *	受信したdataは_arg_re_data_inに格納される。
 *	受信完了するまで続きます。プログラムが停止したら疑ってみてね。 
 *
 * \param _arg_re_data_in	: 受信したdataを格納する所
 */
inline void F_In_bt_tx_2 (char _arg_re_data_in[]);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	受信したデータが_arg_data_compに一致するまで受信し続ける。UART1。
 *	仕様上、合わなかったら無限ループ状態になるので気を付けてね。 
 *
 * \param _arg_data_comp	: 比較対象
 */
inline void F_In_comp_bt_tx_2 (const char _arg_data_comp[]);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	受信したデータが_arg_data_compに一致するまで受信し続ける。UART1
 *	受信したデータは_arg_re_data_inに格納される。
 *	仕様上、合わなかったら無限ループ状態になるので気を付けてね。 
 *
 * \param _arg_re_data_in	: 受信したデータを格納する場所
 * \param _arg_data_comp	: 比較対象
 */
inline void F_In_comp_bt_tx_2 (char _arg_re_data_in[], const char _arg_data_comp[]);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	SlaveのBluetoothと接続する。Bluetoothの緑のLEDが光ったら完了。 
 *
 * \param _arg_slave_num : Slaveの番号
 */
void F_Conect_bt_tx_2 (const E_BT_NUM _arg_slave_num);

/************************************************************************/

#include "Func_bt_tx.cpp"