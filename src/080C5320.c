#include "ffta.h"

struct Unit {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
};

struct Actor {
    struct Unit *unit;
    u8 unknown_04[0x38];
    void *map;
};

struct Grid;

struct Context {
    struct Actor *actor;
    struct Actor *target;
    u8 unknown_08[0xC];
    struct Grid *grid;
    u8 destination_x;
    u8 destination_y;
    u8 direction;
    u8 flags;
    u8 unknown_1C;
    u8 height_limit;
    u8 unknown_1E[2];
    u16 stage;
};

extern u8 func_080CDB84(const void *object);
extern int func_080C4B20(struct Context *context);
extern int func_080C50EC(struct Context *context);
extern int func_080C4E78(struct Context *context);

/* Complete 080C5320..080C5396, 118 bytes:
 * 10b5041c2068006808f02cfc0006002801d000202077207f013804281ed880000149
 * 4018006887464c530c0860530c088e530c088e530c0868530c0870530c08201cfff7
 * ddfb06e0201cfff7bffe02e0201cfff781fd0006000e09e021680868f63000782076
 * 0868f73000786076002010bc02bc0847
 */
u8 func_080C5320(struct Context *context)
{
    if (func_080CDB84(context->actor->unit))
        context->unknown_1C = 0;

    switch (context->unknown_1C) {
    case 1:
        return (u8)func_080C4B20(context);
    case 4:
        return (u8)func_080C50EC(context);
    case 5:
        return (u8)func_080C4E78(context);
    case 2:
    case 3:
        break;
    default:
        context->destination_x = context->actor->unit->x;
        context->destination_y = context->actor->unit->y;
        break;
    }
    return 0;
}
