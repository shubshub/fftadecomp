#include "ffta.h"

struct BgAffineSrc {
    s32 texX;
    s32 texY;
    s16 scrX;
    s16 scrY;
    s16 sx;
    s16 sy;
    u16 alpha;
};

typedef struct {
    u8 unknown_00[0x0C];
    struct BgAffineSrc src;
} AffineWaveState;

extern AffineWaveState *func_0800C614(void *object);

void func_0800DCC4(void *object, const struct BgAffineSrc *src)
{
    AffineWaveState *state = func_0800C614(object);

    state->src.texX = src->texX;
    state->src.texY = src->texY;
    state->src.scrX = src->scrX;
    state->src.scrY = src->scrY;
    state->src.sx = src->sx;
    state->src.sy = src->sy;
    state->src.alpha = src->alpha;
}
