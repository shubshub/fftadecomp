#include "ffta.h"

typedef struct {
    u16 start;
    u16 end;
} RenderRange0801040C;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u16 flags;
    RenderRange0801040C ranges[160];
    u16 horizontal_radius;
    u16 vertical_radius;
} RenderState0801040C;

RenderState0801040C *func_0800C614(void *object);
void func_08010058(void *object, u16 first, u8 count, u8 start, u8 end);
void func_0800F860(s32 x, s32 y, u16 horizontal_radius, u16 vertical_radius,
                  RenderRange0801040C *ranges, u32 mode);

static inline void render_object(void *object)
{
    RenderState0801040C *state = func_0800C614(object);
    func_08010058(object, 0, 160, 245, 250);
    func_0800F860(state->x, state->y, state->horizontal_radius,
                  state->vertical_radius, state->ranges, 1);
}

/* Complete [0x08010464, 0x080104C0): 92 bytes, 39 reachable Thumb instructions.
 * 30b582b0051c0c04240cfcf7d1f8124940180480281cfcf7cbf8041cfa200090281c0021a022f523fff7e4fd0022a05e0223e15ea225ad0062191288023563191b880834009401240194fff7d7f902b030bc01bc004700008a020000
 */
void func_08010464(void *object, u16 radius)
{
    RenderState0801040C *state = func_0800C614(object);

    state->vertical_radius = radius;
    render_object(object);
}
