#include "ffta.h"

/* Target: complete [0x0810DA58, 0x0810DE24), 972 bytes, 486 instructions. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 flag;
} Descriptor0810DA58;

typedef struct {
    u16 unknown_00;
    u16 unknown_02;
    s16 *first;
    s16 *second;
    u8 *state;
    u32 unknown_10;
    u16 index;
    u16 kind;
    u32 unknown_18;
} Child0810DA58;

typedef struct {
    u8 flag;
    u8 alternate;
    u16 timer;
    s16 x;
    s16 y;
    u8 unknown_08;
    u8 states[3];
    u8 ready;
    u8 unknown_0d[3];
    s16 first[2];
    s16 second[2];
    void *children[3];
    u8 unknown_24[12];
    void *effect;
    void *actor;
    void *output;
    void *first_object;
    void *position;
    void *second_object;
    void *loading;
    void *animation;
    void *preparation;
    void *record;
} Payload0810DA58;

typedef struct {
    u8 unknown_00[20];
} AnimationEntry0810DA58;

typedef u32 (*TaskCallback)(void *task, void *request, void *payload);

extern const u8 data_083A2800[];
extern const u8 data_083A28FC[];
extern const u8 data_083A2900[];
extern const u8 data_08149F30[];
extern const u8 data_083A2848[];
extern const u8 data_083A2908[];
extern const AnimationEntry0810DA58 data_083A28C0[];
extern const u8 data_083A2910[];
extern const u8 data_083A2878[];
extern const u8 data_083A2918[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                          u16, u16, void *);
extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD4C4(void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *,
                          void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DD580(void *);
extern void func_080DBDA0(void *, s16 *, s16 *, s16 *);
extern u32 func_0810D728(void *task, void *request, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);
extern u16 func_0801BB0C(s16, s16, u16);
extern void *func_080D6134(void *);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern s8 func_080DD5A8(void *);
extern u8 func_080E0570(void **, u16);
extern void *func_080DBA5C(void *);

u32 func_0810DA58(void *task, Descriptor0810DA58 *descriptor,
                  Payload0810DA58 *payload)
{
    Child0810DA58 child;
    u8 kinds[3];
    s16 x, y, z;
    u8 animation;
    u8 status;
    u16 size;
    const u8 *table;
    u8 mode;
    u8 i;
    u8 variant;
    u16 delay;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        animation = 6;
        if (payload->flag != 0)
            animation = 0;
        if (descriptor->flags & 2)
            payload->alternate = 1;
        payload->loading = func_080E03F8(payload->actor, data_083A2800,
            animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->loading = func_080E05DC(payload->loading);
        if (payload->loading != 0)
            break;
        status = func_080D3B54(payload->actor);
        if (status != 0) {
            descriptor->phase = 2;
            break;
        }
        size = 0x54;
        table = data_083A28FC;
        mode = 1;
        if (payload->alternate) {
            size = 0x34;
            table = data_083A2900;
            mode = 2;
        }
        payload->preparation = func_080DDF68(payload->actor, &payload->output,
            size, mode, &payload->ready, table, 0, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        func_081443FC(kinds, data_08149F30, sizeof(kinds));
        if (payload->ready == 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 0x104;
            break;
        }
        payload->first_object = func_080DD4A4(payload->actor, 1);
        payload->second_object = func_080DD4A4(payload->actor, 0);
        payload->position = func_080DD4C4(payload->second_object);
        func_080DBDC8(payload->position, &x, &y);
        payload->effect = func_080D6098(x, y, 0, 1, 2, payload->unknown_24,
            data_083A2848, task);
        payload->record = func_080DFD8C(data_083A2908, 1, 4, 0, task);
        payload->animation = func_080DCFE4(payload->second_object,
            data_083A28C0, 12, 0x29, 2, task, 0x29);
        if (func_080DD580(payload->first_object) == 0) {
            descriptor->phase = 0x104;
            break;
        }
        func_080DBDA0(payload->position, &x, &y, &z);
        payload->first[0] = x;
        payload->first[1] = y - 12;
        func_080DBDA0(payload->output, &x, &y, &z);
        payload->second[0] = x;
        payload->second[1] = y - 12;
        child.first = payload->first;
        child.second = payload->second;
        for (i = 0; i < 3; i++) {
            child.state = &payload->states[i];
            child.index = i;
            child.kind = kinds[i];
            payload->children[i] = func_08005B6C(func_0810D728, 0xCC, &child,
                task);
        }
        payload->timer = 20;
        descriptor->phase++;
        break;
    case 0x102:
        if (payload->timer != 0) {
            payload->timer--;
            if (payload->timer != 0)
                break;
        }
        if (payload->states[0] == 0)
            break;
        if (payload->states[1] == 0)
            break;
        if (payload->states[2] == 0)
            break;
        payload->record = func_080DFD8C(data_083A2910, 1, 4, 0, task);
        {
            u8 j;

            for (j = 0; j < 3; j++)
                payload->states[j] = 2;
        }
        func_0801BB0C(payload->second[0] - 0x78, payload->second[1] - 0x60,
            0x28);
        descriptor->phase++;
        break;
    case 0x103:
        payload->effect = func_080D6134(payload->effect);
        if (payload->effect != 0)
            break;
        if (payload->states[0] != 3)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 0x104;
            break;
        }
        payload->position = func_080DD748(payload->second_object, &payload->x,
            &payload->y, 0);
        variant = 1;
        delay = 0x2A;
        if (func_080DD5A8(payload->first_object)) {
            variant = 2;
            delay = 0;
        }
        payload->animation = func_080DCFE4(payload->first_object,
            &data_083A28C0[variant], 12, delay, 10, task, 20);
        if (func_080DD580(payload->second_object) && variant == 1) {
            s16 target_x, target_y;

            func_080DBDC8(payload->output, &target_x, &target_y);
            payload->effect = func_080D6098(target_x, target_y, 0, 1, 3,
                payload->unknown_24, data_083A2878, task);
            payload->record = func_080DFD8C(data_083A2918, 1, 4, 0, task);
        }
        descriptor->phase++;
        break;
    case 0x104:
        if (func_080E0570(payload->children, 3) == 0)
            break;
        payload->effect = func_080D6134(payload->effect);
        if (payload->effect != 0)
            break;
        payload->animation = func_080DBA5C(payload->animation);
        if (payload->animation == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
