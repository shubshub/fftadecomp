#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0a : 6;
} SelectedResource0801904C;

typedef struct {
    const SelectedResource0801904C *current;
    u32 unknown_04;
    u32 unknown_08;
    u16 id;
} ResourceSelection0801904C;

extern ResourceSelection0801904C g_state_020020D0;
extern const u8 *const g_table_08526680[];

u32 func_080CE4DC(u16 id, u32 field);
u8 func_080C9400(u8 key);
u32 func_080C8570(u8 first, u8 second, u8 selector);
u16 func_08018C24(u8 *destination, const u8 *text);

u32 func_0801904C(u8 *destination)
{
    u16 id = g_state_020020D0.current
        ? g_state_020020D0.current->id : g_state_020020D0.id;
    u8 unit = func_080C9400(func_080CE4DC(id, 0x30));
    u16 index = func_080C8570(unit, unit, 0);

    func_08018C24(destination, g_table_08526680[index]);
    return 0;
}
