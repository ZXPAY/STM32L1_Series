#include "stm32l1xx.h"                  // Device header
#include "ARM_IO.h"
#include "LCD_Function.h"

// ADC pin test : PA0

int main(){
	// LCD Initialize and Display On
	LCDInitialize();
	LCDBegin();
	LCDWelcome();
	
	
	// Enable the PORTA peripheral
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	// GPIO change to analog mode
	GPIOA ->MODER |= GPIO_MODER_MODER0;
	GPIOA ->OTYPER &= ~GPIO_OTYPER_OT_0;
	GPIOA ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0;
	GPIOA ->PUPDR &= ~GPIO_PUPDR_PUPDR0;
	
	// Select a Clock source for ADC
	RCC ->CR |= RCC_CR_HSION;
	while(!(RCC->CR & RCC_CR_HSIRDY));

	// ADC Code Write Here
	ADC1->CR2 &= ~ADC_CR2_ADON; // Disable the ADC to config
	while(ADC1->SR & ADC_SR_ADONS);
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // Enable ADC1 peripheral clock
	ADC->CCR = 0; // Disable temperature sensor, Vrefint, ADC prescaler = HSI/1
	ADC1->SQR1 |= ADC_SQR5_SQ1_0; // 1st conversion in regular sequence will be from ADC_IN0
	ADC1->CR1 &= ~ADC_CR1_RES;    // 00 : 12 bits resolution
	ADC1->CR2 &= ~ADC_CR2_ALIGN;  // Right alignment
	ADC1->SMPR3 |= ADC_SMPR3_SMP4; // Channel4 sample rate: 384 cycles
	ADC1->CR2 |= ADC_CR2_ADON; // Enable the ADC
	while(!(ADC1->SR & ADC_SR_ADONS)); // Wait until ADC is on
	
	LCDPrintString("Setup OK");
	delay(100000);
	while(1){
		ADC1->CR2 |= ADC_CR2_SWSTART;
		while (!(ADC1->SR & ADC_SR_EOC)); // Wait until conversion end
		setCursor(3,0);
		LCDPrintString("Value:");
		LCDPrintInteger(ADC1->DR, 4);
		LCDPrintString("  ");
		delay(10000);
	}
	
}


