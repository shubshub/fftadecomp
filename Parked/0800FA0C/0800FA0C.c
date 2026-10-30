#include "ffta.h"

/* Target 0x0800FA0C..0x0800FAA8, 156 bytes:
 * 70b54e46454660b481b0041c0d1c161c984624062d042d0c3604360c40460004000c80461b48a6218900e40d1a4aa4180222231cfcf7c4fc8146fcf7e5fd0580468001250571a2239b00c018414601804846fcf7d9fd041cfa20009048460021a022f52300f0f2fa0022a05e0223e15ea2239b00e218128808340095231cfef745fe484601b018bc9846a14670bc02bc084700003df9000840000004
 */

struct Range0800FA0C {
    u16 start;
    u16 end;
};

struct State0800FA0C {
    u16 x;
    u16 y;
    u8 type;
    u8 unknown_05;
    u16 flags;
    struct Range0800FA0C ranges[160];
    u16 radius;
};

struct Task0800FA0C;

extern void func_0800F93C(struct State0800FA0C *state, u16 *destination);
extern struct Task0800FA0C *func_0800C3CC(
    void (*callback)(struct State0800FA0C *, u16 *), u32 size, u32 type,
    u16 *destination);
extern struct State0800FA0C *func_0800C614(struct Task0800FA0C *task);
extern void func_08010058(struct Task0800FA0C *task, u16 first, u8 count,
                         u8 start, u8 end);
extern void func_0800E718(s32 x, s32 y, u16 radius,
                         struct Range0800FA0C *ranges, u8 clip);
extern u16 data_04000040[];

static inline void render_object(struct Task0800FA0C *task)
{
    struct State0800FA0C *state = func_0800C614(task);

    func_08010058(task, 0, 160, 245, 250);
    func_0800E718((s16)state->x, (s16)state->y, state->radius,
                  state->ranges, 1);
}

struct Task0800FA0C *func_0800FA0C(u8 window, u16 x, u16 y, u16 radius)
{
    struct Task0800FA0C *task = func_0800C3CC(func_0800F93C, 0x298, 2,
                                            data_04000040 + window);
    struct State0800FA0C *state = func_0800C614(task);

    state->x = x;
    state->y = y;
    state->type = 1;
    state->radius = radius;
    render_object(task);
    return task;
}
