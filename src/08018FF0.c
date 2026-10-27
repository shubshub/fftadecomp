#include "ffta.h"

/* 0x08018FF0..0x0801904C: 92 bytes. */
struct __attribute__((packed)) SelectedResource08018FF0 {
    u16 id : 10;
    u16 unknown_0A : 6;
};

struct Selection08018FF0 {
    const struct SelectedResource08018FF0 *current;
    u32 unknown_04;
    u32 unknown_08;
    u16 id;
};

extern struct Selection08018FF0 g_state_020020D0;
extern const u8 *const g_table_085567F0[];
extern u32 func_080CE4DC(u16 id, u8 selector);
extern u16 func_08018C24(u8 *destination, const u8 *source);

u32 func_08018FF0(u8 *destination)
{
    u16 index = func_080CE4DC(g_state_020020D0.current
                            ? g_state_020020D0.current->id
                            : g_state_020020D0.id, 0x2E);

    if (index != 0)
        index += 0x61;
    func_08018C24(destination, g_table_085567F0[index]);
    if (index == 0)
        return 13;
    return 0;
}
