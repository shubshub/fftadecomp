#include "ffta.h"

struct Info08042EC4 {
    union {
        s32 count;
        u16 halves[2];
    } value;
};

struct List08042EC4 {
    u8 unknown_00[0x1a];
    u16 selection;
    u8 unknown_1c[0x2c];
};

struct Record08042EC4 {
    u8 unknown_00[0x30];
    u16 id;
    u8 unknown_32[0x16];
    struct Info08042EC4 *info;
    u8 first[0x2c];
    struct List08042EC4 second;
    const void *text;
    u8 unknown_c4[8];
};

struct State08042EC4 {
    u8 unknown_000[0x954];
    struct Record08042EC4 records[1];
};

struct Unit08042EC4 {
    u8 unknown_00[0xe];
    u16 value;
    u8 unknown_10[0x3c];
};

typedef void (*Callback08042EC4)(void);

extern struct State08042EC4 *g_state_03002810;
extern struct Unit08042EC4 data_030009E0[];
extern void func_08016210(u8 *, const void *, u32, u32);
extern u32 func_08017B50(struct List08042EC4 *);
extern void func_08042EB8(struct List08042EC4 *);
extern void func_08042D4C(s32, s16, struct List08042EC4 *);
extern void func_08042E48(struct List08042EC4 *, u16);
extern void func_08037F74(u8 *, Callback08042EC4, Callback08042EC4, u32, u32);
extern void func_08038028(void);
extern void func_08038024(void);
extern void func_08038238(void);

/* Target: [0x08042EC4, 0x08042FDC), 280 bytes, 111 instructions. */
void func_08042EC4(s32 index)
{
    u32 id = g_state_03002810->records[index].id;
    s32 count;
    s32 i;

    func_08016210(g_state_03002810->records[index].first,
                 g_state_03002810->records[index].text,
                 data_030009E0[id].value,
                 g_state_03002810->records[index].info->value.halves[0]);
    count = (u16)func_08017B50(&g_state_03002810->records[index].second);
    func_08042EB8(&g_state_03002810->records[index].second);
    for (i = 0; i < count; i++)
        func_08042D4C(index, i, &g_state_03002810->records[index].second);
    func_08042E48(&g_state_03002810->records[index].second,
                 (u16)(g_state_03002810->records[index].second.selection * 2));
    if (g_state_03002810->records[index].info->value.count > 0) {
        func_08037F74(g_state_03002810->records[index].first,
                     func_08038028, func_08038238, 0, 13);
    } else {
        func_08037F74(g_state_03002810->records[index].first,
                     func_08038024, func_08038238, 0, 13);
    }
}
