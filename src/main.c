#include <msp430.h>
#include <driverlib.h>


#define  DELAY_CYCLES  1045000

// int main(void) {
//     WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
//     PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
//                                             // to activate previously configured port settings
//     P1DIR |= 0x01;                          // Set P1.0 to output direction


//     for(;;) {
//         volatile unsigned int i;            // volatile to prevent optimization
//         P1OUT ^= 0x01;                      // Toggle P1.0 using exclusive-OR

//     }
// }



/**
 * blink.c
 */
int main(void)
{
    WDT_A_hold(WDT_A_BASE);
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P9, GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_PIN7);

    volatile unsigned int i;        // volatile to prevent optimization

    while(1) {
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        __delay_cycles(DELAY_CYCLES);        // delay a while
        GPIO_toggleOutputOnPin(GPIO_PORT_P9, GPIO_PIN7);
    }

}
