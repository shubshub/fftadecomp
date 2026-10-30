#include "ffta.h"

typedef struct Object0800FC04 Object0800FC04;

typedef struct {
    s16 x;
    s16 y;
} Point0800FC04;

typedef struct {
    u16 start;
    u16 end;
} Range0800FC04;

typedef struct {
    s16 x;
    s16 y;
    u8 mode;
    u8 unknown_05;
    u16 flags;
    Range0800FC04 ranges[160];
    const Point0800FC04 *source;
    u16 count;
} State0800FC04;

extern u16 data_04000040[];
extern void func_0800F93C(State0800FC04 *state, u16 *destination);
extern Object0800FC04 *func_0800C3CC(
    void (*callback)(State0800FC04 *, u16 *), u32 size, u32 type,
    u16 *destination);
extern void *func_0800C614(const Object0800FC04 *object);
extern void func_08010058(Object0800FC04 *object, u16 first, u8 count,
                          u8 start, u8 end);
extern void func_0800F308(const Point0800FC04 *source, u32 count,
                          s32 x, s32 y, Range0800FC04 *ranges, u32 mode);

static inline void initialize_source(State0800FC04 *state,
                                     const Point0800FC04 *source, u16 count)
{
    state->mode = 5;
    state->source = source;
    state->count = count;
}

/* Complete [0x0800FC04, 0x0800FC8C): 136 bytes.
 * Target bytes: 70b582b0031c0e1c141c1b062404240c1b48a6218900db0d1a4a9b180222fcf7d3fb051cfcf7f4fc011c05200871a2239b00c8180660a326b60088190480281cfcf7e6fc041cfa200090281c0021a022f52300f0fff9a221890060180068a11909880023e25e0226a35f0834009401240194fff747fb281c02b070bc02bc08473df9000840000004
 */
Object0800FC04 *func_0800FC04(u8 window, const Point0800FC04 *source,
                            u16 count)
{
    Object0800FC04 *object = func_0800C3CC(func_0800F93C, 0x298, 2,
                                         data_04000040 + window);
    State0800FC04 *state;

    initialize_source(func_0800C614(object), source, count);
    state = func_0800C614(object);
    func_08010058(object, 0, 160, 245, 250);
    func_0800F308(state->source, state->count, state->x, state->y,
                  state->ranges, 1);
    return object;
}
