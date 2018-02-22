#include <stdio.h>
#ifndef LCD_Function_H

#define LCD_Function_H

// Define the LCD port pin number
#define LCD_D0_Port GPIOB
#define LCD_D0 8
#define LCD_D1_Port GPIOB
#define LCD_D1 9
#define LCD_D2_Port GPIOA
#define LCD_D2 5
#define LCD_D3_Port GPIOA
#define LCD_D3 6
#define LCD_D4_Port GPIOA
#define LCD_D4 7
#define LCD_D5_Port GPIOB
#define LCD_D5 6
#define LCD_D6_Port GPIOC
#define LCD_D6 7
#define LCD_D7_Port GPIOA
#define LCD_D7 9
#define LCD_E_Port GPIOB  // Enable Pin
#define LCD_E_Pin 0
#define LCD_RS_Port GPIOC  // Register Selected Pin
#define LCD_RS_Pin 0
#define LCD_RW_Port GPIOC  // Read/Write Pin
#define LCD_RW_Pin 1
#define LCD_RST_Port GPIOA
#define LCD_RST_Pin 4
#define TimeDelayBeforeEnable 200
#define TimeDelayBeforeDisable 400

unsigned char LCDPosition[4][8] = {{0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87},
													{0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97},
													{0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f},
													{0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f}};
char Develeper[6] = {0xb5,0xcb,0xcf,0xe8,0xb9,0xda};  // ¾Hµ¾«a
					
							
void delay(int time_delay){
	volatile int i;
	for(i=0;i<time_delay;i++){
	}
}


void LCDInitialize(){
	GPIOSetOutput(LCD_D0_Port, LCD_D0);
	GPIOSetOutput(LCD_D1_Port, LCD_D1);
	GPIOSetOutput(LCD_D2_Port, LCD_D2);
	GPIOSetOutput(LCD_D3_Port, LCD_D3);
	GPIOSetOutput(LCD_D4_Port, LCD_D4);
	GPIOSetOutput(LCD_D5_Port, LCD_D5);
	GPIOSetOutput(LCD_D6_Port, LCD_D6);
	GPIOSetOutput(LCD_D7_Port, LCD_D7);
	GPIOSetOutput(LCD_E_Port, LCD_E_Pin);
	GPIOSetOutput(LCD_RS_Port, LCD_RS_Pin);
	GPIOSetOutput(LCD_RW_Port, LCD_RW_Pin);
	GPIOSetOutput(LCD_RST_Port, LCD_RST_Pin);
	digitalWrite(LCD_RST_Port, LCD_RST_Pin, 1);
}

void LCDReset(){
	digitalWrite(LCD_RST_Port, LCD_RST_Pin, 0);
	delay(20);
	digitalWrite(LCD_RST_Port, LCD_RST_Pin, 1);
}

void EableLCD(){
	delay(TimeDelayBeforeEnable);
	digitalWrite(LCD_E_Port, LCD_E_Pin, 1);
}

void LCDSetToWrite(){
	digitalWrite(LCD_RW_Port, LCD_RS_Pin, 0);
}
void LCDSetToRead(){
	digitalWrite(LCD_RW_Port, LCD_RS_Pin, 1);
}

void LCDCommandMode(){
	digitalWrite(LCD_RS_Port, LCD_RS_Pin, 0);
}
void LCDCharacterMode(){
	digitalWrite(LCD_RS_Port, LCD_RS_Pin, 1);
}


void SendBytesToLCD(char character){
	digitalWrite(LCD_D0_Port, LCD_D0, (character & 0x01));
	digitalWrite(LCD_D1_Port, LCD_D1, (character & 0x02));
	digitalWrite(LCD_D2_Port, LCD_D2, (character & 0x04));
	digitalWrite(LCD_D3_Port, LCD_D3, (character & 0x08));
	digitalWrite(LCD_D4_Port, LCD_D4, (character & 0x10));
	digitalWrite(LCD_D5_Port, LCD_D5, (character & 0x20));
	digitalWrite(LCD_D6_Port, LCD_D6, (character & 0x40));
	digitalWrite(LCD_D7_Port, LCD_D7, (character & 0x80));
	delay(TimeDelayBeforeDisable);
	digitalWrite(LCD_E_Port, LCD_E_Pin, 0);
}

void SendCharacterToLCD(char character){
	LCDSetToWrite();
	LCDCharacterMode();
	EableLCD();
	SendBytesToLCD(character);
}
void SendCommandToLCD(char character){
	LCDSetToWrite();
	LCDCommandMode();
	EableLCD();
	SendBytesToLCD(character);
}

void LCDPrintString(char *characters){
	while(*characters){
		SendCharacterToLCD(*characters++);
	}
}
void LCDPrintMatrix(char *GB_Code, int mat_size){
	for(int i=0;i<mat_size;i++){
		SendCharacterToLCD(*GB_Code++);
	}
}

void LCDPrintInteger(int IntegerData, uint8_t DataLength){
	char Integer2String[DataLength];
	sprintf(Integer2String, "%d", IntegerData);
	LCDPrintString(Integer2String);
}
void LCDPrintFloat(float FloatData, uint8_t DataLength){
	char Integer2String[DataLength];
	sprintf(Integer2String, "%.2f", FloatData);
	LCDPrintString(Integer2String);
}

void LCDClear(){
	SendCommandToLCD(0x01);   // Clear the LCD display
}
void LCDBegin(){
	SendCommandToLCD(0x30);   //0b0011 0000, basic command and 8-bit mode
	SendCommandToLCD(0x0e);   //0b0000 1110, display on and cursor on
	LCDClear();
}
void setCursor(char posx, char posy){   // position 4X8
	if(posx<4 && posy<8){
		SendCommandToLCD(LCDPosition[posx][posy]);
	}
}
void CursorHome(){
	SendCommandToLCD(0x02);
}

void LCDWelcome(){
	LCDClear();
	setCursor(0,0); LCDPrintString("Welcome "); 
	SendCharacterToLCD(0x03); SendCharacterToLCD(0x03); SendCharacterToLCD(0x03); // Heat sign
	setCursor(3,0); LCDPrintString("Power by "); 
	setCursor(3,5); LCDPrintMatrix(&Develeper[0], 6);
	delay(500000);
	LCDClear();
}

#endif
