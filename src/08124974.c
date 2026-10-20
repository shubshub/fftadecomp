#include "ffta.h"

typedef struct {
    u8 x;
    u8 y;
    u8 mapValue;
    u8 unknown_03;
} CoordinateEntry;

typedef struct {
    CoordinateEntry entries[32];
    s32 count;
} CoordinateList;

CoordinateList *func_08121C58(u8 selector);
u8 func_0801CC18(u8 x, u8 y);

void func_08124974(u8 start_x, u8 start_y, u8 end_x, u8 end_y, u8 selector)
{
    CoordinateList *list = func_08121C58(selector);
    s8 coordinate;
    CoordinateEntry *entry;

    list->count = 0;
    if (start_x == end_x) {
        if (start_y > end_y) {
            for (coordinate = start_y; coordinate >= end_y; coordinate--) {
                entry = &list->entries[list->count];
                list->count++;
                entry->x = start_x;
                entry->y = coordinate;
                entry->mapValue = func_0801CC18(entry->x, entry->y);
                entry->unknown_03 = 0;
            }
        } else {
            for (coordinate = start_y; coordinate <= end_y; coordinate++) {
                entry = &list->entries[list->count];
                list->count++;
                entry->x = start_x;
                entry->y = coordinate;
                entry->mapValue = func_0801CC18(entry->x, entry->y);
                entry->unknown_03 = 0;
            }
        }
    } else if (start_y == end_y) {
        if (start_x > end_x) {
            for (coordinate = start_x; coordinate >= end_x; coordinate--) {
                entry = &list->entries[list->count];
                list->count++;
                entry->x = coordinate;
                entry->y = start_y;
                entry->mapValue = func_0801CC18(entry->x, entry->y);
                entry->unknown_03 = 0;
            }
        } else {
            for (coordinate = start_x; coordinate <= end_x; coordinate++) {
                entry = &list->entries[list->count];
                list->count++;
                entry->x = coordinate;
                entry->y = start_y;
                entry->mapValue = func_0801CC18(entry->x, entry->y);
                entry->unknown_03 = 0;
            }
        }
    }
}
