#ifndef __LED_H
#define __LED_H

#include "gpio_driver.h"

#define EXT1x_IRQn			EXTI15_10_IRQn
#define EXT1x_IRQHandler EXTI0_IRQHandler

#define GPIO_BUTTON_PIN  	((uint16_t)0x2000)
#define GPIO_BUTTON_PORT	GPIOC

#define GPIOA_PIN_5	5

#define LED_GREEN			GPIOA_PIN_5

void led_init(void);

void led_turn_on(GPIO_TypeDef *GPIOx , uint16_t pin);

void led_turn_off(GPIO_TypeDef *GPIOx , uint16_t pin);

void led_toggle(GPIO_TypeDef *GPIOx , uint16_t pin);

#endif