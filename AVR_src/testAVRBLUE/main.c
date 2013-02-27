/* LED flash using atmega168 designed by takefuji on sept. 22, 2009*/

#define FOSC	F_CPU
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD	9600
#define UBRR	FOSC/16/BAUD-1
#define SET_

void delay_us(double t)
{
    int tt;
    tt = 8*t/100;
    while(tt--) _delay_us(1);
}

void init_USART0(unsigned int baud)
{
    UBRR0 = baud;
    UCSR0C = (3<<UCSZ00);
    UCSR0B |= _BV(RXEN0) | _BV(TXEN0);
}

void setRXCIE_USART0()
{
    UCSR0B |= _BV(RXCIE0);
}

unsigned char receive_1byte_USART0(void)
{
    loop_until_bit_is_set(UCSR0A,RXC0);
    return UDR0;
}

void transmit_1byte_USART0(unsigned char data)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}

void transmit_str_USART0(char *str)
{
    while(*str != 0){
	transmit_1byte_USART0(*str);
	*str++;
    }
}

void Servo(unsigned char data)
{
    switch(data){
	case 49  : for(;;){
	              DDRB |= 0x20;
		      PORTB = 0x20;
		      _delay_ms(500);
		      PORTB = 0x00;
		      _delay_ms(500);
	           }
	case 'a' : DDRC |= 0x20;
	           for(;;){
		       PORTC = 0x20;
		       delay_us(1100);
		       PORTC = 0x00;
		       delay_us(18900);
		       if(bit_is_set(UCSR0A,RXC0)) break;
		   }
	case 'b'  : for(;;){
	              DDRC |= 0x20;
		      PORTB = 0x20;
		      _delay_ms(500);
		      PORTB = 0x00;
		      _delay_ms(500);
	           }/*
	case 'b' : DDRC |= 0x20;
	           for(;;){
		       PORTC = 0x20;
		       delay_us(2000);
		       PORTC = 0x00;
		       delay_us(18000);
		       if(bit_is_set(UCSR0A,RXC0)) break;
		   }
	case 'c' : DDRB |= 0x01;
	           for(;;){
		       PORTC = 0x20;
		       delay_us(1100);
		       PORTC = 0x00;
		       delay_us(18900);
		       if(bit_is_set(UCSR0A,RXC0)) break;
		   }
	case 'd' : DDRB |= 0x01;
	           for(;;){
		       PORTC = 0x20;
		       delay_us(1100);
		       PORTC = 0x00;
		       delay_us(18900);
		       if(bit_is_set(UCSR0A,RXC0)) break;
		   }
	case 'e' : DDRB |= 0x01;
	           for(;;){
		       PORTC = 0x20;
		       delay_us(1100);
		       PORTC = 0x00;
		       delay_us(18900);
		       if(bit_is_set(UCSR0A,RXC0)) break;
		   }
	case 'f' : DDRB |= 0x01;
	           for(;;){
		       PORTC = 0x20;
		       delay_us(1100);
		       PORTC = 0x00;
		       delay_us(18900);
		       if(bit_is_set(UCSR0A,RXC0)) break;
		   }
	case 'g' : DDRB |= 0x01;
	           for(;;){
		       PORTC = 0x20;
		       delay_us(1100);
		       PORTC = 0x00;
		       delay_us(18900);
		       if(bit_is_set(UCSR0A,RXC0)) break;
		   }*/
    }
}

int i;
int main (int argc, char *argv[])
{
    init_USART0(UBRR);  //initialize USART0
    sei();
    

    for(i=0;i<3;i++){
	DDRC |= 0x20;
	PORTC = 0x20;
	_delay_ms(500);
	PORTC = 0x00;
	_delay_ms(500);
    }
    while(1){
        if(receive_1byte_USART0()=='a'){
	    transmit_str_USART0("abc");
	    for(i=0;i<10;i++){
	    DDRC |= 0x20;
	    PORTC = 0x20;
	    _delay_ms(250);
	    PORTC = 0x00;
	    _delay_ms(250);
	}
    }
    }
    /*while(1){
	unsigned char data = receive_1byte_USART0();
	Servo(data);
	
    }*/
    return 0;
}

