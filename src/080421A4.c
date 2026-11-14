#include "ffta.h"

// Complete target: [0x080421A4, 0x080423D4), 560 bytes.
typedef struct {
    u32 words[5];
} Record080421A4;

typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 unknown_12[0x0e];
} Menu080421A4;

typedef struct {
    u8 unknown_00[0x11];
    s8 cursor;
    u8 unknown_12[2];
} Controls080421A4;

typedef struct {
    u8 unknown_00[0x30];
    u16 id;
    u8 phase;
    u8 unknown_33[3];
    u8 selection;
    u8 unknown_37[0x11];
    void *source;
    u8 display[0x2c];
    Menu080421A4 menu;
    s8 controls[0x14];
    Record080421A4 record;
    u32 unknown_c0;
    void *data;
    u32 unknown_c8;
} Entry080421A4;

typedef struct {
    u8 unknown_000[0x954];
    Entry080421A4 entries[0];
} Context080421A4;

typedef struct {
    u8 unknown_00[2];
    u8 flags;
    u8 unknown_03[0x49];
} Renderer080421A4;

extern Context080421A4 *g_state_03002810;
extern Renderer080421A4 data_030009E0[];
extern void func_08085450(u32, void *, void *, int);
extern void func_08041224(u32, void *, void *, u8, u8);
extern void func_08042030(u32);
extern void func_08017AF4(Menu080421A4 *, s8, int);
extern u32 func_080413A0(u32);
extern void func_08017E28(Record080421A4 *);
extern void func_08037FB0(u32);
extern u8 func_08038014(u32);
extern void func_0808537C(u16, void *, int);

u8 func_080421A4(u32 index)
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
        g_state_03002810->entries[index].menu.flags |= 2;
        func_08017AF4(&g_state_03002810->entries[index].menu,
                     ((Controls080421A4 *)g_state_03002810->entries[index].controls)->cursor, 0x0b);
        g_state_03002810->entries[index].phase = 3;
        break;
    case 3:
        g_state_03002810->entries[index].phase = func_080413A0(index);
        break;
    case 4:
        func_08017E28(&g_state_03002810->entries[index].record);
        g_state_03002810->entries[index].phase = 3;
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
        break;
    case 13:
        break;
    }
    if (g_state_03002810->entries[index].phase > 2
        && data_030009E0[g_state_03002810->entries[index].id].flags >> 7)
        func_0808537C(g_state_03002810->entries[index].id,
                     g_state_03002810->entries[index].display, 1);
    return g_state_03002810->entries[index].phase;
}
