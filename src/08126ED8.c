#include "ffta.h"

/* Complete target [0x08126ED8, 0x08126FCC), 244 bytes, 112 instructions, two
 * literal words in two pools.
 * f0b557464e464546e0b481b00906090e1206120e92461b068046002b2bd1081cfaf7aefe
 * 061c00208146d14557da074f50460138341c8034814509db226892003b684046311c1bf0
 * 97f909e0bcd436082268013a92003b684046311c1bf08cf9251c28688000043880440121
 * 89448436d145dddb33e000229146d1452fda524688180138009000994a46881a0006000e
 * faf776fe061c50460138814504db301c80300768051c04e0311c80310868471e0d1c0024
 * 01208144bc420eda01342968091b890071180a4a1368404604221bf053f904208044bc42
 * f0dbd145d3db01b038bc9846a146aa46f0bc01bc00470000bcd43608
 */

typedef struct {
    u8 x;
    u8 y;
    u8 map_value;
    u8 unknown_03;
} Coordinate08126ED8;

typedef struct {
    Coordinate08126ED8 entries[32];
    s32 count;
} CoordinateList08126ED8;

typedef void (*CopyBuffer08126ED8)(void *destination, const void *source,
                                   u32 size);

extern CoordinateList08126ED8 *func_08121C58(u8 selector);
extern CopyBuffer08126ED8 data_0836D4BC[];

void func_08126ED8(Coordinate08126ED8 *coordinates, u8 first_selector,
                   u8 list_count, u8 reverse)
{
    Coordinate08126ED8 *destination = coordinates;
    CoordinateList08126ED8 *list;
    s32 i;

    if (reverse == 0) {
        list = func_08121C58(first_selector);
        for (i = 0; i < list_count; i++, list++) {
            if (i >= list_count - 1)
                data_0836D4BC[0](destination, list->entries,
                                 list->count * sizeof(*destination));
            else
                data_0836D4BC[0](destination, list->entries,
                                 (list->count - 1) * sizeof(*destination));
            destination += list->count - 1;
        }
    } else {
        for (i = 0; i < list_count; i++) {
            s32 copy_count;
            s32 copied;

            list = func_08121C58(first_selector + list_count - 1 - i);
            if (i >= list_count - 1)
                copy_count = list->count;
            else
                copy_count = list->count - 1;
            for (copied = 0; copied < copy_count; copied++) {
                data_0836D4BC[0](destination,
                                 &list->entries[list->count - 1 - copied],
                                 sizeof(*destination));
                destination++;
            }
        }
    }
}
