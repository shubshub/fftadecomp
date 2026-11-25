#include "ffta.h"

// Target: [0x08040388, 0x08040628), 672 bytes, 226 instructions.

/* The layout and member names of the merged siblings 080421A4, 080423D4 and
 * 08043120, which step their entries the same way. */
struct Controls08040388 {
    u8 unknown_00[0x11];
    s8 cursor;
    u8 unknown_12[2];
};

struct Entry08040388 {
    u8 unknown_00[0x30];
    u16 id;
    u8 phase;
    u8 unknown_33[3];
    u8 selection;
    u8 unknown_37;
    u16 key;
    u8 unknown_3a[0xe];
    void *source;
    u8 display[0x2c];
    u8 menu[0x20];
    s8 controls[0x14];
    u8 record[0x14];
    u8 unknown_c0[4];
    void *data;
    u8 unknown_c8[4];
};

struct State08040388 {
    u8 unknown_000[0x4b4];
    u8 mode;
    u8 saved;
    u8 unknown_4b6[0x49e];
    struct Entry08040388 entries[1];
};

extern struct State08040388 *g_state_03002810;

extern u8 data_030027A4;
extern u8 data_02003CB0[];
extern u8 data_03000990[];
extern u8 data_030008B0[];
extern void func_08085450(u32, void *, void *, int);
extern void func_0803FAA4(u32, void *, void *, u8, u8);
extern void func_08040280(s32);
extern void func_08017AF4(void *, u32, u32);
extern u32 func_0803FC20(u32 index, u32 mask);
extern void func_08017E28(void *);
extern void func_08037FB0(u32);
extern u8 func_08038014(u32);
extern void func_08031708(u8);
extern void func_08019A8C(void *, u16, void *, void *);
extern void func_08013428(int);
extern u16 func_08011860(void);
extern u8 func_080356A0(s32, u8);
extern void func_0808537C(u16, void *, int);

u32 func_08040388(u32 index, u16 mask)
{
    switch (g_state_03002810->entries[index].phase) {
    case 0:
        func_08085450(index, g_state_03002810->entries[index].data,
                      g_state_03002810->entries[index].source, 4);
        g_state_03002810->entries[index].phase = 1;
        break;
    case 1:
        func_0803FAA4(index, g_state_03002810->entries[index].display,
                      g_state_03002810->entries[index].source, 0xff, 0xff);
        g_state_03002810->entries[index].phase = 2;
        break;
    case 2:
        func_08040280(index);
        /* Read through the controls as the siblings read theirs: the ROM
         * forms their address, index * 0xCC + state + 0x9EC, and loads the
         * byte at +0x11 (0x08040486-0x0804048C). */
        func_08017AF4(g_state_03002810->entries[index].menu,
                      ((struct Controls08040388 *)g_state_03002810->entries[index].controls)->cursor,
                      11);
        g_state_03002810->entries[index].phase = 3;
        break;
    case 3:
        g_state_03002810->entries[index].phase = func_0803FC20(index, mask);
        break;
    case 4:
        func_08017E28(g_state_03002810->entries[index].record);
        g_state_03002810->entries[index].phase = 3;
        break;
    case 6:
        g_state_03002810->entries[index].selection = 0xff;
        func_08037FB0(index);
        g_state_03002810->entries[index].phase = 7;
        /* fall through: 0x08040514 runs into case 7 at 0x08040516 */
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
