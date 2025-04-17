#include "cpu.h"

#include <avr/wdt.h>
#include <avr/interrupt.h>

void cpu_software_reset(void)
{
    cli();

    wdt_reset();

    MCUSR &= ~(1 << WDRF);
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = 0x00;

    wdt_enable(WDTO_15MS);

    for (;;);
}

void cpu_watchdog_timer_reset(void) {
    //
}
