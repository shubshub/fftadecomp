#include "ffta.h"

/* Complete [0x080A8700, 0x080A87B4): 180 bytes, 83 instructions. */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_06[2];
} Position;

typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 z;
} Unit080A8700;

typedef struct {
    Unit080A8700 *unit;
} SceneObject;

extern s32 func_08099C1C(void *object, s8 x, s8 y);
extern u8 func_0801CC18(u8 column, u8 row);
extern SceneObject *func_080A05C4(void *owner, const Position *start,
                                  const Position *end, Position *out);

SceneObject *func_080A8700(void *owner, SceneObject *target, s8 x, s8 z,
                           Position *out)
{
    Position start;
    Position end;

    start.x = x * 32 + 16;
    start.z = z * 32 + 16;
    start.y = func_08099C1C(owner, x, z) * 16 + 24;
    end.x = target->unit->x * 32 + 16;
    end.z = target->unit->z * 32 + 16;
    end.y = func_0801CC18(target->unit->x, target->unit->z) * 16 + 24;
    return func_080A05C4(owner, &start, &end, out);
}
