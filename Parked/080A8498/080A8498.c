#include "ffta.h"

typedef struct Actor080A8498 Actor080A8498;
typedef struct Position080A8498 Position080A8498;

/* The workspace starts after eight outgoing words. The callee reads its
 * signed halfword count at +0x48 and passes the workspace to 080A0BB8. */
typedef struct {
    u32 unknown_00[18];
    s16 count;
    u8 unknown_4A[0x136];
} PathWork080A8498;

extern s32 func_080A12FC(PathWork080A8498 *work, Actor080A8498 *source,
                         Actor080A8498 *target, s8 x, s8 y, s8 range, s16 height,
                         Actor080A8498 **hit, s32 *result, Position080A8498 *position,
                         u32 option, u32 flags);

/* Complete [0x080A8498, 0x080A84E8), 80 bytes. */
s32 func_080A8498(Actor080A8498 *source, Actor080A8498 *target, s8 x, s8 y,
                  s8 range, Actor080A8498 **hit, Position080A8498 *position,
                  s32 *result)
{
    PathWork080A8498 work;
    return func_080A12FC(&work, source, target, x, y, range, 0x400,
                         hit, result, position, 0, 0);
}
