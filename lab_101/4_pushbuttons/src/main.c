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
gpio_pin_t button = {PI_3, GPIOI, GPIO_PIN_3};

// map all LED's
gpio_pin_t red = {PI_2, GPIOI, GPIO_PIN_2};
gpio_pin_t amber = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t green = {PB_15, GPIOB, GPIO_PIN_15};
gpio_pin_t red2 = {PC_7, GPIOC, GPIO_PIN_7};
gpio_pin_t amber2 = {PC_6, GPIOC, GPIO_PIN_6};
gpio_pin_t green2 = {PG_6, GPIOG, GPIO_PIN_6};
gpio_pin_t blue = {PG_7, GPIOG, GPIO_PIN_7};


// Declare variables

  int GreenLEDstate;
  int Current;
  int Previous = 0;
  

  long Lastdebouncetime = 0;
  long Debouncedelay = 50;
  long Randnumber;




// this is the main method
int main()
{	
	
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	init_random();
  
  // initialise the gpio pins
  init_gpio(button, INPUT);
	
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
		
		 // Button debouncing
	  static uint8_t button_history = 0xFF;
		
	  // Shift button history and update state
	  button_history = button_history << 1;
	  uint8_t val = read_gpio(button);
		button_history = button_history | val;
		
		// Use pattern matching to determine if button has been pressed, if
		// this is the case reset the button history
		if ((button_history & 0xC7) == 0x07)
		{
			toggle_gpio(red);
			
			button_history = 0xFF;
			
		}
		
    // Read the status of the button switch to a local variable called Reading
		uint32_t Randnumber = (get_random_int() % 6) + 1;
		int Reading = (read_gpio(button));
    
		// Check to see if the button has changed due to noise or button press
	  if (Reading != Previous)
		{
	  // Reset the debouncing timer
		Lastdebouncetime = HAL_GetTick();
		}
		
		
		// Has the reading stayed there for longer than the debounce delay
		
		if ((HAL_GetTick() - Lastdebouncetime) > Debouncedelay)
		
		// If the state of the button has changed
		if (Reading != Current) 
    {
			Current = Reading;
	  
			
	  // Only toggle the LED if the state of the button is high (pressed again)
		if (Current == HIGH)
		{
		toggle_gpio(red);
			write_gpio(red2, LOW);
      write_gpio(green, LOW);  
      write_gpio(red, LOW);
      write_gpio(green2, LOW);
			write_gpio(amber, LOW);
			write_gpio(amber2, LOW);
			write_gpio(blue, LOW);
			
		
			if (Randnumber == 1)
      {
      write_gpio(blue, HIGH);
      }
      
      else if (Randnumber == 2)
      {
      write_gpio(red2, HIGH);
      write_gpio(green, HIGH);
      }

      else if (Randnumber == 3)
      {
      write_gpio(red2, HIGH);
      write_gpio(green, HIGH);  
      write_gpio(blue, HIGH);
      }

      else if (Randnumber == 4)
      {
      write_gpio(red2, HIGH);
      write_gpio(green, HIGH);  
      write_gpio(red, HIGH);
      write_gpio(green2, HIGH);
      }

      else if (Randnumber == 5)
      {
			write_gpio(red2, HIGH);
      write_gpio(green, HIGH);  
      write_gpio(red, HIGH);
      write_gpio(green2, HIGH);
			write_gpio(blue, HIGH);
      }

      else if (Randnumber == 6)
      {
      write_gpio(red2, HIGH);
      write_gpio(green, HIGH);  
      write_gpio(red, HIGH);
      write_gpio(green2, HIGH);
			write_gpio(amber, HIGH);
			write_gpio(amber2, HIGH);
		  }
		
			
	 }
}
			
	
	// Save the previous reading
	
	Previous = Reading;
			
    }
	}
