/*
 * ControlDCMotor.c
 *connecting the DC motor directly without motor drive
 with keypad for entering a number to control the motor
 and LCD to display the Duty Cycle
 
 DUTY_CYCLE = y / (y+1)  ------- > y is the intered value by the user
 --------------------------------------------------------
 *target -> atmega16a
 --------------------
 Interfaces
 1-keypad Interface -> PORTC
 2-LCD Interface
 *Data -> PORTA
 *control -> PORTD
 3- DC Motor PinB0
 *
 * Created: 18/11/2021 03:17:36 م
 * Author : mohamed khaled
 */ 

#include <avr/io.h>
#include "KEYBAD.h"
#include "LCD.h" 
#define F_CPU 1000000ul 
#include <util/delay.h>  

#define  NOTPRESSED 'A'
void RUN_DC_MOTOR(int y);

int main(void) {
	
	// Interface initiation
	KeyPadInit();
	LCD_INIT();
	
	// Initial the direction for DC Motor Pin
	DDRB |= (1<<0);
	
	while (1)
	{
		
		LCD_SEND_A_STRING("ENTER NUMBER TO CONTROL DC MOTOR");
		_delay_ms(100);
		// get the Key pressed by the user
		char x = KeyPadgetkeypressed ();
		
		if(x != NOTPRESSED){
			
			int y = ((int) x - 48) ;
			
			RUN_DC_MOTOR(y);
			
			double DUTY_CYCLE = (double)y / ((double)y+1);
			LCD_SEND_A_STRING("THE DUTY CYCLE = ");
			LCD_CLEAR();
			LCD_SEND_REALNUM( DUTY_CYCLE );
			_delay_ms(100);
			LCD_CLEAR();
			
		}
	}
	
	
}







// This API run DC motor by passing a value the user enter on Keypad

void RUN_DC_MOTOR(int y){
	PORTB |= (1<<0);
	int i ;
	for (i=0 ; i < y ; i++)
	{
		_delay_ms(1000);
	}
	
	PORTB &= ~(1<<0);
	_delay_ms(1000);
}
