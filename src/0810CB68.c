#include "ffta.h"

/* 0x0810CB68 .. 0x0810CC44: 220 bytes, including literal pools. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 unknown_0c;
    u32 unknown_10;
    u16 mode;
} Descriptor0810CB68;

typedef struct {
    u16 unknown_00;
    u8 mode;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *actor;
    void *position;
    u32 effect_state;
    void *coordinate_effect;
    void *actor_effect;
    void *record;
} Payload0810CB68;

extern const u8 data_083A2650[];
extern const u8 data_083A267C[];
extern const u8 data_083A2668[];

extern void *func_080DD748(void *actor, s16 *x, s16 *y, int mode);
extern u8 func_080DD580(void *actor);
extern void *func_080D6098(int x, int y, int a3, int a4, int a5,
                         u32 *state, const void *data, void *owner);
extern void *func_080DFD8C(const void *data, int a2, int a3, int a4,
                         void *owner);
extern void *func_080DCFE4(void *actor, const void *data, int a3, int a4,
                         int a5, void *owner, int a7);
extern void *func_080D6134(void *effect);
extern void *func_080DBA5C(void *effect);

int func_0810CB68(void *owner, Descriptor0810CB68 *descriptor,
                  Payload0810CB68 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        void *actor;
        payload->mode = descriptor->mode;
        actor = descriptor->actor;
        payload->actor = actor;
        payload->position = func_080DD748(actor, &payload->x,
                                          &payload->y, 0);
        break;
    }
    case 0x100:
        if (func_080DD580(payload->actor)) {
            payload->coordinate_effect = func_080D6098(
                payload->x, payload->y, 0, 1, 1, &payload->effect_state,
                data_083A2650, owner);
            payload->record = func_080DFD8C(data_083A267C, 1, 20, 20, owner);
        }
        payload->actor_effect = func_080DCFE4(payload->actor, data_083A2668,
                                             12, 0, 34, owner, 10);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_effect = func_080D6134(payload->coordinate_effect);
        if (payload->coordinate_effect == 0)
            descriptor->phase++;
        break;
    case 0x102:
        payload->actor_effect = func_080DBA5C(payload->actor_effect);
        if (payload->actor_effect == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
