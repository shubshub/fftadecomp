#include "script_entry.h"

/* Complete [0x081253CC, 0x08125444): 120 bytes, 44 instructions. */
typedef struct {
    u8 unknown_0000[0x3C2A];
    u8 index;
} BranchState081253CC;

typedef struct {
    u8 unknown_00;
    u8 active;
    u8 unknown_02[0x92];
    u16 flags;
    u16 mode;
} ScriptState081253CC;

extern BranchState081253CC g_state_02000000;
extern ScriptState081253CC g_state_0200F390;
extern void *func_080C83CC(u8);
extern void *func_08096D7C(void);
extern void *func_08099560(void *, void *);
extern void func_080CE380(void *, u8);
extern void func_081247B4(u8);

void func_081253CC(void)
{
    u32 offset = g_state_02000000.index * sizeof(ScriptEntry);
    const ScriptEntry *entry = (const ScriptEntry *)
        ((const u8 *)g_table_08563A70 + offset);

    if (entry->flags & 4) {
        void *record = func_080C83CC(2);

        if (func_08099560(func_08096D7C(), record))
            func_080CE380(record, 1);
    }
    func_081247B4(0xFF);
    g_state_0200F390.active = 0;
    g_state_0200F390.flags = (g_state_0200F390.flags & ~1) | 2;
    g_state_0200F390.mode = 0;
}
