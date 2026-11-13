#include "ffta.h"

// Target: complete [0x0812D660, 0x0812D7FC), 412 bytes.
// The weighted table at 0x083A8484 holds {weight, kind} halfword pairs.
typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
    u8 direction;
} Object;

typedef struct {
    u16 weight;
    u16 kind;
} Entry0812D660;

extern const Entry0812D660 data_083A8484[];
extern s32 func_0812D1DC(const Object *, const Object *, s8, s8,
                         s8, s8, s8, s32);
extern s16 func_08002804(void);

static inline s32 Chance(const Object *source, const Object *target, s32 kind)
{
    return func_0812D1DC(source, target, (s8)source->x, (s8)source->y,
                         (s8)target->x, (s8)target->y,
                         (s8)target->direction, kind);
}

s32 func_0812D660(const Object *source, const Object *target, u8 average,
                  s16 *kind)
{
    s32 roll;
    u32 i;
    const Entry0812D660 *entry;

    if (average) {
        s32 total;

        total = Chance(source, target, 0x16) + Chance(source, target, 0x18);
        total += Chance(source, target, 0x33);
        total += Chance(source, target, 0x13);
        return total / 4;
    }
    roll = (s16)(func_08002804() % 101);
    i = 0;
    entry = &data_083A8484[i];
    roll -= entry->weight;
    for (;;) {
        if (roll <= 0) {
            *kind = entry->kind;
            return Chance(source, target, *kind);
        }
        i++;
        entry = &data_083A8484[i];
        roll -= entry->weight;
    }
}
