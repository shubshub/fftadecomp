#include "ffta.h"

/* 0x080D5DD4..0x080D5E80: 172 bytes. */
typedef struct EffectObject EffectObject;

extern EffectObject *func_08011348(const u8 *, const u8 *, u16, u8,
                                  s16, s16, s16, s16, u8, u16);
extern void func_08011138(EffectObject *, u8);

EffectObject *func_080D5DD4(const u8 *data, u16 tile, u16 x, u16 y,
                           u16 depth, u8 priority, u8 palette)
{
    const u8 *graphics = data + 4;
    u8 offset_low = data[2];
    u8 offset_high = data[3];
    const u8 *animation = data + ((offset_high << 8) | offset_low);
    u16 flags = 0;
    u8 flags_low = data[0];
    u8 flags_high = data[1];
    s32 data_flags = (flags_high << 8) | flags_low;
    EffectObject *object;

    if (data_flags & 4)
        flags |= 0x2000;
    if (data_flags & 8)
        flags |= 0x4000;
    object = func_08011348(graphics, animation, tile, 1,
                          (s16)x, (s16)y, 0, (s16)depth, priority, flags);
    func_08011138(object, palette);
    return object;
}
