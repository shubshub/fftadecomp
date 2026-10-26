#include "ffta.h"

/* 0x080E6D54..0x080E6E0E: 186 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
} EffectEvent;

typedef struct {
    u16 unknown_00;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *object;
    u32 position_result;
    u8 unknown_10[0x0C];
    void *first_task;
    void *second_task;
} EffectWork;

typedef struct {
    u8 unknown_00[20];
} EffectDescriptor;

extern const u8 data_083975CC[];
extern const EffectDescriptor data_08397614[];
extern u32 func_080DD748(void *object, s16 *x, s16 *y, s16 *z);
extern u8 func_080DD5A8(void *object);
extern void *func_080D6098(s16 x, s16 y, int layer, int enabled,
                           int mode, void *state, const void *descriptor,
                           void *parent);
extern void *func_080DD8C4(void *object, const EffectDescriptor *descriptor,
                           int first, int delay, int second, void *parent);
extern void *func_080D6134(void *task);
extern void *func_080DBA5C(void *object);

int func_080E6D54(void *parent, EffectEvent *event, EffectWork *work)
{
    int mode;
    int delay;

    switch (event->state) {
    case 0:
        work->object = event->object;
        work->position_result = func_080DD748(work->object, &work->x,
                                               &work->y, 0);
        mode = 1;
        delay = 0x2D;
        if (func_080DD5A8(work->object)) {
            mode = 3;
            delay = 0;
        }
        if (mode != 3) {
            work->first_task = func_080D6098(work->x, work->y, 0, 1, 3,
                                             work->unknown_10,
                                             data_083975CC, parent);
        }
        work->second_task = func_080DD8C4(work->object,
                                           &data_08397614[mode],
                                           12, delay, 12, parent);
        break;
    case 1:
        break;
    case 0x100:
        work->first_task = func_080D6134(work->first_task);
        if (!work->first_task) {
            work->second_task = func_080DBA5C(work->second_task);
            if (!work->second_task)
                event->state = 2;
        }
        break;
    }
    return 0;
}
