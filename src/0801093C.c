#include "ffta.h"

// 0x0801093C..0x08010AFC: 448 bytes, 205 instructions.

typedef struct Sprite0801093C {
    u8 active;
    u8 unknown_01[3];
    const void *data;
    u32 unknown_08;
    u16 frame;
    s16 index;
    u8 unknown_10[2];
    u16 frame_count;
    u16 flags;
    u16 unknown_16;
    const u8 *current;
    u8 list;
    u8 mode;
    u16 base;
    u16 unknown_20;
    u16 offset;
    u8 unknown_24;
    u8 unknown_25;
    u8 unknown_26[2];
    u8 unknown_28;
    u8 unknown_29;
    u8 unknown_2A;
    u8 unknown_2B;
    u16 unknown_2C;
    u8 unknown_2E[0x12];
} Sprite0801093C;

typedef struct {
    u16 count;
    u8 unknown_02[2];
    u32 unknown_04;
    u32 unknown_08;
    u32 unknown_0C;
    u32 unknown_10;
    Sprite0801093C *slots;
} SpritePool0801093C;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern SpritePool0801093C data_02009170;
extern BufferCopier const data_0836D4BC[];
extern const Sprite0801093C data_08149828;
/* src/0801075C.c declares index as u16; this caller's `movs #1; negs` for -1
 * is what an s16 parameter produces (a u16 prototype loads 0xFFFF from the
 * pool), and the callee itself narrows index both ways. */
extern u16 func_0801075C(Sprite0801093C *sprite, s16 index, u16 format);
extern void func_08010D2C(Sprite0801093C *sprite);
extern void func_080105C4(Sprite0801093C *sprite);

static inline Sprite0801093C *find_free_slot(void)
{
    s32 i;

    for (i = 0; i < data_02009170.count; i++) {
        if (data_02009170.slots[i].active == 0)
            return &data_02009170.slots[i];
    }
    return 0;
}

Sprite0801093C *func_0801093C(u8 list, const void *data, u32 arg2, u16 frame,
                              u8 mode, u16 base, u16 arg6, u16 offset,
                              u16 arg8, u16 arg9, u16 flags)
{
    Sprite0801093C *sprite = find_free_slot();

    data_0836D4BC[0](sprite, &data_08149828, sizeof(*sprite));
    if (flags & 2) {
        sprite->data = data;
        sprite->current = data;
    } else if (flags & 4) {
        sprite->data = data;
        sprite->index = frame;
        if (flags & 0x2000)
            sprite->current = (const u8 *)data + ((const u16 *)data)[sprite->index];
        else
            sprite->current = (const u8 *)data + ((const u32 *)data)[sprite->index];
    } else {
        sprite->data = data;
        sprite->unknown_08 = arg2;
        sprite->frame = frame;
        sprite->frame_count = func_0801075C(sprite, -1, flags);
    }
    if (flags & 0x800)
        sprite->unknown_16 = 0xFFFF;
    sprite->list = list;
    sprite->mode = mode;
    sprite->base = base;
    sprite->unknown_20 = arg6;
    sprite->offset = offset;
    sprite->unknown_2B = arg9;
    sprite->unknown_2C = arg8;
    if (flags & 0x20) {
        sprite->unknown_28 = 1;
        flags &= ~0x20;
    }
    if (flags & 0x1000) {
        sprite->unknown_29 = 1;
        flags &= ~0x1000;
    }
    if (flags & 0x8000)
        sprite->unknown_25 = 2;
    if (flags & 1) {
        sprite->unknown_25 = 1;
        flags &= ~1;
    }
    sprite->flags = flags;
    if (!(flags & 6))
        func_08010D2C(sprite);
    func_080105C4(sprite);
    return sprite;
}
