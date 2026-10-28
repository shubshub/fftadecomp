#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0A];
    u8 type;
    u8 unknown_0B[6];
    u8 rowCount;
    u8 unknown_12[4];
    u16 scale;
    u16 limit;
    u8 width;
    u8 unknown_1B[0x0F];
    u8 count;
    u8 unknown_2B[0x15];
    u8 status;
    u8 unknown_41[0x2F];
    u8 renderer[0x290];
    u8 *buffer;
    u8 *selected;
    u8 *active;
    u8 entries[0x400];
    u8 fallback[3];
} SelectionRenderState;

extern SelectionRenderState *data_0200918C;
extern u8 *func_08014B84(void *entries, u8 index);
extern u8 func_0801843C(u8 type);
extern u8 func_08018484(u8 type);
extern void func_08013570(void *renderer, const void *source, u8 width, u8 mode);
extern void func_08013528(void *renderer, const void *source);
extern void func_080137C0(void *renderer, u32 value);
extern void func_08013A88(void *row, u32 width);

/* Target: complete [0x08012C30, 0x08012D3C), 268 bytes. */
void func_08012C30(void)
{
    s32 row;

    if (data_0200918C->count == 0)
    {
        data_0200918C->active = data_0200918C->fallback;
        data_0200918C->active[0] = 0x40;
        data_0200918C->fallback[1] = 0x63;
        data_0200918C->fallback[2] = 0;
        return;
    }

    data_0200918C->active = func_08014B84(data_0200918C->entries,
                                        --data_0200918C->count);
    data_0200918C->selected = data_0200918C->buffer;
    data_0200918C->status = 0;
    data_0200918C->scale = 0x1000;
    data_0200918C->limit = 0x8000;

    if (func_0801843C(data_0200918C->type))
        func_08013570(data_0200918C->renderer, data_0200918C->selected,
                      data_0200918C->width, 1);
    else
        func_08013528(data_0200918C->renderer, data_0200918C->selected);

    if (func_08018484(data_0200918C->type))
        func_080137C0(data_0200918C->renderer, 5);

    for (row = 0; row < (data_0200918C->rowCount >> 1); row++)
        func_08013A88(data_0200918C->buffer +
                      ((row * data_0200918C->width) << 6),
                      data_0200918C->width << 1);
}
