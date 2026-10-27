#include "ffta.h"

/* 0809D128 .. 0809D2F8: 464 bytes. */
typedef struct {
    s8 x;
    s8 y;
    u8 value;
    u8 unknown_03;
} PathStep;

typedef struct {
    u8 unknown_00[0xFC];
    u8 type;
    u8 subtype;
    s8 x;
    s8 y;
} UnitData;

typedef struct {
    UnitData *data;
    u8 unknown_04[0x18];
    u8 flags;
    u8 unknown_1D[2];
    u8 height;
    u8 unknown_20[0x60];
    void *object;
} PathUnit;

typedef struct {
    PathUnit *unit;
    PathStep *steps;
    u8 unknown_08[0x10];
    u16 count;
    u16 progress;
    u16 current;
    u16 settings[4];
    u8 unknown_26;
    s8 height;
    u8 mode;
    u8 flags;
    u8 unknown_2A[0xB2];
    u16 special;
    u16 unknown_DE;
    u8 unknown_E0[0x44];
} PathWork;

typedef struct {
    PathUnit *unit;
    PathWork *work;
    PathStep steps[24];
    u8 count;
    u8 unknown_69[3];
    u16 active;
    u8 unknown_6E[0x46];
} PathSlot;

typedef struct {
    u32 unknown_00;
    u8 flags;
    u8 unknown_05[3];
    PathSlot slots[13];
} PathState;

extern void *func_08022840(u32);
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern void (*data_0836D4BC[])(void *, const void *, u32);
extern u8 func_0809A53C(PathUnit *);
extern void func_0809836C(PathUnit *, s32, s32, s32);
extern void func_0809A570(PathUnit *, s32, s32);
extern s32 func_0809B014(PathUnit *, PathStep *, s32, s32, s32);
extern s32 func_08148A98(PathStep *, s32);
extern s32 func_08099644(void *, s32, s32);

static inline PathSlot *find_free_slot(PathState *state)
{
    s32 index;
    for (index = 0; index < 13; index++) {
        if (state->slots[index].unit == 0)
            return &state->slots[index];
    }
    return 0;
}

static inline void initialize_work(PathWork *work, PathUnit *unit,
                                   PathStep *steps, s32 count)
{
    s32 index;

    work->unit = unit;
    work->steps = steps;
    work->count = count;
    work->special = 0;
    work->progress = 0;
    work->settings[0] = 2;
    work->settings[1] = 3;
    work->settings[2] = 4;
    work->settings[3] = 2;
    work->current = 2;
    work->unknown_26 = 0;
    work->unit->flags |= 4;
    work->mode = func_0809A53C(work->unit);
    if (work->mode != 0)
        work->mode--;
    work->height = work->unit->height;
    func_0809836C(work->unit, 11, work->height, 0);
    func_0809A570(work->unit, 0, 2);
    work->flags &= ~2;
    if (unit->data->type == 2 && unit->data->subtype != 5 &&
        func_0809B014(unit, steps, count, unit->data->x, unit->data->y)) {
        work->special = 1;
        work->count = func_08148A98(steps, count);
        for (index = 1; index < count - 1; index++) {
            if (func_08099644(unit->object, steps[index].x, steps[index].y))
                steps[index].value++;
        }
        work->flags |= 2;
    }
}

void func_0809D128(PathState *state, PathUnit *unit,
                   const PathStep *steps, s32 count)
{
    PathSlot *slot = find_free_slot(state);

    slot->unit = unit;
    if (slot->work == 0) {
        PathWork *work = func_08022840(sizeof(PathWork));
        g_callbacks_0836D4B8[0](work, sizeof(PathWork));
        work->unknown_DE = 0;
        slot->work = work;
    }
    state->flags |= 1;
    data_0836D4BC[0](slot->steps, steps, count * sizeof(PathStep));
    slot->count = count;
    g_callbacks_0836D4B8[0](&slot->active, 0x48);
    initialize_work(slot->work, slot->unit, slot->steps, slot->count);
    slot->active = 1;
}
