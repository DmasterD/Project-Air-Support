//-------------------------------------------------------//
//	UltraSoon.c					 //
//	Testing Ultrasoon Sensor			 //
//	Created:	Donderdag 8 April 2015 10:03	 // 
//	Author:		Mike van Lieshout		 //
//	Company:	HoTechnology			 //
//	Project:	Air Support			 //
//-------------------------------------------------------//

#define F_CPU			32000000UL 

#include <avr/io.h>
#include <avr/interrupt.h>

#define ENABLE_UART_E0   1		//Uart Enable
#define E0_BAUD          912600		//32Mhz Supported
#define E0_CLK2X         0		//Dubble Clock Speed

#include <util/delay.h>
#include <avr/pgmspace.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int test = 18547;
int echo;
char time;
char buffer[16];
uint16_t c;
int measure = 0;

#include "uart.h"
#include "usart_driver.h"
#include "UltraSoon.h"

int main(void)
{
	PORTE_DIRSET	=	PIN0_bm;
	PORTE_OUTCLR	=	PIN0_bm;
	PORTB_DIRSET	=	PIN2_bm;
	PORTB_OUTCLR	=	PIN2_bm;
	
	Config32MHzClock();
	InitTimer();
	InitUart();
	InitInterupt1();
	InitInterupt2();
	
	uart_puts(&uartE0, "Welcome\n\r");
	uart_puts(&uartE0, "Type R for reading ultrasoon distance\n\r");
	
	while(1) {
		
		if(measure == 1) {	
			SendDistance();
			measure = 0;
		}
		
		if(c == 'r')
		{
			UltrasoonMeasure();
		}
		
		if(c == 't')
		{
			testmode();
		}
	}
}
