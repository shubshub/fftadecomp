#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[0x0c];
    u16 index;
} Descriptor080FC444;

typedef struct {
    u8 index;
    u8 unknown_01[3];
    s16 x;
    s16 y;
    void *coordinate_task;
    void *actor;
    u8 unknown_10[8];
    void *position_task;
    void *effect_task;
} Payload080FC444;

extern const u8 data_0839D394[];
extern const u8 data_0839D3D0[];
extern void *func_080DD748(void *, s16 *, s16 *, s32);
extern void *func_080D6098(s32, s32, s32, s32, s32, void *,
                         const void *, void *);
extern void *func_080DCFE4(void *, const void *, s32, s32, s32, void *, s32);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

/* 0x080FC444 .. 0x080FC502: 190 bytes, including two literal words. */
s32 func_080FC444(void *task, Descriptor080FC444 *descriptor,
                  Payload080FC444 *payload)
{
    s32 flags;

    switch (descriptor->phase) {
    case 0:
        payload->index = descriptor->index;
        payload->actor = descriptor->actor;
        payload->coordinate_task = func_080DD748(payload->actor,
                                                &payload->x, &payload->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        payload->position_task = func_080D6098(payload->x, payload->y, 0, 1,
                                              2, payload->unknown_10,
                                              data_0839D394, task);
        flags = (payload->index & 1) ? 4 : 2;
        payload->effect_task = func_080DCFE4(payload->actor, data_0839D3D0,
                                           12, 0, flags | 8,
                                           task, 0);
        descriptor->phase++;
        break;
    case 0x101:
        payload->position_task = func_080D6134(payload->position_task);
        if (payload->position_task)
            break;
        payload->effect_task = func_080DBA5C(payload->effect_task);
        if (payload->effect_task)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
