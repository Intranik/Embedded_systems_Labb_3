#include "timer.h"

#include <avr/io.h>

int time = 0;
int oldTime = 0;

void timer_init() {
}

void timer2_init(void) {
    // 22-10 CLOCK SELECT BIT DESCRIPTION
    // PRESCALER ÄR PÅ 1024
    TCCR2B |= (1 << CS20);
    TCCR2B |= (1 << CS21);
    TCCR2B |= (1 << CS22);
    // TABEL 22-9
    // TC2 CONTROL REGISTER A 22.11.1
    TCCR2A &= ~(1 << WGM20);
    TCCR2A |= (1 << WGM21);
    // TC2 CONTROL REGISTER B 22.11.2
    TCCR2B &= ~(1 << WGM22);

    // 1 1 Set OC2A on compare match
    TCCR2A |= (1 << COM2A0);
    TCCR2A |= (1 << COM2A1);

    OCR2A = 15;  // 16000000/1024*0.001-1= 14,625 -> 15
}