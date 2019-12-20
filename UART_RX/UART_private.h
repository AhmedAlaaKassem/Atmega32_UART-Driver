/*
 * UART_private.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Eng Mohamed Hamdy
 */

#ifndef __UART_PRIVATE_H__
#define __UART_PRIVATE_H__


#define UBRRH		*((volatile uint8_t*) 0x40U)
#define UCSRC 		*((volatile uint8_t*) 0x40U)
#define UDR 		*((volatile uint8_t*) 0x2CU)
#define UCSRA 		*((volatile uint8_t*) 0x2BU)
#define	UCSRB		*((volatile uint8_t*) 0x2AU)
#define UBRRL		*((volatile uint8_t*) 0x29U)


#endif /* __UART_PRIVATE_H__ */
