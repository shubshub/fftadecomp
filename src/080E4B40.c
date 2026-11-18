#include "ffta.h"
#include "effect_task.h"

typedef struct PositionSourceLink PositionSourceLink;
typedef struct PaletteRows080D45D0 {
    u8 rows;
    u8 columns;
    u16 values[1];
} PaletteRows080D45D0;
typedef struct {
    u8 unknown_00[2];
    u8 x;
    u8 y;
} Position;
typedef struct {
    u16 state;
    u16 unknown_02;
    PositionSourceLink *source;
    u8 unknown_08[12];
    u16 flags;
    u16 variant;
} Event080E4B40;
typedef struct {
    u8 flags;
    u8 variant;
    s16 x;
    s16 y;
    u16 unknown_06;
    PositionSourceLink *position;
    PositionSourceLink *source;
    u32 result;
    void *task14;
    void *task18;
    void *task1C;
    void *task20;
    void *task24;
    void *task28;
} State080E4B40;

extern u8 data_03003920[];
extern const PaletteRows080D45D0 data_088EA2D4;
extern const Position data_088F548C;
extern const u8 data_089494E0[], data_0894A410[], data_08949528[];
extern const u8 data_08396D88[], data_08396D9C[], data_08396D70[];
extern const u8 data_0894AC90[];
extern u16 g_control_flags_03000940;
extern PositionSourceLink *func_080DD748(PositionSourceLink *, s16 *, s16 *, s16 *);
extern void func_0814186C(const void *, void *, u32);
extern void func_080D45D0(const PaletteRows080D45D0 *, u8, u8, u8, u8);
extern void func_080D7220(const Position *, u8, u8, s16, s16, u16);
extern void *func_080D4704(const void *, void *);

extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4774(void *);
extern u32 func_080035A8(u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, u32 *, const void *, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

/* Complete [0x080E4B40, 0x080E4CF4): 436 bytes. */
s32 func_080E4B40(void *context, Event080E4B40 *event, State080E4B40 *state)
{
    u16 options;

    switch (event->state) {
    case 0:
        {
            u16 zero;
            state->flags = event->flags;
            state->variant = event->variant;
            state->source = event->source;
            state->position = func_080DD748(state->source, &state->x, &state->y, 0);
            zero = 0;
            func_0814186C(&zero, data_03003920, 0x01000010);
            if (state->variant == 1)
                func_080D45D0(&data_088EA2D4, 6, 1, 1, 1);
        }
        break;
    case 2:
        break;
    case 0x100:
        func_080D7220(&data_088F548C, 0, 2, state->x, state->y, 0);
        if (state->variant == 0)
            state->task18 = func_080D4704(data_089494E0, context);
        else
            state->task18 = func_080D4704(data_0894A410, context);
        state->task1C = func_080D4704(data_08949528, context);
        if (state->flags & 1)
            options = 4;
        else
            options = 2;
        state->task24 = func_080DCFE4(state->source, data_08396D88, 12, 50,
                                      options, context, 50);
        if (state->flags & 1)
            options = 16;
        else
            options = 8;
        state->task28 = func_080DFD8C(data_08396D9C, 1,
                                      options | 4, 0, context);
        event->state++;
        break;
    case 0x101:
        state->task1C = func_080D4774(state->task1C);
        if (state->task1C == 0) {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
            state->task14 = func_080D6098(state->x, state->y, 0, 1, 1,
                                         &state->result, data_08396D70, context);
            state->task20 = func_080D4704(data_0894AC90, context);
            event->state++;
        }
        break;
    case 0x102:
        state->task18 = func_080D4774(state->task18);
        if (state->task18 != 0)
            break;
        state->task20 = func_080D4774(state->task20);
        if (state->task20 != 0)
            break;
        state->task14 = func_080D6134(state->task14);
        if (state->task14 == 0)
            event->state++;
        break;
    case 0x103:
        state->task24 = func_080DBA5C(state->task24);
        if (state->task24 == 0)
            event->state = 2;
        break;
    }
    return 0;
}
