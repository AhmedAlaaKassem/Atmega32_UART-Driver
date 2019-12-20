/*
 * UART_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Eng Mohamed Hamdy
 */

#include "Data_Type.h"
#include "Macros.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "Interrupt.h"
#include <avr/interrupt.h>

/*
 *	Static variable store UART mode configuration "Polling or interrupt"
 */
static uint8_t u8_UART_InterruptMode = DUMMY ;
/*
 *	Static variable for UART TX/RX Interrupt Flags
 */
static uint8_t u8_UART_TX_Flag = NULL ;
static uint8_t u8_UART_RX_Flag = NULL ;
/*
 *	Static Buffer store UART TX/RX Data"
 */
static uint8_t u8_UART_Read_Buffer  = NULL ;
static uint8_t u8_UART_Wrire_Buffer = NULL ;

/***************************************************************************************/
/* brief!  UART initialization                                                         */
/* param!  void                                                                        */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t UART_Init(UART_cfg_s *pstr_UART_cfg)
{
	/*
	 *	Development Error Tracer
	 */

	error_t au8_DET = ERROR_OK ;
	if(NULL != pstr_UART_cfg)
	{
		/*
		*	Checking the desired Mode if it's polling or interrupt
		*/
		if(INTERRUPT == pstr_UART_cfg -> u8_Interrupt_Mode)
		{
			Enable_GlobalInterrupt();

			SET_BIT(UCSRB, RXCIE); /* Enable RX Complete Interrupt */
			SET_BIT(UCSRB, TXCIE); /* Enable RT Complete Interrupt */
			SET_BIT(UCSRB, UDRIE); /* Enable Data Register Empty Interrupt */
			u8_UART_InterruptMode = INTERRUPT ;
		}
		else if(POLLING == pstr_UART_cfg -> u8_Interrupt_Mode)
		{
			CLEAR_BIT(UCSRB, RXCIE); /* Disable RX Complete Interrupt */
			CLEAR_BIT(UCSRB, TXCIE); /* Disable RT Complete Interrupt */
			CLEAR_BIT(UCSRB, UDRIE); /* Disable Data Register Empty Interrupt */
			u8_UART_InterruptMode = POLLING ;
		}
		else
		{
			/* Handling of entering wrong Mode */
			au8_DET = E_INTERRUPT_MODE ;
		}

		 /*
		  * selects between accessing the UCSRC or the UBRRH Register
		  */
		SET_BIT(UCSRC, URSEL);

		/* Handling synchronization Mode */
		if(ASYNCHRONOUS == pstr_UART_cfg -> u8_Sync)
		{
			/* "Asynchronous" USART Mode Select */
			CLEAR_BIT(UCSRC, UMSEL);
			if(BAUDRATE_9600 == pstr_UART_cfg -> u16_BaudRate)
			{
				//UCSRC=0b0....... Lw 3aez ast5dm UBRRH, menf3sh a3mlo b CLEAR_BIT 3san htd5ol t2ra al awl w b3den t3ml clear f htla2y fi al bit '1'
				UBRRL = BAUDRATE_9600;//Baud Rate 9600
			}
			else
			{
				/* Handling of entering wrong BaudRate */
				au8_DET = E_BAUDRATE ;
			}

		}
		else if(SYNCHRONOUS == pstr_UART_cfg -> u8_Sync)
		{
			/* "Synchronous" USART Mode Select */
			SET_BIT(UCSRC, UMSEL);
			/*
			 * TODO
			 */
		}
		else
		{
			/* Handling of entering wrong synchronization Mode */
			au8_DET = E_SYNC ;
		}

		/*
		 * Parity Mode
		 */
		if(Disabled_PARITY == pstr_UART_cfg -> u8_Parity)
		{
			CLEAR_BIT(UCSRC, UPM1);
			CLEAR_BIT(UCSRC, UPM0);
		}
		else if(Disabled_PARITY == pstr_UART_cfg -> u8_Parity)
		{
			CLEAR_BIT(UCSRC, UPM1);
			SET_BIT(UCSRC, UPM0);
		}
		else if(Disabled_PARITY == pstr_UART_cfg -> u8_Parity)
		{
			SET_BIT(UCSRC, UPM1);
			SET_BIT(UCSRC, UPM0);
		}
		else
		{
			/* Handling of entering wrong Parity */
			au8_DET = E_PARITY ;
		}

		/*
		 *  Stop Bit Select
		 */
		if(STOP_1B == pstr_UART_cfg -> u8_StopSize)
		{
			CLEAR_BIT(UCSRC, USBS); /* One Stop Bit */
		}
		else if((STOP_2B == pstr_UART_cfg -> u8_StopSize))
		{
			SET_BIT(UCSRC, USBS); /* Two Stop Bit */
		}
		else
		{
			/* Handling of entering wrong Stop size */
			au8_DET = E_STOP_SIZE ;
		}

		if(CHAR_5B == pstr_UART_cfg -> u8_CharSize)
		{
			/* Character Size */
			SET_MASK(UCSRC, CHAR_5B);
			CLEAR_BIT(UCSRB, UCSZ2);
		}
		else if(CHAR_6B == pstr_UART_cfg -> u8_CharSize)
		{
			/* Character Size */
			SET_MASK(UCSRC, CHAR_6B);
			CLEAR_BIT(UCSRB, UCSZ2);
		}
		else if(CHAR_7B == pstr_UART_cfg -> u8_CharSize)
		{
			/* Character Size */
			SET_MASK(UCSRC, CHAR_7B);
			CLEAR_BIT(UCSRB, UCSZ2);
		}
		else if(CHAR_8B == pstr_UART_cfg -> u8_CharSize)
		{
			/* Character Size */
			SET_MASK(UCSRC, CHAR_8B);
			CLEAR_BIT(UCSRB, UCSZ2);
		}
		else if(CHAR_9B == pstr_UART_cfg -> u8_CharSize)
		{
			/* Character Size */
			SET_MASK(UCSRC, CHAR_8B);
			SET_BIT(UCSRB, UCSZ2);
		}
		else
		{
			/* Handling of entering wrong Char size */
			au8_DET = E_CHAR_SIZE ;
		}
		SET_BIT(UCSRB, RXEN); /* RX enable */
		SET_BIT(UCSRB, TXEN); /* TX enable */
	}
	else
	{
		/* Handling of entering null pointer*/
		au8_DET = E_PTR_IS_NULL ;
	}
	return au8_DET;
}

/***************************************************************************************/
/* brief!  UART Send Data                                                              */
/* param!  (I/P) Data                                                                  */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t UART_Start_SendByte(uint8_t au8_TXbyatCpy)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_DET = ERROR_OK ;
	if(POLLING == u8_UART_InterruptMode)
	{
		while(GET_BIT(UCSRA, UDRE) == NULL);
		UDR = au8_TXbyatCpy;
	}
	else if(INTERRUPT == u8_UART_InterruptMode)
	{
		if(FLAG_IS_SET == u8_UART_TX_Flag)
		{
			Disable_GlobalInterrupt();

			u8_UART_Wrire_Buffer = au8_TXbyatCpy;
			u8_UART_TX_Flag = FLAG_IS_CLEAR;

			Enable_GlobalInterrupt();
		}
	}
	else
	{
		/* Handling of entering wrong Mode */
		au8_DET = E_INTERRUPT_MODE ;
	}

	return au8_DET;
}

/***************************************************************************************/
/* brief!  UART Recive Data                                                            */
/* param!  (O/P) pointer to data                                                       */
/* return! u8 Indication of the execution if it fails or not                           */
/***************************************************************************************/
error_t UART_Start_RecieveByte(uint8_t * au8_RXbyatCpy)
{
	/*
	 *	Development Error Tracer
	 */
	error_t au8_DET = ERROR_OK ;
	if(NULL != au8_RXbyatCpy)
	{
		if(POLLING == u8_UART_InterruptMode)
		{
			while(GET_BIT(UCSRA, RXC) == NULL);
			*au8_RXbyatCpy = UDR;
		}
		else if(INTERRUPT == u8_UART_InterruptMode)
		{
			if(FLAG_IS_SET == u8_UART_RX_Flag)
			{
				Disable_GlobalInterrupt();

				*au8_RXbyatCpy = u8_UART_Read_Buffer;
				u8_UART_RX_Flag = FLAG_IS_CLEAR;

				Enable_GlobalInterrupt();

			}
		}
		else
		{
			/* Handling of entering wrong Mode */
			au8_DET = E_INTERRUPT_MODE ;
		}

	}
	else
	{
		/* Handling of entering null pointer*/
		au8_DET = E_PTR_IS_NULL ;
	}

	return au8_DET;

}

/*
ISR(USART_RXC_vect)
{

	u8_UART_RX_Flag = FLAG_IS_SET;
	u8_UART_Read_Buffer = UDR ;

}
*/
ISR(USART_UDRE_vect)
{

	u8_UART_TX_Flag = FLAG_IS_SET;
	UDR = u8_UART_Wrire_Buffer;

}

