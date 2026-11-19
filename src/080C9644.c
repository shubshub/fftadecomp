#include "ffta.h"

typedef struct {
    u32 value;
    u8 kind;
    u8 unknown_05;
    u8 unknown_06;
    u8 unknown_07;
    u8 unknown_08;
    u8 level;
    u8 unknown_0A;
    u8 unknown_0B;
    u8 unknown_0C;
    u8 unknown_0D;
    u8 unknown_0E;
    u8 unknown_0F;
    u8 unknown_10;
    u8 unknown_11;
    u8 unknown_12;
    u8 unknown_13;
    u8 unknown_14;
    u8 unknown_15[3];
    u16 hp;
    u16 max_hp;
    u16 mp;
    u16 max_mp;
    u16 unknown_20;
    u16 unknown_22;
    u16 unknown_24;
    u16 unknown_26;
    u16 flags;
    u8 unknown_2A[0xA8];
    u16 unknown_D2;
    u8 unknown_D4[2];
    u16 unknown_D6;
    u8 unknown_D8[0x1E];
    u8 unknown_F6;
    u8 unknown_F7;
    u8 unknown_F8;
    u8 unknown_F9[7];
    u8 unknown_100;
    u8 unknown_101[4];
    u8 unknown_105;
    u8 unknown_106;
    u8 unknown_107;
} Unit;

typedef struct {
    u8 kind;
    u8 unknown_01;
    u8 unknown_02;
    u8 level;
    u8 level_spread;
    u8 unknown_05;
    u8 unknown_06;
    u8 unknown_07;
    u16 items[5];
    u16 unknown_12;
    u8 unknown_14[0x16];
    u16 flags;
    u8 unknown_2C;
    u8 unknown_2D;
} UnitSource;

typedef struct {
    u8 unknown_00;
    u8 unknown_01;
    u8 unknown_02;
    u8 unknown_03;
    u8 unknown_04[10];
} __attribute__((packed)) KindEntry;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer g_callbacks_0836D4B8[];
extern const KindEntry g_table_085273D8[];
extern const u32 g_table_085516D0[];

extern s32 func_080CA7A4(u16 entry, u8 selector);
extern u32 func_080C92F0(void *object, u32 selector);
extern u8 func_080C8298(void *object);
extern u8 func_080C8240(void *object);
extern u8 func_080C8260(void *object);
extern u8 func_080C9B8C(Unit *unit);
extern s16 func_08002838(s32 range);
extern u32 func_08002804(void);
extern u8 func_080CA078(void);
extern void func_080CA268(Unit *unit, UnitSource *source);
extern void func_080C9F88(Unit *unit, UnitSource *source);
extern void func_080CA22C(Unit *unit);
extern void func_080CA2E8(Unit *unit);
extern void func_080CA0BC(Unit *unit, u8 index);
extern void func_080C9E00(Unit *unit);
extern u8 func_08009FBC(void);
extern s32 func_080C7EA4(const void *object, u32 selector);
extern void func_080C9574(u16 index, u16 enabled);

/* A stat with a random spread: the ROM repeats this block for each of the
 * seven stats at 0x080C9866-0x080C9A12, three func_080C92F0 calls apiece. */
#define VARIED(selector) \
    (func_080C92F0(unit, selector) + \
     (func_080C92F0(unit, selector) / 20 - \
      func_08002838(func_080C92F0(unit, selector) / 20 * 2)))

/* Complete [0x080C9644, 0x080C9B8C): 1352 bytes, 573 instructions.
 * f0b557464e464546e0b486b0071c88461206120e92463048842149000268381c78f0f2fd398d4246
 * 508d01433985107814380006000e032804d880235b01181c014339854146488a244ab91808700026
 * 2d2343449946381cd2300090391cf63102913a1cf73203923b1cf83304930430019041462c310591
 * 454608352c1c2088062101f06df8012805d02088062101f067f8022805d12088032101f061f81428
 * 20d1023402350136042ee8d942461078021c012a22d043461978c800401a40000749411848787871
 * 5878002812d18878f871c87817e00000b8d4360805010000d87352082888024ab9180870dee70000
 * 07010000f8714346987804e0414648787871f871887838724b461978002903d080235b00f8180170
 * 3a71381c0121fff7c5fdb871381c0d21fff7c0fdf87201253d73381c0e21fff7b9fd7873381c0f21
 * fff7b4fdb873381c1021fff7affdf873381c1121fff7aafd3874381c1221fff7a5fd7874381c1321
 * fff7a0fdb874381c1421fff79bfdf874381c1521fff796fd3875381cfef766fd0006002849d0381c
 * 1721fff78bfd0004000c002800d10a207883194c3883381c1821fff77ffd0004000c002800d10a20
 * f883000400142040b883381c1a21fff771fd3884381c1b21fff76cfd7884381c1c21fff767fdb884
 * 381c1d21fff762fdf884381c1921fff75dfd009908800a245246002a00d054467d72012503e00000
 * ffff00000135a54200db1fe1381c00f097f900060028f5d118e1381c1721fff741fd041c381c1721
 * fff73cfd061c381c1721fff737fd142179f014f9400038f7d5ff051c301c142179f00cf9401b2418
 * 2404200c002800d10a2078835d4b99463883381c1821fff71dfd041c381c1821fff718fd061c381c
 * 1821fff713fd142179f0f0f8400038f7b1ff051c301c142179f0e8f8401b24182404200c002800d1
 * 0a20f8830004001449460840b883381c1a21fff7f7fc051c381c1a21fff7f2fc061c381c1a21fff7
 * edfc142179f0caf8400038f78bff041c301c142179f0c2f8001b2d183d84381c1b21fff7dbfc051c
 * 381c1b21fff7d6fc061c381c1b21fff7d1fc142179f0aef8400038f76fff041c301c142179f0a6f8
 * 001b2d187d84381c1c21fff7bffc051c381c1c21fff7bafc061c381c1c21fff7b5fc142179f092f8
 * 400038f753ff041c301c142179f08af8001b2d18bd84381c1d21fff7a3fc051c381c1d21fff79efc
 * 061c381c1d21fff799fc142179f076f8400038f737ff041c301c142179f06ef8001b2d18fd84381c
 * 1921fff787fc051c381c1921fff782fc061c381c1921fff77dfc142179f05af8400038f71bff041c
 * 301c142179f052f8001b2d18009a15805346002b04d054462fe00000ffff00004146c878002801d0
 * 041c12e000f022fb041c38f7e5fe2406240e00040014032178f084ff0004001401382418002c00dc
 * 01244246107900280fd038f7d1fe0004001443461979013178f070ff2018002802dd0006040e00e0
 * 012401207872012500e00135a54205da381c00f07df800060028f6d1788b00243883f88bb883381c
 * 414600f0dffb381c414600f06bfa381c00f0bafb381c00f015fc41464879029a10708879039b1870
 * c87904990870019a148043461978c800401a4000044941180878002806d0011c381c00f0e5fa04e0
 * d8735208381c00f081f90599087800280bd02049059a1078800040180068386083235b00f9180120
 * 087040f74dfa0006002827d1381cfef789fb0006002821d1381cfef793fb000600281bd1381cfef7
 * a9fb0006002815d1381c0321fef7a8f90006ff2109064018000e04280ad8f87902380006000e2928
 * 04d8f87903300121fff7fefc06b038bc9846a146aa46f0bc01bc0047d0165508
 */
void func_080C9644(Unit *unit, UnitSource *source, u8 level)
{
    u32 i;
    s32 count;
    s32 n;
    u16 value;
    const KindEntry *entry;

    g_callbacks_0836D4B8[0](unit, sizeof(Unit));
    unit->flags |= source->flags;
    if (source->kind >= 0x14 && source->kind <= 0x17)
        unit->flags |= 0x1000;
    unit->unknown_105 = source->unknown_12;

    for (i = 0; i < 5; i++) {
        if ((func_080CA7A4(source->items[i], 6) == 1
             || func_080CA7A4(source->items[i], 6) == 2)
            && func_080CA7A4(source->items[i], 3) != 0x14) {
            /* The u8 store (ldrh/strb at 0x080C9728..0x080C972E) is lossless:
             * every id this test admits is <= 0xFC, because the only category
             * 1/2 ids above 0xFC in g_table_0851D180 (0xFD..0x108) have type
             * 0x14. */
            unit->unknown_107 = source->items[i];
            break;
        }
    }

    if (source->kind != 1) {
        entry = &g_table_085273D8[source->kind];
        unit->unknown_05 = entry->unknown_01;
        if (source->unknown_01 == 0) {
            unit->unknown_07 = entry->unknown_02;
            unit->unknown_08 = entry->unknown_03;
        } else {
            unit->unknown_07 = source->unknown_01;
            unit->unknown_08 = source->unknown_02;
        }
    } else {
        unit->unknown_05 = source->unknown_01;
        unit->unknown_07 = source->unknown_01;
        unit->unknown_08 = source->unknown_02;
    }
    if (source->unknown_2D)
        unit->unknown_100 = source->unknown_2D;
    unit->kind = source->kind;

    unit->unknown_06 = func_080C92F0(unit, 1);
    unit->unknown_0B = func_080C92F0(unit, 13);
    unit->unknown_0C = 1;
    unit->unknown_0D = func_080C92F0(unit, 14);
    unit->unknown_0E = func_080C92F0(unit, 15);
    unit->unknown_0F = func_080C92F0(unit, 16);
    unit->unknown_10 = func_080C92F0(unit, 17);
    unit->unknown_11 = func_080C92F0(unit, 18);
    unit->unknown_12 = func_080C92F0(unit, 19);
    unit->unknown_13 = func_080C92F0(unit, 20);
    unit->unknown_14 = func_080C92F0(unit, 21);

    if (func_080C8298(unit)) {
        value = func_080C92F0(unit, 23);
        if (value == 0)
            value = 10;
        unit->hp = unit->max_hp = value;
        value = func_080C92F0(unit, 24);
        if (value == 0)
            value = 10;
        unit->mp = unit->max_mp = value;
        unit->unknown_20 = func_080C92F0(unit, 26);
        unit->unknown_22 = func_080C92F0(unit, 27);
        unit->unknown_24 = func_080C92F0(unit, 28);
        unit->unknown_26 = func_080C92F0(unit, 29);
        unit->unknown_D2 = func_080C92F0(unit, 25);
        count = 10;
        if (level)
            count = level;
        unit->level = 1;
        for (n = 1; n < count; n++) {
            if (!func_080C9B8C(unit))
                break;
        }
    } else {
        value = VARIED(23);
        if (value == 0)
            value = 10;
        unit->hp = unit->max_hp = value;
        value = VARIED(24);
        if (value == 0)
            value = 10;
        unit->mp = unit->max_mp = value;
        unit->unknown_20 = VARIED(26);
        unit->unknown_22 = VARIED(27);
        unit->unknown_24 = VARIED(28);
        unit->unknown_26 = VARIED(29);
        unit->unknown_D2 = VARIED(25);
        if (level) {
            count = level;
        } else {
            if (source->level) {
                count = source->level;
            } else {
                count = func_080CA078() - 1
                        + (s16)((s16)func_08002804() % 3);
                if (count <= 0)
                    count = 1;
            }
            if (source->level_spread) {
                s32 spread = count
                             + (s16)func_08002804() % (source->level_spread + 1);

                if (spread > 0)
                    count = (u8)spread;
                else
                    count = 1;
            }
        }
        unit->level = 1;
        for (n = 1; n < count; n++) {
            if (!func_080C9B8C(unit))
                break;
        }
    }

    unit->hp = unit->max_hp;
    unit->mp = unit->max_mp;
    func_080CA268(unit, source);
    func_080C9F88(unit, source);
    func_080CA22C(unit);
    func_080CA2E8(unit);
    unit->unknown_F6 = source->unknown_05;
    unit->unknown_F7 = source->unknown_06;
    unit->unknown_F8 = source->unknown_07;
    unit->unknown_D6 = 0;
    entry = &g_table_085273D8[source->kind];
    if (entry->unknown_00)
        func_080CA0BC(unit, entry->unknown_00);
    else
        func_080C9E00(unit);
    if (source->unknown_2C) {
        unit->value = g_table_085516D0[source->unknown_2C];
        unit->unknown_106 = 1;
    }
    if (!func_08009FBC() && !func_080C8240(unit) && !func_080C8260(unit)
        && !func_080C8298(unit)) {
        /* Narrowed to u8 before the range test: lsls #24 at 0x080C9B54,
         * then the u8 subtraction at 0x080C9B56-0x080C9B5C. */
        u8 job = func_080C7EA4(unit, 3);

        if ((job >= 1 && job <= 5)
            && (unit->unknown_07 >= 2 && unit->unknown_07 <= 43))
            func_080C9574(unit->unknown_07 + 3, 1);
    }
}
