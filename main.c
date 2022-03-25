#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "button.h"
#include "led.h"
#include "serial.h"
#include "timer.h"

// global variabel
volatile uint8_t ADC_Value = 0;

ISR(ADC_vect) {
    ADC_Value = ADCH;
}
ISR(TIMER2_COMPA_vect) {
    ADCSRA |= (1 << ADSC);
    OCR0A = ADC_Value;
}

int main() {
    DDRB &= ~(1 << PB3);  // lägg PB3 som inmatning
    DDRB &= ~(1 << PB0);  // lägg PB0 som inmatning
    DDRD &= ~(1 << PD2);  // lägg PD2 som inmatning

    LED_init();
    uart_init();
    timer2_init();
    timer_init();

    // ADC
    DDRC &= ~(1 << PC0);
    ADMUX |= (1 << ADLAR);
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADPS0);
    ADCSRA |= (1 << ADPS1);
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADIE);

    sei();
    while (1) {
        button_debounce();  // anropa funktionen

        if (bit_is_set(TIFR2, OCF2A)) {
            time++;                // Global tid i millisekunder
            TIFR2 = (1 << OCF2A);  // återställ flaggan
        }
    }
}
