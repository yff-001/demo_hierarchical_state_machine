#include "cpu.h"

#define MCU_RESET() do { \
                        wdt_enable(WDTO_15MS); \
                        while (1) {} \
                        } whil (0)