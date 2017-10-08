/*
 * main.c
 *
 * this is the main push button application (this code is dependent on the
 * extra shu libraries such as the pinmappings list and the clock configuration
 * library)
 *
 * author:    Alex Shenfield
 * date:      01/09/2017
 * purpose:   55-604481 embedded computer networks : lab 101
 */

// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"
#include "random_numbers.h"

 
// map the push button
gpio_pin_t pb1 = {PI_3, GPIOI, GPIO_PIN_3};


gpio_pin_t red = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t amber = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t green = {PB_15, GPIOB, GPIO_PIN_15};
gpio_pin_t red2 = {PC_7, GPIOC, GPIO_PIN_7};
gpio_pin_t amber2 = {PC_6, GPIOC, GPIO_PIN_6};
gpio_pin_t green2 = {PG_6, GPIOG, GPIO_PIN_6};
gpio_pin_t blue = {PG_7, GPIOG, GPIO_PIN_7};



// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	init_random();
  
  // initialise the gpio pins
  init_gpio(pb1, INPUT);
	
	init_gpio(red, OUTPUT);
	init_gpio(amber, OUTPUT);
	init_gpio(green, OUTPUT);
	init_gpio(red2, OUTPUT);
	init_gpio(amber2, OUTPUT);
	init_gpio(green2, OUTPUT);
	init_gpio(blue, OUTPUT);
  
  // loop forever ...
  while(1)
  {
    // if the button is pressed ...
    if(read_gpio(pb1))
    {
      // turn the led on on the gpio pin
      write_gpio(red, HIGH);
			write_gpio(amber, HIGH);
			write_gpio(green, HIGH);
			write_gpio(red2, HIGH);
			write_gpio(amber2, HIGH);
			write_gpio(green2, HIGH);
			write_gpio(blue, HIGH);
    }
    else
    {
      // turn the led off on the gpio pin
      write_gpio(red, LOW);
			write_gpio(amber, LOW);
			write_gpio(green, LOW);
			write_gpio(red2, LOW);
			write_gpio(amber2, LOW);
			write_gpio(green2, LOW);
			write_gpio(blue, LOW);
    }
  }
}
