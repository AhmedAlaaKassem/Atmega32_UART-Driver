/*
 * UART_interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Eng Mohamed Hamdy
 */

#ifndef __UART_INTERFACE_H__
#define __UART_INTERFACE_H__

/*
*	Error macros
*/
#define ERROR_OK 			0U
#define E_SYNC 				1U  /* channel error */
#define E_BAUDRATE	 		2U  /* prescaler error  */
#define E_CHAR_SIZE 		3U  /* prescaler error  */
#define E_INTERRUPT_MODE  	4U  /* Interrupt or Polling mode error   */
#define E_PTR_IS_NULL 		5U	/* NULL pointer error when using it */
#define E_PARITY 			6U  /* Timer or counter mode error  */
#define E_STOP_SIZE	 		7U	/* Ticks error "number of Ticks more than the max allowed" */
#define E_SPEEDMODE 		8U	/* NULL pointer error when using it */


/*
 * Speed Mode
 */
#define NORMAL_SPEED    	0U
#define DOUBLE_SPEED    	1U

/*
 * Normal Speed BAUDRATE
 */
#define BAUDRATE_2400    	207U
#define BAUDRATE_2800    	103U
#define BAUDRATE_9600   	51U
#define BAUDRATE_14_4K   	34U
#define BAUDRATE_19_2K  	25U
#define BAUDRATE_28_8K  	16U
#define BAUDRATE_38_4k 		12U
#define BAUDRATE_57_6K    	8U
#define BAUDRATE_67_8K    	6U
#define BAUDRATE_115_2k   	3U
#define BAUDRATE_230_4K   	1U
#define BAUDRATE_250K  		1U
#define BAUDRATE_0_5m  		0U

/*
 * Double Speed BAUDRATE
 */
#define DOUBLE_BAUDRATE_2400    	416UL
#define DOUBLE_BAUDRATE_2800    	207U
#define DOUBLE_BAUDRATE_9600   		103U
#define DOUBLE_BAUDRATE_14_4K   	68U
#define DOUBLE_BAUDRATE_19_2K  		51U
#define DOUBLE_BAUDRATE_28_8K  		34U
#define DOUBLE_BAUDRATE_38_4k 		25U
#define DOUBLE_BAUDRATE_57_6K    	16U
#define DOUBLE_BAUDRATE_67_8K    	12U
#define DOUBLE_BAUDRATE_115_2k   	8U
#define DOUBLE_BAUDRATE_230_4K   	3U
#define DOUBLE_BAUDRATE_250K  		3U
#define DOUBLE_BAUDRATE_0_5m  		1U

/* synchronization Mode */
#define ASYNCHRONOUS   		0U
#define SYNCHRONOUS   		1U

/* Parity Mode */
#define Disabled_PARITY   	0U
#define EVEN_PARITY   		2U
#define ODD_PARITY

/* Stop Bit Select */
#define STOP_1B   	0U
#define STOP_2B   	1U

/* Character Size */
#define CHAR_5B   0U
#define CHAR_6B   2U
#define CHAR_7B   4U
#define CHAR_8B   6U
#define CHAR_9B   7U

/* UCSRC */
#define URSEL   7U
#define UMSEL   6U
#define UPM1    5U
#define UPM0    4U
#define USBS    3U
#define UCSZ1   2U
#define UCSZ0   1U
#define UCPOL   0U

/* UCSRA */
#define RXC     7U
#define TXC     6U
#define UDRE    5U
#define FE      4U
#define DOR     3U
#define PE      2U
#define U2X     1U
#define MPCM    0U

/* UCSRB */
#define RXCIE   7U
#define TXCIE   6U
#define UDRIE   5U
#define RXEN    4U
#define TXEN    3U
#define UCSZ2   2U
#define RXB8    1U
#define TXB8    0U

/*
* 	Timer Mode
*/
#define INTERRUPT 	0U
#define POLLING 	1U

/*
 * Mode TX/RX
 */
#define TRANSMIT    TXEN
#define RECIVE   	RXEN
#define TRANSFER   	24U



/*
 *	Definition of the timer configuration structure
 */
typedef struct{
	uint8_t u8_Interrupt_Mode;  /* Interrupt or Polling   */
	uint8_t u8_Sync ;          	/* Clouck or baud rate  */
	uint16_t u16_BaudRate ;     /* The desired prescaler  */
	uint8_t u8_CharSize ;   	/* Timer or counter mode  */
	uint8_t u8_Parity ;      	/* Timer 0, 1 or 2        */
	uint8_t u8_StopSize ;      	 	/* Timer 0, 1 or 2        */
	uint8_t u8_SpeedMode ;      /* Timer 0, 1 or 2        */
	}UART_cfg_s;

/***************************************************************************************/
/* brief!  UART initialization                                                         */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t UART_Init(UART_cfg_s *pstr_UART_cfg);

/***************************************************************************************/
/* brief!  UART Send Data                                                              */
/* param!  (I/P) Data                                                                  */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t UART_Start_SendByte(uint8_t au8_TXbyatCpy);

/***************************************************************************************/
/* brief!  UART Recive Data                                                            */
/* param!  (O/P) pointer to data                                                       */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
extern error_t UART_Start_RecieveByte(uint8_t * au8_RXbyatCpy);


#endif /* __UART_INTERFACE_H__ */
