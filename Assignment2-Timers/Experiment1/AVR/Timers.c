/*******************************************************
Project : Timers
Version : 1.00
Date    : 12/19/2020
Author  : Alireza Majari
Company : P48
Comments: 
This is assignment#1 of Microprocessor Lab.
kharazmi University of Tehran


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 12.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
#include <delay.h>

// Declare your global variables her
int num = 0;
int delay;

// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
    ++delay;
    if(delay == 60){
        if(num < 10){
            PORTC =  num;
        } else {
            num = 0 ;
            PORTC = num;
        }
        num++;
    }

    TCNT1H=0xFF;
    TCNT1L=0xF0;
}

void main(void)
{
    TCCR1A=0x00;
    TCCR1B=0x01;
    TCNT1H=0xFF;
    TCNT1L=0xF0;

    MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    MCUCSR=(0<<ISC2);

    // Timer(s)/Counter(s) Interrupt(s) initialization
    TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

    #asm("sei")    

    DDRC=0xff;
    PORTC=0xff;

    while (1) {

    }
}