#include "ffta.h"

// 0x0812D7FC..0x0812D99C: 416 bytes, complete target span.
typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
    u8 direction;
} Object;

typedef struct {
    u16 weight;
    u16 kind;
} WeightedKind;

extern const WeightedKind data_083A8494[];
extern s32 func_0812D1DC(const Object *, const Object *, s8, s8,
                         s8, s8, s8, s32);
extern s32 func_0812C8DC(const Object *, const Object *, u32, u32);
extern s16 func_08002804(void);

static inline s32 chance(const Object *source, const Object *target, s32 kind)
{
    return func_0812D1DC(source, target, (s8)source->x, (s8)source->y,
                         (s8)target->x, (s8)target->y,
                         (s8)target->direction, kind);
}

s32 func_0812D7FC(const Object *source, const Object *target, u8 average,
                  s16 *kind)
{
    s32 roll;
    u32 i;

    if (average) {
        s32 total;

        total = chance(source, target, 0x16);
        total += chance(source, target, 0x18);
        total += chance(source, target, 0x23);
        total += chance(source, target, 0x1B);
        return total / 4;
    }
    roll = (s16)(func_08002804() % 101);
    for (i = 0; ; i++) {
        if (i > 3) {
            *kind = -1;
            return func_0812C8DC(source, target, 2, 0);
        }
        roll -= data_083A8494[i].weight;
        if (roll <= 0)
            break;
    }
    *kind = data_083A8494[i].kind;
    return chance(source, target, *kind);
}
