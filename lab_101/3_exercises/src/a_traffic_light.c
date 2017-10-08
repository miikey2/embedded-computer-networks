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

// map the second set of traffic LED's
gpio_pin_t red2 = {PC_7, GPIOC, GPIO_PIN_7};
gpio_pin_t amber2 = {PC_6, GPIOC, GPIO_PIN_6};
gpio_pin_t green2 = {PG_6, GPIOG, GPIO_PIN_6};

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
	init_gpio(red2, OUTPUT);
	init_gpio(amber2, OUTPUT);
	init_gpio(green2, OUTPUT);
  
  // loop forever ...
  while(1)
  {
    
    
    toggle_gpio(red);         // Traffic light 1 red LED on
		toggle_gpio(green2);      // Traffic light 2 green LED on

    
    // wait for 4 second
    HAL_Delay(4000);
		
		
		toggle_gpio(amber2);      // Traffic light 2 amber LED on
		toggle_gpio(green2);      // Traffic light 2 green LED on
    
    // wait for 2 second
    HAL_Delay(2000);
		
		
		toggle_gpio(amber);
		toggle_gpio(amber2);
		toggle_gpio(red2);
    
    // wait for 1 second
    HAL_Delay(2000);
		
		
		// toggle the green off and amber on
		toggle_gpio(red);
		toggle_gpio(amber);
		toggle_gpio(green);
    
		
    // wait for 2 second
    HAL_Delay(4000);
				
				
		// toggle the amber off
		toggle_gpio(green);
		toggle_gpio(amber);
		
		
		// wait for 2 second
    HAL_Delay(2000);
		
		
		toggle_gpio(red);
		toggle_gpio(amber);
		toggle_gpio(amber2);
		
		// wait for 2 second
    HAL_Delay(2000);
		
	  write_gpio(red, LOW);
		write_gpio(amber, LOW);
		write_gpio(green, LOW);
		write_gpio(red2, LOW);
		write_gpio(amber2, LOW);
		write_gpio(green2, LOW);
		
		
  }
}