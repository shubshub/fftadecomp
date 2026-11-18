#include "ffta.h"
#include "effect_task.h"

/* Complete 1092-byte target, 446 reached instructions. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[12];
    s16 kind;
    u16 variant;
} Descriptor;

typedef struct LineState {
    s32 x, y, endX, endY;
    s32 stepX, stepY, deltaX, deltaY;
    s32 accumulator, error, remaining;
} LineState;

typedef struct {
    u8 kind;
    u8 index;
    u8 variant;
    u8 unknown_03;
    u16 countdown;
    s16 x, y;
    u8 unknown_0a[6];
    void *actor;
    Struct080DBD5C *coordinate_result;
    void *sprite;
    u8 unknown_1c[8];
    void *position_child;
    void *objects[2];
    void *auxiliary;
    void *timed_child;
    void *script;
    void *initial_child;
    void *extra_effect;
    void *effect;
    void *record_child;
    LineState motion;
} Payload;

typedef struct {
    u8 unknown_00[20];
} EffectConfig;

struct PaletteRows080D45D0;
struct Group080DD4A4;
struct Child080DD4A4;
struct PositionSourceLink;
struct Resource080D5E80;
struct Struct08011058;
struct EffectObject;

extern const u8 data_08396A2C[];
extern const void *data_08396A24[];
extern const struct PaletteRows080D45D0 data_088EA7F0;
extern const u8 data_088ED538[];
extern u16 g_control_flags_03000940;
extern const u8 data_08948D48[];
extern const u8 data_0894D69C[];
extern const u8 data_08396AC8[];
extern const EffectConfig data_08396AA0[];
extern const void *data_08396AFC[];
extern const u8 data_08396A98[];
extern const void *data_08396A90[];
extern const struct Resource080D5E80 data_084F6130;
extern const u8 data_0894ABA0[];
extern const u8 data_08396A9A[];
extern const u8 data_088F46F0[];
extern const u8 data_08948D70[];
extern const u8 data_0894A458[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void func_080D45D0(const struct PaletteRows080D45D0 *, u8, u8, u8, u8);
extern u8 func_080D8858(void *, u16);
extern struct Child080DD4A4 *func_080DD4A4(struct Group080DD4A4 *, u8);
extern struct PositionSourceLink *func_080DD748(struct PositionSourceLink *, s16 *, s16 *, s16 *);
extern void func_080075CC(LineState *, s32, s32, s32, s32);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void func_0800BDA4(void *, u8);
extern u32 func_080035A8(u8);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void func_080D3F84(void *, u8, u8);
extern u8 func_080DD684(const void *, u8);
extern void *func_080DF90C(void *, u32, void *);

extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u32 func_08007880(const void *);
extern void func_080076A0(LineState *);
extern void *func_080D3F08(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
/* Observed signed coordinate view; the defining helper uses their low halves. */
extern u32 func_080D5E80(const struct Resource080D5E80 *, u16, s16, s16, s16, u16, u8);
extern void func_08011058(struct Struct08011058 *, s16);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080D4774(void *);
extern void func_080D4D14(void *, u8);
/* D7220 narrows the coordinate inputs before its subtraction. */
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern u8 func_080D5F24(struct EffectObject **, u16);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080E41E4(void *task, Descriptor *descriptor, Payload *payload)
{
    void *actor;
    struct Child080DD4A4 *object;
    u8 animation;

    switch (descriptor->phase) {
    case 0:
        {
            u16 kind = descriptor->kind;
            if (descriptor->kind != 0x66) {
                payload->kind = kind - 6;
                payload->index = kind - 6;
            } else {
                payload->kind = 2;
                payload->index = 0;
            }
        }
        payload->variant = descriptor->variant;
        actor = descriptor->actor;
        payload->actor = actor;
        animation = data_08396A2C[payload->index];
        if (payload->variant != 0)
            animation = 0;
        if (payload->kind != 2)
            payload->initial_child = func_080E03F8(actor,
                data_08396A24[payload->index], animation, 1, 0, task);
        else
            payload->initial_child = func_080E03F8(actor,
                data_08396A24[0], animation, 7, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (payload->kind == 2) {
            func_080D45D0(&data_088EA7F0, 6, 1, 5, 1);
            func_080D45D0(&data_088EA7F0, 7, 1, 5, 1);
        }
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4((struct Group080DD4A4 *)payload->actor, 0);
        payload->coordinate_result = (Struct080DBD5C *)func_080DD748(
            (struct PositionSourceLink *)object, &payload->x, &payload->y, 0);
        func_080075CC(&payload->motion, payload->y - 40, 0, payload->y - 16, 71);
        func_080D49FC(0, 2, 0, payload->x, (s16)payload->motion.x);
        payload->sprite = func_080D4B64(0, data_088ED538, 0x3E3, 6);
        func_0800BDA4(payload->sprite, 1);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->auxiliary = func_080D4704(data_08948D48, task);
        payload->script = func_080D3E9C(data_0894D69C, task);
        func_080D3F84(payload->script, 12, 0xFF);
        {
            u8 alternate = 1;
            if (func_080DD684(object, 0))
                alternate = 0;
            if (alternate == 0)
                payload->extra_effect = func_080DF90C(payload->coordinate_result,
                    data_08396AC8[payload->index], task);
            payload->effect = func_080DCFE4(object, &data_08396AA0[alternate],
                12, data_08396AC8[payload->index], 2, task,
                data_08396AC8[payload->index]);
        }
        payload->record_child = func_080DFD8C(data_08396AFC[payload->index],
            2, 4, 0, task);
        payload->countdown = 65;
        descriptor->phase++;
        break;
    case 0x101:
        if (func_08007880(&payload->motion) == 0) {
            func_080076A0(&payload->motion);
            func_0800BC08(0, payload->x, (s16)payload->motion.x);
        }
        payload->script = func_080D3F08(payload->script);
        payload->countdown--;
        if (payload->countdown != 0)
            break;
        payload->position_child = func_080D6098(payload->x, payload->y,
            0, 1, data_08396A98[payload->index], payload->unknown_1c,
            data_08396A90[payload->index], task);
        {
            s16 x, y, z;
            func_080DBD5C(payload->coordinate_result, &x, &y, &z);
            payload->objects[0] = (void *)func_080D5E80(&data_084F6130,
                2, x, y, z, 0x39F, 6);
            payload->objects[1] = (void *)func_080D5E80(&data_084F6130,
                3, x, y, z, 0x39F, 6);
            func_08011058((struct Struct08011058 *)payload->objects[0], -1);
            func_08011058((struct Struct08011058 *)payload->objects[1], 1);
        }
        payload->timed_child = func_080D4724(data_0894ABA0, task,
            data_08396A9A[payload->kind]);
        descriptor->phase++;
        break;
    case 0x102:
        payload->auxiliary = func_080D4774(payload->auxiliary);
        if (payload->auxiliary != 0)
            break;
        func_080D4D14(payload->sprite, 0);
        payload->sprite = 0;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        func_080D7220(data_088F46F0, 1, 3, payload->x, payload->y, 0);
        if (payload->kind != 2)
            payload->auxiliary = func_080D4704(data_08948D70, task);
        else
            payload->auxiliary = func_080D4704(data_0894A458, task);
        descriptor->phase++;
        break;
    case 0x103:
        {
            u8 finished = func_080D5F24((struct EffectObject **)payload->objects, 2) != 0;
            payload->position_child = func_080D6134(payload->position_child);
            if (payload->position_child != 0)
                finished = 0;
            if (finished == 0)
                break;
        }
        payload->auxiliary = func_080D4774(payload->auxiliary);
        if (payload->auxiliary != 0)
            break;
        payload->timed_child = func_080D4774(payload->timed_child);
        if (payload->timed_child != 0)
            break;
        {
            u32 mask = func_080035A8(3);
            g_control_flags_03000940 &= ~mask;
        }
        descriptor->phase++;
        break;
    case 0x104:
        payload->extra_effect = func_080DBA5C(payload->extra_effect);
        if (payload->extra_effect != 0)
            break;
        payload->effect = func_080DBA5C(payload->effect);
        if (payload->effect != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
