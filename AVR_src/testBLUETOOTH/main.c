#define FOSC	F_CPU
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <inttypes.h>

#define BAUD	9600
#define UBRR	FOSC/16/BAUD-1
#define SET_

static void (*rx_interrupt_handler)(void);

void delay_us(double t)
{
    int tt;
    tt = 8*t/100;
    while(tt--) _delay_us(1);
}

ISR(USART_RX_vect)
{
    rx_interrupt_handler();
}

void usart_set_rx_interrupt(void(*func)(void))
{
    rx_interrupt_handler = func;
}

void init_USART0(unsigned int baud)
{
    UBRR0 = baud;
    UCSR0C = (3<<UCSZ00);
    UCSR0B |= _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);
}

unsigned char receive_1byte_USART0(void)
{
    loop_until_bit_is_set(UCSR0A,RXC0);
    if((UCSR0A & _BV(FE0)) || (UCSR0A & _BV(DOR0))){
	return -1;
    }

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
	str++;
    }
}

void Servo(unsigned char data)
{
    switch(data){
	case 'a' : OCR1A = 33;
	           break;

	case 'b' : OCR1A = 38;
	           break;

	case 'c' : OCR1A = 41;
	           break;

	case 'd' : OCR1A = 47;
	           break;
	
	case 'e' : OCR1A = 52;
	           break;

	case 'f' : OCR1A = 57;
	           break;

	case 'g' : OCR1A = 59;
	           break;
    }
}

static void rx_interrupt(void)
{
    unsigned char recv_data = receive_1byte_USART0();
    char buf[20] = "Received data = \n";
    int index = 16;
    if(recv_data == -1){
	transmit_str_USART0("Unknown data...\n");
	return;
    }

    buf[index] = recv_data;
    transmit_str_USART0(buf);
    Servo(recv_data);
}

int main (int argc, char *argv[])
{
    init_USART0(UBRR);  //initialize USART0
    usart_set_rx_interrupt(rx_interrupt);
    sei();
    
    TCCR1A = 0b10000010;
    TCCR1B = 0b00011100;  // 256bunshu
    ICR1 = 624;
    DDRB = 0xff;
    DDRC = 0x00;
    DDRD = 0xff;

    while(1){
	sleep_mode();
    }
    
    return 0;

}
