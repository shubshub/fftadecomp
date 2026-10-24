#include "ffta.h"

typedef struct {
    void *object;
    u8 interval;
    u8 direction;
    s8 repeats;
} CycleParameters080DEBAC;

typedef struct {
    u16 state;
    u16 unknown_02;
    CycleParameters080DEBAC *parameters;
    u8 unknown_08[12];
    u16 delay;
} CycleDescriptor080DEBAC;

typedef struct {
    void *object;
    u16 delay;
    u8 interval;
    s8 initial;
    s8 current;
    u8 reload;
    u8 direction;
    s8 repeats;
    u16 action;
} CyclePayload080DEBAC;

extern s8 func_080DBC88(void *object);
extern void func_080DE12C(void *object, u16 action, s8 value);
extern void func_080DE33C(void *object, s8 value, u8 option);

/* 0x080DEBAC - 216 bytes.
 * Target: 30b50d1c141c2988012961d0012902dc002905d05ce080204000814213d057e0
 *         6a6810682060117961725179a1729179e172fdf753f8e0712072607aa071a88a
 *         0130a08044e0a088002804d00138a080000400283cd1a0790138a0710006020e
 *         002a35d1a07a002808d0217a08202056032801d122720ae0481c07e0217a0820
 *         2056002801d1032000e0481e2072a089002806d02068a1890822a256fff770fa
 *         05e02068082161560022fff771fb607aa071e27a0b21615601204042814201d0
 *         501ee0720b202056002801d102202880002030bc02bc0847
 */
u32 func_080DEBAC(void *task, void *descriptor, void *payload)
{
    CycleDescriptor080DEBAC *event = descriptor;
    CyclePayload080DEBAC *state = payload;

    switch (event->state) {
    case 0:
    {
        CycleParameters080DEBAC *parameters = event->parameters;

        state->object = parameters->object;
        state->reload = parameters->interval;
        state->direction = parameters->direction;
        state->repeats = parameters->repeats;
        state->initial = func_080DBC88(state->object);
        state->current = state->initial;
        state->interval = state->reload;
        state->delay = event->delay + 1;
        break;
    }
    case 1:
        break;
    case 0x100:
        if (state->delay != 0) {
            if (--state->delay != 0)
                break;
        }
        if (--state->interval != 0)
            break;
        if (state->direction != 0) {
            if (state->current == 3)
                state->current = 0;
            else
                state->current++;
        } else {
            if (state->current == 0)
                state->current = 3;
            else
                state->current--;
        }
        if (state->action != 0)
            func_080DE12C(state->object, state->action, state->current);
        else
            func_080DE33C(state->object, state->current, 0);
        state->interval = state->reload;
        if (state->repeats != -1)
            state->repeats--;
        if (state->repeats == 0)
            event->state = 2;
        break;
    }
    return 0;
}
