/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <drivers/pwm.h>
#include <zephyr.h>


#define PWM_LED0_NODE DT_ALIAS(pwmled0)

#if DT_NODE_HAS_STATUS(PWM_LED0_NODE, okay)
#define PWM_LABEL DT_PWMS_LABEL(PWM_LED0_NODE)
#define PWM_CHANNEL DT_PWMS_CHANNEL(PWM_LED0_NODE)
#define PWM_FLAGS DT_PWMS_FLAGS(PWM_LED0_NODE)
#else

#warning "Unsupported board: pwm-led0 devicetree alias is not defined"
#define PWM_LABEL ""
#define PWM_CHANNEL 0
#define PWM_FLAGS 0
#endif

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0 DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0 ""
#define PIN 0
#define FLAGS 0
#endif

#define BL_LIGH_NODE DT_ALIAS(bl0)
#if DT_NODE_HAS_STATUS(BL_LIGH_NODE, okay)
#define BL0 DT_GPIO_LABEL(BL_LIGH_NODE, gpios)
#define BL0_PIN DT_GPIO_PIN(BL_LIGH_NODE, gpios)
#define BL0_FLAGS DT_GPIO_FLAGS(BL_LIGH_NODE, gpios)
#else
#define BL0 ""
#define BL0_PIN 0
#define BL0_FLAGS 0
#error "No bl0 alias found"
#endif

#define MIN_PERIOD_USEC (USEC_PER_SEC / 64U)
#define MAX_PERIOD_USEC USEC_PER_SEC

void main(void) {
  const struct device *dev, *bl0_dev;
  bool led_is_on = true;
  int ret;

  dev = device_get_binding(LED0);
  if (dev == NULL) {
    return;
  }

  bl0_dev = device_get_binding(BL0);
  if (NULL == bl0_dev) {
    return;
  }

  const struct device *pwm;
  uint32_t max_period;
  uint32_t period;
  uint8_t dir = 0U;

  pwm = device_get_binding(PWM_LABEL);
  if (!pwm) {
    printk("Error: didn't find %s device\n", PWM_LABEL);
    return;
  }

  max_period = MAX_PERIOD_USEC;
  while (pwm_pin_set_usec(pwm, PWM_CHANNEL, max_period, max_period / 2U,
                          PWM_FLAGS)) {
    max_period /= 2U;
    if (max_period < (4U * MIN_PERIOD_USEC)) {
      printk("Error: PWM device %s "
             "does not support a period at least %u\n",
             PWM_LABEL, 4U * MIN_PERIOD_USEC);
      return;
    }
  }

  // ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
  ret = gpio_pin_configure(dev, PIN, GPIO_INPUT | FLAGS);
  if (ret < 0) {
    return;
  }

  ret = gpio_pin_configure(bl0_dev, BL0_PIN, GPIO_OUTPUT_ACTIVE | BL0_FLAGS);
  if (ret < 0) {
    return;
  }

  printk("Done calibrating; maximum/minimum periods %u/%u usec\n", max_period,
         MIN_PERIOD_USEC);

  period = max_period;

  uint32_t pulse = 100U;
  bool up = true;

  while (1) {

    ret = pwm_pin_set_usec(pwm, PWM_CHANNEL, 15625, pulse, PWM_FLAGS);
    if (ret) {
      printk("Error %d: failed to set pulse width: %d\n", ret, pulse);
      // return;
    }

    if (up && pulse > 15500) {
      up = false;
    }

    if (pulse < 100) {
      up = true;
    }

    pulse = up ? (pulse + 100U) : (pulse - 100U);

    k_sleep(K_MSEC(10));

    /*			ret = pwm_pin_set_usec(pwm, PWM_CHANNEL,
                                                   period, period / 2U,
       PWM_FLAGS); if (ret) { printk("Error %d: failed to set pulse width\n",
       ret); return;
                            }

                            period = dir ? (period * 2U) : (period / 2U);
                            if (period > max_period) {
                                    period = max_period / 2U;
                                    dir = 0U;
                            } else if (period < MIN_PERIOD_USEC) {
                                    period = MIN_PERIOD_USEC * 2U;
                                    dir = 1U;
                            }

                            k_sleep(K_SECONDS(3U));*/

    // gpio_pin_set(dev, PIN, (int)led_is_on);
    // gpio_pin_set(bl0_dev, BL0_PIN, (int)!led_is_on);
    led_is_on = !led_is_on;
    // k_msleep(SLEEP_TIME_MS);
  }
}
