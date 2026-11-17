#include "ffta.h"

// Target: [0x0803D034, 0x0803D094), 96 bytes, 48 instructions.
// f0b581b0061c0f1c13480024311c0e2204f112fc8c2080003518b56100943c700e4800684068
// 447f002c0ed0a01e042804d86846211c2a1cfff79efe6846211c2a1c0123fff73eff38700098
// 306001b0f0bc02bc08470000c418390810280003

struct Entry0803D034 {
    u8 unknown_00[0x14];
};

struct List0803D034 {
    s32 count;
    u8 unknown_04[0x14];
    struct Entry0803D034 *entries;
    u8 unknown_1c[0x214];
    struct Entry0803D034 storage[1];
};

typedef struct {
    u8 unknown_00[0x1d];
    u8 group;
} Data0803D034;

typedef struct {
    u32 unknown_00;
    Data0803D034 *data;
} State0803D034;

extern State0803D034 *g_state_03002810;
extern const u8 data_083918C4[];
extern void func_0814186C(const void *, void *, u32);
extern void func_0803CDAC(s32 *, s32, struct Entry0803D034 *);
extern u8 func_0803CEF8(s32 *, s32, struct Entry0803D034 *, s32);

s32 func_0803D034(struct List0803D034 *list, u8 *result)
{
    s32 count;
    struct Entry0803D034 *entries;
    const u8 *src = data_083918C4;
    s32 group = 0;

    func_0814186C(src, list, 14);
    entries = list->storage;
    list->entries = entries;
    count = 0;
    *result = 0;
    group = g_state_03002810->data->group;
    if (group) {
        if ((u32)(group - 2) <= 4)
            func_0803CDAC(&count, group, entries);
        *result = func_0803CEF8(&count, group, entries, 1);
    }
    list->count = count;
    return count;
}
