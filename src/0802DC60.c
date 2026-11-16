#include "ffta.h"

/* Complete [0x0802DC60, 0x0802DD58): 248 bytes, 117 instructions, including
 * the two-word literal pool at 0x0802DD28.
 * f0b557464e464546e0b481b00006000e00900906090e88461206120e924600f067f9041c
 * 002c5fd00098ff285cd0264b002684461725072189461a78110958784f46384000010843
 * 002804d01007000f604500d10136013d0433002dedda012e42dc0f200099014022781020
 * 4042104008430f2341461940090118400843207041460809072707253840627808267642
 * 311c1140014352465042c00fc0000922524211400143617042461001074a8018407b0001
 * 194001436170201c00f09cf8002805d1a0700ee03c3c0002348f520800f02ef92a1c0240
 * a178301c084010433840a0700020e07001b038bc9846a146aa46f0bc01bc0047
 */

typedef struct {
    u16 group : 4;
    u16 count : 7;
    u16 active : 1;
    u16 unknown_0C : 4;
    u16 unknown_10 : 3;
    u16 unknown_13 : 5;
    u8 unknown_03;
} __attribute__((packed)) GroupRecord;

typedef struct {
    u8 unknown_00[0xD];
    u8 unknown_0D;
    u8 unknown_0E[2];
} SelectionEntry;

typedef struct Unit Unit;

extern GroupRecord data_02003C3C[24];
extern const SelectionEntry g_table_08528F34[];

extern GroupRecord *func_0802DF50(void);
extern Unit *func_0802DE58(const GroupRecord *key);
extern u8 func_0802DF90(const Unit *unit);

void func_0802DC60(u8 id, u8 selector, u8 active)
{
    GroupRecord *record = func_0802DF50();
    GroupRecord *entry;
    Unit *unit;
    s32 matches;
    s32 i;

    if (record == 0 || id == 0xFF)
        return;

    entry = data_02003C3C;
    matches = 0;
    for (i = 0; i < 24; i++, entry++) {
        if (entry->count != 0 && entry->group == id)
            matches++;
    }
    if (matches > 1)
        return;

    record->group = id;
    record->count = selector;
    record->active = active != 0;
    record->unknown_0C = (g_table_08528F34 + selector)->unknown_0D;
    unit = func_0802DE58(record);
    if (unit == 0) {
        record->unknown_10 = 0;
        record->unknown_13 = 0;
        record->unknown_03 = 0;
    } else {
        record->unknown_10 = func_0802DF90(unit);
        record->unknown_13 = 0;
        record->unknown_03 = 0;
    }
}
