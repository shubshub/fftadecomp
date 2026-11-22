#include "ffta.h"

/* Complete [0x08123E00, 0x08124238): 1080 bytes, 325 instructions, with a
 * seven-entry jump table at 0x08123E98 and its literal pools. */

typedef struct {
    u8 unknown_000[4];
    u8 present;
    u8 unknown_005[0x23];
    u16 flags;
    u8 unknown_02A[0xDE];
} Unit;

/* The block at 0x02000000 as src/0802DBA0.c declares it: the ROM reaches the
 * unit array as the base plus 0x80 (0x08123F60). */
typedef struct {
    u8 unknown_0000[0x80];
    Unit units[24];
    u8 unknown_1940[0x2FC4 - 0x1940];
    Unit second_units[12];
    u32 flags;
    u8 unknown_3C28[3];
    u8 counter_3C2B;
    u8 unknown_3C2C[2];
    u16 value_3C2E;
    u8 unknown_3C30[0x3C9C - 0x3C30];
    u16 value_3C9C;
    u8 counter_3C9E;
    u8 counter_3C9F;
} GlobalState;

typedef struct {
    u8 unknown_0000[0xA8];
    u8 state_A8;
    u8 state_A9;
    u8 state_AA;
    u8 unknown_00AB[0x1BD6 - 0xAB];
    u16 value_1BD6;
} ScriptState08123E00;

typedef struct {
    u8 unknown_00[0x94];
    u16 value_94;
    u16 value_96;
} SceneCounters08123E00;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern GlobalState g_state_02000000;
extern ScriptState08123E00 g_state_020020D0;
extern SceneCounters08123E00 g_state_0200F390;
extern u32 data_0200F3AC;
extern Table data_03002710;
extern BufferInitializer const g_callbacks_0836D4B8[];

void func_08123D50(void);
void func_080C95C0(u16 index, u32 value);
void func_08096BA0(void);
void func_08024758(void *object);
void func_080C9574(u16 bitIndex, u16 enabled);
void func_08024ABC(void *state, u8 mode);
void func_08121BF4(void);
void func_0802DBA0(void);
u8 func_080C9540(u16 bitIndex);
void func_080231E8(u8 index, u8 *flag);
void func_08096E78(u8 index, u8 *flag);
void func_080D36B0(void *context, u8 *state);
void func_080231F4(u8 index, u8 *flag);
void func_0802326C(void *context, u8 *state);
void func_080615E0(void *context, u8 *state);
void func_08064EF8(u32 unused, u8 *phase);
void func_0805CF5C(void *context, u8 *phase);
void func_0805D0E0(void *task, u8 *state);
void func_0805873C(u8 index, u8 *flag);
void func_08068AE0(u8 index, u8 *state);
void func_080543EC(u8 index, u8 *state);
void func_08050F1C(u8 index, u8 *state);

void func_08123E00(u8 mode)
{
    Unit *unit;
    s32 i;

    if (mode == 7) {
        func_08123D50();
        return;
    }

    func_080C95C0(0x35, 0);
    g_callbacks_0836D4B8[0](g_state_02000000.second_units,
                            sizeof(g_state_02000000.second_units));
    func_08096BA0();
    func_08024758(&data_0200F3AC);
    for (i = 0x244; i <= 0x24D; i++)
        func_080C9574(i, 0);
    func_080C9574(0x253, 0);
    g_state_020020D0.state_AA = 0;
    g_state_020020D0.state_A9 = 0;
    g_state_020020D0.state_A8 = 0;
    g_state_020020D0.value_1BD6 = 0;

    switch (mode) {
    case 0:
        func_080C95C0(0x33, 0);
        func_08024ABC(&data_0200F3AC, 0);
        func_08121BF4();
        func_08006ADC(&data_03002710, 4, (u32)func_080231E8);
        func_08006ADC(&data_03002710, 2, (u32)func_08096E78);
        func_08006ADC(&data_03002710, 5, (u32)func_080D36B0);
        func_08006ADC(&data_03002710, 6, (u32)func_080231F4);
        func_08006ADC(&data_03002710, 7, 0);
        break;
    case 1:
        func_080C95C0(0x33, 0);
        func_08121BF4();
        g_state_0200F390.value_96 = 0;
        g_state_0200F390.value_94 = 0;
        g_state_02000000.flags &= ~0x17;
        /* The compiler loads 0xFFFF from the pool for the first store
         * (0x08123F46) and, its register reused for the next address
         * (0x08123F4A), builds it again with movs/rsbs for the second
         * (0x08123F4E). */
        g_state_02000000.value_3C2E = 0xFFFF;
        g_state_02000000.value_3C9C = 0xFFFF;
        g_state_02000000.counter_3C9F = 0;
        g_state_02000000.counter_3C9E = 0;
        /* Walked as src/0802DBA0.c walks the same array. */
        unit = g_state_02000000.units;
        for (i = 0; i < 24; i++, unit++) {
            if (unit->present) {
                if (unit->flags & 0x400)
                    unit->flags &= ~0x400;
                if (unit->flags & 0x80)
                    unit->flags &= ~0x80;
            }
        }
        for (i = 0x220; i <= 0x226; i++)
            func_080C9574(i, 0);
        func_0802DBA0();
        func_08006ADC(&data_03002710, 4, (u32)func_080231E8);
        func_08006ADC(&data_03002710, 2, (u32)func_08096E78);
        func_08006ADC(&data_03002710, 5, (u32)func_080D36B0);
        func_08006ADC(&data_03002710, 6, (u32)func_080231F4);
        func_08006ADC(&data_03002710, 7, (u32)func_0802326C);
        break;
    case 2:
        func_080C95C0(0x33, 1);
        func_08024ABC(&data_0200F3AC, 0);
        func_08121BF4();
        g_state_02000000.counter_3C2B = 0;
        func_08006ADC(&data_03002710, 4, (u32)func_080231E8);
        func_08006ADC(&data_03002710, 2, (u32)func_08096E78);
        func_08006ADC(&data_03002710, 6, (u32)func_080231F4);
        if (func_080C9540(0x40)) {
            func_08006ADC(&data_03002710, 5, (u32)func_080615E0);
            func_08006ADC(&data_03002710, 7, (u32)func_08064EF8);
        } else {
            func_08006ADC(&data_03002710, 5, (u32)func_0805CF5C);
            func_08006ADC(&data_03002710, 7, (u32)func_0805D0E0);
        }
        break;
    case 3:
        func_080C95C0(0x33, 3);
        func_08024ABC(&data_0200F3AC, 0);
        g_state_02000000.counter_3C2B = 0;
        func_08006ADC(&data_03002710, 4, (u32)func_080231E8);
        func_08006ADC(&data_03002710, 2, (u32)func_08096E78);
        func_08006ADC(&data_03002710, 5, (u32)func_0805873C);
        func_08006ADC(&data_03002710, 6, (u32)func_080231F4);
        break;
    case 4:
        func_080C95C0(0x33, 2);
        func_08024ABC(&data_0200F3AC, 0);
        g_state_02000000.counter_3C2B = 0;
        func_08006ADC(&data_03002710, 4, (u32)func_080231E8);
        func_08006ADC(&data_03002710, 2, (u32)func_08096E78);
        func_08006ADC(&data_03002710, 5, (u32)func_08068AE0);
        func_08006ADC(&data_03002710, 6, (u32)func_080231F4);
        break;
    case 5:
        func_080C95C0(0x33, 4);
        func_08024ABC(&data_0200F3AC, 0);
        g_state_02000000.counter_3C2B = 0;
        func_08006ADC(&data_03002710, 4, (u32)func_080231E8);
        func_08006ADC(&data_03002710, 2, (u32)func_08096E78);
        func_08006ADC(&data_03002710, 5, (u32)func_080543EC);
        func_08006ADC(&data_03002710, 6, (u32)func_080231F4);
        break;
    case 6:
        func_080C95C0(0x33, 5);
        func_08024ABC(&data_0200F3AC, 0);
        g_state_02000000.counter_3C2B = 0;
        func_08006ADC(&data_03002710, 4, (u32)func_080231E8);
        func_08006ADC(&data_03002710, 2, (u32)func_08096E78);
        func_08006ADC(&data_03002710, 5, (u32)func_08050F1C);
        func_08006ADC(&data_03002710, 6, (u32)func_080231F4);
        break;
    }
}
