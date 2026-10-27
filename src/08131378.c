#include "ffta.h"

typedef struct {
    u8 unknown_00[0xD6];
    u16 resource;
    u8 unknown_D8[0x1E];
    s8 column;
    s8 row;
} Unit;

typedef struct {
    u8 unknown_00;
    u8 kind;
    u8 handler;
} ActionRecord;

typedef struct {
    Unit *source;
    Unit *target;
    void *unknown_08;
    u16 action_id;
    u16 equipment_id;
    u8 unknown_10[0x20];
    ActionRecord *record;
} ActionState;

typedef u8 (*ActionHandler)(ActionState *state);
extern ActionState data_0200F3F0;
extern ActionHandler const data_083A8678[];
extern u8 func_0812F2CC(Unit *source, Unit *target, u8 kind);
extern s32 func_0812F124(Unit *unit);
extern u8 func_08133A58(const Unit *unit, s32 kind);
extern s32 func_080CA7A4(u16 equipment_id, u8 selector);
extern u32 func_080CCD50(u16 action_id, u8 selector);
extern u16 func_0812E6A4(const Unit *unit);
extern u8 func_0812F0E4(const Unit *unit, s8 column, s8 row);
extern u8 func_080CDA64(const Unit *unit);

/* 0x08131378..0x08131474: 252 bytes; check and evaluate an action. */
u8 func_08131378(void)
{
    ActionState *state = &data_0200F3F0;
    u32 category;
    u8 result;

    if (!func_0812F2CC(state->source, state->target, state->record->kind))
        return 0;
    if (state->record->kind == 0x4A && !func_0812F124(state->target))
        return 0;
    if (!func_08133A58(state->target, state->record->kind))
        return 0;

    if (state->equipment_id == 0)
        category = 0x11;
    else
        category = func_080CA7A4(state->equipment_id, 3);
    if ((func_080CCD50(state->action_id, 3) == 1 &&
         (category == 13 || category == 14)) ||
        func_080CCD50(state->action_id, 3) == 3) {
        u16 identifier = func_0812E6A4(state->target);

        if (func_0812F0E4(state->target, state->target->column,
                          state->target->row) && identifier == 6 &&
            !func_080CCD50(state->action_id, 0x11))
            return 0;
    }
    if (state->record->kind == 7 && state->target->resource == 0)
        return 0;

    result = data_083A8678[data_0200F3F0.record->handler](&data_0200F3F0);
    if (result && func_080CDA64(state->target))
        result = 100;
    return result;
}
