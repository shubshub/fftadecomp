#include "ffta.h"

// Target: complete [0x08107DA8, 0x081080EA), 834 bytes, 417 instructions.
typedef struct Event {
    u16 phase;
    u16 unknown_02;
    u32 argument;
    u8 *state;
    u8 unknown_0c[8];
    u16 mode;
} Event;

typedef struct Position {
    s16 x;
    s16 y;
    s16 z;
    s16 unknown_6;
} Position;

typedef struct Work {
    u8 unknown_00[6];
    u8 part;
    u8 unknown_07;
    u8 *state;
    u8 mode;
    u8 duration;
    u8 unknown_0e[2];
    u32 effect;
    s16 x[0x3c];
    s16 y[0x3c];
    s16 z[0x3c];
    Position start;
    Position end;
    u32 task;
    Struct080DBD5C *object;
    u32 actor;
    u32 unknown_198;
} Work;

extern void *func_081443FC(void *, const void *, u32);
extern u8 data_08149E9C[], data_08507114[], data_083A0ED4[];
extern Struct080DBD5C *func_080DD47C(u32);
extern s8 func_080DBC88(Struct080DBD5C *);
extern void func_080D8B7C(u32, s16 *, s16 *, s16 *);
extern u32 func_080D5E80(const void *, u16, s16, s16, s16, s16, u8);
extern void func_08010884(u32, u8);
extern void func_0801115C(u32, u8);
extern void func_0801121C(u32, s16);
extern u16 func_08141898(u32);
extern s32 func_08141870(s32, s32);
extern u32 func_080D6238(u32 *, const Position *, const Position *, u16, u16, s16 *, s16 *, s16 *, u16, u32);
extern u8 func_080D63C8(u32);
extern u8 func_080D6478(u32);
extern u32 func_080D6530(u32);
extern void func_080D5C20(u32);
extern u32 func_080DFD8C(const void *, u8, u16, u16, u32);
extern u32 func_080DD4B4(u32, u8);
extern void func_080DC0BC(u32, u8);
extern void func_080D8858(u32, u8);
extern void func_08011428(u32);

static inline void offset_position(int mode, int part, const Position *origin, Position *out)
{
    Position table[2][4];

    func_081443FC(table, data_08149E9C, sizeof(table));
    out->x = origin->x + table[part][mode].x;
    out->y = origin->y + table[part][mode].y;
    out->z = origin->z + table[part][mode].z;
}

static inline u32 create_effect(u16 mode, u16 part, const Position *origin)
{
    Position position;
    u32 effect;

    offset_position(mode, part, origin, &position);
    effect = func_080D5E80(data_08507114, 0, position.x, position.y, position.z, 0x3F7, 9);
    func_08010884(effect, 1);
    func_0801115C(effect, 0);
    func_0801121C(effect, -1);
    return effect;
}

static inline s32 distance(const Position *from, const Position *to)
{
    s16 dx = to->x - from->x;
    s16 dy = to->y - from->y;
    s16 dz = to->z - from->z;
    u32 square;
    s32 length;

    square = dx * dx;
    square += dz * dz;
    square <<= 8;
    length = func_08141898(square);
    length >>= 4;
    square = length * length;
    square += dy * dy;
    square <<= 8;
    length = func_08141898(square);
    length >>= 4;
    return length;
}

static inline u32 start_motion(u32 owner, u8 duration, u8 mode, u8 part, u32 *scene, s16 *x, s16 *y, s16 *z,
                               const Position *origin, const Position *end)
{
    Position start;
    Position target;

    offset_position(mode, part, origin, &start);
    target.x = end->x;
    target.y = end->y + 0x18;
    target.z = end->z;
    return func_080D6238(scene, &start, &target, 0x30, duration, x, y, z, 0, owner);
}

u32 func_08107DA8(u32 owner, Event *event, Work *w)
{
    switch (event->phase) {
    case 0:
        w->actor = event->argument;
        w->state = event->state;
        w->part = event->mode;
        w->object = func_080DD47C(w->actor);
        func_080DBD5C(w->object, &w->start.x, &w->start.y, &w->start.z);
        w->mode = func_080DBC88(w->object);
        func_080D8B7C(w->actor, &w->end.x, &w->end.y, &w->end.z);
        w->end.y += 0x10;
        *w->state = 0;
        break;
    case 1:
        break;
    case 0x100: {
        u8 time;

        w->effect = create_effect(w->mode, w->part, &w->start);
        time = func_08141870(distance(&w->start, &w->end), 5);
        time += 12;
        if (time < 3)
            time = 3;
        if (time > 0x3B)
            time = 0x3B;
        w->duration = time;
        w->task = start_motion(owner, w->duration, w->mode, w->part, &w->effect, w->x, w->y, w->z, &w->start, &w->end);
        event->phase++;
        break;
    }
    case 0x101:
        if (func_080D63C8(w->task)) {
            *w->state = 1;
            event->phase++;
        }
        break;
    case 0x102:
        if (*w->state == 2) {
            func_0801115C(w->effect, 1);
            func_080D5C20(w->task);
            w->unknown_198 = func_080DFD8C(data_083A0ED4, 1, 4, 0, owner);
            func_080DC0BC(func_080DD4B4(w->actor, 0), 0);
            event->phase++;
        }
        break;
    case 0x103:
        if (func_080D6478(w->task)) {
            *w->state = 3;
            func_080D8858(w->actor, 0);
            event->phase++;
        }
        break;
    case 0x104:
        w->task = func_080D6530(w->task);
        if (!w->task) {
            func_08011428(w->effect);
            w->effect = 0;
            *w->state = 4;
            event->phase = 2;
        }
        break;
    }
    return 0;
}
