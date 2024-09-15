#include <msp430.h>
#include "driverlib.h"
#include "hal_utils.h"
#include "hal_err.h"

#define  DELAY_CYCLES_FOR_1US  1
#define  DELAY_CYCLES_FOR_1MS  1045
// Delay for a specified number of microseconds using DWT
void hal_delay_us(size_t us)
{
    size_t i = 0;
    for (i = 0; i < us; i ++) {
        __delay_cycles(DELAY_CYCLES_FOR_1US);
    }
}

// Delay for a specified number of milliseconds (uses HAL_Delay)
void hal_delay_ms(size_t ms)
{
    size_t i = 0;
    for (i = 0; i < ms; i ++) {
        __delay_cycles(DELAY_CYCLES_FOR_1MS);
    }
}

// Sleep for a specified number of microseconds (approximate, uses busy wait)
void hal_sleep_us(size_t us)
{
    hal_delay_us(us);  // Approximate microsecond sleep using delay
}

// Sleep for a specified number of milliseconds
void hal_sleep_ms(size_t ms)
{
    hal_delay_ms(ms);  // Add delay after wakeup
}