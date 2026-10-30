#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u16 field_1A;
} ClampState08037E28;

typedef struct {
    u8 unknown_00[0x30];
    u16 field_30;
    u8 unknown_32[4];
    u8 field_36;
    u8 unknown_37[0x41];
    ClampState08037E28 field_78;
    u8 unknown_94[0x38];
} Record08037E28;

typedef struct {
    u8 unknown_000[0x954];
    Record08037E28 records[0];
} State08037E28;

typedef struct {
    u8 unknown_00[0x1C];
    u16 *field_1C;
    u8 unknown_20[0x16];
    s8 field_36;
    u8 unknown_37[0x12];
    s8 field_49;
    s8 field_4A;
    s8 field_4B;
} Descriptor08037E28;

extern State08037E28 *g_state_03002810;
extern Descriptor08037E28 data_030009E0[];
extern u16 func_08017B68(ClampState08037E28 *state, u32 index);
extern s32 func_08142950(s32 numerator, s32 denominator);

/* Complete target: [0x08037E28, 0x08037F0C), 228 bytes, 100 instructions. */
void func_08037E28(s32 slot, u16 selection)
{
    Descriptor08037E28 *descriptor;
    u16 *values;
    s32 stride;
    s32 row;
    s32 column;

    g_state_03002810->records[slot].field_36 =
        func_08017B68(&g_state_03002810->records[slot].field_78,
                     (s8)selection);
    descriptor = &data_030009E0[g_state_03002810->records[slot].field_30];
    stride = descriptor->field_36 * 2;
    row = descriptor->field_49;
    row += func_08142950((s16)selection, descriptor->field_4B >> 1);
    values = descriptor->field_1C + stride * row;

    for (column = 1; column < descriptor->field_4A; column++) {
        values[0] = (values[0] & 0x0FFF) + 0xB000;
        values[descriptor->field_36] =
            (values[descriptor->field_36] & 0x0FFF) + 0xB000;
        values++;
    }
}
