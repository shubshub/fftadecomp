#include "ffta.h"

// Target: complete [0x08125444, 0x08125560), 284 bytes, 142 instructions.
typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0x108 - 0x2A];
} SceneRecord08125444;

typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} SceneUnit08125444;

typedef struct {
    SceneUnit08125444 *unit;
    u8 unknown_04[0x2C];
    u32 flags;
} SceneObject08125444;

typedef struct {
    u8 actor;
    u8 target;
    u8 x[4];
    u8 y[4];
} Placement08125444;

extern SceneRecord08125444 g_state_02000080[24];
extern SceneRecord08125444 *func_08121CB4(u8);
extern SceneRecord08125444 *func_080C83CC(u8);
extern void *func_08096D7C(void);
extern SceneObject08125444 *func_08099560(void *, SceneRecord08125444 *);
extern void *func_08099644(void *, s8, s8);
extern u8 func_08124ACC(u8, u8, u8, u8);
extern SceneObject08125444 *func_081242A0(u32, u32, u32, u32, u32, u32, u32);

static inline SceneRecord08125444 *resolve_record(u8 selector)
{
    SceneRecord08125444 *record;
    s32 index;

    if (selector == 255) {
        record = g_state_02000080;
        for (index = 0; index < 24; index++, record++) {
            if (record->flags & 0x400)
                return record;
        }
        return 0;
    } else if ((s8)selector < 0) {
        return func_08121CB4(selector);
    } else {
        return func_080C83CC(selector);
    }
}

void func_08125444(const u8 *script)
{
    Placement08125444 p;
    SceneRecord08125444 *record;
    SceneObject08125444 *object;
    s32 i;

    p.actor = script[0];
    p.target = script[1];
    p.x[0] = script[2];
    p.y[0] = script[3];
    p.x[1] = script[4];
    p.y[1] = script[5];
    p.x[2] = script[6];
    p.y[2] = script[7];
    p.x[3] = 0;
    p.y[3] = 0;

    for (i = 0; i < 3; i++) {
        if (func_08099644(func_08096D7C(), p.x[i], p.y[i]) == 0) {
            p.x[3] = p.x[i];
            p.y[3] = p.y[i];
            break;
        }
    }

    record = resolve_record(p.target);
    object = func_08099560(func_08096D7C(), record);
    if (object == 0)
        p.target = 0;
    else
        p.target = func_08124ACC(p.x[3], p.y[3], object->unit->x, object->unit->y);

    object = func_081242A0(p.actor, p.x[3], p.y[3], p.target, 0, 0, 2);
    object->flags |= 1;
}
