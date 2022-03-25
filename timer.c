#include "timer.h"

#include <avr/io.h>

int time = 0;
int oldTime = 0;

void timer_init() {
    // PWM MODE
    TCCR0A &= ~(1 << COM0A0);
    TCCR0A |= (1 << COM0A1);

    TCCR0A |= (1 << WGM00);
    TCCR0A |= (1 << WGM01);
    TCCR0B &= ~(1 << CS02);

    // PRESCALER = 64 TABLE 15-9
    TCCR0B |= (1 << CS00);
    TCCR0B |= (1 << CS01);
    TCCR0B &= ~(1 << CS02);
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

    // Interrupts
    TIMSK2 |= (1 << OCIE2A);

    // 16000000/1024*0.001 -1 since it starts at index 0, to get ~10ms = 100Hz
    OCR2A = 155;
}