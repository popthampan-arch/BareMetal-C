#include <stdint.h>
#include <stdbool.h>

#define VIEW_LIGHT   ((volatile uint8_t * const)0xE000U)
#define VIEW_DECIMAL ((volatile uint8_t * const)0xE800U)

#define BTN_MINUS    ((volatile uint8_t * const)0xD006U)
#define BTN_PLUS     ((volatile uint8_t * const)0xD007U)

typedef struct {
    bool light;         
    uint8_t period;     
    uint8_t count;      
} model_t;

typedef enum {
    NONE,
    PLUS,
    MINUS
} command;

void model_init(model_t *m)
{
    m->light = false;
    m->period = 35U;  
    m->count = 0U;
}

void model_update(model_t *m, command cmd)
{

    if (cmd == PLUS)
    {
        if (m->period < 95U)
            m->period += 5U;
    }
    else if (cmd == MINUS)
    {
        if (m->period > 5U)
            m->period -= 5U;
    }

    m->count++;

    if (m->count >= m->period)
    {
        m->count = 0U;
        m->light = !m->light;
    }
}


void view_update(const model_t *m)
{
    uint8_t tens, ones, bcd;

    *VIEW_LIGHT = m->light ? 1U : 0U;

    tens = m->period / 10U;
    ones = m->period % 10U;
    bcd = (tens << 4) | ones;

    *VIEW_DECIMAL = bcd;
}

command controller_read(void)
{
    if (*BTN_PLUS)
        return PLUS;

    if (*BTN_MINUS)
        return MINUS;

    return NONE;
}

void main(void)
{
    model_t model;
    command cmd;

    model_init(&model);

    while (true)
    {
        cmd = controller_read();
        model_update(&model, cmd);
        view_update(&model);
    }
}
