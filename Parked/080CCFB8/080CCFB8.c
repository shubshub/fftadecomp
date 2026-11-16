// 0x080CCFB8 - 306 bytes: 206 of code, 2 of padding, a 12-byte literal pool
// (g_table_0851BA84, g_callbacks_0836D4B8, g_table_08520080) and 86 more
// bytes of code, ending at 0x080CD0EA.
//
// Collects the selection indices of a unit's job row that sit at the given
// level and are either flagged on the unit (+0x40 table, bit 0x80) or named
// by one of the unit's five equipped entries.  Writes them to out and
// returns how many were written.
#include "ffta.h"

typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u8 marker;
    u8 value;
} __attribute__((packed)) EffectPair;

typedef struct {
    u8 count;
    u8 unknown_01;
    EffectPair pairs[9];
} EffectRecord;

typedef struct {
    u8 unknown_00[6];
    u8 level;
    u8 unknown_07;
} SelectionInfo;

typedef struct {
    u8 unknown_00[7];
    u8 category;              /* +0x07 */
    u8 unknown_08[0x22];
    u16 entries[5];           /* +0x2A */
    u8 count;                 /* +0x34 */
    u8 unknown_35[0x0B];
    u8 flags[0];              /* +0x40 */
} Unit;

extern const SelectionInfo *const g_table_0851BA84[];
extern BufferInitializer const g_callbacks_0836D4B8[];
extern const EffectRecord g_table_08520080[];

extern s32 func_080C7EA4(const void *unit, u32 selector);
extern s32 func_080CA7A4(u16 identifier, u8 selector);

/* The text of func_080CD560 (src/080CD560.c), inlined: the ROM repeats its
   null test, 0/1 result and u8 index narrowing at 0x080CD068-0x080CD096. */
static inline u8 IsFlagged(const void *object, u8 index)
{
    const u8 *record = object;

    if (record != 0) {
        const u8 *flags = record + 0x40;

        if (flags[index] & 0x80)
            return 1;
    }
    return 0;
}

u8 func_080CCFB8(Unit *unit, u8 *list, u8 level)
{
    u8 found[0x20];
    u8 *out = list;
    const SelectionInfo *row;
    s32 count;
    s32 i;
    s32 k;

    row = g_table_0851BA84[func_080C7EA4(unit, 3)];
    row++;
    g_callbacks_0836D4B8[0](found, sizeof(found));

    count = 0;
    for (i = 0; i <= 4; i++) {
        if (unit->entries[i] != 0) {
            const EffectRecord *effects =
                &g_table_08520080[func_080CA7A4(unit->entries[i], 0x12)];

            for (k = 0; k < effects->count; k++) {
                if (effects->pairs[k].marker != 0
                    && effects->pairs[k].marker == unit->category)
                    found[count++] = effects->pairs[k].value;
            }
        }
    }

    for (i = 1; i < unit->count; i++, row++) {
        if (row->level == level) {
            if (IsFlagged(unit, i)) {
                *out++ = i;
            } else {
                for (k = 0; k < count; k++) {
                    if (found[k] == i)
                        *out++ = i;
                }
            }
        }
    }

    return out - list;
}
