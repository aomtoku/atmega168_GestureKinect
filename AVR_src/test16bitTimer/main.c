#include <avr/io.h>
#include <util/delay.h>

int main(void){
    TCCR1A = 0b10000010;
    TCCR1B = 0b00011100;
    ICR1 = 624;
    DDRB = 0xff;
    DDRC = 0x00;
    DDRD = 0xff;

    while(1){
	OCR1A = 36;
	_delay_ms(1000);
	OCR1A = 57;
	_delay_ms(1000);
	OCR1A = 36;
	_delay_ms(1000);
	OCR1A = 57;
	_delay_ms(1000);
    }

    return 0;
}

