#include "ffta.h"

// 0x0801F6C0..0x0801F80C: 332 bytes, 146 instructions.
typedef struct {
    u8 unknown_00[0x1E];
    u16 fill_color;
} ResourceState;

extern ResourceState g_state_02007F40;
extern u8 data_02003CB0[];
extern void func_08141868(const void *source, void *destination, u32 control);
extern void func_08141890(const void *source, void *destination);
extern void *func_0801ED24(const void *source, void *relocation_base, u8 flags,
                         void *first, void *second, u32 x, u32 y, u32 attributes);

void func_0801F6C0(const u32 *resource, u16 index, u16 x, u16 y,
                   void *first, void *second, u8 clear)
{
    const u32 *header = resource;
    u16 first_index;
    const u8 *source;
    const u8 *relocation_base;
    u8 flags;
    u32 fill_a;
    u32 fill_b;

    while (!*header) {
        header++;
    }
    first_index = (*header - 4) >> 2;
    if (!resource[index]) {
        if (first) {
            fill_a = g_state_02007F40.fill_color | (g_state_02007F40.fill_color << 16);
            func_08141868(&fill_a, first, 0x01000200);
        }
        if (second) {
            fill_b = g_state_02007F40.fill_color | (g_state_02007F40.fill_color << 16);
            func_08141868(&fill_b, second, 0x01000200);
        }
        return;
    }
    source = (const u8 *)resource + resource[index];
    if (*source == 0x10) {
        func_08141890(source, data_02003CB0);
        source = data_02003CB0;
    } else {
        source += 4;
    }
    relocation_base = (const u8 *)resource + (resource[first_index] & 0x0FFFFFFF);
    if (clear) {
        if (first) {
            fill_b = g_state_02007F40.fill_color | (g_state_02007F40.fill_color << 16);
            func_08141868(&fill_b, first, 0x01000200);
        }
        if (second) {
            fill_a = g_state_02007F40.fill_color | (g_state_02007F40.fill_color << 16);
            func_08141868(&fill_a, second, 0x01000200);
        }
    }
    flags = 0;
    if (resource[first_index] & 0x80000000) {
        flags = 1;
    }
    if (resource[first_index] & 0x40000000) {
        flags |= 2;
    }
    func_0801ED24(source, (void *)relocation_base, flags, first, second, x, y, 0);
}
