#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "button.h"
#include "led.h"
#include "serial.h"
#include "timer.h"
int main() {
    DDRB &= ~(1 << PB3);  // lägg PB3 som inmatning

    DDRB &= ~(1 << PB0);  // lägg PB0 som inmatning

    DDRD &= ~(1 << PD2);  // lägg PD2 som inmatning

    // LED_init();
    uart_init();
    timer2_init();

    while (1) {
        button_debounce();  // anropa funktionen

        if (bit_is_set(TIFR2, OCF2A)) {
            time++;                // Global tid i millisekunder
            TIFR2 = (1 << OCF2A);  // återställ flaggan
        }
    }
}
