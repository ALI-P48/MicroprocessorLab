/*******************************************************
Project : LCDsExp3
Version : 1.00
Date    : 1/6/2021
Author  : Alireza Majari
Company : P48
Comments: 
This is Assignment#3 Experiment#3 of Microprocessor Lab.
kharazmi University of Tehran


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 12.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
#include <alcd.h>
#include <stdio.h>
#include <delay.h>

unsigned int positiveEdge;
unsigned int negativeEdge;
unsigned int end;
char frequency[16];
unsigned int period;
long freq;

void main(void)
{
    lcd_init(20);
    lcd_puts("initiating...");
    DDRC =0xFF;
    PORTC = 0x00;

    while(1)
    {
        TCCR1A = 0;
        TCNT1=0;
        TIFR = (1<<ICF1);
        TCCR1B = 0x41;            
        
        while ((TIFR&(1<<ICF1)) == 0);    
        
        positiveEdge = (256 * ICR1H) + ICR1L;
        TIFR = (1<<ICF1);
        TCCR1B = 0x01;       
        
        while ((TIFR&(1<<ICF1)) == 0); 
        
        negativeEdge = (256 * ICR1H) + ICR1L;
        TIFR = (1<<ICF1);
        TCCR1B = 0x41;        
        
        while ((TIFR&(1<<ICF1)) == 0); 
        
        end = (256 * ICR1H) + ICR1L;
        TIFR = (1<<ICF1);
        TCCR1B = 0;

		if(positiveEdge < end)
		{
			period = end - positiveEdge;

			freq= 8000000UL/period;
            sprintf(frequency,"Frequency= %d Hz", (int)freq);

            lcd_clear();
			lcd_puts(frequency);
		} 

        delay_ms(150);
	}
}