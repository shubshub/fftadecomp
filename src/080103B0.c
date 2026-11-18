#include "ffta.h"

typedef struct {
    u16 left;
    u16 right;
} Scanline;

typedef struct RenderState {
    s16 x;
    s16 y;
    u8 unknown_04[4];
    Scanline ranges[160];
    u16 first;
    u16 second;
} RenderState;

extern RenderState *func_0800C614(void *object);
extern void func_08010058(void *object, u16 first, u8 count,
                         u8 start, u8 end);
extern void func_0800F770(s16 x, s16 y, u16 first, u16 second,
                         Scanline *ranges, u8 mode);

static inline void render_object(void *object)
{
    RenderState *state = func_0800C614(object);

    func_08010058(object, 0, 160, 245, 250);
    func_0800F770(state->x, state->y, state->first, state->second,
                  state->ranges, 1);
}

/* Complete [0x080103B0, 0x0801040C): 92 bytes, 39 reachable Thumb instructions.
 * 30b582b0051c0c04240cfcf72bf9124940180480281cfcf725f9041cfa200090281c0021a022f523fff73efe0022a05e0223e15ea225ad0062191288023563191b880834009401240194fff7b9f902b030bc01bc004700008a020000
 */
void func_080103B0(void *object, u16 value)
{
    func_0800C614(object)->second = value;
    render_object(object);
}
