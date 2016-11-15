
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
//��Ԃ��g���ꍇ��__ODD__�A�����Ԃ̏ꍇ��__EVEN__�ɂ��Ă��������B

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
 *	IO���W�X�^�̐ݒ���s��
 */
void F_Set_io_bt_tx_2 ();

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	Bluetooth�Ɏg�p����UART��ݒ肷��BUART1�B
 *
 * \param _arg_nf_isr : ���荞�ݏ�����ON/OFF
 */
void F_Set_uart_bt_tx_2 (BOOL _arg_nf_isr);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	Slave�̔ԍ���DIP�X�C�b�`����ǂݎ��B
 *	���������ꍇ�ATRUE�A���s�����ꍇFALSE��return����
 * 
 * \return BOOL �ǂݎ��̐��ۂ̒ʒm
 */
BOOL F_In_bt_num_bt_tx_2(E_BT_NUM &_arg_re_bt_slave_num);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	�R���g���[������̃f�[�^���󂯎��ABluetooth�ő��M����`�֕ϊ�����B
 *	�ϊ��́A�f�[�^��16�i���ŕ\�������̂𕶎���ɂ������̂ɂ���B 
 *
 * \param _arg_re_data_in : ��M�����f�[�^�B�ϊ��ς݁B���̂܂ܑ��M���ĂˁB
 */
void F_In_controler_bt_tx_2 (C_UART_R &_arg_uart_r, char _arg_re_data_in[]);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	Bluetooth��_arg_data_out�𑗐M����BUART1���g���B
 *	���M��������܂ő����܂��B�v���O��������~������^���Ă݂ĂˁB
 *
 * \param _arg_data_out : ���M����data
 */
inline void F_Out_bt_tx_2 (const char _arg_data_out[]);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	Bluetooth�����M����BUART1���g���܂��B
 *	��M����data��_arg_re_data_in�Ɋi�[�����B
 *	��M��������܂ő����܂��B�v���O��������~������^���Ă݂ĂˁB 
 *
 * \param _arg_re_data_in	: ��M����data���i�[���鏊
 */
inline void F_In_bt_tx_2 (char _arg_re_data_in[]);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	��M�����f�[�^��_arg_data_comp�Ɉ�v����܂Ŏ�M��������BUART1�B
 *	�d�l��A����Ȃ������疳�����[�v��ԂɂȂ�̂ŋC��t���ĂˁB 
 *
 * \param _arg_data_comp	: ��r�Ώ�
 */
inline void F_In_comp_bt_tx_2 (const char _arg_data_comp[]);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	��M�����f�[�^��_arg_data_comp�Ɉ�v����܂Ŏ�M��������BUART1
 *	��M�����f�[�^��_arg_re_data_in�Ɋi�[�����B
 *	�d�l��A����Ȃ������疳�����[�v��ԂɂȂ�̂ŋC��t���ĂˁB 
 *
 * \param _arg_re_data_in	: ��M�����f�[�^���i�[����ꏊ
 * \param _arg_data_comp	: ��r�Ώ�
 */
inline void F_In_comp_bt_tx_2 (char _arg_re_data_in[], const char _arg_data_comp[]);

/** Made 2016 / 11 / 06 (Sun)
 * \brief 
 *	Slave��Bluetooth�Ɛڑ�����BBluetooth�̗΂�LED���������犮���B 
 *
 * \param _arg_slave_num : Slave�̔ԍ�
 */
void F_Conect_bt_tx_2 (const E_BT_NUM _arg_slave_num);

/************************************************************************/

#include "Func_bt_tx.cpp"