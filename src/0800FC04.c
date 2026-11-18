#include "polygon_scanline.h"

typedef struct ScanlineTask ScanlineTask;

typedef struct {
    s16 x;
    s16 y;
    u8 type;
    u8 unknown_05;
    u16 flags;
    PolygonSpan ranges[160];
    const PolygonPoint *points;
    u16 count;
} State0800FC04;

extern void func_0800F93C(State0800FC04 *state, u16 *destination);
extern ScanlineTask *func_0800C3CC(
    void (*callback)(State0800FC04 *, u16 *), u16 payload_bytes,
    u16 element_size, u16 *destination);
extern void *func_0800C614(const ScanlineTask *task);
extern void func_08010058(void *object, u16 first, u8 count, u8 start,
                          u8 end);

/* The render step: refetch the state, clear the 160 scanline ranges, then
 * rasterize the polygon into them.  The same statements, apart from type and
 * member names, are render_object in merged src/08010284.c (func_0800F308 on
 * the pointer at +0x288 and the u16 count at +0x28C) and case 5 of merged
 * src/0800E4DC.c.  The ROM's second func_0800C614 call, at 0x0800FC44, is the
 * helper's own state fetch. */
static inline void render_object(ScanlineTask *task)
{
    State0800FC04 *state = func_0800C614(task);

    func_08010058(task, 0, 160, 245, 250);
    func_0800F308(state->points, state->count, state->x, state->y,
                  state->ranges, 1);
}

/* Complete [0x0800FC04, 0x0800FC8C): 136 bytes, 59 instructions.
 * Target bytes: 70b582b0031c0e1c141c1b062404240c1b48a6218900db0d1a4a9b180222fcf7d3fb051cfcf7f4fc011c05200871a2239b00c8180660a326b60088190480281cfcf7e6fc041cfa200090281c0021a022f52300f0fff9a221890060180068a11909880023e25e0226a35f0834009401240194fff747fb281c02b070bc02bc08473df9000840000004
 */
ScanlineTask *func_0800FC04(u8 window, const PolygonPoint *points,
                            u16 count)
{
    ScanlineTask *task = func_0800C3CC(func_0800F93C, 0x298, 2,
                                       (u16 *)0x04000040 + window);
    State0800FC04 *state = func_0800C614(task);

    state->type = 5;
    state->points = points;
    state->count = count;
    render_object(task);
    return task;
}
