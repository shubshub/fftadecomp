#include "ffta.h"

typedef struct Unit Unit;

typedef struct {
    u8 unknown_00;
    u8 kind;
    u8 handler;
    u8 variant;
} ActionRecord;

typedef struct {
    Unit *source;
    Unit *target;
    u8 unknown_08[0x28];
    ActionRecord *record;
} ActionState;

typedef s32 (*ActionEvaluator)(ActionState *state);

extern ActionState data_0200F3F0;
extern ActionEvaluator const g_table_083A86F8[];
extern s32 func_08133988(void);
extern u8 func_0812F358(void);
extern u8 func_08130868(void *unit, void *target);

/* Complete [0x08131B20, 0x08131BB6): 150 bytes, including the state,
 * evaluator-table and jump-table literals and the five-entry jump table at
 * 0x08131B74:
 * 30b5044d2868002802d06868002803d100203de0f0f300020c49286bc078800040180168
 * 281c10f07ffb041c01f01cff4443fdf701fc0006000e0138042826d88000034940180068
 * 87460000f8863a08741b1308881b1308881b13089a1b1308881b1308881b130828686968
 * fef76cfe000600280bd0002409e028686968fef763fe00060028f6d1012c00dc0224201c
 * 30bc02bc0847
 */
s32 func_08131B20(void)
{
    ActionState *state = &data_0200F3F0;
    s32 result;

    if (!state->source || !state->target)
        return 0;

    result = g_table_083A86F8[state->record->variant](state);
    result *= func_08133988();

    switch (func_0812F358()) {
    case 1:
    case 2:
    case 4:
    case 5:
        if (func_08130868(state->source, state->target))
            result = 0;
        break;
    case 3:
        if (func_08130868(state->source, state->target))
            result = 0;
        else if (result < 2)
            result = 2;
        break;
    }
    return result;
}
