#include "ffta.h"
#include "effect_task.h"

/* Complete 846-byte target, 361 reached instructions. */
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
    u8 unknown_0c[16];
    void *position_child;
    void *objects[3];
    void *actor;
    void *output;
    Struct080DBD5C *coordinate_result;
    void *resource_child;
    void *initial_child;
    void *special_effect;
    void *alternate_effect;
    void *preparation;
    void *record_child;
} Payload;

struct Group080DD4A4;
struct Child080DD4A4;
struct PositionSourceLink;
struct FlagRecord;
struct Resource080D5E80;
struct Struct08011058;
struct EffectObject;

extern const u8 data_0839E468[];
extern const u8 data_0839E504[];
extern const u8 data_0839E4A4[];
extern const u8 data_0894ABA0[];
extern const u8 data_0839E508[];
extern u8 data_0600F9E0[];
extern u8 data_06005800[];
extern const struct Resource080D5E80 data_084F6130;
extern const struct Resource080D5E80 data_084FF2AC;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern u8 func_080DC12C(void *, u8, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern struct Child080DD4A4 *func_080DD4A4(struct Group080DD4A4 *, u8);
extern struct PositionSourceLink *func_080DD748(struct PositionSourceLink *,
                                               s16 *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D4724(const void *, void *, u16);
extern u8 func_080DD580(void *);
extern void *func_080DFA70(void *, u32, u32, u32, u32, u32, void *, void *,
                         u32, u32, void *);

extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4774(void *);
extern u32 func_080DD73C(const struct FlagRecord *);
/* Conditional low-halfword coordinate view, as in matched 08106F38. */
extern u32 func_080D5E80(const struct Resource080D5E80 *, u16,
                        s16, s16, s16, u16, u8);
extern void func_08011058(struct Struct08011058 *, s16);
extern u8 func_080D5F24(struct EffectObject **, u16);
extern void *func_080D6134(void *);
extern u8 func_080DE244(void *);
extern void *func_080DBA5C(void *);

u32 func_080FF970(void *task, Descriptor *descriptor, Payload *payload)
{
    void *actor;
    struct Child080DD4A4 *object;
    u8 animation;
    u8 actor_status;
    u8 busy;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        animation = 5;
        if (payload->flag != 0)
            animation = 0;
        payload->initial_child = func_080E03F8(actor, data_0839E468,
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
            &payload->output, 0x8007, 1, &payload->ready, data_0839E504,
            5, actor_status, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        payload->countdown = 20;
        descriptor->phase++;
        break;
    case 0x102:
        payload->countdown--;
        if (payload->countdown != 0)
            break;
        func_080DC12C(payload->actor, 0, 2);
        payload->countdown = 20;
        descriptor->phase++;
        break;
    case 0x103:
        if (payload->countdown != 0) {
            payload->countdown--;
            if (payload->countdown != 0)
                break;
        }
        busy = func_080D8B4C();
        if (busy != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4((struct Group080DD4A4 *)payload->actor, 0);
        payload->coordinate_result = (Struct080DBD5C *)func_080DD748(
            (struct PositionSourceLink *)object, &payload->x, &payload->y, 0);
        payload->position_child = func_080D6098(payload->x, payload->y,
            0, 1, 4, payload->unknown_0c, data_0839E4A4, task);
        payload->resource_child = func_080D4724(data_0894ABA0, task, 20);
        if (func_080DD580(object)) {
            payload->special_effect = func_080DFA70(payload->coordinate_result,
                2, 6, 7, 0x347, 0x340, data_0600F9E0, data_06005800,
                0x46, busy, task);
        } else {
            payload->alternate_effect = func_080DCFE4(object, 0, 12,
                0, 2, task, 0x46);
        }
        payload->record_child = func_080DFD8C(data_0839E508, 2, 4, 0, task);
        payload->countdown = 20;
        descriptor->phase++;
        break;
    case 0x104:
        if (payload->countdown != 0) {
            payload->countdown--;
            if (payload->countdown != 0)
                break;
        }
        payload->resource_child = func_080D4774(payload->resource_child);
        if (payload->resource_child != 0)
            break;
        {
            s16 x, y, z;
            func_080DBD5C(payload->coordinate_result, &x, &y, &z);
            if ((u8)func_080DD73C((const struct FlagRecord *)payload->coordinate_result))
                y += 16;
            payload->objects[0] = (void *)func_080D5E80(&data_084F6130, 4,
                x, (s16)(y - 16), z, 0x39F, 6);
            payload->objects[1] = (void *)func_080D5E80(&data_084FF2AC, 0,
                x, y, z, 0x359, 6);
            payload->objects[2] = (void *)func_080D5E80(&data_084F6130, 5,
                x, (s16)(y - 16), z, 0x39F, 6);
            func_08011058((struct Struct08011058 *)payload->objects[0], -1);
            func_08011058((struct Struct08011058 *)payload->objects[1], -1);
            func_08011058((struct Struct08011058 *)payload->objects[2], 1);
        }
        descriptor->phase++;
        break;
    case 0x105:
        if (!func_080D5F24((struct EffectObject **)payload->objects, 3))
            break;
        payload->position_child = func_080D6134(payload->position_child);
        if (payload->position_child != 0)
            break;
        if (func_080DE244(payload->output) == 0)
            break;
        payload->alternate_effect = func_080DBA5C(payload->alternate_effect);
        if (payload->alternate_effect != 0)
            break;
        payload->special_effect = func_080DBA5C(payload->special_effect);
        if (payload->special_effect != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
