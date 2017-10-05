/*
 * main.c
 *
 * this is the main blinky application (this code is dependent on the
 * extra shu libraries such as the pinmappings list and the clock configuration
 * library)
 *
 * author:    Dr. Alex Shenfield
 * date:      01/09/2017
 * purpose:   55-604481 embedded computer networks : lab 101
 */

// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"

// map the red, amber and green LED to their respective pins
gpio_pin_t red = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t amber = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t green = {PB_15, GPIOB, GPIO_PIN_15};

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
  
  // initialise the gpio pins
  init_gpio(red, OUTPUT);
	init_gpio(amber, OUTPUT);
	init_gpio(green, OUTPUT);
  
  // loop forever ...
  while(1)
  {
    
    // toggle the red led on
    toggle_gpio(red);
    
    // wait for 1 second
    HAL_Delay(1000);
		
		
		// toggle the amber led on aswell
		toggle_gpio(amber);
    
    // wait for 1 second
    HAL_Delay(1000);
		
		
		// toggle the amber and red off, but green on
		toggle_gpio(amber);
		toggle_gpio(red);
		toggle_gpio(green);
    
    // wait for 1 second
    HAL_Delay(1000);
		
		
		// toggle the green off and amber on
		toggle_gpio(green);
		toggle_gpio(amber);
    
    // wait for 1 second
    HAL_Delay(1000);
				
		// toggle the amber off
		toggle_gpio(amber);
		
    		
		
  }
}