#include <stdbool.h>
#include <stdint.h>

#define LED0 ((volatile bool *)0xE000U)
#define LED1 ((volatile bool *)0xE001U)
#define LED3 ((volatile bool *)0xE003U)
#define COUNTER (volatile uint16_t *)0x4FF0
void delay(uint16_t n) {
    uint16_t c;
    *COUNTER = 0;
    c = 0;
    while (c < n) {
        c = c + 1;
    }
}

void main(void) {

    volatile bool *led0; 
    volatile bool *led1; 
    volatile bool *led3; 
    led0 = LED0;
    led1 = LED1;
    led3 = LED3;

    while (true) {
        *led1 = true;
        delay(1500);
        *led1 = false;

        *led3 = true;
        delay(1500);
        *led3 = false;

        *led0 = true;
        delay(1500);
        *led0 = false;

        *led3 = true;
        delay(1500);
        *led3 = false;

        *led0 = true;
        delay(1500);
        *led0 = false;

        *led3 = true;
        delay(1500);
        *led3 = false;
    }

}
