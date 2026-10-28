#include "selection_state.h"

typedef struct {
    u8 unknown_00[0x22];
    u8 type;
    u8 unknown_23;
    u8 condition;
    u8 unknown_25[3];
} SelectionRecord;

typedef struct {
    u8 unknown_00[0x3C24];
    u32 flags;
} MainState;

extern const SelectionRecord g_table_0854CD54[];
extern u8 g_state_02000000[];
extern u8 func_080C95A8(u16 flag);
extern u8 func_08009C94(void);
extern u8 func_08009DD0(void);
extern void func_08096D7C(void);
extern u8 func_0809A7B8(void);
extern u8 func_080CED5C(u8 index);
extern void func_08009AFC(u8 code);
extern u8 func_0809A8C8(void);
extern u8 func_0809A77C(void);
extern u8 func_0809A848(void);
extern u8 func_08009CE0(void);

/* Target: complete [0x08009E9C, 0x08009FBA), 286 bytes. */
u8 func_08009E9C(u8 result)
{
    u16 index;
    const SelectionRecord *record;

    if (g_state_020020D0.override_index == 0)
        index = g_state_020020D0.index;
    else
        index = g_state_020020D0.override_index;
    record = &g_table_0854CD54[index];

    if (func_080C95A8(13) != 1)
    {
        if (func_08009C94())
            return 1;
        if (func_08009DD0())
            return 1;
    }

    if (record->condition == 0)
    {
        func_08096D7C();
        if (!func_0809A7B8())
        {
            if (func_080CED5C(0))
            {
                MainState *state = (MainState *)g_state_02000000;
                state->flags |= 4;
            }
            func_08009AFC(0xAA);
            return 1;
        }
    }

    switch (record->type)
    {
    case 0:
        func_08096D7C();
        if (!func_0809A8C8() && func_08009CE0())
            return 1;
        break;
    case 1:
        func_08096D7C();
        if (!func_0809A77C())
        {
            if (func_08009CE0())
                return 1;
            return 2;
        }
        break;
    case 3:
        func_08096D7C();
        if (!func_0809A848())
        {
            if (func_08009CE0())
                return 1;
            return 2;
        }
        break;
    case 2:
        func_08096D7C();
        if (!func_0809A77C())
            return 2;
        break;
    }
    return result;
}
