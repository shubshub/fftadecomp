#include "positioned_equipment.h"

/* Complete target [0x0812C7F4, 0x0812C8DC): 232 bytes. */
typedef struct Unit Unit;

extern const s8 data_083A8444[];
extern u8 func_0812C56C(Unit *unit);
extern u8 func_0812C5CC(Unit *unit, u16 entry, u8 option);
extern s32 func_0812C610(Unit *unit);
extern s32 func_0812C634(Unit *source, Unit *target);
extern s32 func_0812C670(s32 value);
extern s32 func_0812C700(s8 source_x, s8 source_y, s8 target_x, s8 target_y, s8 direction);
extern s32 func_0812C7B8(Unit *unit);
extern u8 func_0812F0E4(Unit *unit, s8 x, s8 y);

s32 func_0812C7F4(Unit *source, Unit *target, u16 entry,
                  s8 source_x, s8 source_y, s8 target_x, s8 target_y,
                  s8 direction, u32 check_position, u8 option)
{
    s32 value;

    if (!func_0812C56C(target))
        return 100;
    if (check_position && func_0812F0E4(target, target_x, target_y) &&
        func_0812C5CC(target, entry, option))
        return 0;

    value = func_0812C7B8(target);
    value /= data_083A8444[func_0812C700(source_x, source_y, target_x, target_y, direction)];
    value += func_0812C634(source, target);
    value += func_0812C610(source);
    value = func_0812C670(value);
    return 100 - value;
}
