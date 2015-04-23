/******************** INTERRUPTS *************
interrupts(0)   disable interrupts
interrupts(1)   re-enable interrupts

return 1 = OK
       0 = error with message print

Uses intrupt pointer set by setup()
Does not disable FIQ which seems to
cause a system crash
Avoid calling immediately after keyboard input
or key strokes will not be dealt with properly

*******************************************/

int interrupts(int flag)
  {
  static unsigned int sav132 = 0;
  static unsigned int sav133 = 0;
  static unsigned int sav134 = 0;

  if(flag == 0)    // disable
    {
    if(sav132 != 0)
      {
      // Interrupts already disabled so avoid printf
      return(0);
      }

    if( (*(intrupt+128) | *(intrupt+129) | *(intrupt+130)) != 0)
      {
      printf("Pending interrupts\n");  // may be OK but probably
      return(0);                       // better to wait for the
      }                                // pending interrupts to
                                       // clear

    sav134 = *(intrupt+134);
    *(intrupt+137) = sav134;
    sav132 = *(intrupt+132);  // save current interrupts
    *(intrupt+135) = sav132;  // disable active interrupts
    sav133 = *(intrupt+133);
    *(intrupt+136) = sav133;
    }
  else            // flag = 1 enable
    {
    if(sav132 == 0)
      {
      printf("Interrupts not disabled\n");
      return(0);
      }

    *(intrupt+132) = sav132;    // restore saved interrupts
    *(intrupt+133) = sav133;
    *(intrupt+134) = sav134;
    sav132 = 0;                 // indicates interrupts enabled
    }
  return(1);
  }

/***************** SETUP ****************
Sets up five GPIO pins as described in comments
Sets timer and interrupt pointers for future use
Does not disable interrupts
return 1 = OK
       0 = error with message print
************************************/

int setup()
  {
  int memfd;
  unsigned int timend;
  void *gpio_map,*timer_map,*int_map;

  memfd = open("/dev/mem",O_RDWR|O_SYNC);
  if(memfd < 0)
    {
    printf("Mem open error\n");
    return(0);
    }

  gpio_map = mmap(NULL,4096,PROT_READ|PROT_WRITE,
                  MAP_SHARED,memfd,GPIO_BASE);

  timer_map = mmap(NULL,4096,PROT_READ|PROT_WRITE,
                  MAP_SHARED,memfd,TIMER_BASE);

  int_map = mmap(NULL,4096,PROT_READ|PROT_WRITE,
                  MAP_SHARED,memfd,INT_BASE);

  close(memfd);

  if(gpio_map == MAP_FAILED ||
     timer_map == MAP_FAILED ||
     int_map == MAP_FAILED)
    {
    printf("Map failed\n");
    return(0);
    }
              // interrupt pointer
  intrupt = (volatile unsigned *)int_map;
              // timer pointer
  timer = (volatile unsigned *)timer_map;
  ++timer;    // timer lo 4 bytes
              // timer hi 4 bytes available via *(timer+1)

              // GPIO pointers
  gpio = (volatile unsigned *)gpio_map;
  gpset = gpio + 7;     // set bit register offset 28
  gpclr = gpio + 10;    // clr bit register
  gpin = gpio + 13;     // read all bits register

      // setup  GPIO 2/3 = inputs    have pull ups on board
      //        control reg = gpio + 0 = pin/10
      //        GPIO 2 shift 3 bits by 6 = (pin rem 10) * 3
      //        GPIO 3 shift 3 bits by 9 = (pin rem 10) * 3

  *gpio &= ~(7 << 6);   // GPIO 2  3 bits = 000 input
  *gpio &= ~(7 << 9);   // GPIO 3  3 bits = 000 input

     // setup GPIO 18 = input
  *(gpio+1) &= ~(7 << 24);  // GPIO 18 input
     // enable pull up on GPIO 18
  *(gpio+37) = 2;           // PUD = 2  pull up
                            //     = 0  disable pull up/down
                            //     = 1  pull down
  timend = *timer+2;        // 2us delay
  while( (((*timer)-timend) & 0x80000000) != 0);
  *(gpio+38) = (1 << 18);   // PUDCLK bit set clocks PUD=2 to GPIO 18
  timend = *timer+2;        // 2us delay
  while( (((*timer)-timend) & 0x80000000) != 0);
  *(gpio+37) = 0;           // zero PUD
  *(gpio+38) = 0;           // zero PUDCLK
                            // finished pull up enable

     //      GPIO 14/15 = outputs
     //      control reg = gpio + 1 = pin/10
     //      GPIO 14 shift 3 bits by 12 = (pin rem 10) * 3
     //      GPIO 15 shift 3 bits by 15 = (pin rem 10) * 3

  *(gpio+1) &= ~(7 << 12);  // GPIO 14 zero 3 bits
  *(gpio+1) |= (1 << 12);   // 3 bits = 001 output

  *(gpio+1) &= ~(7 << 15);  // GPIO 15 zero 3 bits
  *(gpio+1) |= (1 << 15);   // 3 bits = 001 output

  return(1);
  }

/**************** PULL UPS *********

pull up register  PUD = gpio+37
clock register PUDCLK = gpio+38

1. set PUD =  0 disable pull up/down
              1 enable pull down
              2 enable pull up
              3 reserved
   *(gpio+37) = 2  to pull up

2. wait 150 cycles

3. set bit of GPIO pin in PUDCLK
   so for GPIO 3    *(gpio+38) = 8
   to clock PUD into GPIO 3 only

4. wait 150 cycles

5. write 0 to PUD

6. write 0 to PUDCLK

************ END ************************/
