/*******************************************************
Project : TimersEXP2
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
#include <math.h> 

// Declare your global variables her
int num = 0;
int delay0;
int delay1;
int turn=1;

int getdigit(int num, int n)
{
    int r;
    r = num / pow(10, n);
    r = r % 10;
    return r;
}

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
   ++delay1;
   
   if(delay1 ==2){  
        PORTB = pow(2, turn-1);     
        PORTC = getdigit(num, turn-1);
        turn++;
        if(turn>4) {
            turn=1;
        }    
        delay1 =0;
   }      
   
    TCNT0=0x00;
}


// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
    ++delay0;
    if(delay0 == 250){
        if(num > 9999){
            num = 0;
        } 
        num++;  
        delay0 = 0;
    }

    TCNT1H=0xFF;
    TCNT1L=0xF0;
}

void main(void)
{
    TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
    TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
    TCNT0=0x00;
    OCR0=0x00;
    TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
    TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);
    TCNT1H=0xFF;
    TCNT1L=0xF0;
    MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    MCUCSR=(0<<ISC2);   
    
    #asm("sei")    

    DDRC=0xff;
    PORTC=0xff; 
    
    DDRB=0xff;
    PORTB=0xff;

    while (1) {

    }
}
