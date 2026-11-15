#include "ffta.h"

/* Complete target: [0x080CF690, 0x080CF7F4), 356 bytes, 173 instructions,
 * two literal words in two pools.
 * f0b54f464646c0b481b0002700251048804607220026414674182178101c084000281fd06178
 * 80200840002812d0a078c006c00e0021009266f7bafe009a002808d161787f20084060700148
 * 80460de0342e00022178101c084041498846002800d0013706360135042dd4dd212040428146
 * 00218c46042564464444217807200840002824d0a178202008400e1c00281ed1617880200840
 * 002819d16279fe23181c104000280dd0f02806d051080139490001201040084360716179181c
 * 0840002805d14020304349460840a070002706208444013d002dceda052f39d1072601277f42
 * 00254446a17840200840002822d1002322780720104000280fd061788020084000280ad13020
 * 1040002806d160790106480eb04201da061c2f1c06330135042d08dc41465c18a17840200840
 * 0028dfd001277f4201204042874208d07800c019400041464418a07840210843a07001b018bc
 * 9846a146f0bc01bc0047342e0002
 */

/* The 6-byte record as src/080D0F74.c declares it, except bits 3..7, of which
 * this function tests bits 4..5: unknown_03 and mode are as src/080445DC.c
 * declares them.  The state holds five of them at 0x2E34, which is entries[5]
 * at 0x224 of the block at 0x02002C10 in src/08044158.c. */
typedef struct {
    u8 category : 3;
    u8 unknown_03 : 1;
    u8 mode : 2;
    u8 unknown_06 : 2;
    u8 unknown_08 : 7;
    u8 disabled : 1;
    u8 selection : 5;
    u8 primary : 1;
    u8 secondary : 1;
    u8 resource : 8;
    u8 unknown_1f : 1;
    u16 id : 9;
    u16 unknown_29 : 7;
} __attribute__((packed)) ActionEntry;

typedef struct {
    u8 unknown_00[0x2E34];
    ActionEntry records[5];
} ItemListState;

extern ItemListState g_state_02000000;
extern u32 func_08036440(u8 value, u32 mode);

void func_080CF690(void)
{
    ActionEntry *record;
    /* The number of occupied records in the first two loops, then the index
     * of the selected record, -1 for none: one variable, r7 throughout. */
    s32 n = 0;
    s32 i;
    s32 minimum;

    for (i = 0; i < 5; i++) {
        record = &g_state_02000000.records[i];
        if (record->category && record->disabled && !func_08036440(record->selection, 0)) {
            record->disabled = 0;
            break;
        }
        if (record->category)
            n++;
    }
    for (i = 0; i < 5; i++) {
        record = &g_state_02000000.records[i];
        if (record->category && !record->primary && !record->disabled) {
            if (record->unknown_29 != 0 && record->unknown_29 != 0x78)
                record->unknown_29--;
            if (record->unknown_29 == 0) {
                record->secondary = 1;
                record->primary = 0;
                n = 0;
            }
        }
    }
    if (n == 5) {
        minimum = 7;
        n = -1;
        for (i = 0; i < 5; i++) {
            record = &g_state_02000000.records[i];
            if (record->secondary) {
                n = -1;
                break;
            }
            if (record->category && !record->disabled && !record->mode
                && record->unknown_29 < minimum) {
                minimum = record->unknown_29;
                n = i;
            }
        }
        if (n != -1) {
            record = &g_state_02000000.records[n];
            record->secondary = 1;
        }
    }
}
