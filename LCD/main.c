#include "stm32l1xx.h"                  // Device header
#include "ARM_IO.h"
#include "LCD_Function.h"

/*
LCD Test:
LCD : MJ12864G-1 (Position 4X8)
Pin01 : VSS (Ground)
Pin02 : VDD (Power 5V)
Pin03 : 
Pin04 : RS (High:Character/Data Mode, Low:Instruction Mode)
Pin05 : R/W (High:Read, Low:Write)
Pin06 : E (Enable Pin)
Pin07 ~ Pin14 : Data Bus, D0 ~ D7
Pin15 : 
Pin16 : 
Pin17 : RST(Active Low)
Pin18 : 
Pin19 : LED+
Pin20 : LED-
*/

int main(){
	int data=0;
	LCDInitialize();
	LCDBegin();
	LCDWelcome();
	LCDPrintString("Hello World!");
	setCursor(1,0); LCDPrintInteger(12345, 5);
	setCursor(2,0); LCDPrintFloat(3.141592, 4);

	
	GPIOSetInput(STM32L_BUTTON_PORT, STM32L_BUTTON_PIN);

	while(1){
		int bt_state = digitalRead(STM32L_BUTTON_PORT, STM32L_BUTTON_PIN);
		if(bt_state == 0){
				LCDClear();		
		}
	}
	
	
}




