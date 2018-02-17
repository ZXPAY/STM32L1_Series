#include "stm32l1xx.h"                  // Device header

void delay (int a);

int main (void) {
	// Enable the GPIO clock for port A using AHB and RCC
	RCC ->AHBENR |= RCC_AHBENR_GPIOAEN;
	// Set any control Register for portA pin 10  ==> °t¦XManual Register Address
	GPIOA ->MODER |= GPIO_MODER_MODER10_0;
	// Out Type
	GPIOA ->OTYPER &= ~(GPIO_OTYPER_OT_10); // &= ~  ==> ½T«O¹Bºâ«á³¬°0
	// OS Speed
	GPIOA ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10;
	// GPIO pull-up/ pull-down register ==> PUPDR
	GPIOA ->PUPDR &= ~(GPIO_PUPDR_PUPDR10);   // &= ~  ==> ½T«O¹Bºâ«á³£¬°00
	
	while(1){
		// turn on the LED
		// GPIO port bit set/reset register  BSRR
		// BSRR ==> Set
		GPIOA ->BSRR |= GPIO_BSRR_BS_10;
		delay(1000);
		// turn off the LED 
		// BRR ==> bit reset register
		GPIOA ->BRR |= GPIO_BRR_BR_10;  
		// or can use BSRR like this ==> GPIOA ->BRR |= GPIO_BRR_BR_10; 
		delay(1000);
	}

}
void delay (int a)
{
    volatile int i,j;

    for (i=0 ; i < a ; i++)
    {
        for(j=0;j<250;j++);
    }

}
