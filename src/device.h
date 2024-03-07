#ifndef DEVICE_H
#define DEVICE_H

/* ATMega 328P specific configurations */

#define MCU_RESET() do { \
                        wdt_enable(WDTO_15MS); \
                        while (1) {} \
                        } whil (0)

#endif
