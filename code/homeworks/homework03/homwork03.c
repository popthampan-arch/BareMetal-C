#include <stdbool.h>
#include <stdint.h>

#define SWITCH_BASE 0xC010
#define LED    0xE000

int main(void)
{
    volatile unsigned char *switches = (unsigned char *)SWITCH_BASE;
    volatile unsigned char *led = (unsigned char *)LED;

    unsigned char target[8] = {0, 1, 0, 0, 0, 0, 1, 0};

    int match = 1;

    for (int i = 0; i < 8; i++)
    {
        if (switches[i] != target[i])
        {
            match = 0;
            break;
        }
    }

    if (match)
        *led = 1;
    else
        *led = 0;

    while (1);
}
