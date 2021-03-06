/*******************************************************
Project : LCDsExp1
Version : 1.00
Date    : 1/1/2021
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

void main(void)
{
    DDRC=0xff;
    PORTC=0xff;

    #asm("sei")    
    
    lcd_init(20);

    while (1) {    
        lcd_gotoxy(0,0);
        lcd_putsf("Hello World!");
    }
}