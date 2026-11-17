#include "ffta.h"
#include "control_flags.h"

// Target: complete [0x0811EF58, 0x0811F28C), 820 bytes including literal pools.
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *unknown_04;
} Request0811EF58;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Motion0811EF58;

typedef struct {
    u16 flags;
    u16 timer;
    u8 unknown_04[4];
    u8 first_index;
    u8 second_index;
    u8 countdown;
    u8 unknown_0b;
    void *first_tasks[8];
    void *second_tasks[8];
    void *object;
    void *task_50;
    void *task_54;
    void *task_58;
    Motion0811EF58 x_motion;
    Motion0811EF58 y_motion;
    void *resource;
} State0811EF58;

typedef struct {
    u16 phase;
    u8 unknown_02[0x12];
    s16 x;
    s16 y;
    u16 selector;
    u8 unknown_1a[2];
} Descriptor0811EF58;

typedef u32 (*TaskCallback0811EF58)(void *, void *, void *);

extern const u8 data_083A7394[];
extern const u8 data_088F3A38[];
extern const u8 data_0894CF90[];
extern const u8 data_0894DED0[];
extern const u8 data_0894CFBC[];
extern const u16 data_083A7504[];

extern void *func_080D7A70(const void *, u8, void *);
extern void *func_080D7ABC(void *);
extern void func_080D49FC(u8, u8, u8, u8, u8);
extern void func_0800BD24(u8, u8);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u16 func_080035A8(u8);
extern u16 func_080035D0(u8);
extern void func_0800BDA4(void *, u8);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void func_080E0608(Motion0811EF58 *, s16, s16, s16);
extern void func_080E064C(Motion0811EF58 *);
extern u8 func_080E0570(void **, u16);
extern void *func_08005B6C(TaskCallback0811EF58, u16, void *, void *);
extern u32 func_0811ED40(void *, void *, void *);
extern u32 func_0811EE48(void *, void *, void *);
extern void *func_080D4774(void *);
extern u8 func_080E0690(Motion0811EF58 *);
extern void *func_080D3F08(void *);
extern void func_080D4D14(void *, u8);
extern void func_080D4020(void);

u32 func_0811EF58(void *owner, Request0811EF58 *request, State0811EF58 *state)
{
    Descriptor0811EF58 d;

    if (state->flags & 0x8000)
        return 0;

    switch (request->phase) {
    case 0:
        state->resource = func_080D7A70(data_083A7394, 3, owner);
        break;
    case 1:
        break;
    case 0x100:
        state->resource = func_080D7ABC(state->resource);
        if (state->resource == 0) {
            state->flags |= 1;
            state->flags |= 0x8000;
            request->phase++;
        }
        break;
    case 0x101:
        func_080D49FC(1, 3, 0, 0xab, 0xf);
        func_0800BD24(1, 0);
        state->object = func_080D4B64(1, data_088F3A38, 0x2f5, 6);
        g_control_flags_03000940.display |= func_080035A8(3);
        func_0800BDA4(state->object, 1);
        state->task_54 = func_080D4704(data_0894CF90, owner);
        state->task_50 = func_080D3E9C(data_0894DED0, owner);
        func_080E0608(&state->x_motion, 0xab, 0x30, 0x177);
        func_080E0608(&state->y_motion, 0xf, 0x6e, 0x177);
        g_control_flags_03000940.win0h_hi = 0xab;
        g_control_flags_03000940.win0h_lo = 0xf0;
        g_control_flags_03000940.win0v_hi = 0xf;
        g_control_flags_03000940.win0v_lo = 0xa0;
        g_control_flags_03000940.winin_lo = 0x3f;
        g_control_flags_03000940.winout_lo = 0x3f & ~func_080035D0(3);
        g_control_flags_03000940.display |= 0x2000;
        state->countdown = 8;
        request->phase++;
        break;
    case 0x102: {
        u8 i;
        u8 slot;
        u8 next_slot;

        func_080E0570(state->first_tasks, 8);
        func_080E0570(state->second_tasks, 8);
        func_080E064C(&state->x_motion);
        func_080E064C(&state->y_motion);
        g_control_flags_03000940.win0h_hi = state->x_motion.current;
        g_control_flags_03000940.win0v_hi = state->y_motion.current;
        func_0800BC08(1, state->x_motion.current, state->y_motion.current);
        for (i = state->first_index; i <= 0x15; i++) {
            if (data_083A7504[i] > state->timer)
                break;
            if (state->timer == data_083A7504[i]) {
                d.x = state->x_motion.current + 0x20;
                d.y = state->y_motion.current + 0x18;
                d.selector = i;
                slot = i & 7;
                state->first_tasks[slot] =
                    func_08005B6C(func_0811ED40, 0x2c, &d, owner);
                state->first_index++;
                break;
            }
        }
        if (--state->countdown == 0) {
            state->countdown = 8;
            d.x = state->x_motion.current + 0x28;
            d.y = state->y_motion.current + 0x18;
            d.selector = state->second_index;
            next_slot = state->second_index & 7;
            state->second_tasks[next_slot] =
                func_08005B6C(func_0811EE48, 0x2c, &d, owner);
            state->second_index++;
        }
        state->timer++;
        state->task_54 = func_080D4774(state->task_54);
        if (state->task_54 == 0) {
            if (state->timer == 0x159)
                state->task_58 = func_080D4704(data_0894CFBC, owner);
            if (func_080E0690(&state->x_motion) &&
                func_080E0690(&state->y_motion))
                request->phase++;
        }
        break;
    }
    case 0x103:
        state->task_50 = func_080D3F08(state->task_50);
        if (state->task_50 == 0) {
            if (state->task_58) {
                state->task_58 = func_080D4774(state->task_58);
                if (state->task_58 != 0)
                    break;
                func_080D4D14(state->object, 1);
                state->object = 0;
                g_control_flags_03000940.display &= ~func_080035A8(3);
                g_control_flags_03000940.display &= 0xdfff;
                state->flags |= 2;
            }
            if (func_080E0570(state->first_tasks, 8) &&
                func_080E0570(state->second_tasks, 8)) {
                func_080D4020();
                request->phase = 2;
            }
        }
        break;
    }
    return 0;
}
