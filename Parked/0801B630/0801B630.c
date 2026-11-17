#include "ffta.h"

// 0x0801B630..0x0801B6C8: 152 bytes, 140 bytes of Thumb code and four
// literal words (data_0836DA74, data_0836DA7C, data_0836DA84, g_state_02007F40).
// Builds a 0x30-byte descriptor on the stack and hands it to func_0801AF08
// together with the two tile-map layer buffers.

typedef struct {
    u8 flags_a;
    u8 flags_b;
    u8 unknown_02[2];
    u8 kind;
    u8 unknown_05;
    u16 field_06;
    u16 field_08;
    u16 field_0A;
    u8 unknown_0C[0x12];
    u16 field_1E;
    u8 unknown_20[8];
    u16 x;
    u16 y;
    u8 unknown_2C[4];
} Descriptor0801B630;

typedef struct {
    u8 unknown_00[0x1e];
    u16 field_1E;
} State0801B630;

extern State0801B630 g_state_02007F40;
extern u16 data_0836DA74[];
extern u16 data_0836DA7C[];
extern u16 data_0836DA84[];

extern u16 *func_0801AD1C(u8 layer);
extern void func_0801AF08(Descriptor0801B630 *descriptor, u32 a, u32 b, u16 *first, u16 *second, u32 third);

void func_0801B630(u16 x, u16 y, u8 kind, u32 a, u32 b)
{
    Descriptor0801B630 descriptor;
    u16 *first;

    descriptor.kind = kind;
    descriptor.field_06 = data_0836DA74[kind];
    descriptor.field_08 = data_0836DA7C[kind];
    descriptor.field_0A = data_0836DA84[kind];
    descriptor.flags_a = 0;
    descriptor.flags_b = 0;
    if (a == 0)
        descriptor.flags_a = 0x80;
    if (b == 0)
        descriptor.flags_b = 0x80;
    descriptor.x = x << 3;
    descriptor.y = y << 3;
    descriptor.field_1E = g_state_02007F40.field_1E;
    first = func_0801AD1C(0);
    func_0801AF08(&descriptor, a, b, first, func_0801AD1C(1), 0);
}
