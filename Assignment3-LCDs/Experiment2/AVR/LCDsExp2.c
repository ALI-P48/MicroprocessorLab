/*******************************************************
Project : LCDsExp2
Version : 1.00
Date    : 1/2/2021
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

int delay;
int cursorX;
int cursorY;
char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int index;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
   ++delay;
   
   if(delay ==500){   
        lcd_putchar(alphabet[index]);
        index+=1;
        cursorX+=1;

        if(cursorX==20){
            cursorX=0;
            cursorY=1;
         }

        lcd_gotoxy(cursorX,cursorY);
        delay=0;

        if(index == 26){    
            index = 0;
            cursorX = 0;
            cursorY = 0;    
            lcd_clear(); 
        }
   }      
}

void main(void)
{
    DDRC=0xff;
    PORTC=0xff; 
    
    index = 0;
    cursorX = 0;
    cursorY = 0;
    delay = 0; 
                                                         
    lcd_init(20); 
    
    TCCR0=0x01;
    TCNT0=0x00;
    OCR0=0x00;
    TIMSK=0x01;
    #asm("sei")

    while (1) {    
    
    }
}
