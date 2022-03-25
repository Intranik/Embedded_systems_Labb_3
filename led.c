#include "led.h"

#include <avr/io.h>
#include <stdint.h>

void LED_init() {
    DDRD |= (1 << PD6);
    // DDRB &= ~(1 << PB0);  // lägg PB0 som inmatning
    // DDRB &= ~(1 << PB3);  // lägg PB3 som inmatning
    // DDRD &= ~(1 << PD2);  // lägg PD2 som inmatning
}

uint8_t simple_ramp() {
    return 1;
}
