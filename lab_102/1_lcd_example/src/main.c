/*
 * main.c
 *
 * this is the main lcd application
 *
 * author:    Dr. Alex Shenfield
 * date:      04/09/2017
 * purpose:   55-604481 embedded computer networks : lab 102
 */

// include the basic headers and hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "stm32746g_discovery_lcd.h"
#include "adc.h"
#include "gpio.h"



  // Declare Variables
  uint8_t Light = 30;
  uint8_t Temperature = 25;
	uint8_t Light2 = 50;
  uint8_t Temperature2 = 45;
  int state_change = 0;
	int lcd_clear = 0;

  // Map the Pot, temp and pushbutton
  gpio_pin_t pot = {PF_7, GPIOF, GPIO_PIN_7};
  gpio_pin_t temp = {PF_6, GPIOF, GPIO_PIN_6};

  gpio_pin_t button = {PB_8, GPIOB, GPIO_PIN_8};
  gpio_pin_t led1 = {PI_2, GPIOI, GPIO_PIN_2};

  // Funtions
  void Press_to_begin ();
  void Print_Room_1();
  void Print_Room_2();
  void Print_PIR();

  // Declare strings]
	char str[28];
  char str1[28];
	char str2[28];

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	init_adc(pot);
	init_adc(temp);
	init_gpio(led1, OUTPUT);
	init_gpio(button, INPUT);
	
	// initialise the lcd
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
	BSP_LCD_Clear(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font24);	
  
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
		if ((button_history & 0xDF) == 0x07){
			
			if (state_change == 0){
				state_change = 1;
			}
			
			else if (state_change == 1){
				state_change = 2;
			}
			
			else if (state_change == 2){
				state_change = 3;
			}
			
			else if (state_change == 3){
				state_change = 1;
			}
			
			button_history = 0xFF;
			
		}
		
		
		
		  
		
		
		  switch (state_change) {
			
			case 0:
			Press_to_begin();
			break;
			
			
			
			case 1:
			if (lcd_clear == 0) {
			BSP_LCD_Clear(LCD_COLOR_BLACK);
			lcd_clear = 1;
			}
			Print_Room_1();
		  break;
		
			
			
			case 2:
			if (lcd_clear == 1) {
			BSP_LCD_Clear(LCD_COLOR_BLACK);
			lcd_clear = 2;
			}
			Print_Room_2();
			break;
			
			
			
			case 3:
			if (lcd_clear == 2) {
			BSP_LCD_Clear(LCD_COLOR_BLACK);
			lcd_clear = 0;
			}
			Print_PIR();
			break;
				
		}
		
		
		
  }
 }

void Press_to_begin()
 {
	    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
		  sprintf(str, "Please press the button");
			BSP_LCD_DisplayStringAtLine(5, (uint8_t *)str);
			sprintf(str2, "to begin...");
			BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str2);
 }
 
void Print_Room_1()
{
			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
      sprintf(str2, "ROOM 1");
		  BSP_LCD_DisplayStringAtLine(1, (uint8_t *)str2);
	
	  	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		  sprintf(str, "Light = %d", Light);
      BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str);
			
			sprintf(str1, "Temperature = %d", Temperature);
      BSP_LCD_DisplayStringAtLine(4, (uint8_t *)str1);
}
void Print_Room_2()
{			
			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
      sprintf(str2, "ROOM 2");
		  BSP_LCD_DisplayStringAtLine(1, (uint8_t *)str2);
	
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		  sprintf(str, "Light = %d", Light2);
      BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str);
			
			sprintf(str1, "Temperature = %d", Temperature2);
      BSP_LCD_DisplayStringAtLine(4, (uint8_t *)str1);
}
void Print_PIR()
{
	    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
      sprintf(str2, "    ROOM 1        ROOM 2");
		  BSP_LCD_DisplayStringAtLine(1, (uint8_t *)str2);
	    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	    BSP_LCD_FillRect(35, 50, 185, 200);
			BSP_LCD_FillRect(255, 50, 185, 200);
}
