#include "ffta.h"

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

/* Complete [0x08126ED8, 0x08126FCC): 244 bytes, 112 instructions. */
void func_08126ED8(Coordinate08126ED8 *destination, u8 first_selector,
                   u8 list_count, u8 reverse)
{
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
            copied = 0;
            while (copied < copy_count) {
                copied++;
                data_0836D4BC[0](destination,
                                  &list->entries[list->count - copied],
                                  sizeof(*destination));
                destination++;
            }
        }
    }
}
