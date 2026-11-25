#include "ffta.h"

// Complete target: [0x08040F38, 0x08041224), 748 bytes, 257 instructions.
typedef struct {
    u32 words[5];
} Record08040F38;

typedef struct {
    u8 unknown_00[0x20];
} Menu08040F38;

typedef struct {
    u8 unknown_00[0x11];
    s8 cursor;
    u8 unknown_12[2];
} Controls08040F38;

typedef struct {
    u8 unknown_00[0x30];
    u16 id;
    u8 phase;
    u8 unknown_33[3];
    u8 selection;
    u8 unknown_37;
    u16 key;
    u8 dirty;
    u8 unknown_3b[0x0d];
    void *source;
    u8 display[0x2c];
    Menu08040F38 menu;
    s8 controls[0x14];
    Record08040F38 record;
    u32 unknown_c0;
    void *data;
    u32 unknown_c8;
} Entry08040F38;

typedef struct {
    u8 unknown_000[0x4a0];
    Record08040F38 record;
    u8 mode;
    u8 saved;
    u8 unknown_4b6[0x49e];
    Entry08040F38 entries[0];
} Context08040F38;

extern Context08040F38 *g_state_03002810;
extern u8 data_030027A4;
extern u8 data_02003CB0[];
extern u8 data_03000990[];
extern u8 data_030008B0[];
extern void func_08085450(u32, void *, void *, int);
extern void func_08040628(u32, void *, void *, u8, u8);
extern void func_08040E30(u32);
extern void func_08017AF4(Menu08040F38 *, s8, int);
extern void func_080407A4(u32);
extern u32 func_0804082C(u32, u16);
extern void func_08017E28(Record08040F38 *);
extern void func_08037FB0(u32);
extern u8 func_08038014(u32);
extern void func_08031708(u8);
extern void func_08019A8C(void *, u16, void *, void *);
extern void func_08013428(int);
extern u16 func_08011860(void);
extern void func_080356A0(u32, u8);
extern void func_0808537C(u16, void *, int);

u32 func_08040F38(u32 index, u16 mask)
{
    switch (g_state_03002810->entries[index].phase) {
    case 0:
        g_state_03002810->entries[index].selection = 0;
        func_08085450(index, g_state_03002810->entries[index].data,
                     g_state_03002810->entries[index].source, 4);
        g_state_03002810->entries[index].phase = 1;
        break;
    case 1:
        func_08040628(index, g_state_03002810->entries[index].display,
                     g_state_03002810->entries[index].source, 0xff, 0xff);
        g_state_03002810->entries[index].phase = 2;
        break;
    case 2:
        func_08040E30(index);
        func_08017AF4(&g_state_03002810->entries[index].menu,
                     ((Controls08040F38 *)g_state_03002810->entries[index].controls)->cursor, 0x0b);
        g_state_03002810->entries[index].phase = 3;
        func_080407A4(index);
        break;
    case 3:
        g_state_03002810->entries[index].phase = func_0804082C(index, mask);
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
    case 9:
        g_state_03002810->saved = data_030027A4;
        func_08031708(0x3f);
        func_08019A8C(data_02003CB0, g_state_03002810->entries[index].key,
                     data_03000990, data_030008B0);
        func_08013428(-0x120);
        g_state_03002810->entries[index].phase = 11;
        break;
    case 11:
        if (func_08011860()) {
            func_08031708(g_state_03002810->saved);
            g_state_03002810->entries[index].dirty = 1;
            g_state_03002810->entries[index].record = g_state_03002810->record;
            func_080356A0(index, g_state_03002810->mode);
            g_state_03002810->entries[index].phase = 3;
        }
        break;
    }
    if (g_state_03002810->entries[index].phase > 2)
        func_0808537C(g_state_03002810->entries[index].id,
                     g_state_03002810->entries[index].display, 1);
    return g_state_03002810->entries[index].phase;
}
