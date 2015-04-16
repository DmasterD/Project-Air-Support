#define 32MHZ 		1 		//Enable 32MHZ clock speed
#define BUFFERLEN 	16 		//Uart Bufferlength
#define DECIMAL 	10		//Decimal numbers

void Config32MHzClock(void)
{
	if( 32MHZ == 1) {
	CCP		=	CCP_IOREG_gc;
	OSC.CTRL       |=	OSC_RC32MEN_bm;
	while (!(OSC.STATUS & OSC_RC32MRDY_bm)) ;
	CCP		=	CCP_IOREG_gc;
	CLK.CTRL	=	CLK_SCLKSEL_RC32M_gc;
	};
};

void InitUart(void)
{
	init_uart(&uartE0, &USARTE0, F_CPU, E0_BAUD, E0_CLK2X);
	PMIC.CTRL = PMIC_LOLVLEN_bm;
	sei();
};

void InitInterupt1(void)
{
	PORTB.INT0MASK	=	PIN0_bm;
	PORTB.PIN0CTRL	=	PORT_ISC_RISING_gc;
	PORTB.INTCTRL	=	PORT_INT0LVL_LO_gc;
	PMIC.CTR       |=	PMIC_LOLVLEN_bm;
	sei();
};

void InitInterupt2(void)
{
	PORTB.INT1MASK	=	PIN1_bm;
	PORTB.PIN1CTRL	=	PORT_ISC_FALLING_gc;
	PORTB.INTCTRL	=	PORT_INT1LVL_MED_gc;
	PMIC.CTRL      |=	PMIC_MEDLVLEN_bm;
	sei();
};

void InitTimer(void)
{
	TCC0.CTRLD			=	TC_EVACT_CAPT_gc|	// Event capture
					TC_EVSEL_CH0_gc;		// For Channel 0
	TCC0.CTRLB			=	TC0_CCAEN_bm;		// Enable Inp. Capt. Ch. A
	TCC0.CTRLA			=	TC_CLKSEL_DIV8_gc;	// Prescaling 8
	TCC0.PER			=	0XFFFF;			// Maximal value
	TCC0.CTRLFSET			=	TC_CMD_RESTART_gc;	// start TImer
};

ISR(PORTB_INT0_vect)
{
	TCC0.CTRLFSET	=	TC_CMD_RESTART_gc;
};

ISR(PORTB_INT1_vect)
{
	measure		=	1;
	PORTE_OUTTGL	=	PIN0_bm;
	echo		=	TCC0.CCA;
};

void emptybuffer(void)
{
	for (int i = 0; i < BUFFERLEN; i++)
	{
		buffer[i] = 0;
	}
};

void SendDistance(void)
{
	emptybuffer();
	itoa(echo, buffer, DECIMAL);
	uart_puts(&uartE0, "Distance: ");
	
	for (int i = 0; i < BUFFERLEN; i++)
	{
		itoa(echo, buffer, DECIMAL);
		char a = buffer[i];
		uart_putc(&uartE0, a);
	};
	
	uart_puts(&uartE0, "\n\r");
};

void UltrasoonMeasure(void)
{
	PORTE_OUTTGL = PIN0_bm;
	uart_puts(&uartE0, "Reading Ultrasoon\n\r");
	PORTB.OUTSET = PIN2_bm;
	_delay_us(20);
	PORTB.OUTCLR = PIN2_bm;
};

void testmode(void)
{
	uart_puts(&uartE0, "Test mode activated!\n\r");
	uart_puts(&uartE0, "Test integer: ");
	for (int i = 0; i < BUFFERLEN; i++)
	{
		emptybuffer();
		itoa(test, buffer, DECIMAL);
		char a = buffer[i];
		uart_putc(&uartE0, a);
	};
	uart_puts(&uartE0, "\n\r");
};
