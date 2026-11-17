#include "ffta.h"

// Target: complete [0x080D4A28, 0x080D4B64), 316 bytes, literal pool included.

typedef struct {
    u32 values[2];
} WordPair;

typedef struct {
    u32 values[4];
} WordQuad;

extern const WordPair data_08149A88;
extern const WordPair data_08149A90;
extern const WordPair data_08149A98;
extern const u16 data_08149AA0[];
extern const WordQuad data_08149AA4;

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void func_0800AFAC(u32 base, u16 index, u32 zero, u8 group, u32 mask);
extern void func_0800BC90(u8 group, u32 enable, u8 layer);
extern void func_0800BCE0(u8 group, u32 enable);
extern void func_0800BD24(u8 group, u32 enable);
extern void func_080034B8(u16 control, u8 layer);
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);
extern u32 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);

void func_080D4A28(u8 group, u8 layer, u16 index, u16 x, u16 y, u8 priority)
{
    WordPair screens;
    WordPair masks;
    WordPair maps;
    WordPair characters;
    u16 flags[2];
    WordQuad priorities;

    screens = data_08149A88;
    maps = data_08149A88;
    characters = data_08149A90;
    masks = data_08149A98;
    func_081443FC(flags, data_08149AA0, sizeof(flags));
    priorities = data_08149AA4;

    func_0800AFAC(screens.values[group], index, 0, group, masks.values[index]);
    func_0800BC90(group, 1, layer);
    func_0800BC08(group, (s16)x, (s16)y);
    func_0800BCE0(group, 1);
    func_0800BD24(group, 1);
    func_080034B8(func_08003A74(maps.values[group]) |
                  func_08003A80(characters.values[index]) |
                  flags[index] | priorities.values[priority], layer);
    func_08003508(0, layer);
    func_08003558(0, layer);
}
