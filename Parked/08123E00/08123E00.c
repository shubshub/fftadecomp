#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA8];
    u8 state_A8;
    u8 state_A9;
    u8 state_AA;
    u8 unknown_AB[0x1B2B];
    u16 value_1BD6;
} SceneScriptState;

typedef struct {
    u8 unknown_0000[0x3C24];
    u32 flags;
    u8 unknown_3C28[3];
    u8 state_3C2B;
    u8 unknown_3C2C[2];
    u16 value_3C2E;
    u8 unknown_3C30[0x6C];
    u16 value_3C9C;
    u8 state_3C9E;
    u8 state_3C9F;
} SceneState;

typedef struct {
    u8 unknown_00[0x94];
    u16 value_94;
    u16 value_96;
} SceneCounters;

typedef struct {
    u8 unknown_00[4];
    u8 present;
    u8 unknown_05[0x23];
    u16 flags;
    u8 unknown_2A[0xDE];
} Unit;

typedef void (*RegionOperation)(void *destination, u32 size);

extern SceneScriptState g_state_020020D0;
extern SceneState g_state_02000000;
extern SceneCounters g_state_0200F390;
extern Unit g_state_02000080[24];

void func_08123D50(void);
void func_080C95C0(u16 index, u32 value);
void func_08096BA0(void);
void func_08024758(void *state);
void func_080C9574(u16 index, u32 value);
void func_08024ABC(void *state, u32 value);
void func_08121BF4(void);
void func_0802DBA0(void);
u8 func_080C9540(u16 index);
void func_080231E8();
void func_08096E78();
void func_080D36B0();
void func_080231F4();
void func_0802326C();
void func_080615E0();
void func_08064EF8();
void func_0805CF5C();
void func_0805D0E0();
void func_0805873C();
void func_08068AE0();
void func_080543EC();
void func_08050F1C();

void func_08123E00(u8 mode)
{
    s32 index;
    Table *callbacks = (Table *)0x03002710;

    if (mode == 7) {
        func_08123D50();
        return;
    }

    func_080C95C0(0x35, 0);
    (*(RegionOperation const *)0x0836D4B8)((void *)0x02002FC4, 0xC60);
    func_08096BA0();
    func_08024758((void *)0x0200F3AC);

    for (index = 0x244; index <= 0x24D; index++)
        func_080C9574(index, 0);
    func_080C9574(0x253, 0);
    g_state_020020D0.state_AA = 0;
    g_state_020020D0.state_A9 = 0;
    g_state_020020D0.state_A8 = 0;
    g_state_020020D0.value_1BD6 = 0;

    switch (mode) {
    case 0:
        func_080C95C0(0x33, 0);
        func_08024ABC((void *)0x0200F3AC, 0);
        func_08121BF4();
        func_08006ADC(callbacks, 4, (u32)func_080231E8);
        func_08006ADC(callbacks, 2, (u32)func_08096E78);
        func_08006ADC(callbacks, 5, (u32)func_080D36B0);
        func_08006ADC(callbacks, 6, (u32)func_080231F4);
        func_08006ADC(callbacks, 7, 0);
        break;
    case 1:
        func_080C95C0(0x33, 0);
        func_08121BF4();
        g_state_0200F390.value_96 = 0;
        g_state_0200F390.value_94 = 0;
        g_state_02000000.flags &= ~0x17;
        g_state_02000000.value_3C2E = 0xFFFF;
        g_state_02000000.value_3C9C = 0xFFFF;
        g_state_02000000.state_3C9F = 0;
        g_state_02000000.state_3C9E = 0;

        for (index = 0; index < 24; index++) {
            Unit *unit = &g_state_02000080[index];

            if (unit->present) {
                if (unit->flags & 0x400)
                    unit->flags &= ~0x400;
                if (unit->flags & 0x80)
                    unit->flags &= ~0x80;
            }
        }

        for (index = 0x220; index <= 0x226; index++)
            func_080C9574(index, 0);
        func_0802DBA0();
        func_08006ADC(callbacks, 4, (u32)func_080231E8);
        func_08006ADC(callbacks, 2, (u32)func_08096E78);
        func_08006ADC(callbacks, 5, (u32)func_080D36B0);
        func_08006ADC(callbacks, 6, (u32)func_080231F4);
        func_08006ADC(callbacks, 7, (u32)func_0802326C);
        break;
    case 2:
        func_080C95C0(0x33, 1);
        func_08024ABC((void *)0x0200F3AC, 0);
        func_08121BF4();
        g_state_02000000.state_3C2B = 0;
        func_08006ADC(callbacks, 4, (u32)func_080231E8);
        func_08006ADC(callbacks, 2, (u32)func_08096E78);
        func_08006ADC(callbacks, 6, (u32)func_080231F4);
        if (func_080C9540(0x40)) {
            func_08006ADC(callbacks, 5, (u32)func_080615E0);
            func_08006ADC(callbacks, 7, (u32)func_08064EF8);
        } else {
            func_08006ADC(callbacks, 5, (u32)func_0805CF5C);
            func_08006ADC(callbacks, 7, (u32)func_0805D0E0);
        }
        break;
    case 3:
        func_080C95C0(0x33, 3);
        func_08024ABC((void *)0x0200F3AC, 0);
        g_state_02000000.state_3C2B = 0;
        func_08006ADC(callbacks, 4, (u32)func_080231E8);
        func_08006ADC(callbacks, 2, (u32)func_08096E78);
        func_08006ADC(callbacks, 5, (u32)func_0805873C);
        func_08006ADC(callbacks, 6, (u32)func_080231F4);
        break;
    case 4:
        func_080C95C0(0x33, 2);
        func_08024ABC((void *)0x0200F3AC, 0);
        g_state_02000000.state_3C2B = 0;
        func_08006ADC(callbacks, 4, (u32)func_080231E8);
        func_08006ADC(callbacks, 2, (u32)func_08096E78);
        func_08006ADC(callbacks, 5, (u32)func_08068AE0);
        func_08006ADC(callbacks, 6, (u32)func_080231F4);
        break;
    case 5:
        func_080C95C0(0x33, 4);
        func_08024ABC((void *)0x0200F3AC, 0);
        g_state_02000000.state_3C2B = 0;
        func_08006ADC(callbacks, 4, (u32)func_080231E8);
        func_08006ADC(callbacks, 2, (u32)func_08096E78);
        func_08006ADC(callbacks, 5, (u32)func_080543EC);
        func_08006ADC(callbacks, 6, (u32)func_080231F4);
        break;
    case 6:
        func_080C95C0(0x33, 5);
        func_08024ABC((void *)0x0200F3AC, 0);
        g_state_02000000.state_3C2B = 0;
        func_08006ADC(callbacks, 4, (u32)func_080231E8);
        func_08006ADC(callbacks, 2, (u32)func_08096E78);
        func_08006ADC(callbacks, 5, (u32)func_08050F1C);
        func_08006ADC(callbacks, 6, (u32)func_080231F4);
        break;
    }
}
