#include "ffta.h"

// 0x0801F1A8..0x0801F2EC: 324 bytes, 162 instructions.
typedef struct {
    u8 unknown_00[0x168];
    void *transfer;
    u8 unknown_16C[4];
    void *relocation_base;
    u8 unknown_174[12];
    u8 flags;
} ResourceState;

typedef struct {
    u8 unknown_00[4];
    u8 offset[4];
    u8 unknown_08[0x50];
} ResourceEntry;

extern ResourceState g_state_02007F40;
extern ResourceEntry data_08569104[];
extern u8 data_02003CB0[];
extern u16 *func_0801AD1C(u8 layer);
extern u16 func_0801E6E4(void);
extern void func_0801F124(const void *resource);
extern void *func_0801ED24(const void *source, void *relocation_base, u8 flags,
                         u32 mode, u32 x, u32 y, u32 attributes, u32 size);
extern void func_08141868(const void *source, void *destination, u32 control);
extern void func_08141890(const void *source, void *destination);

void func_0801F1A8(const u8 *src)
{
    u32 fill;
    u16 *dest = func_0801AD1C(0);

    if (src[0] == 0x10) {
        func_08141890(src, dest);
    } else if (src[0] == 1) {
        u32 low_byte = src[1];
        u32 low = (src[2] << 8) | low_byte;
        u32 id = (src[3] << 16) | low;

        if (id != 0xFFFFFF) {
            const ResourceEntry *entry = &data_08569104[id];
            u32 offset_byte = entry->offset[0];
            u32 offset_low = (entry->offset[1] << 8) | offset_byte;
            u32 offset_middle = (entry->offset[2] << 16) | offset_low;
            u32 offset = (entry->offset[3] << 24) | offset_middle;

            func_0801F1A8((const u8 *)data_08569104 + offset);
        } else {
            u16 value = func_0801E6E4();
            fill = (value << 16) | value;
            func_08141868(&fill, dest, 0x01001000);
        }
        func_0801F124(src + 4);
        g_state_02007F40.transfer = func_0801ED24(g_state_02007F40.transfer,
                                                  g_state_02007F40.relocation_base,
                                                  g_state_02007F40.flags,
                                                  0, 0, 0, 0, 0x800);
    } else if (src[0] == 0x11) {
        u32 low_byte = src[1];
        u32 low = (src[2] << 8) | low_byte;
        u32 id = (src[3] << 16) | low;

        if (id != 0xFFFFFF) {
            const ResourceEntry *entry = &data_08569104[id];
            u32 offset_byte = entry->offset[0];
            u32 offset_low = (entry->offset[1] << 8) | offset_byte;
            u32 offset_middle = (entry->offset[2] << 16) | offset_low;
            u32 offset = (entry->offset[3] << 24) | offset_middle;

            func_0801F1A8((const u8 *)data_08569104 + offset);
        } else {
            u16 value = func_0801E6E4();
            fill = (value << 16) | value;
            func_08141868(&fill, dest, 0x01001000);
        }
        func_08141890(src + 4, data_02003CB0);
        func_0801F124(data_02003CB0);
        g_state_02007F40.transfer = func_0801ED24(g_state_02007F40.transfer,
                                                  g_state_02007F40.relocation_base,
                                                  g_state_02007F40.flags,
                                                  0, 0, 0, 0, 0x800);
    } else {
        func_08141868(src + 4, dest, 0x1000);
    }
}
