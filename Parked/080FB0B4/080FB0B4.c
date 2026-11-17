// Target: complete [0x080FB0B4, 0x080FB35C), 680 bytes.
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor080FB0B4;

typedef struct {
    s16 x;
    s16 y;
    u16 countdown;
    u8 flag;
    u8 ready;
    void *output;
    void *coordinate_result;
    void *object;
    void *actor;
    void *initial_child;
    void *sprite;
    void *effect;
    void *child;
    void *preparation;
    void *record_child;
} Payload080FB0B4;

extern const u8 data_0839CBB4[];
extern const u8 data_0839CBE0[];
extern const u8 data_0839CBCC[];
extern const u8 data_0839CBE4[];
extern const u8 data_08502560[];
extern const u8 data_0894848C[];
extern const u8 data_08149D78[];
extern const u8 data_08149D7C[];
extern void *func_081443FC(void *destination, const void *source, u32 bytes);

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                           u16, u16, void *);
extern void func_080DBFFC(void *, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080D8B5C(void *, s16 *, s16 *);
extern void func_080DBD78(void *, s16 *, s16 *, s16 *);
extern u8 func_0809D6BC(s8, s8);
extern void *func_080D5CC0(const void *, u8, s16, s16, u16, u8, u8, u8);
extern void func_08011118(void *, u8);
extern void *func_080DF9E4(void *, u16, u16, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DBA5C(void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DE1F0(void *);
extern void *func_080D4774(void *);
extern void *func_08011484(void *);

u32 func_080FB0B4(void *task, Descriptor080FB0B4 *descriptor,
                  Payload080FB0B4 *payload)
{
    void *actor;
    u8 animation;
    u8 status;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        animation = 2;
        if (payload->flag != 0)
            animation = 0;
        payload->initial_child = func_080E03F8(actor, data_0839CBB4,
            animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        status = func_080D3B54(payload->actor);
        if (status != 0) {
            descriptor->phase = 2;
            break;
        }
        payload->preparation = func_080DDF68(payload->actor,
            &payload->output, 0x8007, 1, &payload->ready, data_0839CBE0,
            5, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        func_080DBFFC(payload->actor, 0);
        payload->countdown = 10;
        descriptor->phase++;
    case 0x102: {
        u8 animations[4];
        u8 directions[4];
        s16 actor_x, actor_y;
        s16 target_x, target_z, target_y;
        u8 direction;

        func_081443FC(animations, data_08149D78, sizeof(animations));
        func_081443FC(directions, data_08149D7C, sizeof(directions));
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
        payload->object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->object,
            &payload->x, &payload->y, 0);
        func_080D8B5C(payload->actor, &actor_x, &actor_y);
        func_080DBD78(payload->output, &target_x, &target_z, &target_y);
        direction = func_0809D6BC(actor_x - target_x, actor_y - target_y);
        payload->sprite = func_080D5CC0(data_08502560,
            animations[direction], payload->x, payload->y,
            0x3E1, 6, 0, 1);
        func_08011118(payload->sprite, directions[direction]);
        payload->child = func_080DF9E4(payload->object, 11, 0, task);
        if (payload->child != 0) {
            payload->effect = func_080D4704(data_0894848C, task);
            payload->record_child = func_080DFD8C(data_0839CBE4, 1, 4, 0,
                task);
        }
        descriptor->phase++;
        break;
    }
    case 0x103:
        payload->child = func_080DBA5C(payload->child);
        if (payload->child != 0)
            break;
        payload->child = func_080DCFE4(payload->object, data_0839CBCC, 12,
            0, 12, task, 0);
        descriptor->phase++;
        break;
    case 0x104:
        if (func_080DE1F0(payload->output) == 0)
            break;
        payload->effect = func_080D4774(payload->effect);
        if (payload->effect != 0)
            break;
        payload->sprite = func_08011484(payload->sprite);
        if (payload->sprite != 0)
            break;
        payload->child = func_080DBA5C(payload->child);
        if (payload->child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
