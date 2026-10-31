#include "ffta.h"

typedef struct {
    const void *image;
    u8 unknown_04[0x28];
    u16 flags;
    s16 coordinates[3];
    s16 x;
    s16 y;
    u16 angle;
    s16 first_offset;
    s16 second_offset;
    u8 unknown_3E[0x1A];
} Record080A9D18;

typedef struct {
    void *owner;
    u8 unknown_04[0x20];
    s16 x[3];
    s16 y[3];
    s16 timers[3];
    u8 unknown_36[0x0A];
    u8 flags;
    u8 unknown_41[3];
    Record080A9D18 records[2];
    u8 unknown_F4[0x98];
} Entry080A9D18;

typedef struct {
    Entry080A9D18 entries[13];
    u8 unknown_141C[0x120];
    u16 flags;
} State080A9D18;

extern void func_0801C984(s16 first, s16 second, s16 third,
                         s16 *first_output, s16 *second_output);
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                         u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                         u32 value, u8 mode, const void *transform);
extern void func_080018A0(const void *image, s32 x, s32 y, u32 variant,
                         u32 flip_x, u32 flip_y, u32 flag_28, u32 flag_29,
                         u32 value, s16 scale_x, s16 scale_y, u16 angle,
                         u32 mode);
extern void func_080A9A48(Entry080A9D18 *entry);
extern void func_080A9C80(Entry080A9D18 *entry);

/* 0x080A9D18..0x080A9E6C, complete 340-byte target:
 * F0 B5 57 46 4E 46 45 46 E0 B4 8B B0 09 90 00 25
 * 68 00 40 19 41 01 40 18 80 00 09 99 40 18 80 46
 * 42 46 40 32 11 78 01 20 08 40 01 35 0A 95 00 28
 * 6B D0 00 23 99 46 92 46 54 46 21 78 04 20 08 40
 * 00 28 5D D0 58 20 4C 46 44 43 40 46 44 30 06 19
 * 30 68 00 28 54 D0 40 46 05 19 28 1C 72 30 00 21
 * 40 5E 29 1C 74 31 00 22 89 5E 2A 1C 76 32 00 23
 * D2 5E 44 34 44 44 23 1C 34 33 36 34 00 94 72 F7
 * F5 FD 28 1C 70 30 00 88 01 27 3C 1C 04 40 00 2C
 * 13 D1 30 68 29 1C 78 31 00 26 89 5F 2A 1C 7A 32
 * 00 23 D2 5E 00 94 01 94 02 94 03 94 04 94 05 94
 * 06 94 00 23 58 F7 B2 F8 22 E0 30 68 29 1C 78 31
 * 00 24 09 5F 2A 1C 7A 32 00 26 92 5F 00 24 00 94
 * 01 94 2B 1C 7E 33 00 26 9B 5F 02 93 03 94 2B 1C
 * 80 33 00 24 1B 5F 04 93 80 23 5B 00 05 93 06 93
 * 2B 1C 7C 33 1B 88 07 93 08 97 00 23 57 F7 44 FD
 * 01 26 B1 44 48 46 01 28 96 DD 0A 9D 0C 2D 00 DC
 * 7E E7 09 99 0E 4A 88 18 01 88 02 20 08 40 00 28
 * 0D D1 09 9C 0C 25 20 1C FF F7 02 FE 20 1C FF F7
 * 1B FF C6 23 5B 00 E4 18 01 3D 00 2D F3 DA 0B B0
 * 38 BC 98 46 A1 46 AA 46 F0 BC 01 BC 00 47 00 00
 * 3C 15 00 00. */
void func_080A9D18(State080A9D18 *state)
{
    s32 i;
    s32 j;

    for (i = 0; i < 13; i++) {
        Entry080A9D18 *entry = &state->entries[i];

        if (entry->flags & 1) {
            for (j = 0; j < 2; j++) {
                Record080A9D18 *record = &entry->records[j];

                if ((entry->flags & 4) && record->image != 0) {
                    func_0801C984(record->coordinates[0], record->coordinates[1],
                                  record->coordinates[2], &record->x, &record->y);
                    if (!(record->flags & 1))
                        func_08001F34(record->image, record->x, record->y,
                                      0, 0, 0, 0, 0, 0, 0, 0);
                    else
                        func_080018A0(record->image, record->x, record->y,
                                      0, 0, 0, record->first_offset, 0,
                                      record->second_offset, 0x100, 0x100,
                                      record->angle, 1);
                }
            }
        }
    }

    if (!(state->flags & 2)) {
        for (i = 0; i < 13; i++) {
            func_080A9A48(&state->entries[i]);
            func_080A9C80(&state->entries[i]);
        }
    }
}
