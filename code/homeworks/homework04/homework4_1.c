#include <stdint.h>
#include <stdbool.h>
#include "baremetal_delay.h"

#define DELAY (3000)

#define VIEW_DECIMAL ((volatile uint8_t * const)0xE800U)

void view_update(uint8_t value)
{
    uint8_t tens;
    uint8_t ones;
    uint8_t bcd;

    if (value > 99U)
    {
        *VIEW_DECIMAL = 0xEEU;
    }
    else
    {
        tens = value / 10U;
        ones = value % 10U;

        bcd = (tens << 4) | ones;
        *VIEW_DECIMAL = bcd;
    }
}

void main(void)
{
    while (true)
    {
        *VIEW_DECIMAL = 0x93U;
        baremetal_delay(DELAY);

        *VIEW_DECIMAL = 0x45U;
        baremetal_delay(DELAY);

        *VIEW_DECIMAL = 0x26U;
        baremetal_delay(DELAY);

        view_update(93);
        baremetal_delay(DELAY);

        view_update(45);
        baremetal_delay(DELAY);

        view_update(26);
        baremetal_delay(DELAY);
    }
}
