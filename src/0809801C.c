#include "ffta.h"

typedef struct {
    u8 unknown_00[0xfd];
    u8 movement;
} Unit0809801C;

typedef struct {
    Unit0809801C *unit;
    u32 unknown_04;
    s16 x;
    s16 height;
    s16 y;
    u8 unknown_0E[0x10];
    u8 value_1E;
    u8 unknown_1F[0x11];
    u32 flags_30;
    u16 value_34;
} Display0809801C;

typedef struct {
    s32 x : 16;
    s32 height : 16;
    s32 y : 16;
} Position0809801C;

extern u8 func_0801CC7C(u8 column, u8 row);
extern u8 func_0801CD08(u8 column, u8 row);
extern u8 func_0801CC18(u8 column, u8 row);
extern u16 func_08022238(void *object, u8 *output);
extern u16 func_08022268(void *object, u8 *output);

/* An inlined copy of func_0809995C (src/0809995C.c). */
static inline u8 inlined_0809995C(Display0809801C *context)
{
    Position0809801C position;

    position.height = context->height >> 4;
    position.x = context->x >> 5;
    position.y = context->y >> 5;
    if (context->unit->movement != 2)
        return 0;
    if (position.x < 0 || position.y < 0 || position.x > 15 || position.y > 15)
        return 0;
    if (!func_0801CC7C((u16)position.x, (u16)position.y))
        return 0;
    if (!(func_0801CD08((u16)position.x, (u16)position.y) & 2))
        return 0;
    if ((s8)func_0801CC18((u16)position.x, (u16)position.y) <= position.height)
        return 0;
    return 1;
}

/* An inlined copy of func_0809A340 (src/0809A340.c). */
static inline void inlined_0809A340(Display0809801C *object)
{
    u8 output;

    object->value_34 = func_08022238(object->unit, &output);
    if (object->flags_30 & 0x20)
        object->value_34 = 0x2A;
    object->value_1E = output;
}

/* An inlined copy of func_0809A36C (src/0809A36C.c). */
static inline void inlined_0809A36C(Display0809801C *object)
{
    u8 output;

    object->value_34 = func_08022268(object->unit, &output);
    if (object->flags_30 & 0x20)
        object->value_34 = 0xE6;
    object->value_1E = output;
}

/* Complete [0x0809801C, 0x0809812E): 274 bytes, 127 instructions.
 * Target: f0b5474680b481b0051c286b802149020840002801d0286867e068890004001500041649194001432889000440150004000c134a904646460e400643b0464346a889000440150004000c2240141c04432868011cfd310f78011c022f0bd118040214002a07db20040014002803db0f2a01dc0f2806dd002028e00000ffff00000000ffff1806060e2006040e301c211c84f7e6fd0006002801d1002015e0301c211c84f723fe0740002f01d100200ce0301c211c84f7a2fd0006001642461114884201dc002000e00120296800280bd0081c69468af7baf8a886286b2021084000280dd0e6200ae0081c69468af796f8a886286b20210840002801d02a20a88668460078a87701b008bc9846f0bc01bc0047
 */
void func_0809801C(Display0809801C *display)
{
    /* Two copies of the func_0809A340 call: the ROM loads display->unit on
     * each path (0x08098032; 0x080980E6 moved at 0x08098104) and the copies
     * share their tail from 0x08098106. */
    if (display->flags_30 & 0x10000)
        inlined_0809A340(display);
    else if (inlined_0809995C(display))
        inlined_0809A36C(display);
    else
        inlined_0809A340(display);
}
