#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2190];
    u8 mode;
} ScriptModeState;

typedef struct {
    u8 unknown_00[0x1C];
    u8 view[0x28];
    u8 unknown_44[0x50];
    u16 flags;
} ScriptViewState;

extern ScriptModeState g_state_02000000;
extern ScriptViewState g_state_0200F390;

void func_0800397C(u8 enabled);
void func_08096BA0(void);
u8 func_080C95A8(u16 index);
void func_080BD11C(u8 value);
void *func_08096D7C(void);
void func_0809AB14(void *context);
void func_081256BC(void);
void func_08024758(void *view);
void func_08121BF4(void);
void func_080231E8(u8 index, u8 *flag);
void func_08096E78(u8 index, u8 *flag);
void func_080D36B0(u8 index, u8 *flag);
void func_080231F4(u8 index, u8 *flag);
void func_0802326C(u8 index, u8 *flag);

void func_08123D50(void)
{
    ScriptViewState *state;
    Table *callbacks;

    func_0800397C(g_state_02000000.mode != 2);
    state = &g_state_0200F390;
    state->flags |= 0x80;
    func_08096BA0();
    func_080BD11C(func_080C95A8(0x35));
    func_0809AB14(func_08096D7C());
    func_081256BC();
    func_08024758(state->view);
    func_08121BF4();
    callbacks = (Table *)0x03002710;
    func_08006ADC(callbacks, 4, (u32)func_080231E8);
    func_08006ADC(callbacks, 2, (u32)func_08096E78);
    func_08006ADC(callbacks, 5, (u32)func_080D36B0);
    func_08006ADC(callbacks, 6, (u32)func_080231F4);
    func_08006ADC(callbacks, 7, (u32)func_0802326C);
}
