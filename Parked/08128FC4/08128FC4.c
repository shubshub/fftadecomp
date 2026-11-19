#include "ffta.h"

typedef struct {
    u8 count;
    u8 unknown_01[5];
    u8 selected[3];
    u8 special;
    u8 unknown_0A[2];
    u8 progress[0];
} AbilityState08128FC4;

typedef struct {
    u8 unknown_00[0x2A];
    u16 equipment[5];
    AbilityState08128FC4 abilities;
} Unit08128FC4;

typedef struct {
    u8 unknown_00;
    u8 unknown_01_0 : 4;
    u8 kind : 4;
    u8 index : 3;
    u8 unknown_02_3 : 5;
} __attribute__((packed)) Key08128FC4;

typedef struct {
    u8 unknown_00[8];
    Unit08128FC4 *unit;
    Key08128FC4 *key;
    u8 unknown_10[0x3A8 - 0x10];
    u8 line[0];
} State08128FC4;

typedef struct {
    u16 name;
    u8 unknown_02[2];
    u16 action;
    u8 unknown_06;
    u8 required_points;
} AbilityInfo08128FC4;

typedef struct {
    u8 unknown_0000[0x1F64];
    u32 gil;
} GameState08128FC4;

typedef void (*ClearFunction)(void *destination, u32 size);

extern GameState08128FC4 g_state_02000000;
extern const u8 *const g_table_085567F0[];
extern const u8 *const g_table_08526680[];
extern ClearFunction g_callbacks_0836D4B8[];
extern const u8 data_083A8260[];
extern const u8 data_083A8264[];
extern const u16 data_083A8268[];
extern const u16 data_083A8274[];
extern const u16 data_083A827E[];

extern u32 func_08002804(void);
extern u16 func_08018ABC(u8 *buffer, u32 value);
extern u16 func_08018C24(u8 *destination, const u8 *source);
extern u16 func_08018CB8(u8 *destination, s8 width);
extern s32 func_080C7EA4(const void *unit, u32 selector);
extern u8 func_080C95A8(u16 index);
extern void func_080C95C0(u16 index, u32 value);
extern void func_080CA2E8(void *object);
extern s32 func_080CA7A4(u16 entry, u8 selector);
extern s32 func_080CA9E8(u16 identifier, u8 quantity);
extern void func_080CAF78(Unit08128FC4 *unit, u16 entry, u8 slot);
extern u8 func_080CB2B4(u32 identifier);
extern u8 func_080CB54C(void *object, u8 enabled);
extern u8 func_080CCA80(void);
extern u32 func_080CCD50(u16 index, u8 selector);
extern u8 func_080CD1FC(const Unit08128FC4 *unit, u8 value);
extern const AbilityInfo08128FC4 *func_080CD480(u8 job, u8 ability);
extern void func_080CD544(Unit08128FC4 *unit, u8 index);
extern void func_080CD620(Unit08128FC4 *unit, u8 index);
extern void func_080CD654(Unit08128FC4 *unit, u8 value);
extern void *func_08121B64(u32 size);
extern void func_08121B78(u8 *object);
extern u8 func_08128C3C(State08128FC4 *state, u8 kind);
extern void func_08128E40(u8 count);
extern const u8 *func_08128EE0(u8 mode);

/* Draws one of the unit's abilities that holds AP (index 1 up), or 0 when none
 * does.  The ROM spills the draw to [sp, #0x10] and moves it into r5 only
 * after the list is freed (0x081291E4): it is a value returned into the
 * caller, which keeps the ability in its own register. */
static inline u8 pick_ability_with_ap(Unit08128FC4 *unit)
{
    AbilityState08128FC4 *abilities = &unit->abilities;
    u8 *learned;
    u8 selected;
    s32 n;
    s32 i;

    learned = func_08121B64(abilities->count);
    g_callbacks_0836D4B8[0](learned, abilities->count);
    selected = 0;
    for (i = 1, n = 0; i < abilities->count; i++) {
        if (abilities->progress[i] & 0x7F)
            learned[n++] = i;
    }
    if (n != 0)
        selected = learned[(s16)func_08002804() % n];
    func_08121B78(learned);
    return selected;
}

/* Moves one equipped item, or with item 0 every equipped item, from the unit
 * into the inventory.  The ROM binds the argument to a fresh register at
 * 0x08129330 (adds r5, r2, #0), and its slot walks use r4 where the caller's
 * gathering loop counted in r3. */
static inline void take_equipment(Unit08128FC4 *unit, u16 item)
{
    s32 slot;
    s32 found;

    if (item != 0) {
        for (slot = 0, found = -1; slot < 5; slot++) {
            if (unit->equipment[slot] == item) {
                found = slot;
                break;
            }
        }
        func_080CAF78(unit, 0, found);
        func_080CA9E8(item, 1);
        func_080CB54C(unit, 1);
    } else {
        for (slot = 0; slot < 5; slot++) {
            item = unit->equipment[slot];
            if (item != 0) {
                func_080CAF78(unit, 0, slot);
                func_080CA9E8(item, 1);
            }
        }
        func_080CB54C(unit, 1);
    }
    func_080CA2E8(unit);
}

/* Complete [0x08128FC4, 0x0812949C): 1240 bytes, 486 instructions.
 * Applies one event effect to the unit, selected by the key's kind, and writes
 * its message at state->line.  Returns 0, an item number tagged 0x1000 (the
 * caller draws its icon) or 0x2000 (gil). */
u16 func_08128FC4(State08128FC4 *state)
{
    Unit08128FC4 *unit = state->unit;
    u16 result = 0;
    u8 index = state->key->index;
    u8 *line = state->line;
    const u8 *text;

    switch (state->key->kind) {
    case 1: {
        u8 stat = (s16)func_08002804() % 7;

        line += func_08018C24(line, g_table_085567F0[stat + 0x2D5]);
        line += func_08018CB8(line, 5);
        *line++ = 0x81;
        *line++ = 0x0E;
        func_08018ABC(line, func_08128C3C(state, stat));
        break;
    }
    case 2:
        func_08018C24(line, func_08128EE0(index));
        break;
    case 3: {
        const u16 *items;
        s32 count;
        u16 available[6];
        s32 n;
        s32 i;
        u16 item;

        if (index == 2) {
            count = 5;
            items = data_083A8274;
        } else if (index == 3) {
            items = data_083A827E;
            count = 3;
        } else {
            items = data_083A8268;
            count = 6;
        }
        for (i = 0, n = 0; i < count; i++) {
            if (func_080CB2B4(items[i]))
                available[n++] = items[i];
        }
        if (n == 0) {
            text = g_table_085567F0[737];
        } else {
            item = available[(s16)func_08002804() % n];
            text = g_table_08526680[func_080CA7A4(item, 0)];
            func_080CA9E8(item, 99);
            result = item | 0x1000;
        }
        func_08018C24(line, text);
        break;
    }
    case 4:
        if (func_080CCA80() == 0) {
            text = g_table_085567F0[737];
        } else {
            func_08128E40(data_083A8264[index]);
            text = g_table_085567F0[index + 0x2E2];
        }
        func_08018C24(line, text);
        break;
    case 5: {
        u8 ability = pick_ability_with_ap(unit);

        if (ability == 0) {
            text = g_table_085567F0[742];
        } else {
            const AbilityInfo08128FC4 *info =
                func_080CD480(func_080C7EA4(unit, 3), ability);
            u8 level;

            text = g_table_085567F0[info->name];
            if (index == 0) {
                level = unit->abilities.progress[ability] & 0x7F;
                if (level < info->required_points / 2) {
                    if (level & 1)
                        level++;
                    level /= 2;
                } else {
                    level = info->required_points / 2;
                }
            } else {
                level = 0;
            }
            if (func_080CCD50(info->action, 0x16))
                level = 0;
            unit->abilities.progress[ability] = level;
            if (func_080CD1FC(unit, ability)) {
                func_080CD544(unit, ability);
            } else {
                func_080CD654(unit, ability);
                func_080CB54C(unit, 1);
            }
            func_080CD620(unit, ability);
        }
        func_08018C24(line, text);
        break;
    }
    case 6: {
        u16 equipped[5];
        s32 n;
        s32 i;
        u16 picked;

        g_callbacks_0836D4B8[0](equipped, sizeof(equipped));
        for (i = 0, n = 0; i < 5; i++) {
            if (unit->equipment[i] != 0)
                equipped[n++] = unit->equipment[i];
        }
        if (index == 3) {
            n = 1;
            picked = 0;
            text = g_table_085567F0[736];
        } else if (n == 0) {
            picked = 0;
            text = g_table_085567F0[737];
        } else {
            picked = equipped[(s16)func_08002804() % n];
            text = g_table_08526680[func_080CA7A4(picked, 0)];
            result = picked | 0x1000;
        }
        if (n != 0)
            take_equipment(unit, picked);
        func_08018C24(line, text);
        break;
    }
    case 7: {
        u8 level = func_080C95A8(12);

        if (index == 0) {
            if (level <= 1)
                level = 1;
        } else if (index == 1) {
            if (level <= 2)
                level = 2;
        } else {
            level = 3;
        }
        if (level == 1)
            text = g_table_085567F0[733];
        else if (level == 2)
            text = g_table_085567F0[734];
        else
            text = g_table_085567F0[735];
        if (func_080C95A8(12) < level)
            func_080C95C0(12, level);
        func_08018C24(line, text);
        break;
    }
    case 8: {
        u16 amount = 20000 / data_083A8260[index];

        if (g_state_02000000.gil <= amount)
            amount = g_state_02000000.gil;
        g_state_02000000.gil -= amount;
        line += func_08018ABC(line, amount);
        func_08018C24(line, g_table_085567F0[732]);
        result = 0x2000;
        break;
    }
    }
    return result;
}
