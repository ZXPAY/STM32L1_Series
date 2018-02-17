#include "stm32l1xx.h"                  // Device header
// Button1 on the stm32L1 board is PC13
// LED2 on the stm32L1 board is D13(PA5)
void delay(int a);

int main(void){
	// Reset the clock _ control and enable the pin
	RCC ->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC ->AHBENR |= RCC_AHBENR_GPIOCEN;
	
	// Setup LED Ouput mode, type, speed, pull-up, pull-down
	GPIOA ->MODER |= GPIO_MODER_MODER5_0;
	GPIOA ->MODER &= ~(GPIO_MODER_MODER5_1);
	GPIOA ->OTYPER &= ~(GPIO_OTYPER_OT_5);
	GPIOA ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5;
	GPIOA ->PUPDR &= ~(GPIO_PUPDR_PUPDR5); // 內建有pull-up, pull-down
	
	// Setup Button Input mode, type
	GPIOC ->MODER &= ~(GPIO_MODER_MODER13);
	GPIOC ->PUPDR &= ~(GPIO_PUPDR_PUPDR13); // 內建有pull-up, pull-down
	
	volatile char led_state = 0, bt_press = 0;
	volatile int press_nums = 0, release_nums;
	const int bt_threshold = 200;
	while(1){
		// Using IDR(input data register) to know whether the button pressed
		int bt_state = !(GPIOC ->IDR & GPIO_IDR_IDR_13); // bt is pull-up resister
		if(bt_state == 1){
			if(bt_press == 1){
				if(press_nums > bt_threshold){
					// Toggle the LED on or off
					if(led_state == 0){
						GPIOA ->BSRR |= GPIO_BSRR_BS_5;
						led_state = 1;
					}
					else{
						GPIOA ->BSRR |= GPIO_BSRR_BR_5;
						led_state = 0;
					}
					bt_press = 0;
				}
				else{
					press_nums++;
					release_nums = 0;
				}
			}
		}
		else if(bt_state==0){
			if(bt_press == 0){
				press_nums = 0;
				release_nums++;
				if(release_nums > bt_threshold){
					bt_press = 1;
				}
			}
		}
	}
}

void delay(int a){
	volatile int i,j;
	for(i=0;i<a;i++){
		for(j=0;j<250;j++);
	}
	
}

