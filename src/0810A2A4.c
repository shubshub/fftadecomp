#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[0x0c];
    u16 mode;
} Descriptor0810A2A4;

typedef struct {
    u8 mode;
    u8 unknown_01[3];
    s16 x;
    s16 y;
    void *actor;
    void *coordinate_result;
    u8 unknown_10[0x0c];
    void *coordinate_child;
    void *effect_child;
} Payload0810A2A4;

extern const u8 data_083A1AD4[];
extern const u8 data_083A1B1C[];
extern void *func_080DD748(void *, s16 *, s16 *, s32);
extern void *func_080D6098(s32, s32, s32, s32, s32, void *,
                         const void *, void *);
extern void *func_080DCFE4(void *, const void *, s32, s32, s32, void *, s32);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

/* 0x0810A2A4 .. 0x0810A362: 190 bytes, including two literal words. */
s32 func_0810A2A4(void *task, Descriptor0810A2A4 *descriptor,
                  Payload0810A2A4 *payload)
{
    s32 flags;

    switch (descriptor->phase) {
    case 0:
        payload->mode = descriptor->mode;
        payload->actor = descriptor->actor;
        payload->coordinate_result = func_080DD748(payload->actor,
            &payload->x, &payload->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 3, payload->unknown_10, data_083A1AD4, task);
        flags = (payload->mode & 1) ? 4 : 2;
        payload->effect_child = func_080DCFE4(payload->actor, data_083A1B1C,
            12, 30, flags | 8, task, 30);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child)
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
