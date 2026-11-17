#include "ffta.h"

// Target: 0x081074D8..0x0810781A, 834 bytes, 417 instructions.
// Callback of func_08005B6C created by func_0810781C (state size 0x19c).
// Local access views; original declaration types and extents are unknown.
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 *status;
    u32 unknown_0c;
    u32 unknown_10;
    u16 variant;
} Event081074D8;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Place081074D8;

typedef struct {
    u16 unknown_00;
    u16 unknown_02;
    u16 unknown_04;
    u8 variant;
    u8 unknown_07;
    u8 *status;
    u8 facing;
    u8 duration;
    u8 unknown_0e[2];
    void *object;
    s16 path_x[60];
    s16 path_y[60];
    s16 path_z[60];
    Place081074D8 base;
    Place081074D8 target;
    void *motion;
    Struct080DBD5C *actor_object;
    void *actor;
    void *sequence;
} State081074D8;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 unknown_06;
} Entry081074D8;

extern const u8 data_08149E5C[];
extern const u8 data_08507114[];
extern const u8 data_083A0D20[];

// Prototypes describe the argument values used at these call sites.
extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void *func_080DD47C(void *);
extern u8 func_080DBC88(void *);
extern void func_080D8B7C(void *, u16 *, u16 *, u16 *);
extern void *func_080D5E80(const void *, u16, s16, s16, s16, u16, u8);
extern void func_08010884(void *, u8);
extern void func_0801115C(void *, u8);
extern void func_0801121C(void *, int);
extern u16 func_08141898(u32);
extern s32 func_08141870(s32, s32);
extern void *func_080D6238(void *, const Place081074D8 *,
                           const Place081074D8 *, u16, u16, s16 *, s16 *,
                           s16 *, u16, void *);
extern u8 func_080D63C8(void *);
extern u8 func_080D6478(void *);
extern void *func_080D6530(void *);
extern void func_080D5C20(void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DD4B4(void *, u8);
extern void func_080DC0BC(void *, u8);
extern u8 func_080D8858(void *, u16);
extern void func_08011428(void *);

static inline void place(u8 facing, u8 variant, Place081074D8 *base,
                         Place081074D8 *out)
{
    Entry081074D8 table[2][4];

    func_081443FC(table, data_08149E5C, sizeof(table));
    out->x = base->x + table[variant][facing].x;
    out->y = base->y + table[variant][facing].y;
    out->z = base->z + table[variant][facing].z;
}

static inline void *launch(u8 duration, u8 facing, u8 variant, void *object,
                           s16 *x, s16 *y, s16 *z, Place081074D8 *base,
                           Place081074D8 *target, void *task)
{
    Place081074D8 from;
    Place081074D8 to;

    place(facing, variant, base, &from);
    to.x = target->x;
    to.y = target->y + 0x18;
    to.z = target->z;
    return func_080D6238(object, &from, &to, 0x30, duration, x, y, z, 0, task);
}

static inline u8 travel(Place081074D8 *to, Place081074D8 *from)
{
    s32 dx;
    s16 dy;
    s32 dz;
    s32 square;
    u16 dist;
    u8 v;

    dx = to->x - from->x;
    dy = to->y - from->y;
    dz = to->z - from->z;
    square = (s16)dx * (s16)dx;
    square += (s16)dz * (s16)dz;
    square <<= 8;
    dist = func_08141898(square) >> 4;
    square = dist * dist;
    square += dy * dy;
    square <<= 8;
    dist = func_08141898(square) >> 4;
    v = func_08141870(dist, 5);
    v += 12;
    if (v < 3)
        v = 3;
    if (v > 0x3b)
        v = 0x3b;
    return v;
}

static inline void *create(u8 facing, u8 variant, Place081074D8 *base)
{
    Place081074D8 pos;
    void *obj;

    place(facing, variant, base, &pos);
    obj = func_080D5E80(data_08507114, 0, pos.x, pos.y, pos.z, 0x3e9, 6);
    func_08010884(obj, 1);
    func_0801115C(obj, 0);
    func_0801121C(obj, -1);
    return obj;
}

u32 func_081074D8(void *task, Event081074D8 *event, State081074D8 *state)
{
    switch (event->phase) {
    case 0:
        state->actor = event->actor;
        state->status = event->status;
        state->variant = event->variant;
        state->actor_object = func_080DD47C(state->actor);
        func_080DBD5C(state->actor_object, (s16 *)&state->base.x,
                      (s16 *)&state->base.y, (s16 *)&state->base.z);
        state->facing = func_080DBC88(state->actor_object);
        func_080D8B7C(state->actor, &state->target.x, &state->target.y,
                      &state->target.z);
        state->target.y += 0x20;
        *state->status = 0;
        break;
    case 1:
        break;
    case 0x100:
        state->object = create(state->facing, state->variant, &state->base);
        state->duration = travel(&state->target, &state->base);
        state->motion = launch(state->duration, state->facing, state->variant,
                               &state->object, state->path_x, state->path_y,
                               state->path_z, &state->base, &state->target,
                               task);
        event->phase++;
        break;
    case 0x101:
        if (func_080D63C8(state->motion)) {
            *state->status = 1;
            event->phase++;
        }
        break;
    case 0x102:
        if (*state->status == 2) {
            func_0801115C(state->object, 1);
            func_080D5C20(state->motion);
            state->sequence = func_080DFD8C(data_083A0D20, 1, 4, 0, task);
            func_080DC0BC(func_080DD4B4(state->actor, 0), 0);
            event->phase++;
        }
        break;
    case 0x103:
        if (func_080D6478(state->motion)) {
            *state->status = 3;
            func_080D8858(state->actor, 0);
            event->phase++;
        }
        break;
    case 0x104:
        state->motion = func_080D6530(state->motion);
        if (state->motion == 0) {
            func_08011428(state->object);
            state->object = 0;
            *state->status = 4;
            event->phase = 2;
        }
        break;
    }
    return 0;
}
