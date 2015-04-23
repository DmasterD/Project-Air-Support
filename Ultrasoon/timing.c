/********** ACCURATE TIMER for REAL TIME CONTROL ***

This C program illustrates accurate timing on a
Raspberry Pi by sending a 50kHz signal to a GPIO pin
with a jitter of about 0.1 microseconds. It uses the
processor's 1MHz timer and disables interrupts.
It includes GPIO setup and read/write code.

Compiled from console with gcc under the standard
Debian distribution.
Tested with a keyboard and HDMI monitor attached,
and X Windows not started.

**************************************************/


/*********** TIMER CODE example *******

unsigned int timend;

setup()                  // initialise system
                         // call only once

interrupts(0);           // disable interrupts

timend = *timer + 200;   // Set up 200 microsecond delay
                         // Maximum possible delay
                         // is 7FFFFFF or about 35 minutes

while((((*timer)-timend) & 0x80000000) != 0);  // delay loop

                     // This works even if *timer
                     // overflows to zero during the delay,
                     // or if the while test misses the exact
                     // termination when (*timer-timend) == 0.
                     // Jitter in delay about 1 microsceond.
                     // Can be reduced to about 0.1 microsecond
                     // by synchronising the timend set
                     // instruction to a change in *timer

                     // if interrupts are not disabled
                     // the delay can occasionally be
                     // 2ms (or more) longer than requested
                     // and is routinely out by up to 0.1ms

interrupts(1);       // re-enable interrupts

*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

#define GPIO_BASE  0x20200000
#define TIMER_BASE 0x20003000
#define INT_BASE 0x2000B000

volatile unsigned *gpio,*gpset,*gpclr,*gpin,*timer,*intrupt;

/******************** GPIO read/write *******************/
  // outputs  CLK = GPIO 15 = connector pin 10
  //          DAT = GPIO 14 = connector pin 8
  // code example
  //    CLKHI;
#define CLKHI *gpset = (1 << 15)  // GPIO 15
#define CLKLO *gpclr = (1 << 15)
#define DATHI *gpset = (1 << 14)  // GPIO 14
#define DATLO *gpclr = (1 << 14)
  // inputs   P3  = GPIO 3 = connector pin 5 (Rev 2 board)
  //          P2  = GPIO 2 = connector pin 3 (Rev 2 board)
  //          ESC = GPIO 18 = connector pin 12
  // code examples
  //   if(P2IN == 0)
  //   if(P2IN != 0)
  //   n = P2INBIT;  //  0 or 1
#define ESCIN (*gpin & (1 << 18))   // GPIO 18
#define P2IN (*gpin & (1 << 2))    // GPIO 2
#define P3IN (*gpin & (1 << 3)     // GPIO 3
#define P2INBIT ((*gpin >> 2) & 1)  // GPIO 2
#define P3INBIT ((*gpin >> 3) & 1)  // GPIO 3
/******************* END GPIO ****************/

int setup(void);
int interrupts(int flag);

main()
  {
  int n,getout;
  unsigned int timend;

  sleep(1);    // 1 second delay
               // When the program starts, the interrupt
               // system may still be dealing with the
               // last Enter keystroke. This gives it
               // time to finish.

  setup();     // setup GPIO, timer and interrupt pointers

  interrupts(0);    // Disable interrupts to ensure
                    // accurate timing.
                    // Re-enable via interrupts(1) as
                    // soon as accurate timing is no
                    // longer needed.

        // screen output, keyboard input (and who
        // knows what else) stop working until
        // interrupts are re-enabled

  // 50kHz signal to CLK output = GPIO 15 connector pin 10
  // 1000000 cycles = 20 seconds
  // checks ESC input pin = GPIO 18 connector pin 12
  // if lo - loop terminates

  getout = 0;
  timend = *timer + 10;   // set up 10us delay from
                          // current timer value
  for(n = 0 ;  n < 1000000 && getout == 0 ; ++n)
    {
                          //  delay to timend
    while( (((*timer)-timend) & 0x80000000) != 0);

    CLKHI;           // output GPIO 15 hi

                     // check input GPIO 18 pin
                     // which is pulled hi by setup()
                     // exit loop if lo
    if(ESCIN == 0)
      getout = 1;
                         // 10us delay
    timend += 10;
    while( (((*timer)-timend) & 0x80000000) != 0);

    CLKLO;               // output GPIO 15 lo

    timend += 10;        // 10us delay at start of next loop
    }

  interrupts(1);         // re-enable interrupts

  return;
  }
