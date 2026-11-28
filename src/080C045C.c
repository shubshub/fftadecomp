#include "ffta.h"

/* Complete target [0x080C045C, 0x080C127C): 3616 bytes, 1405 instructions.
 *
 * The step function of the module whose state lives at 0x020101F8 (caller
 * func_080C1438; set up by func_080C034C, which pushes phase 0 and starts at
 * phase 9 or 11).  One phase per call, switched on the halfword at +0x54F4;
 * the jump table at 0x080C048C lists the cases in source order 11, 12, 9, 10,
 * 0 .. 8, 13.  Returns 0 once the module is finished, 1 otherwise.
 *
 *   9/10  build a 16x16 tile map, six tiles per call, then pop the phase
 *   0-2   build the candidate lists for both sides
 *   3-5   run a position search for every candidate choice
 *   6/7   pick the destination when no search found a position
 *   8     commit the result to the unit, or return 0
 *   11-13 restore a saved command set (the reverse of func_080C17C8)
 */

typedef struct {
    u8 unknown_00[0x1C];
    u16 unknown_1C;
    u8 unknown_1E[0xF6 - 0x1E];
    u8 x;
    u8 y;
} Unit080C045C;

typedef struct {
    Unit080C045C *unit;
    u8 unknown_04[0x7C];
    void *collection;
} Context080C045C;

typedef struct {
    u16 action;
    u16 parameter;
} Action080C045C;

typedef struct {
    Action080C045C action;
    u8 unknown_04[8];
    s16 score;
    u8 unknown_0E[3];
    u8 flags;
    u8 unknown_12[2];
} Choice080C045C;

typedef struct {
    Context080C045C *unit;
    Choice080C045C choices[40];
    u16 count;
} Candidate080C045C;

typedef struct {
    Candidate080C045C candidates[13];
    u16 count;
} Side080C045C;

typedef struct {
    u8 x;
    u8 y;
    u8 height;
    u8 unknown_03;
} Position080C045C;

typedef struct {
    Context080C045C *actor;
    Context080C045C *target;
    u16 action;
    u16 unit_value;
    u8 unknown_0C[0x1AC - 0xC];
    u8 start_x;
    u8 start_y;
    u8 end_x;
    u8 end_y;
    u8 direction;
    u8 has_position;
    u8 has_candidate;
    u8 candidate_x;
    u8 candidate_y;
    u8 candidate_end_x;
    u8 candidate_end_y;
    u8 unknown_1B7[0x200 - 0x1B7];
    void *small_buffer;
    Position080C045C *positions;
    u8 unknown_208[0x21C - 0x208];
} Search080C045C;

typedef u8 (*Evaluator080C045C)(Search080C045C *search, void *work);

typedef struct {
    u16 state;
    u16 count;
    u16 entries[(0x553C - 0x54F8) / 2];
} Phase080C045C;

typedef struct {
    void *object;
    Context080C045C *context;
    Context080C045C *units[13];
    Context080C045C *other_units[13];
    u16 unit_count;
    u16 other_unit_count;
    Side080C045C sides[2];
    Evaluator080C045C evaluator;
    Search080C045C search;
    u8 side;
    u8 choice;
    u8 candidate;
    u8 flags;
    u8 unknown_54B0;
    u8 unknown_54B1;
    u8 unknown_54B2;
    u8 unknown_54B3;
    u8 x;
    u8 y;
    u8 candidate_x;
    u8 candidate_y;
    u8 candidate_end_x;
    u8 candidate_end_y;
    u8 direction;
    u8 unknown_54BB;
    u8 unknown_54BC;
    u8 unknown_54BD;
    u16 action;
    u16 unknown_54C0;
    u16 unknown_54C2;
    u16 unknown_54C4;
    u16 unknown_54C6;
    u16 unknown_54C8;
    u8 saved_x;
    u8 saved_y;
    u8 values[4];
    u8 mode : 4;
    u8 next : 4;
    u8 unknown_54D1_lo : 4;
    u8 unknown_54D1_hi : 4;
    u8 unknown_54D2_lo : 4;
    u8 unknown_54D2_hi : 4;
    u8 unknown_54D3_lo : 4;
    u8 unknown_54D3_hi : 4;
    u8 unknown_54D4_lo : 4;
    u8 unknown_54D4_hi : 4;
    u8 unknown_54D5[3];
    u16 field_54D8;
    u16 field_54DA;
    u16 field_54DC;
    u16 field_54DE;
    u8 unknown_54E0[4];
    u8 commands[4];
    u8 command_count;
    u8 unknown_54E9[3];
    u8 *map;
    s8 scan_x;
    s8 scan_y;
    u8 unknown_54F2[2];
    Phase080C045C phase;
} State080C045C;

typedef void (*BufferInitializer080C045C)(void *destination, u32 size);
typedef void (*BufferCopier080C045C)(void *destination, const void *source, u32 size);

extern BufferInitializer080C045C const g_callbacks_0836D4B8[];
extern BufferCopier080C045C const data_0836D4BC[];

extern void *func_08022840(u32 size);
extern void func_08022854(void *object);
extern s32 func_08099F58(Context080C045C *context, s8 x, s8 y, u8 range);
extern s32 func_08099FB0(Context080C045C *context, s32 x, s32 y);
extern int func_0809A604(Context080C045C *context, u8 x, u8 y, u8 range,
                         Position080C045C *positions);
extern void *func_080BDAFC(void);
extern void func_080BDB18(void *workspace);
extern void func_080BDBAC(void *workspace);
extern s8 func_080BE9F0(Side080C045C *side, Context080C045C *excluded, s8 x, s8 y);
extern Evaluator080C045C func_080C01D0(Search080C045C *search, Context080C045C *source,
                                       Context080C045C *target, Side080C045C *group,
                                       Side080C045C *other_group, Action080C045C *selection,
                                       u8 side, u8 *map, u8 alternate);
extern void func_080C2940(void *object, u8 first, u8 second, Side080C045C *side);
extern u8 func_080C32C0(Unit080C045C *unit, Unit080C045C *target, Choice080C045C *choice,
                        u8 flag);
extern void *func_080C47A8(Context080C045C *context);
extern u8 func_080C47FC(void *object);
extern void func_080C480C(void *object);
extern s16 func_080C4830(void *object, Context080C045C **output);
extern s16 func_080C486C(void *object, Context080C045C **output);
extern void *func_080C5398(Context080C045C *owner, Context080C045C *unit,
                           Context080C045C **units, u16 count,
                           Context080C045C **other_units, u16 other_count);
extern void func_080C53F8(void *object);
extern void func_080C5420(void *object, u8 first, u8 second);
extern void func_080C5428(void *object, u8 *x, u8 *y);
extern u8 func_080C5434(void *object);
extern u8 func_080C5438(void *object);
extern void func_080C7610(u8 *values);
extern u8 func_080C7638(void);
extern u8 func_080C8298(Unit080C045C *unit);
extern u8 func_080C9540(u16 flag);
extern s32 func_080CA3EC(const void *unit);
extern u32 func_080CCD50(u16 index, u8 selector);
extern s16 func_0812ED98(Unit080C045C *unit, u16 entry);
extern u8 func_0812F0E4(Unit080C045C *unit, s8 x, s8 y);

/* The same tile lookup as func_080BF5A4 and func_080BE074 (src/080BF5A4.c,
 * src/080BE074.c). */
static inline u8 *tile_at(u8 *map, s8 x, s8 y)
{
    return map + (y << 4) + x;
}

/* Picks the tile to move to: the last reachable tile func_0809A604 lists near
 * (x, y), or the unit's own tile when it lists none.  Phases 6 and 7 both use
 * it; the ROM repeats the block at 0x080C0DB2..0x080C0E38 and at
 * 0x080C0F5A..0x080C0FCC, has no other copy and no out-of-line one, and the
 * block written out at both sites compiles to 3584 bytes. */
static inline void choose_destination(Context080C045C *context, u8 x, u8 y,
                                      u8 *out_x, u8 *out_y)
{
    Position080C045C *positions = func_08022840(0x1000);
    int count = func_0809A604(context, x, y, (u32)func_080CA3EC(context->unit) / 10, positions);

    if (count <= 0) {
        *out_x = context->unit->x;
        *out_y = context->unit->y;
    } else {
        *out_x = positions[count - 1].x;
        *out_y = positions[count - 1].y;
    }
    func_08022854(positions);
}

u8 func_080C045C(State080C045C *state)
{
    s32 i;
    Search080C045C *search;
    Phase080C045C *phase;
    u16 cost;

    switch (state->phase.state) {
    case 11:
        func_080C7610(state->values);
        state->phase.state = 12;
        break;
    case 12:
        if (func_080C7638())
            break;
        state->x = state->unknown_54D1_lo;
        state->y = state->unknown_54D1_hi;
        state->unknown_54B2 = state->unknown_54D2_lo;
        state->unknown_54B3 = state->unknown_54D2_hi;
        state->direction = state->mode;
        state->action = state->field_54D8;
        state->unknown_54BB = state->unknown_54D4_lo;
        state->unknown_54C0 = state->field_54DA;
        state->unknown_54B0 = state->unknown_54D3_lo;
        state->unknown_54B1 = state->unknown_54D3_hi;
        state->unknown_54C2 = state->field_54DC;
        state->unknown_54C4 = state->field_54DE;
        data_0836D4BC[0](state->commands, state->values, 4);
        state->command_count = state->next;
        state->commands[state->command_count++] = 0;
        state->phase.state = 13;
        break;
    case 9:
        state->map = func_08022840(0x100);
        g_callbacks_0836D4B8[0](state->map, 0x100);
        state->scan_x = 0;
        state->scan_y = 0;
        state->phase.state = 10;
        break;
    case 10:
        for (i = 0; i < 6; i++) {
            if (func_08099FB0(state->context, state->scan_x, state->scan_y)) {
                *tile_at(state->map, state->scan_x, state->scan_y) = 2;
                if (!func_0812F0E4(state->context->unit, state->scan_x, state->scan_y))
                    *tile_at(state->map, state->scan_x, state->scan_y) |= 0x80;
            } else if (func_08099F58(state->context, state->scan_x, state->scan_y, 0xFF)) {
                *tile_at(state->map, state->scan_x, state->scan_y) = 1;
                if (!func_0812F0E4(state->context->unit, state->scan_x, state->scan_y))
                    *tile_at(state->map, state->scan_x, state->scan_y) |= 0x80;
            }
            if (++state->scan_x > 15) {
                state->scan_y++;
                state->scan_x = 0;
                if (state->scan_y > 15) {
                    /* Pop the phase, as func_080C5F94 pops its queue; agbcc
                     * moves this to the end (0x080C1248, reached by the far
                     * branch at 0x080C0706). */
                    phase = &state->phase;
                    phase->state = phase->entries[--phase->count];
                    break;
                }
            }
        }
        break;
    case 0:
        state->unknown_54BB = 0;
        state->unknown_54BC = 0;
        state->object = func_080C47A8(state->context);
        state->phase.state = 1;
        break;
    case 1:
        if (func_080C47FC(state->object))
            break;
        state->phase.state = 2;
        break;
    case 2:
        func_080C2940(state->object, 8, 1, &state->sides[1]);
        func_080C2940(state->object, 0x87, 0, &state->sides[0]);
        state->unit_count = func_080C486C(state->object, state->units);
        state->other_unit_count = func_080C4830(state->object, state->other_units);
        func_080C480C(state->object);
        /* The ROM keeps this store (0x080C07B4) ahead of the new workspace. */
        state->object = 0;
        state->object = func_080BDAFC();
        state->phase.state = 3;
        break;
    case 3:
        if (state->choice >= state->sides[state->side].candidates[state->candidate].count
            || !func_080C32C0(state->context->unit,
                              state->sides[state->side].candidates[state->candidate].unit->unit,
                              &state->sides[state->side].candidates[state->candidate]
                                   .choices[state->choice],
                              (state->flags >> 3) & 1)) {
            g_callbacks_0836D4B8[0](&state->search, sizeof(state->search));
            state->phase.state = 5;
            break;
        }
        if (state->side == 0) {
            if (state->sides[state->side].candidates[state->candidate]
                    .choices[state->choice].score >= 0) {
                g_callbacks_0836D4B8[0](&state->search, sizeof(state->search));
                state->phase.state = 5;
                break;
            }
        } else {
            if (state->sides[state->side].candidates[state->candidate]
                    .choices[state->choice].score <= 0) {
                g_callbacks_0836D4B8[0](&state->search, sizeof(state->search));
                state->phase.state = 5;
                break;
            }
        }
        func_080BDBAC(state->object);
        state->evaluator = func_080C01D0(
            &state->search, state->context,
            state->sides[state->side].candidates[state->candidate].unit,
            &state->sides[state->side ? 1 : 0],
            &state->sides[state->side ? 0 : 1],
            &state->sides[state->side].candidates[state->candidate]
                 .choices[state->choice].action,
            state->side == 0, state->map, (state->flags >> 6) & 1);
        state->phase.state = 4;
        break;
    case 4:
        if (state->evaluator(&state->search, state->object))
            break;
        search = &state->search;
        if (search->positions) {
            func_08022854(search->positions);
            search->positions = 0;
        }
        if (search->small_buffer) {
            func_08022854(search->small_buffer);
            search->small_buffer = 0;
        }
        /* fall through */
    case 5:
        if (!state->search.has_position) {
            if (state->search.has_candidate && !(state->flags & 1)) {
                state->flags |= 1;
                state->candidate_x = state->search.candidate_x;
                state->candidate_y = state->search.candidate_y;
                state->candidate_end_x = state->search.candidate_end_x;
                state->candidate_end_y = state->search.candidate_end_y;
            }
            state->choice++;
            if (state->choice >= state->sides[state->side].candidates[state->candidate].count) {
                state->choice = 0;
                state->candidate++;
                if (state->candidate >= state->sides[state->side].count) {
                    state->candidate = 0;
                    if (++state->side > 1) {
                        state->side = 0;
                        func_080BDB18(state->object);
                        state->object = 0;
                        state->phase.state = 6;
                        break;
                    }
                }
            }
            state->phase.state = 3;
            break;
        }
        func_080BDB18(state->object);
        state->object = 0;
        state->x = state->search.start_x;
        state->y = state->search.start_y;
        state->unknown_54B2 = state->search.end_x;
        state->unknown_54B3 = state->search.end_y;
        state->direction = state->search.direction;
        state->action = state->search.action;
        state->unknown_54C0 = state->search.unit_value;
        state->flags |= 0x10;
        state->direction = func_080BE9F0(&state->sides[1], state->context, state->x, state->y);
        if (state->flags & 8) {
            state->phase.state = 8;
            break;
        }
        state->command_count = 0;
        if (*(u16 *)&state->search.start_x == *(u16 *)&state->context->unit->x) {
            if (!func_080C9540(3))
                state->commands[state->command_count++] = 3;
            /* Copied again after the call: 0x080C0C50..0x080C0C5E. */
            state->unknown_54B2 = state->search.end_x;
            state->unknown_54B3 = state->search.end_y;
            if ((state->flags & 0x40) || func_080C9540(4)) {
                state->commands[state->command_count++] = 0;
                state->phase.state = 8;
                break;
            }
            if (!func_080C9540(3)) {
                state->commands[state->command_count++] = 4;
                state->phase.state = 8;
                break;
            }
            state->phase.state = 6;
            break;
        }
        if (state->flags & 0x40) {
            state->commands[state->command_count++] = 0;
        } else {
            state->commands[state->command_count++] = 2;
            if (!func_080C9540(3))
                state->commands[state->command_count++] = 3;
            state->commands[state->command_count++] = 0;
        }
        state->phase.state = 8;
        break;
    case 6:
        if (state->flags & 8) {
            state->phase.state = 8;
            break;
        }
        state->command_count = 0;
        if (state->flags & 0x40) {
            state->direction = func_080BE9F0(&state->sides[1], state->context,
                                             state->context->unit->x, state->context->unit->y);
            state->commands[state->command_count++] = 0;
            state->phase.state = 8;
            break;
        }
        if (state->flags & 1) {
            choose_destination(state->context, state->candidate_x, state->candidate_y,
                               &state->x, &state->y);
            state->direction = func_080BE9F0(&state->sides[1], state->context,
                                             state->x, state->y);
            if (*(u16 *)&state->context->unit->x != *(u16 *)&state->x)
                state->commands[state->command_count++] = 2;
            state->commands[state->command_count++] = 0;
            state->phase.state = 8;
            break;
        }
        state->object = func_080C5398(state->context,
                                      state->sides[state->side].candidates[0].unit,
                                      state->units, state->unit_count,
                                      state->other_units, state->other_unit_count);
        if (func_080C8298(state->context->unit))
            func_080C5420(state->object, 5, 0xFF);
        else
            func_080C5420(state->object, 4, 0xFF);
        state->phase.state = 7;
        break;
    case 7:
        if (func_080C5438(state->object))
            break;
        func_080C5428(state->object, &state->x, &state->y);
        state->direction = func_080C5434(state->object);
        func_080C53F8(state->object);
        state->object = 0;
        choose_destination(state->context, state->x, state->y, &state->x, &state->y);
        state->direction = func_080BE9F0(&state->sides[1], state->context, state->x, state->y);
        /* Both arms keep their own final push: 0x080C1000 and 0x080C1044. */
        if (*(u16 *)&state->x == *(u16 *)&state->context->unit->x) {
            state->commands[state->command_count++] = 0;
        } else {
            state->commands[state->command_count++] = 2;
            state->commands[state->command_count++] = 0;
        }
        state->phase.state = 8;
        break;
    case 8:
        {
            u8 x = state->context->unit->x;
            u8 y = state->context->unit->y;
            u8 swap;

            state->context->unit->x = state->saved_x;
            state->context->unit->y = state->saved_y;
            state->context->unit->unknown_1C = state->unknown_54C8;
            if (state->flags & 8) {
                if (state->action == 0 || !func_080CCD50(state->action, 0x13)
                    || !(state->flags & 0x10)) {
                    state->action = state->unknown_54C6;
                    state->unknown_54B2 = state->unknown_54B0;
                    state->unknown_54B3 = state->unknown_54B1;
                    return 0;
                }
                state->unknown_54C2 = state->unknown_54C6;
                state->unknown_54C4 = state->action;
                swap = state->unknown_54B0;
                state->unknown_54B0 = state->unknown_54B2;
                state->unknown_54B2 = swap;
                swap = state->unknown_54B1;
                state->unknown_54B1 = state->unknown_54B3;
                state->unknown_54B3 = swap;
                state->x = x;
                state->y = y;
                state->action = 0x21;
                return 0;
            }
        }
        if (!(state->flags & 4) || state->action == 0 || !(state->flags & 0x10)
            || !func_080CCD50(state->action, 0x13))
            return 0;
        state->flags |= 0x40;
        /* The cost is narrowed to a halfword first (0x080C11AC). */
        cost = func_0812ED98(state->context->unit, state->action);
        state->context->unit->unknown_1C -= cost;
        state->unknown_54C6 = state->action;
        state->unknown_54B0 = state->unknown_54B2;
        state->unknown_54B1 = state->unknown_54B3;
        state->context->unit->x = state->x;
        state->context->unit->y = state->y;
        state->flags &= ~0x10;
        state->search.has_position = 0;
        state->search.has_candidate = 0;
        state->flags |= 8;
        state->object = func_080BDAFC();
        state->flags &= ~1;
        state->phase.state = 5;
        break;
    case 13:
        return 0;
    }
    return 1;
}
