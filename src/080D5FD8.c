#include "ffta.h"

typedef struct SchedulerDescriptor080D5FD8 {
    u8 unknown_00[4];
    u32 value;
    u8 unknown_08[12];
    u16 palette;
    u8 unknown_16[6];
} SchedulerDescriptor080D5FD8;

typedef u32 (*SchedulerCallback080D5FD8)(void *task, void *descriptor,
                                         void *payload);

extern u16 data_03003A60[];
extern u8 data_083954B8[];
extern u8 func_080CB99C(u16 id);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u32 func_080D65D4(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(SchedulerCallback080D5FD8 callback, u16 payload_size,
                           void *descriptor, void *parent);
extern u32 func_08011348(const void *entries, const void *data, u16 index,
                        u8 layer, s16 x, s16 y, s16 width, s16 height,
                        u8 mode, u16 attributes);

// Complete [0x080D5FD8, 0x080D6098): 192 bytes, 83 instructions.
u32 func_080D5FD8(u16 id, u8 layer, u16 x, u16 y, u16 width, u32 tiles,
                  u8 bank, void *parent)
{
    SchedulerDescriptor080D5FD8 descriptor;

    func_0814186C(data_03003A60 + func_080CB99C(id) * 16,
                  data_03003A60 + bank * 16, 0x10);
    descriptor.palette = id;
    descriptor.value = tiles;
    func_08005B6C(func_080D65D4, 0x88,
                  &descriptor, parent);
    return func_08011348(data_083954B8, 0, 0, layer, (s16)x, (s16)y, (s16)width,
                         (s16)((tiles - 0x06010000) >> 5), bank, 6);
}
