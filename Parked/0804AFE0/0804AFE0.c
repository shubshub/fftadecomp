#include "ffta.h"

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeat;
} MenuInput;

typedef struct {
    u16 id;
    u16 kind;
    u8 unknown_04[4];
} MenuChoice;

typedef struct {
    u8 unknown_00[0x33];
    u8 stage;
    u8 kind;
    u8 unknown_35[9];
    u16 event;
    u16 value;
    u8 unknown_42[0x8A];
} MenuSlot;

typedef struct {
    u8 x;
    u8 y;
    u8 unknown_02[2];
} MenuPosition;

typedef union {
    MenuSlot slots[4];
    struct {
        u8 unknown_954[0x2B4];
        void *window;
        u8 unknown_C0C[0x2D0];
        MenuPosition positions[16];
        u8 count;
        u8 first;
        u8 unknown_F1E;
        u8 cursor;
        u8 marker;
        u8 flags;
    } tail;
} MenuRegion;

typedef struct {
    u8 unknown_00[0x9D];
    u8 timer;
    u16 delay;
    u8 unknown_A0[0x415];
    u8 savedDisplay;
    u8 unknown_4B6[2];
    u8 active[6];
    u8 requestFlags[6];
    u8 unknown_4C4[0x450];
    MenuChoice choices[8];
    MenuRegion region;
} MenuState;

typedef struct {
    u8 active;
    u8 unknown_01[4];
    u8 mode;
    u8 unknown_06[0x46];
} MenuUnit;

extern MenuState *g_state_03002810;
extern MenuInput data_03000000;
extern MenuUnit data_030009E0[];
extern u8 data_0201F536;
extern u8 data_0201F537;
extern u8 data_0201F538;
extern u8 data_0201F539;
extern u8 data_030027A4;
extern u8 data_03000990[];
extern u8 data_030008B0[];
extern u8 data_02003CB0[];
extern const u16 data_0852A212[];
extern void func_08035720(void);
extern void func_08031708(u32 display);
extern void func_08031714(void);
extern void func_0801174C(void *window, u32 layer, u32 page, void *a3, void *a4,
                         u32 a5, u32 a6, u32 a7, u32 a8, u32 a9);
extern u16 func_08011860(void);
extern void func_08013364(void);
extern u8 func_08013380(void);
extern void func_08141540(u32 sound);
extern u8 func_08038734(void);
extern void func_0804A6B0(u32 count, u32 mode);
extern void func_0808A604(u32 unit, u32 animation);
extern void func_0804ADC8(u32 mode, MenuPosition *positions, u32 a2, u32 a3);
extern void func_080359E4(u32 index, u32 mode);
extern void func_08019A8C(void *buffer, u16 text, void *a2, void *a3);
extern void func_08013428(s32 offset);
extern u16 func_08038524(u16 id, u16 value);
extern u16 func_0803865C(u16 id, u16 value);
extern void func_0804AD44(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5);
extern void func_0804AA20(u32 count);
extern void func_080CB27C(void *buffer);
extern void func_0803578C(void);

/* Complete target: [0x0804AFE0, 0x0804B7E6), 2054 bytes, 773 instructions. */
void func_0804AFE0(s32 index)
{
    switch (g_state_03002810->region.slots[index].stage)
    {
    case 0:
    case 1:
        func_08035720();
        func_08031708(0x46);
        g_state_03002810->requestFlags[index] = 0;
        func_0801174C(g_state_03002810->region.tail.window, 1, 7,
                     data_03000990, data_030008B0, 2, 2, 24, 4, 203);
        g_state_03002810->region.slots[index].stage = 2;
        break;
    case 2:
        func_08011860();
        if (data_03000000.pressed & 1)
        {
            func_08013364();
            data_0201F536 = 3;
            g_state_03002810->region.slots[index].stage = 7;
        }
        break;
    case 3:
    {
        s32 i;
        u8 *count;

        func_08031714();
        func_08141540(0x65);
        count = &data_0201F539;
        *count = func_08038734();
        func_0804A6B0(*count, 1);
        for (i = 0; i < *count + 1; i++)
        {
            g_state_03002810->region.tail.positions[i].x = 116;
            g_state_03002810->region.tail.positions[i].y = 69 + (i << 4);
        }
        g_state_03002810->region.tail.count = data_0201F539 + 1;
        g_state_03002810->region.tail.first = 0;
        g_state_03002810->region.tail.cursor = 0;
        g_state_03002810->region.tail.marker = 0xFF;
        g_state_03002810->region.tail.flags = 3;
        data_0201F537 = 5;
        data_030009E0[data_0201F537].mode = 2;
        func_0808A604(5, 11);
        data_0201F536 = 5;
        g_state_03002810->region.slots[index].stage = 10;
        break;
    }
    case 4:
    {
        u8 *count = &data_0201F539;
        *count = func_08038734();
        func_0804A6B0(*count, 2);
        func_0808A604(5, 2);
        g_state_03002810->region.slots[index].stage = 5;
        break;
    }
    case 5:
        func_08031714();
        g_state_03002810->region.tail.flags = 0x23;
        func_0804ADC8(5, g_state_03002810->region.tail.positions, 0, 1);
        if (data_03000000.held & 0xF0)
            break;
        if (data_03000000.pressed & 1)
        {
            func_08141540(0x64);
            if (g_state_03002810->region.tail.cursor == g_state_03002810->region.tail.count - 1)
            {
                func_0808A604(5, 5);
                g_state_03002810->region.slots[index].stage = 11;
            }
            else if (g_state_03002810->choices[g_state_03002810->region.tail.cursor].kind == 0)
            {
                g_state_03002810->region.slots[index + 1].kind = 0;
                func_080359E4(index + 1, 20);
                data_0201F536 = 6;
                g_state_03002810->region.slots[index].stage = 9;
            }
            else if (g_state_03002810->choices[g_state_03002810->region.tail.cursor].kind == 1)
            {
                g_state_03002810->region.slots[index + 1].kind = 1;
                func_080359E4(index + 1, 20);
                data_0201F536 = 6;
                g_state_03002810->region.slots[index].stage = 9;
            }
            else
            {
                g_state_03002810->region.slots[index + 1].kind = 2;
                func_080359E4(index + 1, 20);
                data_0201F536 = 6;
                g_state_03002810->region.slots[index].stage = 9;
            }
        }
        else if (data_03000000.pressed & 2)
            func_08141540(0x6A);
        else if (data_03000000.pressed & 4)
        {
            if (g_state_03002810->region.tail.cursor != g_state_03002810->region.tail.count - 1)
            {
                if (g_state_03002810->choices[g_state_03002810->region.tail.cursor].kind == 0)
                    break;
                if (g_state_03002810->choices[g_state_03002810->region.tail.cursor].kind == 1)
                {
                    u16 text;
                    g_state_03002810->savedDisplay = data_030027A4;
                    func_08031708(0x3F);
                    g_state_03002810->region.tail.flags |= 0x10;
                    text = g_state_03002810->choices[g_state_03002810->region.tail.cursor].id + 0x439;
                    func_08019A8C(data_02003CB0, text, data_03000990, data_030008B0);
                    func_08013428(-288);
                    g_state_03002810->region.slots[index].stage = 17;
                }
                else
                {
                    u16 id = g_state_03002810->choices[g_state_03002810->region.tail.cursor].id;
                    u16 text = data_0852A212[id];
                    g_state_03002810->savedDisplay = data_030027A4;
                    func_08031708(0x3F);
                    g_state_03002810->region.tail.flags |= 0x10;
                    func_08019A8C(data_02003CB0, text, data_03000990, data_030008B0);
                    func_08013428(-288);
                    g_state_03002810->region.slots[index].stage = 17;
                }
            }
        }
        break;
    case 6:
        if (g_state_03002810->region.slots[index + 1].event & 1)
        {
            func_08141540(0x64);
            if (g_state_03002810->region.slots[index + 1].kind == 1)
                g_state_03002810->choices[g_state_03002810->region.tail.cursor].id =
                    func_08038524(g_state_03002810->choices[g_state_03002810->region.tail.cursor].id,
                                 g_state_03002810->region.slots[index + 1].value);
            else if (g_state_03002810->region.slots[index + 1].kind == 2)
                g_state_03002810->choices[g_state_03002810->region.tail.cursor].id =
                    func_0803865C(g_state_03002810->choices[g_state_03002810->region.tail.cursor].id,
                                 g_state_03002810->region.slots[index + 1].value);
        }
        else
        {
            g_state_03002810->region.slots[index].stage = 5;
            break;
        }
        g_state_03002810->region.slots[index].stage = 4;
        break;
    case 17:
        if (func_08011860())
        {
            func_08031708(g_state_03002810->savedDisplay);
            g_state_03002810->delay = 10;
            data_0201F536 = 5;
            g_state_03002810->region.slots[index].stage = 18;
        }
        break;
    case 18:
        data_03000000.pressed = 0;
        data_03000000.held = 0;
        data_03000000.repeat = 0;
        if (g_state_03002810->delay)
            g_state_03002810->delay--;
        else
        {
            g_state_03002810->region.tail.flags &= 0xEF;
            g_state_03002810->region.slots[index].stage = data_0201F536;
        }
        break;
    case 9:
        if (g_state_03002810->region.slots[index + 1].stage == 0xFF)
            g_state_03002810->region.slots[index].stage = data_0201F536;
        g_state_03002810->region.tail.flags = 1;
        func_0804ADC8(0, g_state_03002810->region.tail.positions, 0, 0);
        break;
    case 7:
    {
        u8 *result = &data_0201F538;
        if ((*result = func_08011860()) != 0)
            g_state_03002810->region.slots[index].stage = data_0201F536;
        break;
    }
    case 10:
        if (data_030009E0[data_0201F537].active == 0)
            g_state_03002810->region.slots[index].stage = data_0201F536;
        break;
    case 11:
        func_08031708(0x40);
        g_state_03002810->requestFlags[index] = 0;
        func_0801174C(g_state_03002810->region.tail.window, 1, 8,
                     data_03000990, data_030008B0, 2, 1, 24, 4, 203);
        func_08013428(-288);
        func_0804AD44(27, 36, 67, 36, 0, 243);
        g_state_03002810->timer = 0;
        g_state_03002810->region.slots[index].stage = 14;
        break;
    case 14:
        func_08011860();
        if (g_state_03002810->timer++ > 2)
            g_state_03002810->region.slots[index].stage = 12;
        break;
    case 12:
    {
        func_08011860();
        func_0804AA20(data_0201F539);
        data_0201F537 = 5;
        data_030009E0[data_0201F537].mode = 2;
        func_0808A604(5, 11);
        g_state_03002810->region.slots[index].stage = 15;
        break;
    }
    case 15:
        if (func_08011860())
        {
                if (!func_08013380())
                data_0201F536 = 16;
            else
                data_0201F536 = 3;
            func_08013364();
            data_0201F537 = 5;
            data_030009E0[data_0201F537].mode = 1;
            func_0808A604(5, 5);
            g_state_03002810->region.slots[index].stage = 7;
        }
        break;
    case 16:
        func_08011860();
        if (data_030009E0[data_0201F537].active == 0)
        {
            func_080CB27C(data_02003CB0);
            g_state_03002810->region.slots[index].stage = 0xFF;
        }
        break;
    case 8:
        if (g_state_03002810->delay)
            g_state_03002810->delay--;
        else
            g_state_03002810->region.slots[index].stage = data_0201F536;
        break;
    case 0xFF:
        func_08031714();
        func_0803578C();
        g_state_03002810->active[index] = 0;
        break;
    }
}
