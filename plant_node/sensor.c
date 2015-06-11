

#include "sensor.h"

#define ENABLE_DEBUG (1)
#include "debug.h"

/* -------------------------------------------------- */
#ifndef BOARD_IOT_LAB_M3

timex_t sensor_timer;


static volatile unsigned int sensor_value = 0;

static timex_t last_button_time;
static timex_t current_button_time; /*XXX: put here cause got message: */
static timex_t delta_time; /* ... Cannot debug, stack too small */

void button_cb(void *arg){

    vtimer_now(&current_button_time);
    delta_time = timex_sub(current_button_time, last_button_time);
    //DEBUG("GPIO_BUTTON triggered (%u:%u)\n", 
    //	  delta_time.seconds, delta_time.microseconds);
    if (delta_time.seconds > 0 || delta_time.microseconds > 700000) {
      //DEBUG("[changed sensor_value]\n");
      sensor_value = (sensor_value+1) % 3; /* 0,1,2 */
      last_button_time = current_button_time;
    }
}


int sensor_init(void)
{
    vtimer_now(&last_button_time);
    sensor_timer = timex_set(1, 0); /* 1 sec. */

    /* initialize the GPIO of the button */
    gpio_init_int(GPIO_BUTTON_PIN, GPIO_NOPULL, GPIO_RISING, button_cb, 0);

    /* NOT USED: */
    /* initialize a GPIO that powers the sensor just during a measure */
    DEBUG("Initializing GPIO_%i as power supplying pin", GPIO_POWER_PIN);
    if (gpio_init_out(GPIO_POWER_PIN, GPIO_NOPULL) == 0) {
        DEBUG("    [ok]\n");
    }
    else {
        DEBUG("    [failed]\n");
        return 1;
    }

    /* initialize ADC device */
    DEBUG("Initializing ADC_%i @ %i bit resolution", ADC_IN_USE, (6 + (2* RES)));
    if (adc_init(ADC_IN_USE, RES) == 0) {
        DEBUG("    [ok]\n");
    }
    else {
        DEBUG("    [failed]\n");
        return 1;
    }
    return 0;
}

void sensor_get_humidity(unsigned int *humidity)
{
    DEBUG("Checking moisture...\n");

#if 0
    gpio_set(GPIO_POWER_PIN);

    /* wait until the sensor is ready to go */
    vtimer_sleep(sensor_timer);
    *humidity = adc_sample(ADC_IN_USE, ADC_CHANNEL_USE);
    gpio_clear(GPIO_POWER_PIN);
#endif
    *humidity = sensor_value * 1500;

    printf("Humidity: ADC_%i: %4i\n", ADC_IN_USE, *humidity);
}

/* -------------------------------------------------- */
#else /* BOARD_IOT_LAB_M3 */

int sensor_init(void)
{
  return 0;
}

void sensor_get_humidity(unsigned int *humidity)
{
}

/* -------------------------------------------------- */
#endif /* BOARD_IOT_LAB_M3 */

