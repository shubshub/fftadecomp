#include "ffta.h"

/* Target 0x080FE234, complete [0x080FE234, 0x080FE2E6), 178 bytes. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor_object;
} Descriptor080FE234;

typedef struct {
    u16 unknown_00;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *actor_object;
    void *coordinate_result;
    u8 unknown_10[8];
    void *position_task;
    void *effect_task;
    void *sound_task;
} Payload080FE234;

struct Data080FE234;
extern const struct Data080FE234 data_0839D874;
extern const struct Data080FE234 data_0839D8A4;
extern const struct Data080FE234 data_0839D8C0;

extern void *func_080DD748(void *, s16 *, s16 *, s32);
extern void *func_080D6098(s16, s16, s16, u8, u16, void *,
                         const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080FE234(void *task, Descriptor080FE234 *descriptor,
                  Payload080FE234 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->actor_object = descriptor->actor_object;
        payload->coordinate_result = func_080DD748(payload->actor_object,
            &payload->x, &payload->y, 0);
        payload->position_task = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->unknown_10, &data_0839D874, task);
        payload->effect_task = func_080DCFE4(payload->actor_object,
            &data_0839D8A4, 12, 20, 2, task, 20);
        payload->sound_task = func_080DFD8C(&data_0839D8C0, 1, 4, 0, task);
        break;
    case 1:
        break;
    case 0x100:
        payload->position_task = func_080D6134(payload->position_task);
        if (payload->position_task != 0)
            break;
        payload->effect_task = func_080DBA5C(payload->effect_task);
        if (payload->effect_task != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
