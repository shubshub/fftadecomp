#include "ffta.h"
#include "effect_task.h"

typedef struct Task0810B25C Task0810B25C;
typedef struct Object0810B25C Object0810B25C;
typedef struct Position0810B25C Position0810B25C;
typedef struct Sprite0810B25C Sprite0810B25C;
typedef struct Resource0810B25C Resource0810B25C;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    Object0810B25C *input;
    u8 unknown_08[4];
    u32 flags;
    u8 unknown_10[6];
    u16 option;
} Request0810B25C;

typedef struct {
    s16 x;
    s16 y;
    u8 unknown_04[2];
    u8 option;
    u8 special;
    u8 ready_first;
    u8 ready_second;
    u8 unknown_0A[2];
    Position0810B25C *overlay;
    Position0810B25C *position;
    Object0810B25C *selected;
    Object0810B25C *input;
    Task0810B25C *opening;
    u8 ready_motion;
    u8 unknown_21[3];
    Task0810B25C *motion;
    Sprite0810B25C *graphics;
    Task0810B25C *scene;
    Task0810B25C *text;
    Task0810B25C *overlay_task;
    Task0810B25C *effect;
} State0810B25C;

extern const u8 data_083A1EC4[];
extern const u8 data_083A1EE8[];
extern const u8 data_083A1F00[];
extern const u8 data_083A1F14[];
extern const u8 data_083A1F1C[];
extern const u8 data_083A1F24[];
extern const Resource0810B25C data_088F1D9C;
extern const u8 data_0894D69C[];
extern u16 g_control_flags_03000940;

/* Conditional local call views follow the saved complete entries' incoming
 * consumption and this owner's transport; they assert no helper effects. */
/* 035A8 returns the zero-extended table halfword in the full R0 word;
 * published callers consume it as a word-sized control mask. */
extern u32 func_080035A8(u8);
extern void func_080D38B4(void);
extern u8 func_080D3B54(Object0810B25C *);
extern Task0810B25C *func_080D3E9C(const void *, Task0810B25C *);
extern Task0810B25C *func_080D3F08(Task0810B25C *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern Sprite0810B25C *func_080D4B64(u8, const Resource0810B25C *, u16, u8);
extern Sprite0810B25C *func_080D4D2C(Sprite0810B25C *, u8);
extern Task0810B25C *func_080D6098(s16, s16, u16, u8, u16, u8 *, const void *, Task0810B25C *);
extern Task0810B25C *func_080D6134(Task0810B25C *);
extern u8 func_080D8858(Object0810B25C *, u16);
extern Task0810B25C *func_080DBA5C(Task0810B25C *);
extern void func_080DBDC8(Position0810B25C *, s16 *, s16 *);

extern u32 func_080DD4A4(Object0810B25C *, u8);
extern Position0810B25C *func_080DD748(Object0810B25C *, s16 *, s16 *, s16 *);
extern Task0810B25C *func_080DDF68(Object0810B25C *, Position0810B25C **, u16, u8, u8 *, const void *, u16, u16, Task0810B25C *);
extern u8 func_080DE1F0(Position0810B25C *);
extern Task0810B25C *func_080DFD8C(const void *, u8, u16, u16, Task0810B25C *);
extern Task0810B25C *func_080E03F8(Object0810B25C *, const void *, u8, u8, const s16 *, Task0810B25C *);
extern Task0810B25C *func_080E05DC(Task0810B25C *);

u32 func_0810B25C(Task0810B25C *parent, Request0810B25C *request, State0810B25C *state)
{
    s16 x;
    s16 y;

    switch (request->phase) {
    case 0: {
        u8 count;
        state->option = request->option;
        state->input = request->input;
        count = 3;
        if (state->option)
            count = 0;
        if (request->flags & 2)
            state->special = 1;
        state->opening = func_080E03F8(state->input, data_083A1EC4,
                                     count, 0, 0, parent);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        u16 mode;
        state->opening = func_080E05DC(state->opening);
        if (state->opening)
            break;
        if (func_080D3B54(state->input)) {
            request->phase = 2;
            break;
        }
        mode = 0x54;
        if (state->special)
            mode = 0x34;
        state->overlay_task = func_080DDF68(state->input, &state->overlay,
            mode, 2, &state->ready_first, data_083A1F14, 0, 0, parent);
        request->phase++;
        break;
    }
    case 0x101:
        if (!state->ready_first)
            break;
        func_080DBDC8(state->overlay, &x, &y);
        func_080D49FC(0, 2, 0, x, y);
        state->graphics = func_080D4B64(0, &data_088F1D9C, 0x3CC, 6);
        {
            u32 mask = func_080035A8(2);
            u16 control = g_control_flags_03000940;
            control |= mask;
            g_control_flags_03000940 = control;
        }
        state->scene = func_080D3E9C(data_0894D69C, parent);
        state->effect = func_080DFD8C(data_083A1F1C, 1, 4, 0, parent);
        request->phase++;
        break;
    case 0x102:
        if (!state->ready_second)
            break;
        if (!func_080D8858(state->input, 0)) {
            request->phase = 2;
            break;
        }
        state->selected = (Object0810B25C *)func_080DD4A4(state->input, 0);
        state->position = func_080DD748(state->selected, &state->x, &state->y, 0);
        state->motion = func_080D6098(state->x, state->y, 0, 1, 1,
            &state->ready_motion, data_083A1EE8, parent);
        state->text = func_080DCFE4(state->selected, data_083A1F00,
            12, 20, 4, parent, 20);
        state->effect = func_080DFD8C(data_083A1F24, 1, 4, 0, parent);
        request->phase++;
        break;
    case 0x103:
        if (!func_080DE1F0(state->overlay))
            break;
        state->motion = func_080D6134(state->motion);
        if (state->motion)
            break;
        state->graphics = func_080D4D2C(state->graphics, 0);
        if (state->graphics)
            break;
        {
            u32 mask = func_080035A8(2);
            u16 control = g_control_flags_03000940;
            control &= ~mask;
            g_control_flags_03000940 = control;
        }
        state->scene = func_080D3F08(state->scene);
        if (state->scene)
            break;
        state->text = func_080DBA5C(state->text);
        if (state->text)
            break;
        request->phase = 2;
        break;
    }
    return 0;
}
