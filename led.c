#include <stdint.h>
#include "led.h"


/**
led intialization
*/

void led_init(void){
	
	gpio_pin_conf_t led_pin_conf;
	/* enable the clock for the GPIOA port */
	_HAL_RCC_GPIOA_CLK_ENABLE();
	
	led_pin_conf.pin = LED_GREEN;
	led_pin_conf.mode = GPIO_PIN_OUTPUT_MODE;
	led_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSHPULL;
	led_pin_conf.speed = GPIO_PIN_SPEED_MEDIUM;
	led_pin_conf.pull = GPIO_PIN_NO_PULL_PUSH;
	
	hal_gpio_init(GPIOA, &led_pin_conf);
	
}


//led operations
void led_turn_on(GPIO_TypeDef *GPIOx, uint16_t pin){
	hal_gpio_write_to_pin(GPIOx,pin,1); //led pin is 5
}

void led_turn_off(GPIO_TypeDef *GPIOx, uint16_t pin){
	hal_gpio_write_to_pin(GPIOx,pin,0);
	
}

void led_toggle(GPIO_TypeDef *GPIOx, uint16_t pin){
	if(hal_gpio_read_from_pin(GPIOx,pin))
	{
		hal_gpio_write_to_pin(GPIOx,pin, 0);
	}
	
	else
	{
		hal_gpio_write_to_pin(GPIOx, pin, 1);
	}
	
	//alternative
#if 0
		//logic2
		hal_gpio_write_to_pin(GPIOx,pin, ~(hal_gpio_read_from_pin(GPIOx,pin) ));
#endif
}




uint16_t count;


int main(void){
	
	uint32_t i;
	
	/*intializing led */
		led_init();
	/* push button at PC13 */
	
	/*enabling cloc for gpioc */
	_HAL_RCC_GPIOC_CLK_ENABLE();
	
	/*configure the button interrupt as falling edge */
	hal_gpio_configure_interrupt( GPIO_BUTTON_PIN , INT_FALLING_EDGE );
	/*Enable the Interrupt on EXTI14 line */
	hal_gpio_enable_interrupt(GPIO_BUTTON_PIN, EXTI15_10_IRQn);
	
	//on the led
	led_turn_on(GPIOA,LED_GREEN);
		
#if 0	
		while(1)
		{
		
		led_turn_on(GPIOA,LED_GREEN);		
		
		
		//led_turn_off(GPIOA,LED_GREEN);
		
		return 0;
		}

}
#endif
while(1);
}

/**
	* @brief ISR for the configured EXTI0 interrupt
	* @retval None
	*/

void EXTI15_10_IRQHandler(void)
{
	hal_gpio_clear_interrupt(GPIO_BUTTON_PIN);
	/*My task*/
	led_turn_off(GPIOA,LED_GREEN);
}