#include "ffta.h"

/* 0x0800FEAC..0x0800FF00: 84 bytes. */

typedef struct {
    u16 left;
    u16 right;
} Scanline;

typedef struct {
    s16 x;
    s16 y;
    u8 type;
    u8 unknown_05;
    u16 flags;
    Scanline lines[160];
    const u8 *data;
    u16 frame;
} RasterAnimation;

typedef struct ScanlineTask ScanlineTask;

extern void func_0800F93C(RasterAnimation *state, u16 *destination);
extern ScanlineTask *func_0800C3CC(
    void (*callback)(RasterAnimation *, u16 *), u32 size, u32 type,
    u16 *destination);
extern RasterAnimation *func_0800C614(ScanlineTask *task);
extern void func_0800C628(ScanlineTask *task, u8 enabled);
extern void func_0800E110(ScanlineTask *task);
extern u16 data_04000040[];

ScanlineTask *func_0800FEAC(u8 window, const u8 *data)
{
    ScanlineTask *task = func_0800C3CC(func_0800F93C, 0x298, 2,
                                    data_04000040 + window);
    RasterAnimation *state = func_0800C614(task);

    state->type = 9;
    state->data = data;
    state->frame = 0;
    func_0800C628(task, 1);
    func_0800E110(task);
    return task;
}
