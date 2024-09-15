#include <msp430.h>
#include <driverlib.h>
#include "hal_gpio.h"
#include "hal_utils.h"

int main(void)
{
    WDT_A_hold(WDT_A_BASE);
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode

    while(1) {
        hal_gpio_unit_test();
    }
}
