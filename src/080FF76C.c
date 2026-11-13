// Target: complete [0x080FF76C, 0x080FF96E), 514 bytes.
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor;

typedef struct {
    u8 flag;
    u8 unknown_01;
    u16 countdown;
    s16 x, y;
    u8 ready;
    u8 unknown_09[3];
    u8 unknown_0c[4];
    void *position_child;
    void *actor;
    void *output;
    void *coordinate_result;
    void *initial_child;
    void *effect;
    void *preparation;
    void *record_child;
} Payload;

extern const u8 data_0839E3C0[];
typedef struct {
    const u8 *paths[2];
} PathPair;

extern const PathPair data_08149DD0;
extern const u8 data_0839E408[];
extern const u8 data_0839E41C[];
extern const u8 data_0839E420[][8];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern u8 func_080DC12C(void *, u8, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern u8 func_080DD580(void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern u8 func_080DE244(void *);
extern void *func_080DBA5C(void *);

u32 func_080FF76C(void *task, Descriptor *descriptor, Payload *payload)
{
    void *actor;
    void *object;
    u8 animation;
    u8 actor_status;
    u32 variant;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        animation = 2;
        if (payload->flag != 0)
            animation = 0;
        payload->initial_child = func_080E03F8(actor, data_0839E3C0,
            animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        actor_status = func_080D3B54(payload->actor);
        if (actor_status != 0) {
            descriptor->phase = 2;
            break;
        }
        payload->preparation = func_080DDF68(payload->actor,
            &payload->output, 0x8007, 1, &payload->ready, data_0839E41C,
            5, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        payload->countdown = 16;
        descriptor->phase++;
        break;
    case 0x102:
        payload->countdown--;
        if (payload->countdown != 0)
            break;
        func_080DC12C(payload->actor, 0, 2);
        payload->countdown = 16;
        descriptor->phase++;
        break;
    case 0x103: {
        PathPair pair = data_08149DD0;

        if (payload->countdown != 0) {
            payload->countdown--;
            if (payload->countdown != 0)
                break;
        }
        if (func_080D8B4C() != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(object, &payload->x,
            &payload->y, 0);
        variant = 0;
        if (func_080DD580(object) == 0)
            variant = 1;
        payload->position_child = func_080D6098(payload->x, payload->y,
            0, 1, 1, payload->unknown_0c, pair.paths[variant], task);
        payload->effect = func_080DCFE4(object, data_0839E408, 12,
            0x52, 4, task, 0x50);
        payload->record_child = func_080DFD8C(data_0839E420[variant], 1, 4,
            0, task);
        descriptor->phase++;
        break;
    }
    case 0x104:
        payload->position_child = func_080D6134(payload->position_child);
        if (payload->position_child != 0)
            break;
        if (func_080DE244(payload->output) == 0)
            break;
        payload->effect = func_080DBA5C(payload->effect);
        if (payload->effect == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
