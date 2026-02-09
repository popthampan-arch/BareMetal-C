#include <stdint.h>
#include <stdbool.h>

#define VIEW_LIGHT0  ((volatile uint8_t * const)0xE000U)
#define VIEW_LIGHT1  ((volatile uint8_t * const)0xE001U)
#define VIEW_LIGHT2  ((volatile uint8_t * const)0xE002U)
#define VIEW_LIGHT3  ((volatile uint8_t * const)0xE003U)

#define VIEW_DECIMAL ((volatile uint8_t * const)0xE800U)

#define BTN_MINUS    ((volatile uint8_t * const)0xD006U)
#define BTN_PLUS     ((volatile uint8_t * const)0xD007U)
#define BTN_LEFT     ((volatile uint8_t * const)0xD004U)
#define BTN_RIGHT    ((volatile uint8_t * const)0xD005U)

typedef struct {
    bool light;
    uint8_t period;
    uint8_t count;
    uint8_t position;
} model_t;

typedef enum {
    NONE,
    PLUS,
    MINUS,
    LEFT,
    RIGHT
} command;

void model_init(model_t *m)
{
    m->light = false;
    m->period = 35U;
    m->count = 0U;
    m->position = 0U;
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
    else if (cmd == LEFT)
    {
        if (m->position == 0U)
            m->position = 3U;
        else
            m->position--;
    }
    else if (cmd == RIGHT)
    {
        if (m->position == 3U)
            m->position = 0U;
        else
            m->position++;
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

    *VIEW_LIGHT0 = 0U;
    *VIEW_LIGHT1 = 0U;
    *VIEW_LIGHT2 = 0U;
    *VIEW_LIGHT3 = 0U;

    if (m->light)
    {
        if (m->position == 0U) *VIEW_LIGHT0 = 1U;
        else if (m->position == 1U) *VIEW_LIGHT1 = 1U;
        else if (m->position == 2U) *VIEW_LIGHT2 = 1U;
        else *VIEW_LIGHT3 = 1U;
    }

    tens = m->period / 10U;
    ones = m->period % 10U;
    bcd = (tens << 4) | ones;

    *VIEW_DECIMAL = bcd;
}

command controller_read(void)
{
    if (*BTN_PLUS)  return PLUS;
    if (*BTN_MINUS) return MINUS;
    if (*BTN_LEFT)  return LEFT;
    if (*BTN_RIGHT) return RIGHT;

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
