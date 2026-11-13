#include "script_record.h"

// Complete target [0x0802BA40, 0x0802BAF6): 182 bytes, 91 instructions.

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} Unit0802BA40;

typedef struct {
    Unit0802BA40 *unit;
} Entry0802BA40;

typedef struct {
    u8 unknown_00[0x5C];
    s16 unknown_5C;
} Member0802BA40;

typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
} Request0802BA40;

extern void *func_08096D7C(void);
extern u16 func_0800A018(void);
extern u32 func_08099D08(void *owner, Entry0802BA40 **out);
extern Member0802BA40 *func_08099560(void *owner, u32 key);
extern void *func_08099544(void *owner);
extern u32 func_08099CC4(void *owner);
extern u32 func_08099CD0(void *owner);

void func_0802BA40(Request0802BA40 *request, u32 key, u16 *first, u16 *second)
{
    void *owner = func_08096D7C();

    if (request->flags & 0x10) {
        const ScriptRecord *record = &g_table_0854CD54[func_0800A018()];
        Entry0802BA40 *entries[13];
        s32 count = func_08099D08(owner, entries);
        s32 active;
        s32 i;

        if (count >= 13)
            count = 13;
        active = 0;
        for (i = 0; i < count; i++) {
            if (entries[i]->unit != 0 && (entries[i]->unit->flags & 1))
                active++;
        }
        *first = active;
        *second = record->unknown_20[0];
    } else {
        u8 present;
        u32 total;

        *first = func_08099560(owner, key)->unknown_5C + 1;
        present = func_08099544(owner) != 0;
        total = func_08099CC4(owner);
        total += func_08099CD0(owner);
        *second = total + present;
    }
}
