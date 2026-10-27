#include "ffta.h"

/* 0x0812EF94..0x0812F008: 116 bytes. */
typedef struct {
    u8 unknown_00[0xF6];
    s8 x;
    s8 y;
    s8 height;
} PositionedUnit;

extern int func_0812C7F4(PositionedUnit *, PositionedUnit *, u16,
                        s8, s8, s8, s8, s8, u8, u8);
extern u8 func_080CDA64(const PositionedUnit *);

int func_0812EF94(PositionedUnit *source, PositionedUnit *target,
                  u16 entry, u8 mode, u8 option)
{
    int result = func_0812C7F4(source, target, entry,
                              source->x, source->y,
                              target->x, target->y, target->height,
                              mode, option);

    if (result != 0 && func_080CDA64(target))
        result = 100;
    return result;
}
