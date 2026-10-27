#include "ffta.h"

struct Unit08050E1C;

struct Cursor08050E1C {
    u8 unknown_00[4];
    struct Unit08050E1C *unit;
    u8 unknown_08[8];
    u8 flags;
};

struct Menu08050E1C {
    u8 unknown_00[0x7C];
    struct Cursor08050E1C cursor;
};

extern void func_08017E28(struct Cursor08050E1C *cursor);

void func_08050E1C(struct Menu08050E1C *menu)
{
    func_08017E28(&menu->cursor);
}
