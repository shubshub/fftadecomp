#include "ffta.h"

typedef struct Object0800FB68 Object0800FB68;

typedef struct {
    u16 start;
    u16 end;
} Range0800FB68;

typedef struct {
    s16 x;
    s16 y;
    u8 mode;
    u8 unknown_05;
    u16 flags;
    Range0800FB68 ranges[160];
    u16 radius;
} State0800FB68;

extern u16 data_04000040[];
extern void func_0800F93C(State0800FB68 *state, u16 *destination);
extern Object0800FB68 *func_0800C3CC(
    void (*callback)(State0800FB68 *, u16 *), u32 size, u32 type,
    u16 *destination);
extern void *func_0800C614(const Object0800FB68 *object);
extern void func_08010058(Object0800FB68 *object, u16 first, u8 count,
                          u8 start, u8 end);
extern void func_0800F068(s32 x, s32 y, u16 radius,
                          Range0800FB68 *ranges, u32 mode);

static inline void initialize_state(State0800FB68 *state, u16 x, u16 y,
                                    u16 radius)
{
    state->x = x;
    state->y = y;
    state->mode = 3;
    state->radius = radius;
}

/* Complete [0x0800FB68, 0x0800FC04): 156 bytes.
 * Target bytes: 70b54e46454660b481b0041c0d1c161c984624062d042d0c3604360c40460004000c80461b48a6218900e40d1a4aa4180222231cfcf716fc8146fcf737fd0580468003210171a2239b00c018414601804846fcf72bfd041cfa20009048460021a022f52300f044fa0022a05e0223e15ea2239b00e2181288083401230093231cfff73efa484601b018bc9846a14670bc02bc08473df9000840000004
 */
Object0800FB68 *func_0800FB68(u8 window, u16 x, u16 y, u16 radius)
{
    Object0800FB68 *object = func_0800C3CC(func_0800F93C, 0x298, 2,
                                         data_04000040 + window);
    State0800FB68 *state;

    initialize_state(func_0800C614(object), x, y, radius);
    state = func_0800C614(object);
    func_08010058(object, 0, 160, 245, 250);
    func_0800F068(state->x, state->y, state->radius, state->ranges, 1);
    return object;
}
