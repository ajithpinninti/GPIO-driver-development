

#include <stdint.h>
#include "gpio_driver.h"

/*********************************************************************/
/*																																		*/
/*										Static helper functions													*/
/*																																		*/
/**********************************************************************/

/**
* @brief Configures the mode of a pin : input, output, alt or analog mode
*	 @param *GPIOx : GPIO Port Base address
*	 @param pin_no : GPIO pin number
*	 @param mode 	 : mode to be configured
*	 @retval None
*/
static void hal_gpio_configure_pin_mode(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t mode)
{
			GPIOx ->MODER |= (mode << (2*pin_no) ); 	//every pin take 2 bits to configure mode so 32 bits 16 pins
}

/**
	* @brief configures the output type of pin
	* @param op_type : output type to be confitred with 
	* @retrival none
*/

static void hal_gpio_pin_otype(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t op_type)
{
	GPIOx->OTYPER |= ( op_type << pin_no); // 0 pushpull 1 opendrain
	
}

/**
	* @brief configures the speed of the pin
	* @param speed: value of the speed
	* @retval None
*/
static void hal_gpio_configure_pin_speed(GPIO_TypeDef *GPIOx , uint16_t pin_no, uint32_t speed)
{
	GPIOx->OSPEEDR |= ( speed << (2 * pin_no) );
}

/**
	* @brief configures the inernal pullup or pull down reistors
	* @param pupd : specifies which restor to active
	@retrival None
*/
void hal_gpio_configure_pin_pupd( GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t pupd)
{
	GPIOx->PUPDR |= ( pupd << ( 2*pin_no) );
}

/**
	* @brief intializes the gpio pin
	* @param *gpio_pin_conf : Pointer to the pin conf structure sen by application
	* @retval None
	*/
void hal_gpio_init( GPIO_TypeDef *GPIOx, gpio_pin_conf_t *gpio_pin_conf )
{
	//GPIOx->MODER &= 
	hal_gpio_configure_pin_mode(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->mode);
	hal_gpio_pin_otype(GPIOx, gpio_pin_conf->pin, gpio_pin_conf->op_type);
	hal_gpio_configure_pin_speed(GPIOx,gpio_pin_conf->pin, gpio_pin_conf->speed);
	hal_gpio_configure_pin_pupd(GPIOx , gpio_pin_conf->pin, gpio_pin_conf->pull);
	
}

/* ***************************************************************************
**************************************************************************/

/** @brief reading value from given pin number
	* @retval uint8_t : Value read
*/
uint8_t hal_gpio_read_from_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no)
{
	uint8_t value;
	/* Read from the IDR register then right shift by the value of pin number to get
	the input status value of the pin to lsb */
	
	value = ( ( GPIOx->IDR >> pin_no ) & 0x00000001);
	
	return value;
}

/** 
	* @brief Write a value to given pin number
	* @param *GPIOx	:	GPIO Port Base address
	* @param pin_no : GPIO pin number
	* @param val : value to be writtebn
	*	@retval None
*/

void hal_gpio_write_to_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint8_t val)
{
		if(val)
			GPIOx ->ODR |= ( 1 << pin_no) ;
		else
			GPIOx ->ODR &= ~( 1 << pin_no);
}


/**
	*@brief Set the alernate functioality for the given pin
	*@param alt_fun_value: alternate function to be configured with
	*@retval None
*/

/****changed heerrreee >*****/

void hal_gpio_set_alt_function(GPIO_TypeDef *GPIOx , uint16_t pin_no, uint16_t alt_fun_value)
{	
	if ( pin_no <= 7)
	{	
		GPIOx ->AFR[0] |= ( alt_fun_value << ( (pin_no) * 4 ) );
	}
	else
	{	GPIOx ->AFR[1] |= ( alt_fun_value << ( (pin_no % 8) * 4) );
	}
}


/***************************************************************************/
/***************************************************************************/

/*												Interrupts																			*/

/***************************************************************************/
/***************************************************************************/

/**
	* @brief Configure the interrupt for a given pin number
	*	@param pin_no : GPIO pin numbner
	* @param edge_sel: Triggering edge selection value of type "int_edge_sel_t"
	* @retval None
	*/
	void hal_gpio_configure_interrupt(uint16_t pin_no, int_edge_sel_t edge_sel){
		
		if(edge_sel == INT_RISING_EDGE)
		{
			EXTI->RTSR |= 1 << pin_no;
		}
		else if(edge_sel == INT_FALLING_EDGE)
		{
			EXTI->FTSR |= 1 << pin_no;
		}
		else if(edge_sel == INT_RISING_FALLING_EDGE)
		{
			EXTI ->FTSR |= 1 << pin_no;
			EXTI ->RTSR |= 1 << pin_no;
		}
		else{
			   ;//TODO
		}
	}
	
	/**
	* @brief enable the interrupt for a given pin number and irq number
	*	@param pin_no : GPIO pin numbner
	* @param irq_no : irq_number to be enabled in NVIC
	* @retval None
	*/
	void hal_gpio_enable_interrupt(uint16_t pin_no, IRQn_Type irq_no){
		EXTI->IMR |= ( 1<< pin_no);
		NVIC_EnableIRQ(irq_no);
	}
	
	/**
	* @brief Clear the sticky interrupt pending bit if set
	*	@param pin_no : GPIO pin number
	* @retval None
	*/
	void hal_gpio_clear_interrupt(uint16_t pin){
		EXTI -> PR |= 1<< pin ;
		if( EXTI->PR & ( 1 << pin ) ){
			EXTI -> PR |= 1<< pin ;
		}
	}
	



	
