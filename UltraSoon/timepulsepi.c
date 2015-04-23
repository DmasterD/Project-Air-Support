void timepulse(void) {

unsigned int timend;

setup()                  // initialise system
                         // call only once

interrupts(0);           // disable interrupts

timend = *timer + 20;    // Set up 20 microsecond delay
                         // Maximum possible delay
                         // is 7FFFFFF or about 35*60/10 = 3 minutes

while((((*timer)-timend) & 0x80000000) != 0);  // delay loop

                     // This works even if *timer
                     // overflows to zero during the delay,
                     // or if the while test misses the exact
                     // termination when (*timer-timend) == 0.
                     // Jitter in delay about 1 microsecond.
                     // Can be reduced to about 0.1 microsecond
                     // by synchronising the timend set
                     // instruction to a change in *timer
                     // if interrupts are not disabled
                     // the delay can occasionally be
                     // 2ms (or more) longer than requested
                     // and is routinely out by up to 0.1ms

interrupts(1);       // re-enable interrupts

}
