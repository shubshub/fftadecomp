#include "ffta.h"

/* Complete 0x0812D660..0x0812D7FC: 412 bytes, 195 instructions and two
 * literal words (0x0812D7A0, 0x0812D7F8).
 * f0b557464e464546e0b486b0071c0e1c1c1c1206002a00d176e01621f630049000228256f723db199a461b781b061b16f624a419a146002020560090f720801980460078000600160190351cf8350020285602900391381c311cfff78ffd05901821049b00229a5654460023e3564c4600202056009044460020205601900020285602900391381c311cfff777fd05990c183321049b00229a56504600780006001684464b4600201856009043460020185601900020285602900391381c311c6346fff75bfd2418132104980022825653461b781b061b169a464b4600201856009043460020185601900020285602900391381c311c5346fff740fd2018002800da033080103fe0d5f64cf800040014652115f0edf800040214002308490888121a3d1cf635f720c0198046f62080198146f72080198246f8208019844607e084843a0801331448990009180888121a002af7dc488820800023e15e0022aa5644460023e3564c46002020560090544600202056019064460020205602900391381c311cfff7fafc06b038bc9846a146aa46f0bc02bc084784843a08
 */
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

extern const WeightedKind data_083A8484[];
extern s32 func_0812D1DC(const Object *, const Object *, s8, s8,
                         s8, s8, s8, s32);
extern u32 func_08002804(void);

/* The same helper as src/0812D7FC.c. */
static inline s32 chance(const Object *source, const Object *target, s32 kind)
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

    if (average) {
        s32 total;

        total = chance(source, target, 0x16);
        total += chance(source, target, 0x18);
        total += chance(source, target, 0x33);
        total += chance(source, target, 0x13);
        return total / 4;
    }
    roll = (s16)func_08002804() % 101;
    for (i = 0; ; i++) {
        roll -= data_083A8484[i].weight;
        if (roll <= 0) {
            *kind = data_083A8484[i].kind;
            break;
        }
    }
    return chance(source, target, *kind);
}
