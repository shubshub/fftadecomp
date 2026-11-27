// Target: complete [0x081137BC, 0x08113916), 346 bytes, 160 instructions.
#include "ffta.h"

typedef struct {
    u16 phase;
} Descriptor081137BC;

typedef struct {
    u16 frame;
    u8 unknown_02[4];
    u8 count;
    u8 unknown_07;
    void *objects[20];
} Payload081137BC;

/* data_083A36F8: 20 entries of 8 bytes (to 0x083A3798), one per object, in
 * the order phase 0x100 starts them. */
typedef struct {
    u8 frame;
    u8 id;
    s16 x;
    s16 y;
    u8 unknown_06[2];
} Entry081137BC;

extern const Entry081137BC data_083A36F8[];
extern const u8 data_08505EDC[];

extern void *func_080D5CC0(const void *, u16, s16, s16, s16, u8, u8, u8);
extern void func_08011058(void *, s16);
extern u8 func_080D5F24(void **, u16);
extern void func_080107D4(void *, s16, s16, s16);

/* Starts object n from its table entry, puts it at draw order 1 and counts
 * it.  The ROM has this once, at 0x08113800-0x08113830.  It is a
 * do { } while (0) statement macro, the agbcc-era form of a multi-statement
 * macro. */
#define START_OBJECT(payload, n)                                            \
    do {                                                                    \
        (payload)->objects[n] = func_080D5CC0(data_08505EDC,                \
            data_083A36F8[n].id, data_083A36F8[n].x, data_083A36F8[n].y,    \
            0x280, 6, 0, 0);                                                \
        func_08011058((payload)->objects[n], 1);                            \
        (payload)->count++;                                                 \
    } while (0)

/* Moves every live object down one pixel on even frames.  The ROM has this
 * block twice, at 0x08113840-0x08113884 (phase 0x100) and
 * 0x0811389E-0x081138E8 (phase 0x101).  The loop compares with the count
 * as `i < 20` (cmp #0x14; blo at 0x08113882 and 0x081138E6): a literal bound
 * would fold to `i <= 19`. */
static inline void MoveObjectsDown081137BC(void **objects, u16 frame,
                                           u8 count)
{
    u8 i;
    u16 x;
    u16 y;
    u16 z;

    if (frame & 1)
        return;
    for (i = 0; i < count; i++) {
        if (objects[i] != 0) {
            func_08011040((Struct08011040 *)objects[i], &x, &y, &z);
            func_080107D4(objects[i], x, y + 1, 0);
        }
    }
}

u32 func_081137BC(void *task, Descriptor081137BC *descriptor,
                  Payload081137BC *payload)
{
    u8 count;

    switch (descriptor->phase) {
    case 0:
        break;
    case 0x100:
        count = payload->count;
        if (count < 20 && payload->frame >= data_083A36F8[count].frame)
            START_OBJECT(payload, count);
        payload->frame++;
        func_080D5F24(payload->objects, 20);
        MoveObjectsDown081137BC(payload->objects, payload->frame, 20);
        if (payload->count > 19)
            descriptor->phase++;
        break;
    case 0x101:
        payload->frame++;
        MoveObjectsDown081137BC(payload->objects, payload->frame, 20);
        if (func_080D5F24(payload->objects, 20))
            descriptor->phase++;
        break;
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
