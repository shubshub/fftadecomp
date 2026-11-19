#include "script_entry.h"

/* Complete target: [0x080CF7F4, 0x080CFA48), 596 bytes, 268 instructions,
 * ten literal words in two pools.
 * f0b5474680b42349234a88180078042800d81ae10027072320480a1804251178181c08400028
 * 00d001370632013d002df5da032f00dd08e119483818047832f7e7ff00040014642173f088f8
 * 00040014a04200ddf9e000270125124c2806000e66f76cfd0006002801d020783f1801340135
 * 1e2df2dd002f00d1e6e032f7c8ff00040014391c73f069f8041c0125054e0ce0000000000002
 * 90210000342e00004c3a5608503a5608013601351e2d0adc2806000e66f742fd00060028f4d0
 * 3078241a002cf0da1f2d00d1bee02f1c00253a4e317807200840b44600280bd00723321c0632
 * 0135042d05dc161c3178181c08400028f5d10024e122d2199046002360461a18117807200840
 * 002809d09078c009d1787f22114049000143414500d193e006330134042ceadd25480268301c
 * 062172f091fc7800c0198000214940188079c400241aa400241a1f482418691c072001403078
 * 0822524202400a430820024331204042024032706378db065b0f0325291c194089013f201040
 * 084330709b082b407078073d05401d43757062785209a0781f210840c30013438021181c0840
 * 002814d0094803401f20034099007d20404205400d43757015e0342e0002b8d43608fc445608
 * 704656087fff0000181c66f7b3fc1f210140890072787d204042104008437070002030717179
 * 02380840707140460204110c01242140c901b3787f25281c18400843b070520c2a40f1788020
 * 404208401043f0703806000e66f78cfc1f210140b278202040421040084320210843b0707078
 * 802108437070707904400c200443747108bc9846f0bc01bc0047
 */

/* The 6-byte record as src/080D0B48.c declares it; the state holds five of
 * them at 0x2E34. */
typedef struct {
    u16 category : 3;
    u16 unknown_03 : 1;
    u16 mode : 2;
    u16 type : 4;
    u16 unknown_0a : 5;
    u16 disabled : 1;
    u16 selection : 5;
    u16 primary : 1;
    u16 secondary : 1;
    u16 resource : 8;
    u16 unknown_1f : 1;
    u16 id : 9;
    u16 unknown_29 : 7;
} __attribute__((packed)) ActionEntry;

typedef struct {
    u8 unknown_0000[0x2190];
    u8 unknown_2190;
    u8 unknown_2191[0xCA3];
    ActionEntry records[5];
} ItemListState;

/* One 27-byte row, as src/080D0B48.c declares it. */
typedef struct {
    u8 unknown_00;
    u16 mode : 1;
    u16 unknown_09 : 1;
    u16 type : 3;
    u16 value : 8;
    u16 unknown_15 : 3;
    u8 unknown_03[24];
} __attribute__((packed)) SelectionRecord;

extern ItemListState g_state_02000000;
/* A chance out of 100 for each number of occupied records, 0 to 3. */
extern const u8 g_table_08563A4C[];
/* The weight of each of the 30 categories, category 1 first. */
extern const u8 g_table_08563A50[];
/* Script entries 0xE1 and up of g_table_08563A70 (12 * 0xE1 = 0xA8C). */
extern const ScriptEntry g_table_085644FC[];
extern const SelectionRecord g_table_08564670[];
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern u32 func_08002804(void);
extern u8 func_08036330(u8 selector);

/* With byte 0x2190 of the state above 4 and at most three of the five records
 * occupied, a random roll against the chance for that number picks one of
 * the 30 categories that func_08036330 reports, weighted by its table.  When
 * no occupied record already holds that category's resource (0xE1 plus the
 * category), the first free record is cleared and filled in from the
 * category's script entry and selection row. */
void func_080CF7F4(void)
{
    ActionEntry *entry;
    const ScriptEntry *script;
    const SelectionRecord *record;
    /* The number of occupied records, then the sum of the weights, then the
     * chosen category: one variable, r7 throughout, as n is in
     * src/080CF690.c. */
    s32 n;
    s32 i;
    s32 j;
    s32 remaining;
    u8 threshold;
    s16 random;

    if (g_state_02000000.unknown_2190 <= 4)
        return;
    n = 0;
    for (i = 0; i < 5; i++) {
        entry = &g_state_02000000.records[i];
        if (entry->category != 0)
            n++;
    }
    if (n > 3)
        return;
    threshold = g_table_08563A4C[n];
    random = (s16)func_08002804() % 100;
    if (random > threshold)
        return;
    n = 0;
    for (i = 1; i <= 30; i++) {
        if (func_08036330(i))
            n += g_table_08563A50[i - 1];
    }
    if (n == 0)
        return;
    remaining = (s16)func_08002804() % n;
    for (i = 1; i <= 30; i++) {
        if (func_08036330(i)) {
            remaining -= g_table_08563A50[i - 1];
            if (remaining < 0)
                break;
        }
    }
    if (i == 31)
        return;
    n = i;
    for (i = 0; i < 5; i++) {
        entry = &g_state_02000000.records[i];
        if (entry->category == 0)
            break;
    }
    for (j = 0; j < 5; j++) {
        ActionEntry *other = &g_state_02000000.records[j];

        if (other->category != 0 && other->resource == n + 0xE1)
            return;
    }
    g_callbacks_0836D4B8[0](entry, sizeof(*entry));
    script = &g_table_085644FC[n];
    record = &g_table_08564670[script->selector];
    entry->category = i + 1;
    entry->unknown_03 = 1;
    entry->mode = 0;
    entry->type = record->type;
    if (record->value & 0x80)
        entry->unknown_0a = record->value & ~0x80;
    else
        entry->unknown_0a = func_08036330(record->value);
    entry->id = 0;
    entry->resource = n + 0xE1;
    entry->selection = func_08036330(n);
    entry->primary = 1;
    entry->disabled = 1;
    entry->unknown_29 = 6;
}
