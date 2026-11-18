#include "ffta.h"

typedef struct {
    u8 unknown_00[0x94];
    u16 flags;
} BattleState;

typedef struct {
    u8 unknown_0000[0x1F6C];
    u16 count;
} ProgressState;

typedef struct {
    u8 unknown_00[4];
    u8 kind;
    u8 unknown_05[0x23];
    u16 flags;
    u8 unknown_2A[0xC6];
    u8 counter;
    u8 unknown_F1[0x10];
    u8 field_101;
    u8 unknown_102[6];
} Unit;

extern BattleState g_state_0200F390;
extern ProgressState g_state_02000000;
extern Unit g_state_02000080[24];
extern void func_080C95C0(u16 index, u32 value);
extern void func_080C9574(u16 index, u16 enabled);
extern u8 func_080C95A8(u16 index);
extern void func_080CBF34(void);

void func_08124F24(void)
{
    Unit *unit;
    s32 i;

    func_080C95C0(6, 1);
    if (g_state_0200F390.flags & 0x80)
        return;
    func_080C9574(0x45, 1);
    if (g_state_02000000.count < 0xFFFF)
        g_state_02000000.count++;
    if (g_state_02000000.count == 10 || g_state_02000000.count == 20)
        func_080C9574(0x3B, 1);
    func_080CBF34();

    unit = g_state_02000080;
    for (i = 0; i < 24; i++, unit++) {
        if (unit->kind) {
            if (unit->counter)
                unit->counter--;
            if (func_080C95A8(13) != 1 && (unit->flags & 1))
                unit->flags |= 0x80;
            unit->field_101 = 0;
        }
    }
}
