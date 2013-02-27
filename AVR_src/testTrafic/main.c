#include <avr/io.h>
#include <util/delay.h>

int servo_jr(int i);

int main(void){
    TCCR0A = 0xa3;
    TCCR0B = 0x03;
    DDRB = 0xff;
    DDRC = 0x00;
    DDRD = 0xff;

    while(1){
	OCR0A = servo_jr(30);
	_delay_ms(1000);
	OCR0A = servo_jr(60);
	_delay_ms(1000);
	OCR0A = servo_jr(30);
	_delay_ms(1000);
	OCR0A = servo_jr(60);
	_delay_ms(1000);
    }

    return 0;
}

int servo(int i){
    int a = (i/7)+8;
    return a;
}

int servo_jr(int i){
    int a = (i/6)+12;
    if(a>38)a=37;
    return a;
}
