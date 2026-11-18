#include "ffta.h"
#include "effect_task.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor;

typedef struct {
    u16 counter;
    u8 flag;
    u8 unknown_03;
    s16 x, y;
    Struct080DBD5C *coordinate_result;
    u8 unknown_0C[8];
    void *position_child;
    void *objects[2];
    void *initial_child;
    void *actor;
    void *effect_child;
    void *record_child;
} Payload;

struct Group080DD4A4;
struct Child080DD4A4;
struct PositionSourceLink;
struct FlagRecord;
struct EffectObject;
struct Struct08011058;
struct Resource080D5E80;

extern const u8 data_083A098C[];
extern const u8 data_083A09BC[];
extern const u8 data_083A09EC[];
extern const u8 data_083A0A00[];
extern const struct Resource080D5E80 data_084F6130;
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern struct Child080DD4A4 *func_080DD4A4(struct Group080DD4A4 *, u8);
extern struct PositionSourceLink *func_080DD748(struct PositionSourceLink *, s16 *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);

extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u32 func_080DD73C(const struct FlagRecord *);
/* Conditional low-halfword coordinate view, also used by matched F2FFC. */
extern u32 func_080D5E80(const struct Resource080D5E80 *, u16, s16, s16, s16, u16, u8);
extern void func_08011058(struct Struct08011058 *, s16);
extern void func_080DF8CC(void *);
extern u8 func_080D5F24(struct EffectObject **, u16);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

/* Complete 502-byte target, including its reached branch-skipped pools. */
u32 func_08106F38(void *task, Descriptor *descriptor, Payload *payload)
{
    void *actor;
    struct Child080DD4A4 *actor_object;
    u8 animation;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        animation = 4;
        if (payload->flag != 0)
            animation = 0;
        payload->initial_child = func_080E03F8(actor, data_083A098C,
            animation, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        actor_object = func_080DD4A4((struct Group080DD4A4 *)payload->actor, 0);
        payload->coordinate_result = (Struct080DBD5C *)func_080DD748(
            (struct PositionSourceLink *)actor_object, &payload->x, &payload->y, 0);
        payload->position_child = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->unknown_0C, data_083A09BC, task);
        payload->effect_child = func_080DCFE4(actor_object, data_083A09EC,
            12, 85, 4, task, 85);
        payload->record_child = func_080DFD8C(data_083A0A00, 3, 4, 0, task);
        payload->counter = 20;
        descriptor->phase++;
        break;
    case 0x101:
        payload->counter--;
        if (payload->counter != 0)
            break;
        {
            s16 x, y, z;
            func_080DBD5C(payload->coordinate_result, &x, &y, &z);
            if ((u8)func_080DD73C((const struct FlagRecord *)payload->coordinate_result))
                y += 16;
            payload->objects[0] = (void *)func_080D5E80(&data_084F6130, 0,
                x, y, z, 0x36E, 6);
            payload->objects[1] = (void *)func_080D5E80(&data_084F6130, 1,
                x, y, z, 0x36E, 6);
            func_08011058((struct Struct08011058 *)payload->objects[0], -1);
            func_08011058((struct Struct08011058 *)payload->objects[1], 1);
        }
        payload->counter = 10;
        descriptor->phase++;
        break;
    case 0x102:
        if (payload->counter != 0) {
            payload->counter--;
            if (payload->counter != 0)
                break;
            func_080DF8CC(payload->coordinate_result);
        }
        if (!func_080D5F24((struct EffectObject **)payload->objects, 2))
            break;
        payload->position_child = func_080D6134(payload->position_child);
        if (payload->position_child != 0)
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
