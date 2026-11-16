/* Complete target: [0x08037E28, 0x08037F0C), 228 bytes, 100 instructions.
 * f0b54f464646c0b40c04240c2f4ecc21051c4d43306828182d49401821060916
 * dff78efe316849192a4a8918087030684019294940180188284a4c2048431c21
 * 89188846804487183622d2199146002696577600381c49300025455724042414
 * 0230017809064916201c0af15dfd2d18301c68434000424611680b180124391c
 * 4a310020085684421ada154eb0200002051c88464f461988301c084040191880
 * 002179564900c9180a88301c104040190880023301344146002008568442eadb
 * 18bc9846a146f0bc01bc004710280003cc0900008a09000084090000e0090003
 * ff0f0000
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u16 field_1A;
} ClampState08017B68;

typedef struct {
    u8 unknown_00[0x30];
    u16 object_id;
    u8 unknown_32[4];
    u8 field_36;
    u8 unknown_37[0x41];
    ClampState08017B68 list;
    u8 unknown_94[0x38];
} Record08037E28;

typedef struct {
    u8 unknown_000[0x954];
    Record08037E28 records[0];
} State08037E28;

typedef struct {
    u8 unknown_00[0x1C];
    u16 *second_plane;
    u8 unknown_20[0x16];
    s8 plane_stride;
    u8 unknown_37[0x12];
    s8 field_49;
    s8 width;
    s8 height;
} Window08037E28;

extern State08037E28 *g_state_03002810;
extern Window08037E28 data_030009E0[];
extern u16 func_08017B68(ClampState08017B68 *state, u32 index);

void func_08037E28(s32 slot, u16 selection)
{
    u16 *values;
    u16 window;
    s32 column;

    g_state_03002810->records[slot].field_36 =
        func_08017B68(&g_state_03002810->records[slot].list,
                     (s8)selection);
    window = g_state_03002810->records[slot].object_id;
    /* lsls r6, r6, #1 at 0x08037E7A doubles the stride before the remainder
     * call, the (field_15 << 1) of func_08017B9C (src/08017B9C.c). */
    values = data_030009E0[window].second_plane
        + (data_030009E0[window].plane_stride << 1)
        * (data_030009E0[window].field_49
           + (s16)selection % (data_030009E0[window].height >> 1));

    for (column = 1; column < data_030009E0[window].width; column++) {
        values[0] = (values[0] & 0x0FFF) + 0xB000;
        values[data_030009E0[window].plane_stride] =
            (values[data_030009E0[window].plane_stride] & 0x0FFF) + 0xB000;
        values++;
    }
}
