// func_0800D3BC: 0x0800D3BC-0x0800D61A (606 bytes)
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

struct BgAffineDst {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    s32 dx;
    s32 dy;
};

typedef struct {
    volatile u16 pa : 16;
    volatile u16 pb : 16;
    volatile u16 pc : 16;
    volatile u16 pd : 16;
    volatile u16 x_l : 16;
    volatile u16 x_h : 16;
    volatile u16 y_l : 16;
    volatile u16 y_h : 16;
} __attribute__((packed)) AffineLine;

typedef struct {
    u16 mode;
    s16 unknown_02;
    s16 unknown_04;
    s16 unknown_06;
    s16 unknown_08;
    u8 unknown_0A[2];
    struct BgAffineSrc src;
    u8 unknown_20[8];
    u16 unknown_28;
    u8 unknown_2A[4];
    u16 unknown_2E;
    u16 unknown_30;
    u8 unknown_32[2];
    u16 unknown_34;
    u16 unknown_36;
    s16 unknown_38[160];
    s16 unknown_178[160];
} AffineWave;

void func_08141864(const struct BgAffineSrc *src, struct BgAffineDst *dst, s32 count);

void func_0800D3BC(AffineWave *wave, AffineLine *out)
{
    struct BgAffineSrc src;
    struct BgAffineDst row;
    struct BgAffineDst base;
    s16 range = 0;
    s16 start;
    s16 end;
    s32 i;
    s32 dy;
    s32 x;
    s32 y;

    switch (wave->mode) {
    case 1:
        range = wave->unknown_34;
        break;
    case 2:
        range = wave->unknown_36;
        break;
    case 3:
        range = wave->unknown_36;
        break;
    }
    x = (wave->unknown_06 + wave->unknown_02) << 8;
    y = (wave->unknown_08 + wave->unknown_04) << 8;
    wave->src.texX = x;
    wave->src.texY = y;
    wave->src.scrY = wave->unknown_04;
    func_08141864(&wave->src, &base, 1);
    src.texX = x;
    src.texY = y;
    src.scrX = wave->unknown_28;
    src.scrY = wave->unknown_04;
    src.sy = wave->unknown_2E;
    src.alpha = wave->unknown_30;
    start = 0;
    end = 159;
    if (wave->mode != 0) {
        start = wave->unknown_04 - range;
        if (start < 0)
            start = 0;
        end = range + wave->unknown_04;
    }
    for (i = 0; i < 160; i++) {
        if (i < start || i > end) {
            out->pa = base.pa;
            out->pb = base.pb;
            out->pc = base.pc;
            out->pd = base.pd;
            out->x_l = base.dx;
            out->x_h = base.dx >> 16;
            dy = (wave->unknown_08 + i) << 8;
            dy += base.dy;
            out->y_l = dy;
            out->y_h = dy >> 16;
        } else {
            src.sx = wave->unknown_178[i];
            func_08141864(&src, &row, 1);
            dy = wave->unknown_38[i] + wave->unknown_08 + i;
            dy <<= 8;
            row.dy += dy;
            out->pa = row.pa;
            out->pb = row.pb;
            out->pc = row.pc;
            out->pd = row.pd;
            out->x_l = row.dx;
            out->x_h = row.dx >> 16;
            out->y_l = row.dy;
            out->y_h = row.dy >> 16;
        }
        out++;
    }
}
