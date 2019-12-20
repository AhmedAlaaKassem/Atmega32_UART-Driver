/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Eng Mohamed Hamdy
 */

#include "Data_Type.h"
#include "Macros.h"
#include "DIO_interface.h"
#include "UART_interface.h"
#include <util/delay.h>


int main(void)
{
	UART_cfg_s Cfg;
	Cfg.u16_BaudRate = BAUDRATE_9600;
	Cfg.u8_CharSize  = CHAR_8B;
	Cfg.u8_Interrupt_Mode = POLLING;
	//Cfg.u8_Interrupt_Mode = INTERRUPT;
	Cfg.u8_Parity = Disabled_PARITY;
	Cfg.u8_SpeedMode = NORMAL_SPEED;
	Cfg.u8_StopSize = STOP_1B;
	Cfg.u8_Sync = ASYNCHRONOUS;


	UART_Init(&Cfg);

	DIO_INIT_Pin(DIO_PB4, OUTPUT_PIN);

	DIO_Write_Pin(DIO_PB4, LOW_PIN);


	uint8_t Data;

	while (1)
	{

		UART_Start_RecieveByte(&Data);
		 _delay_ms(1000);

		 if(Data == 0X11)
		 {
			 DIO_Write_Pin(DIO_PB4, HIGH_PIN);
			 _delay_ms(1000);
			 DIO_Write_Pin(DIO_PB4, LOW_PIN);
		 }
		 else
		 {
			 DIO_Write_Pin(DIO_PA5, LOW_PIN);
		 }

	}

return 0;
}
