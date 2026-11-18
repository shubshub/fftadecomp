#include "ffta.h"

typedef struct {
    s16 base;
    u8 first_row;
    u8 last_row;
    u8 phase;
    u8 amplitude;
    u8 frame_step;
    u8 row_step;
    u8 unknown_08[0x14];
} ScanlineEffect;

typedef struct __attribute__((packed)) {
    volatile s16 value;
} ScanlineValue;

extern s32 func_08007A4C(u8 angle);

void func_0800C720(ScanlineEffect *effect, u16 *cursor, u8 stride)
{
    s16 base = effect->base;
    s16 amplitude;
    u8 phase;
    u8 row;

    effect->phase += effect->frame_step;
    amplitude = effect->amplitude;
    phase = effect->phase;
    for (row = 0; row < effect->first_row; row++) {
        ((ScanlineValue *)cursor)->value = base;
        phase += effect->row_step;
        cursor = (u16 *)((u8 *)cursor + stride);
    }
    for (; row <= effect->last_row; row++) {
        s16 offset = 0;
        if (amplitude)
            offset = ((s16)func_08007A4C(phase) * amplitude) >> 8;
        offset += base;
        ((ScanlineValue *)cursor)->value = offset;
        phase += effect->row_step;
        cursor = (u16 *)((u8 *)cursor + stride);
    }
    for (; row < 160; row++) {
        ((ScanlineValue *)cursor)->value = base;
        cursor = (u16 *)((u8 *)cursor + stride);
    }
}
