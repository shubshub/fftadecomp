#include "ffta.h"

// func_080423D4 - [0x080423D4, 0x080425F8), 548 bytes.
// Phase dispatcher for one menu slot: runs the slot's phase handler and,
// once the menu is live, refreshes its renderer.

typedef struct {
    u8 unknown_00[0x11];
    s8 cursor;
    u8 unknown_12[2];
} Controls080423D4;

typedef struct {
    u8 unknown_00[0x30];
    u16 id;
    u8 phase;
    u8 unknown_33[3];
    u8 selection;
    u8 unknown_37[0x11];
    void *source;
    u8 display[0x2c];
    u8 menu[0x20];
    s8 controls[0x14];
    u8 record[0x14];
    u32 unknown_c0;
    void *data;
    u32 unknown_c8;
} Entry080423D4;

typedef struct {
    u8 unknown_000[0x954];
    Entry080423D4 entries[0];
} Context080423D4;

typedef struct {
    u8 unknown_00[2];
    u8 unknown_02 : 7;
    u8 visible : 1;
    u8 unknown_03[0x49];
} Resource080423D4;

extern Context080423D4 *g_state_03002810;
extern Resource080423D4 data_030009E0[];
extern void func_08085450(u32, void *, void *, int);
extern void func_08041224(u32, void *, void *, u8, u8);
extern void func_08042030(u32);
extern void func_08017AF4(void *, s8, int);
extern u32 func_080415EC(u32);
extern void func_08017E28(void *);
extern void func_08037FB0(u32);
extern u8 func_08038014(u32);
extern void func_0808537C(u16, void *, int);

u8 func_080423D4(u32 index)
{
    switch (g_state_03002810->entries[index].phase) {
    case 0:
        func_08085450(index, g_state_03002810->entries[index].data,
                     g_state_03002810->entries[index].source, 4);
        g_state_03002810->entries[index].phase = 1;
        break;
    case 1:
        func_08041224(index, g_state_03002810->entries[index].display,
                     g_state_03002810->entries[index].source, 0xff, 0xff);
        g_state_03002810->entries[index].phase = 2;
        break;
    case 2:
        func_08042030(index);
        g_state_03002810->entries[index].phase = 3;
        func_08017AF4(g_state_03002810->entries[index].menu,
                     ((Controls080423D4 *)g_state_03002810->entries[index].controls)->cursor, 0x0b);
        break;
    case 3:
        g_state_03002810->entries[index].phase = func_080415EC(index);
        break;
    case 4:
        func_08017E28(g_state_03002810->entries[index].record);
        g_state_03002810->entries[index].phase = 3;
        break;
    case 5:
        break;
    case 6:
        g_state_03002810->entries[index].selection = 0xff;
        func_08037FB0(index);
        g_state_03002810->entries[index].phase = 7;
    case 7:
        if (func_08038014(index))
            g_state_03002810->entries[index].phase = 0xff;
        break;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        break;
    }
    if (g_state_03002810->entries[index].phase > 2
        && data_030009E0[g_state_03002810->entries[index].id].visible)
        func_0808537C(g_state_03002810->entries[index].id,
                     g_state_03002810->entries[index].display, 1);
    return g_state_03002810->entries[index].phase;
}
