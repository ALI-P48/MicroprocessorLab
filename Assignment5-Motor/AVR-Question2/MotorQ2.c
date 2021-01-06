/*******************************************************
Project : MotorQ2
Version : 1.00
Date    : 1/6/2021
Author  : Alireza Majari
Company : P48
Comments: 
This is Assignment#5 of Microprocessor Lab.
kharazmi University of Tehran


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 12.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>

int delay;
int timerStarted;
int states[4][4] = {
    {1, 0, 0, 1},
    {1, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 1}
};
int currentState;

// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
    if(timerStarted==1) {
        if(delay==0) {
            PORTA.0 = states[currentState][0];  
            PORTA.1 = states[currentState][1];
            PORTA.2 = states[currentState][2];
            PORTA.3 = states[currentState][3];
        }
        
        if(delay>5 && delay<=10) {
            PORTA = 0x00;
        }  
        
        if(delay == 10){
            delay = 0;  
            if(currentState<3) {
                ++currentState;
            } else {
                currentState=0;
                timerStarted=0;
            }
        } else {
            ++delay;
        } 

        TCNT1H=0xFF;
        TCNT1L=0xF0;
    }   
}

void main(void)
{
    //init timer1
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

    DDRC = 0x00;   
    PINC = 0x00;  
       
    DDRA = 0xff;  
    PORTA = 0x00;   
    
    delay = 0;   
    timerStarted = 0;
    currentState = 0;

    while (1) {
        if(PINC.2==0 &&  timerStarted==0) //when button is pressed once     
        { 
             delay = 0;  
             timerStarted=1;
        }
    }
}