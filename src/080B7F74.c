#include "ffta.h"

typedef struct {
    void *unit;
    u8 unknown_04[4];
    u16 x;
    u16 z;
    u16 y;
} MapEntry;

typedef struct {
    u8 x;
    u8 y;
    u8 z;
    u8 unknown_03;
} MapPoint;

typedef struct {
    MapEntry *source;
    MapPoint *points;
    u32 count;
    u16 ability;
    u16 parameter;
} PointCollector;

extern u8 func_080B4C90(void *source, void *destination, u16 ability,
                        u16 parameter);

/* 0x080B7F74..0x080B7FC6: 82 bytes. */
u8 func_080B7F74(MapEntry *entry, PointCollector *collector)
{
    if (func_080B4C90(collector->source->unit, entry->unit,
                      collector->ability, collector->parameter)) {
        collector->points[collector->count].x = entry->x >> 5;
        collector->points[collector->count].z = entry->z >> 4;
        collector->points[collector->count].y = entry->y >> 5;
        collector->count++;
    }
    return 1;
}
