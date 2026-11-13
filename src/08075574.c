#include "script_record.h"

// Complete target [0x08075574, 0x08075620): 172 bytes, 76 instructions.

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} Member08075574;

typedef struct {
    Member08075574 *member;
} Entry08075574;

extern void *func_08096D7C(void);
extern u16 func_0800A018(void);
extern u32 func_08099D08(void *owner, Entry08075574 **out);
extern u16 *func_0808B8E4(u32 window, u32 plane, s32 x, s32 y);
extern void func_08035A68(u16 *dst, u16 count, u32 value, u16 base);

void func_08075574(void)
{
    Entry08075574 *entries[13];
    void *owner = func_08096D7C();
    const ScriptRecord *record = &g_table_0854CD54[func_0800A018()];
    s16 count = func_08099D08(owner, entries);
    s32 active = 0;
    s32 i;
    u8 value;
    u16 *destination;
    s16 shown;

    for (i = 0; i < count; i++) {
        Member08075574 *member = entries[i]->member;

        if (member != 0 && (member->flags & 1))
            active++;
    }
    shown = active;
    value = record->unknown_20[0];

    destination = func_0808B8E4(3, 1, 10, 0);
    func_08035A68(destination, 2, shown, shown != 0 ? 0xf000 : 0xa000);
    func_08035A68(func_0808B8E4(3, 1, 13, 0), 2, value,
                  value != 0 ? 0xf000 : 0xa000);
}
