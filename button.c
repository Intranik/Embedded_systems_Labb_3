#include "button.h"

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "timer.h"

int button_debounce() {  // vi är i ett avstudsningsfat

    if (bit_is_set(PIND, PD2)) {
        if (oldTime == 0) {
            oldTime = time;  // updaterar
            printf("pushed\r\n");
        }
    } else if (oldTime != 0 && (time - oldTime) > 10) {
        oldTime = 0;
        printf("released\r\n");
    }
}
