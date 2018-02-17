#define STM32L_BUTTON_PORT GPIOC
#define STM32L_BUTTON_PIN 13



/*
	only Setting the digital Output function
	Mode : digital output pin
	OS : High speed
	Otype : Output pull-push
	Pull-up/Pull-down : None
*/
void GPIOSetOutput(GPIO_TypeDef *port,int pin_number){
	if(port == GPIOA){
		RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
	}
	else if(port == GPIOB){
		RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;
	}
	else if(port == GPIOC){
		RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
	}
	else if(port == GPIOD){
		RCC -> AHBENR |= RCC_AHBENR_GPIODEN;
	}
	else if(port == GPIOE){
		RCC -> AHBENR |= RCC_AHBENR_GPIOEEN;
	}
	else if(port == GPIOF){
		RCC -> AHBENR |= RCC_AHBENR_GPIOFEN;
	}
	port ->MODER &= ~(1 <<((pin_number*2)+1));
	port ->MODER |= 1 << (pin_number*2);
	port ->OTYPER &= ~pin_number;
	port ->OSPEEDR |= (1 << ((pin_number*2)+1)) | (1 << (pin_number*2));
	port ->PUPDR &= ~(1 <<((pin_number*2)+1)) & ~(1 << (pin_number*2));
}

void digitalWrite(GPIO_TypeDef *port, int pin_number, uint8_t state){
	if(state){
		port->BSRR |= (1 << pin_number);
	}
	else{
		port->BRR |= (1 << pin_number);
	}
}

void GPIOSetInput(GPIO_TypeDef *port,int pin_number){
	port ->MODER &= ~(1 <<((pin_number*2)+1)) & ~(1 << (pin_number*2));
	port ->PUPDR &= ~(1 <<((pin_number*2)+1)) & ~(1 << (pin_number*2));
}
int digitalRead(GPIO_TypeDef *port, int pin_number){
	return port ->IDR & (1<<STM32L_BUTTON_PIN);
}


