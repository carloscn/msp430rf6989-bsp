#include "hal_err.h"
#include "hal_gpio.h"
#include "hal_utils.h"
#include "hal_config.h"
#include "gpio.h"
#include <stdio.h>

static int32_t msp430fr69cc_gpio_p1_0_init_map_to_gpio_0(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    return HAL_SUCCESS;
}

static void msp430fr69cc_gpio_p1_0_deinit_map_to_gpio_0(void)
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN0);
}

static int32_t msp430fr69cc_gpio_p1_0_read_pin_map_to_gpio_0(HAL_GPIO_PIN_STATE *res)
{
    int32_t ret = HAL_SUCCESS;
    int32_t pin_state = 0;

    pin_state = GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN0);
    if (pin_state > GPIO_INPUT_PIN_HIGH) {
        ret = HAL_ERR_UNSUPPORTED;
        goto finish;
    }

    *res = pin_state == GPIO_INPUT_PIN_HIGH ? \
           HAL_GPIO_PIN_SET: \
           HAL_GPIO_PIN_RESET;
finish:
    return ret;
}

static void msp430fr69cc_gpio_p1_0_write_pin_map_to_gpio_0(HAL_GPIO_PIN_STATE value)
{
    if (HAL_GPIO_PIN_SET == value) {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        return;
    }
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

static void msp430fr69cc_gpio_p1_0_toggle_pin_map_to_gpio_0(void)
{
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

static int32_t msp430fr69cc_gpio_p1_0_lock_pin_map_to_gpio_0(void)
{
    return HAL_ERR_UNSUPPORTED;
}

static int32_t msp430fr69cc_gpio_p9_7_init_map_to_gpio_1(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_PIN7);

    return HAL_SUCCESS;
}

static void msp430fr69cc_gpio_p9_7_deinit_map_to_gpio_1(void)
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P9, GPIO_PIN7);
}

static int32_t msp430fr69cc_gpio_p9_7_read_pin_map_to_gpio_1(HAL_GPIO_PIN_STATE *res)
{
    int32_t ret = HAL_SUCCESS;
    int32_t pin_state = 0;

    pin_state = GPIO_getInputPinValue(GPIO_PORT_P9, GPIO_PIN7);
    if (pin_state > GPIO_INPUT_PIN_HIGH) {
        ret = HAL_ERR_UNSUPPORTED;
        goto finish;
    }

    *res = pin_state == GPIO_INPUT_PIN_HIGH ? \
           HAL_GPIO_PIN_SET: \
           HAL_GPIO_PIN_RESET;
finish:
    return ret;
}

static void msp430fr69cc_gpio_p9_7_write_pin_map_to_gpio_1(HAL_GPIO_PIN_STATE value)
{
    if (HAL_GPIO_PIN_SET == value) {
        GPIO_setOutputHighOnPin(GPIO_PORT_P9, GPIO_PIN7);
        return;
    }
    GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN7);
}

static void msp430fr69cc_gpio_p9_7_toggle_pin_map_to_gpio_1(void)
{
    GPIO_toggleOutputOnPin(GPIO_PORT_P9, GPIO_PIN7);
}

static int32_t msp430fr69cc_gpio_p9_7_lock_pin_map_to_gpio_1(void)
{
    return HAL_ERR_UNSUPPORTED;
}

// Initialize the specified GPIO pin according to the hal_gpio_init structure
int32_t hal_gpio_init(HAL_GPIO_CTX *gpio)
{
    int32_t ret = HAL_SUCCESS;

    if (NULL == gpio) {
        ret = HAL_ERR_NULL_POINTER;
        goto finish;
    }

    switch(gpio->hal_num) {
        case HAL_GPIO_0:
            ret = msp430fr69cc_gpio_p1_0_init_map_to_gpio_0();
            if (ret != HAL_SUCCESS) {
                goto finish;
            }
            break;
        case HAL_GPIO_1:
            ret = msp430fr69cc_gpio_p9_7_init_map_to_gpio_1();
            if (ret != HAL_SUCCESS) {
                goto finish;
            }
            break;
#if LOCK_CODE
        case HAL_GPIO_2:
        case HAL_GPIO_3:
        case HAL_GPIO_4:
#endif /* LOCK_CODE */
        default:
            ret = HAL_ERR_HW_LACK;
            goto finish;
    }

finish:
    return ret;
}

// Deinitialize the specified GPIO pin
void hal_gpio_deinit(HAL_GPIO_CTX *gpio)
{
    if (NULL == gpio) {
        return;
    }
    switch(gpio->hal_num) {
        case HAL_GPIO_0:
            msp430fr69cc_gpio_p1_0_deinit_map_to_gpio_0();
            return;
        case HAL_GPIO_1:
            msp430fr69cc_gpio_p9_7_deinit_map_to_gpio_1();
            return;
#if LOCK_CODE
        case HAL_GPIO_2:
        case HAL_GPIO_3:
        case HAL_GPIO_4:
#endif /* LOCK_CODE */
        default:
            return;
    }
}

// Read the input pin state
int32_t hal_gpio_read_pin(HAL_GPIO_CTX *gpio, HAL_GPIO_PIN_STATE *res)
{
    int32_t ret = HAL_SUCCESS;

    if ((NULL == gpio) ||
        (NULL == res)) {
        ret = HAL_ERR_NULL_POINTER;
        goto finish;
    }

    switch(gpio->hal_num) {
        case HAL_GPIO_0:
            ret = msp430fr69cc_gpio_p1_0_read_pin_map_to_gpio_0(res);
            if (ret != HAL_SUCCESS) {
                goto finish;
            }
            break;
        case HAL_GPIO_1:
            ret = msp430fr69cc_gpio_p9_7_read_pin_map_to_gpio_1(res);
            if (ret != HAL_SUCCESS) {
                goto finish;
            }
            break;
#if LOCK_CODE
        case HAL_GPIO_2:
        case HAL_GPIO_3:
        case HAL_GPIO_4:
#endif /* LOCK_CODE */
        default:
            ret = HAL_ERR_HW_LACK;
            goto finish;
    }

finish:
    return ret;
}

// Write to the specified output pin
int32_t hal_gpio_write_pin(HAL_GPIO_CTX *gpio, HAL_GPIO_PIN_STATE state)
{
    int32_t ret = HAL_SUCCESS;

    // Null pointer check
    if (NULL == gpio) {
        ret = HAL_ERR_NULL_POINTER;
        goto finish;
    }
    // Check if the state is valid
    if ((state != HAL_GPIO_PIN_SET) && (state != HAL_GPIO_PIN_RESET)) {
        ret = HAL_ERR_UNSUPPORTED;
        goto finish;
    }

    switch(gpio->hal_num) {
        case HAL_GPIO_0:
            msp430fr69cc_gpio_p1_0_write_pin_map_to_gpio_0(state);
            break;
        case HAL_GPIO_1:
            msp430fr69cc_gpio_p9_7_write_pin_map_to_gpio_1(state);
            break;
#if LOCK_CODE
        case HAL_GPIO_2:
        case HAL_GPIO_3:
        case HAL_GPIO_4:
#endif /* LOCK_CODE */
        default:
            ret = HAL_ERR_HW_LACK;
            goto finish;
    }

finish:
    return ret;
}

// Toggle the specified GPIO pin
int32_t hal_gpio_toggle_pin(HAL_GPIO_CTX *gpio)
{
    int32_t ret = HAL_SUCCESS;

    // Null pointer check
    if (NULL == gpio) {
        ret = HAL_ERR_NULL_POINTER;
        goto finish;
    }

    switch(gpio->hal_num) {
        case HAL_GPIO_0:
            msp430fr69cc_gpio_p1_0_toggle_pin_map_to_gpio_0();
            break;
        case HAL_GPIO_1:
            msp430fr69cc_gpio_p9_7_toggle_pin_map_to_gpio_1();
            break;
#if LOCK_CODE
        case HAL_GPIO_2:
        case HAL_GPIO_3:
        case HAL_GPIO_4:
#endif /* LOCK_CODE */
        default:
            ret = HAL_ERR_HW_LACK;
            goto finish;
    }

finish:
    return ret;
}

// Lock the specified GPIO pin configuration
int32_t hal_gpio_lock_pin(HAL_GPIO_CTX *gpio)
{
    int32_t ret = HAL_SUCCESS;

    // Null pointer check
    if (NULL == gpio) {
        ret = HAL_ERR_NULL_POINTER;
        goto finish;
    }

    switch(gpio->hal_num) {
        case HAL_GPIO_0:
            ret = msp430fr69cc_gpio_p1_0_lock_pin_map_to_gpio_0();
            if (ret != HAL_SUCCESS) {
                goto finish;
            }
            break;
        case HAL_GPIO_1:
            ret = msp430fr69cc_gpio_p9_7_lock_pin_map_to_gpio_1();
            if (ret != HAL_SUCCESS) {
                goto finish;
            }
            break;
#if LOCK_CODE
        case HAL_GPIO_2:
        case HAL_GPIO_3:
        case HAL_GPIO_4:
#endif /* LOCK_CODE */
        default:
            ret = HAL_ERR_HW_LACK;
            goto finish;
    }

finish:
    return ret;
}

#if HAL_UNIT_TEST
// Mock test function for hal_gpio
void hal_gpio_unit_test(void)
{
    size_t i = 1;

    HAL_GPIO_CTX red_led_test_gpio = {
        .hal_num = HAL_GPIO_0,
    };

    HAL_GPIO_CTX green_led_test_gpio = {
        .hal_num = HAL_GPIO_1,
    };

    // Test GPIO initialization
    if (hal_gpio_init(&red_led_test_gpio) == HAL_SUCCESS) {
        printf("GPIO initialized successfully.\n");
    } else {
        printf("GPIO initialization failed.\n");
    }
    // Test GPIO initialization
    if (hal_gpio_init(&green_led_test_gpio) == HAL_SUCCESS) {
        printf("GPIO initialized successfully.\n");
    } else {
        printf("GPIO initialization failed.\n");
    }

    while (i) {
        // Test writing to GPIO pin
        if (hal_gpio_write_pin(&red_led_test_gpio, HAL_GPIO_PIN_SET) == HAL_SUCCESS) {
            printf("GPIO write success (SET).\n");
        } else {
            printf("GPIO write failed.\n");
        }
        hal_delay_ms(200);
        // Test writing to GPIO pin
        if (hal_gpio_write_pin(&green_led_test_gpio, HAL_GPIO_PIN_SET) == HAL_SUCCESS) {
            printf("GPIO write success (SET).\n");
        } else {
            printf("GPIO write failed.\n");
        }
        hal_delay_ms(200);
        hal_delay_ms(1000);
        // Test reading from GPIO pin
        enum hal_gpio_pin_state state;
        if (hal_gpio_read_pin(&green_led_test_gpio, &state) == HAL_SUCCESS) {
            printf("GPIO read success: %s\n", state == HAL_GPIO_PIN_SET ? "SET" : "RESET");
        } else {
            printf("GPIO read failed.\n");
        }
        hal_delay_ms(1000);
        if (hal_gpio_toggle_pin(&green_led_test_gpio) == HAL_SUCCESS) {
            printf("GPIO toggled successfully.\n");
        } else {
            printf("GPIO toggle failed.\n");
        }
        hal_delay_ms(200);
        if (hal_gpio_toggle_pin(&red_led_test_gpio) == HAL_SUCCESS) {
            printf("GPIO toggled successfully.\n");
        } else {
            printf("GPIO toggle failed.\n");
        }
        hal_delay_ms(1000);
        // Test locking the GPIO pin
        if (hal_gpio_lock_pin(&red_led_test_gpio) == HAL_SUCCESS) {
            printf("GPIO locked successfully.\n");
        } else {
            printf("GPIO lock failed.\n");
        }
         hal_delay_ms(1000);
         i --;
    }
    // Deinitialize the GPIO pin
    hal_gpio_deinit(&green_led_test_gpio);
    hal_gpio_deinit(&red_led_test_gpio);
}
#endif /* HAL_UNIT_TEST */