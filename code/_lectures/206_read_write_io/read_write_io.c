#include <stdbool.h>
#include <stdint.h>

#define LED0    ((volatile bool *)0xE000U)
#define TOGGLE0 ((volatile bool *)0xC000U)

void main(void) {

    volatile bool *led0    = LED0;
    volatile bool *toggle0 = TOGGLE0;

    while (true) {
        if (*toggle0) {
            *led0 = false;
        } else {
            *led0 = true;
        }
    }
}
