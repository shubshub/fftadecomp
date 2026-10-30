#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} FlaggedObject;

typedef struct {
    u8 unknown_00[9];
    u8 field_09;
    u8 value;
    u8 unknown_0B[0xF];
    u16 field_1A;
    u16 unknown_1C;
    u16 field_1E;
    u16 field_20;
    u16 field_22;
    u16 field_24;
    u16 field_26;
    u16 flags;
    u8 unknown_2A[0xA8];
    s16 field_D2;
} ValueUnit;

extern u8 func_080C8298(const FlaggedObject *object);
extern u32 func_080C92F0(void *object, u32 selector);
extern u32 func_08002804(void);
extern s32 func_081426B8(s32 numerator, s32 denominator);
extern s32 func_08142950(s32 numerator, s32 denominator);

/* Complete [0x080C9B8C, 0x080C9E00): 628 bytes, 276 instructions.
 * 70b5051c687a013000216872a972281cfef77cfb0006002800d025e1687a322805d9322068726320
 * a87200201de1688b002824d0281c2921fff794fb041c0a2178f074fd698b09186983201c0a2178f0
 * b9fe041c002c0dd038f70efe000400140a2178f0affe00040014a04202da688b01306883688b7e49
 * 884200d96983e88b002824d0281c2a21fff76cfb041c0a2178f04cfde98b0918e983201c0a2178f0
 * 91fe041c002c0dd038f7e6fd000400140a2178f087fe00040014a04202dae88b0130e883e88b6a49
 * 884200d9e983281cd2300022815e061c002925d0281c2b21fff740fb041c0a2178f020fd31880918
 * 3180201c0a2178f065fe041c002c0dd038f7bafd000400140a2178f05bfe00040014a04202da3088
 * 013030800021705e5349884200dd3180288c002824d0281c2c21fff717fb041c0a2178f0f7fc298c
 * 09182984201c0a2178f03cfe041c002c0dd038f791fd000400140a2178f032fe00040014a04202da
 * 288c01302884288c3f49884200d92984688c002824d0281c2d21fff7effa041c0a2178f0cffc698c
 * 09186984201c0a2178f014fe041c002c0dd038f769fd000400140a2178f00afe00040014a04202da
 * 688c01306884688c2b49884200d96984a88c002824d0281c2e21fff7c7fa041c0a2178f0a7fca98c
 * 0918a984201c0a2178f0ecfd041c002c0dd038f741fd000400140a2178f0e2fd00040014a04202da
 * a88c0130a884a88c1749884200d9a984e88c002824d0281c2f21fff79ffa041c0a2178f07ffce98c
 * 0918e984201c0a2178f0c4fd041c002c0dd038f719fd000400140a2178f0bafd00040014a04202da
 * e88c0130e884e88c0349884200d9e984012070bc02bc0847e7030000
 */
u8 func_080C9B8C(ValueUnit *unit)
{
    s32 value;

    unit->field_09++;
    unit->value = 0;
    if (func_080C8298((const FlaggedObject *)unit))
        return 1;
    if (unit->field_09 > 50) {
        unit->field_09 = 50;
        unit->value = 99;
        return 0;
    }

    if (unit->field_1A != 0) {
        value = (s32)func_080C92F0(unit, 0x29);
        unit->field_1A += func_081426B8(value, 10);
        value = func_08142950(value, 10);
        if (value != 0) {
            if ((s16)func_08142950((s16)func_08002804(), 10) < value)
                unit->field_1A++;
        }
        if (unit->field_1A > 999)
            unit->field_1A = 999;
    }

    if (unit->field_1E != 0) {
        value = (s32)func_080C92F0(unit, 0x2A);
        unit->field_1E += func_081426B8(value, 10);
        value = func_08142950(value, 10);
        if (value != 0) {
            if ((s16)func_08142950((s16)func_08002804(), 10) < value)
                unit->field_1E++;
        }
        if (unit->field_1E > 999)
            unit->field_1E = 999;
    }

    if (unit->field_D2 != 0) {
        value = (s32)func_080C92F0(unit, 0x2B);
        unit->field_D2 += func_081426B8(value, 10);
        value = func_08142950(value, 10);
        if (value != 0) {
            if ((s16)func_08142950((s16)func_08002804(), 10) < value)
                unit->field_D2++;
        }
        if (unit->field_D2 > 999)
            unit->field_D2 = 999;
    }

    if (unit->field_20 != 0) {
        value = (s32)func_080C92F0(unit, 0x2C);
        unit->field_20 += func_081426B8(value, 10);
        value = func_08142950(value, 10);
        if (value != 0) {
            if ((s16)func_08142950((s16)func_08002804(), 10) < value)
                unit->field_20++;
        }
        if (unit->field_20 > 999)
            unit->field_20 = 999;
    }

    if (unit->field_22 != 0) {
        value = (s32)func_080C92F0(unit, 0x2D);
        unit->field_22 += func_081426B8(value, 10);
        value = func_08142950(value, 10);
        if (value != 0) {
            if ((s16)func_08142950((s16)func_08002804(), 10) < value)
                unit->field_22++;
        }
        if (unit->field_22 > 999)
            unit->field_22 = 999;
    }

    if (unit->field_24 != 0) {
        value = (s32)func_080C92F0(unit, 0x2E);
        unit->field_24 += func_081426B8(value, 10);
        value = func_08142950(value, 10);
        if (value != 0) {
            if ((s16)func_08142950((s16)func_08002804(), 10) < value)
                unit->field_24++;
        }
        if (unit->field_24 > 999)
            unit->field_24 = 999;
    }

    if (unit->field_26 != 0) {
        value = (s32)func_080C92F0(unit, 0x2F);
        unit->field_26 += func_081426B8(value, 10);
        value = func_08142950(value, 10);
        if (value != 0) {
            if ((s16)func_08142950((s16)func_08002804(), 10) < value)
                unit->field_26++;
        }
        if (unit->field_26 > 999)
            unit->field_26 = 999;
    }
    return 1;
}
